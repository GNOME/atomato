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

#include "shell-action-provider.h"

struct _ShellActionProviderPrivate {
	GHashTable *actions;
};

static GObjectClass *action_parent_class = NULL;
static GObjectClass *provider_parent_class = NULL;

/*
 * ShellAction class implementation
 */

typedef struct {
	GObject parent;

	gchar *script_file;
	gchar *name;
	gchar *section;
	gchar *description;
} ShellAction;

typedef struct {
	GObjectClass parent_class;
} ShellActionClass;

static const gchar *
shell_action_get_name (AtomatoAction *action)
{
	ShellAction *shell_action = (ShellAction *) action;

	return (const gchar *) shell_action->name;
}

static const gchar *
shell_action_get_section (AtomatoAction *action)
{
	ShellAction *shell_action = (ShellAction *) action;

	return (const gchar *) shell_action->section;
}

static const gchar *
shell_action_get_description (AtomatoAction *action)
{
	ShellAction *shell_action = (ShellAction *) action;

	return (const gchar *) shell_action->description;
}

static GValue *
shell_action_run (AtomatoAction *action, GValueArray *arguments)
{
}

static void
shell_action_interface_init (gpointer g_iface, gpointer iface_data)
{
	AtomatoActionInterface *iface = (AtomatoActionInterface *) g_iface;

	iface->get_name = shell_action_get_name;
	iface->get_section = shell_action_get_section;
	iface->get_description = shell_action_get_description;
	iface->run = shell_action_run;
}

static void
shell_action_instance_init (GTypeInstance *instance, gpointer g_class)
{
	ShellAction *shell_action = (ShellAction *) instance;
}

static void
shell_action_finalize (GObject *object)
{
	ShellAction *shell_action = (ShellAction *) object;

	if (shell_action->script_file) {
		g_free (shell_action->script_file);
		shell_action->script_file = NULL;
	}

	if (shell_action->name) {
		g_free (shell_action->name);
		shell_action->name = NULL;
	}

	if (shell_action->section) {
		g_free (shell_action->section);
		shell_action->section = NULL;
	}

	if (shell_action->description) {
		g_free (shell_action->description);
		shell_action->description = NULL;
	}

	action_parent_class->finalize (object);
}

static void
shell_action_class_init (ShellActionClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS (klass);

	action_parent_class = g_type_class_ref (G_TYPE_OBJECT);

	object_class->finalize = shell_action_finalize;
}

GType 
shell_action_get_type (void)
{
	static GType type = 0;

	if (type == 0) {
		static const GTypeInfo info = {
			sizeof (ShellActionClass),
			NULL,   /* base_init */
			NULL,   /* base_finalize */
		        shell_action_class_init,   /* class_init */
			NULL,   /* class_finalize */
			NULL,   /* class_data */
			sizeof (ShellAction),
			0,      /* n_preallocs */
			shell_action_instance_init    /* instance_init */
		};
		static const GInterfaceInfo iap_info = {
			(GInterfaceInitFunc) shell_action_interface_init,    /* interface_init */
			NULL,               /* interface_finalize */
			NULL                /* interface_data */
		};

		type = g_type_register_static (G_TYPE_OBJECT, "ShellAction", &info, 0);
		g_type_add_interface_static (type, ATOMATO_TYPE_ACTION, &iap_info);
	}

	return type;
}

static AtomatoAction *
shell_action_new (const gchar *script_file)
{
	AtomatoAction *action;
	ShellAction *shell_action;
	gchar **a;

	if (!script_file) {
		g_warning ("%s: 'script_file' is NULL", __FUNCTION__);
		return NULL;
	}

	action = shell_action = g_object_new (shell_action_get_type (), NULL);
	shell_action->script_file = g_strdup (script_file);
	shell_action->name = g_path_get_basename (shell_action->script_file);

	a = g_strsplit (shell_action->name, ".", 0);
	if (a && a[0])
		shell_action->section = g_strdup (a[0]);

	g_strfreev (a);

	return action;
}

/*
 * ShellActionProvider class implementation
 */

static GSList *
shell_action_provider_get_actions (AtomatoActionProvider *provider)
{
	GSList *list = NULL;
	ShellActionProvider *shell_provider = (ShellActionProvider *) provider;

	if (!shell_provider->priv->actions) {
		GDir *dir;
		GError *error = NULL;

		shell_provider->priv->actions =
			g_hash_table_new_full (g_str_hash, g_str_equal, g_free, g_object_unref);

		/* Load all scripts in ATOMATO_ACTIONS_DIR */
		dir = g_dir_open (ATOMATO_ACTIONS_DIR "/shell", 0, &error);
		if (dir) {
			gchar *file;

			while ((file = g_dir_read_name (dir))) {
				gchar *full_path;

				full_path = g_strdup_printf ("%s/shell/%s",
							     ATOMATO_ACTIONS_DIR,
							     file);

				list = g_slist_append (list, shell_action_new (full_path));
				g_free (full_path);
			}

			g_dir_close (dir);
		} else {
			g_warning ("%s: %s", __FUNCTION__, error->message);
			g_error_free (error);
		}
	}

	return list;
}

static void
shell_action_provider_interface_init (gpointer g_iface, gpointer iface_data)
{
	AtomatoActionProviderInterface *iface = (AtomatoActionProviderInterface *) g_iface;

	iface->get_actions = shell_action_provider_get_actions;
}

static void
shell_action_provider_instance_init (GTypeInstance *instance, gpointer g_class)
{
	ShellActionProvider *shell_provider = (ShellActionProvider *) instance;

	shell_provider->priv = g_new0 (ShellActionProviderPrivate, 1);
}

static void
shell_action_provider_finalize (GObject *object)
{
	ShellActionProvider *provider = (ShellActionProvider *) object;

	if (provider->priv) {
		if (provider->priv->actions) {
			g_hash_table_destroy (provider->priv->actions);
			provider->priv->actions = NULL;
		}

		g_free (provider->priv);
		provider->priv = NULL;
	}

	provider_parent_class->finalize (object);
}

static void
shell_action_provider_class_init (ShellActionProviderClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS (klass);

	provider_parent_class = g_type_class_ref (G_TYPE_OBJECT);

	object_class->finalize = shell_action_provider_finalize;
}

GType 
shell_action_provider_get_type (void)
{
	static GType type = 0;

	if (type == 0) {
		static const GTypeInfo info = {
			sizeof (ShellActionProviderClass),
			NULL,   /* base_init */
			NULL,   /* base_finalize */
		        shell_action_provider_class_init,   /* class_init */
			NULL,   /* class_finalize */
			NULL,   /* class_data */
			sizeof (ShellActionProvider),
			0,      /* n_preallocs */
			shell_action_provider_instance_init    /* instance_init */
		};
		static const GInterfaceInfo iap_info = {
			(GInterfaceInitFunc) shell_action_provider_interface_init,    /* interface_init */
			NULL,               /* interface_finalize */
			NULL                /* interface_data */
		};

		type = g_type_register_static (G_TYPE_OBJECT, "ShellActionProvider", &info, 0);
		g_type_add_interface_static (type, ATOMATO_TYPE_ACTION_PROVIDER, &iap_info);
	}

	return type;
}
