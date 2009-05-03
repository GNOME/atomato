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

#include <stdlib.h>
#include "atomato-action.h"

static void
atomato_action_base_init (gpointer g_class)
{
	static gboolean initialized = FALSE;

	if (!initialized) {
		/* Create signals for the interface */
		initialized = TRUE;
	}
}

GType
atomato_action_get_type (void)
{
	static GType type = 0;

	if (type == 0) {
		static const GTypeInfo info = {
			sizeof (AtomatoActionInterface),
			atomato_action_base_init,   /* base_init */
			NULL,   /* base_finalize */
			NULL,   /* class_init */
			NULL,   /* class_finalize */
			NULL,   /* class_data */
			0,
			0,      /* n_preallocs */
			NULL    /* instance_init */
		};
		type = g_type_register_static (G_TYPE_INTERFACE, "AtomatoAction", &info, 0);
	}

	return type;
}

/**
 * atomato_action_get_name:
 */
const gchar *
atomato_action_get_name (AtomatoAction *action)
{
	return ATOMATO_ACTION_GET_INTERFACE (action)->get_name (action);
}

/**
 * atomato_action_get_section:
 */
const gchar *
atomato_action_get_section (AtomatoAction *action)
{
	return ATOMATO_ACTION_GET_INTERFACE (action)->get_section (action);
}

/**
 * atomato_action_get_description:
 */
const gchar *
atomato_action_get_description (AtomatoAction *action)
{
	return ATOMATO_ACTION_GET_INTERFACE (action)->get_description (action);
}

/**
 * atomato_action_run:
 */
GValue *
atomato_action_run (AtomatoAction *action, GValueArray *arguments)
{
	return ATOMATO_ACTION_GET_INTERFACE (action)->run (action, arguments);
}

/**
 * atomato_action_free_argument:
 */
void
atomato_action_free_argument (AtomatoActionArgument *argument)
{
	g_return_if_fail (argument != NULL);

	g_free (argument->name);
	g_free (argument->description);

	g_free (argument);
}
