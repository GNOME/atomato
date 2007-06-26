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

#include "atomato-action-provider.h"

static void
atomato_action_provider_base_init (gpointer g_class)
{
	static gboolean initialized = FALSE;

	if (!initialized) {
		/* Create signals for the interface */
		initialized = TRUE;
	}
}

GType
atomato_action_provider_get_type (void)
{
	static GType type = 0;

	if (type == 0) {
		static const GTypeInfo info = {
			sizeof (AtomatoActionProviderInterface),
			atomato_action_provider_base_init,   /* base_init */
			NULL,   /* base_finalize */
			NULL,   /* class_init */
			NULL,   /* class_finalize */
			NULL,   /* class_data */
			0,
			0,      /* n_preallocs */
			NULL    /* instance_init */
		};
		type = g_type_register_static (G_TYPE_INTERFACE, "AtomatoActionProvider", &info, 0);
	}

	return type;
}

/**
 * atomato_action_provider_get_method:
 * @provider: An action provider.
 *
 * Returns the method implemented by the action provider to make calls to
 * actions.
 *
 * Return value: The method implemented by the action provider.
 */
AtomatoMethod
atomato_action_provider_get_method (AtomatoActionProvider *provider)
{
	return ATOMATO_ACTION_PROVIDER_GET_INTERFACE (provider)->get_method (provider);
}

/**
 * atomato_action_provider_run_action:
 * @provider: An action provider.
 * @action_name: The name of the action to be executed.
 * @input_args: Input arguments.
 *
 * Runs a specific action through the selected action provider implementation.
 *
 * Return value: An array with all output values returned from the action.
 */
GValueArray *
atomato_action_provider_run_action (AtomatoActionProvider *provider,
				    AtomatoAction *action,
				    const GValueArray *input_args)
{
	return ATOMATO_ACTION_PROVIDER_GET_INTERFACE (provider)->run_action (provider, action, input_args);
}
