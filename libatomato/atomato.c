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

static GSList *action_providers = NULL;

static void
initialize (void)
{
	if (action_providers != NULL)
		return;

	action_providers = g_slist_append (action_providers, g_object_new (DBUS_TYPE_ACTION_PROVIDER, NULL));
}

/**
 * gnome_automator_list_actions:
 *
 */
GSList *
atomato_list_actions (void)
{
	GSList *sl, *all_names = NULL;

	initialize ();

	for (sl = action_providers; sl != NULL; sl = sl->next) {
		GSList *names;

		names = atomato_action_provider_list_actions (ATOMATO_ACTION_PROVIDER (sl->data));
		if (names)
			all_names = g_slist_concat (all_names, names);
	}

	return all_names;
}
