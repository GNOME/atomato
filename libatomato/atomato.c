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

static GSList *action_providers = NULL;
static gboolean initialized = FALSE;

static void
add_action_provider (AtomatoActionProvider *provider)
{
	action_providers = g_slist_append (action_providers, provider);
}

static void
initialize (void)
{
	if (initialized)
		return;

	/* initialize action providers */
	action_providers = g_slist_append (action_providers,
					   g_object_new (SHELL_TYPE_ACTION_PROVIDER, NULL));
	action_providers = g_slist_append (action_providers,
					   g_object_new (DBUS_TYPE_ACTION_PROVIDER, NULL));

	initialized = TRUE;
}

/**
 * atomato_list_actions:
 *
 */
GSList *
atomato_list_actions (void)
{
	GSList *list = NULL, *l;

	initialize ();

	for (l = action_providers; l != NULL; l = l->next) {
		GSList *provider_list;

		provider_list = atomato_action_provider_get_actions (
			ATOMATO_ACTION_PROVIDER (l->data));

		list = g_slist_concat (list, provider_list);
	}

	return list;
}

/**
 * atomato_free_actions_list:
 * @list: List of actions as returned by #atomato_list_actions.
 *
 * Frees the memory associated with an actions list.
 */
void
atomato_free_actions_list (GSList *list)
{
	while (list) {
		g_object_unref (G_OBJECT (list->data));
		list = g_slist_remove (list, list->data);
	}
}
