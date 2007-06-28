/* GNOME Automation Library
 * Copyright (C) 2006 The GNOME Foundation
 *
 * Authors:
 *	 Rodrigo Moya (rodrigo@gnome-db.org)
 *
 * This Library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This Library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this Library; see the file COPYING.LIB.  If not,
 * write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include "atomato.h"
#include "dbus-action-provider.h"
#include "shell-action-provider.h"

static GHashTable *action_providers = NULL;
static GHashTable *actions = NULL;
static gboolean initialized = FALSE;

static void
add_action_provider (AtomatoActionProvider *provider)
{
	AtomatoMethod method, *ptr_method;

	method = atomato_action_provider_get_method (provider);
	if (g_hash_table_lookup (action_providers, &method)) {
		g_warning ("2 providers for the same method!!!!");
		return;
	}

	ptr_method = g_new (AtomatoMethod, 1);
	*ptr_method = method;

	g_hash_table_insert (action_providers, ptr_method, provider);
}

static void
read_actions_from_dir (const gchar *path)
{
	GDir *dir;
	const gchar *file;

	dir = g_dir_open (path, 0, NULL);
	if (!dir)
		return;

	while ((file = g_dir_read_name (dir))) {
		gchar *action_file;
		GSList *list;

		if (!g_str_has_suffix (file, ".atomato"))
			continue;

		action_file = g_build_filename (path, file, NULL);
		list = atomato_read_action_file (action_file);
		g_free (action_file);
		while (list != NULL) {
			AtomatoAction *action;
			gchar *full_name;

			action = list->data;

			if (!actions) {
				actions = g_hash_table_new_full (g_str_hash, g_str_equal,
								 g_free, atomato_action_free);
			}

			full_name = g_strdup_printf ("%s.%s", action->section, action->name);
			if (g_hash_table_lookup (actions, full_name)) {
				g_warning ("2 actions with the same name!!!");
				g_free (full_name);
			} else
				g_hash_table_insert (actions, full_name, action);

			list = g_slist_remove (list, list->data);
		}
	}

	g_dir_close (dir);
}

static void
read_action_dirs (void)
{
	gint i;
	gchar *path;
	const gchar* const * system_dirs;

	system_dirs = g_get_system_data_dirs ();
	for (i = 0; system_dirs[i] != NULL; i++) {
		path = g_build_filename (system_dirs[i], "atomato", "actions", NULL);
		read_actions_from_dir ((const gchar *) path);
		g_free (path);
	}
}

static void
initialize (void)
{
	if (initialized)
		return;

	/* get all available actions */
	read_action_dirs ();

	/* initialize action providers */
	action_providers = g_hash_table_new_full (g_int_hash, g_int_equal, g_free, g_object_unref);
	add_action_provider (ATOMATO_ACTION_PROVIDER (g_object_new (SHELL_TYPE_ACTION_PROVIDER, NULL)));
	add_action_provider (ATOMATO_ACTION_PROVIDER (g_object_new (DBUS_TYPE_ACTION_PROVIDER, NULL)));

	initialized = TRUE;
}

static void
add_provider_method_hash_cb (gpointer key, gpointer value, gpointer user_data)
{
	AtomatoMethod *method = key;
	GSList **list = user_data;

	*list = g_slist_append (*list, GINT_TO_POINTER (*method));
}

/**
 * atomato_list_methods:
 */
GSList *
atomato_list_methods (void)
{
	GSList *list = NULL;

	initialize ();

	g_hash_table_foreach (action_providers, (GHFunc) add_provider_method_hash_cb, &list);

	return list;
}

static void
add_action_hash_cb (gpointer key, gpointer value, gpointer user_data)
{
	AtomatoAction *action = value;
	GSList **list = user_data;

	*list = g_slist_append (*list, action);
}

/**
 * atomato_list_actions:
 *
 */
GSList *
atomato_list_actions (void)
{
	GSList *list = NULL;

	initialize ();

	g_hash_table_foreach (actions, (GHFunc) add_action_hash_cb, &list);

	return list;
}
