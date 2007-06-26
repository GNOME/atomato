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
};

static GObjectClass *parent_class = NULL;

static AtomatoMethod
shell_action_provider_get_method (AtomatoActionProvider *provider)
{
	g_return_val_if_fail (SHELL_IS_ACTION_PROVIDER (provider), ATOMATO_METHOD_UNKNOWN);

	return ATOMATO_METHOD_SHELL;
}

static GValueArray *
shell_action_provider_run_action (AtomatoActionProvider *provider,
				  AtomatoAction *action,
				  const GValueArray *input_args)
{
	return NULL;
}

static void
shell_action_provider_interface_init (gpointer g_iface, gpointer iface_data)
{
	AtomatoActionProviderInterface *iface = (AtomatoActionProviderInterface *) g_iface;

	iface->get_method = shell_action_provider_get_method;
	iface->run_action = shell_action_provider_run_action;
}

static void
shell_action_provider_instance_init (GTypeInstance *instance, gpointer g_class)
{
	ShellActionProvider *provider = (ShellActionProvider *) instance;

	provider->priv = g_new0 (ShellActionProviderPrivate, 1);
}

static void
shell_action_provider_finalize (GObject *object)
{
	ShellActionProvider *provider = (ShellActionProvider *) object;

	if (provider->priv) {

		g_free (provider->priv);
		provider->priv = NULL;
	}

	parent_class->finalize (object);
}

static void
shell_action_provider_class_init (ShellActionProviderClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS (klass);

	parent_class = g_type_class_ref (G_TYPE_OBJECT);

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
