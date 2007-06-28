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

#include <string.h>
#include <libxml/tree.h>
#include <dbus/dbus-glib.h>
#include <atomato.h>
#include "dbus-action-provider.h"

struct _DbusActionProviderPrivate {
	//DBusGConnection *system_connection;
	DBusGConnection *session_connection;
	//DBusGProxy *system_proxy;
	DBusGProxy *session_proxy;

	GHashTable *names;
};

static GObjectClass *parent_class = NULL;

static void
parse_xml_interface (DbusActionProvider *dbus_provider, xmlNodePtr xml_node)
{
	xmlNodePtr subnode, arg_node;

	for (subnode = xml_node->xmlChildrenNode; subnode != NULL; subnode = subnode->next) {
		AtomatoAction *action;

		if (strcmp ((char *) subnode->name, "method"))
			continue;

		action = g_new0 (AtomatoAction, 1);
		action->name = g_strdup (xmlGetProp (subnode, "name"));

		for (arg_node = subnode->xmlChildrenNode; arg_node != NULL;
		     arg_node = arg_node->next) {
			AtomatoActionArgument *argument;

			if (strcmp ((char *) arg_node->name, "arg"))
				continue;

			argument = g_new0 (AtomatoActionArgument, 1);
			argument->name = g_strdup (xmlGetProp (arg_node, "name"));
			//argument->direction = g_strdup (xmlGetProp (arg_node, "direction"));
			//argument->type = g_strdup (xmlGetProp (arg_node, "type"));

			action->args = g_list_append (action->args, argument);
		}

		g_hash_table_insert (dbus_provider->priv->names, action->name, action);
	}
}

static void
parse_xml_document (DbusActionProvider *dbus_provider, char *data)
{
	xmlDocPtr xml_doc;

	xml_doc = xmlParseMemory (data, strlen (data));
	if (xml_doc) {
		xmlNodePtr xml_root, xml_node;

		xml_root = xmlDocGetRootElement (xml_doc);
		if (!strcmp ((char *) xml_root->name, "node")) {
			for (xml_node = xml_root->xmlChildrenNode; xml_node != NULL; xml_node = xml_node->next) {
				if (strcmp ((char *) xml_node->name, "interface"))
					continue;
				parse_xml_interface (dbus_provider, xml_node);
			}
		} else
			g_warning ("Invalid XML returned from Introspect\n");

		xmlFreeDoc (xml_doc);
	} else
		g_warning ("Could not parse XML from Introspect call\n");
}

static void
list_dbus_names (DbusActionProvider *dbus_provider, DBusGProxy *proxy, DBusGConnection *connection)
{
	GError *error = NULL;
	gchar **name_list, **name_list_ptr;

	if (dbus_g_proxy_call (proxy, "ListNames", &error, G_TYPE_INVALID,
			       G_TYPE_STRV, &name_list, G_TYPE_INVALID)) {
		for (name_list_ptr = name_list; *name_list_ptr; name_list_ptr++) {
			DBusGProxy *proxy_tmp;
			gchar *data;

			error = NULL;
			proxy_tmp = dbus_g_proxy_new_for_name_owner (connection, *name_list_ptr,
								     "/", DBUS_INTERFACE_INTROSPECTABLE,
								     &error);
			if (!proxy_tmp) {
				g_warning ("Could not create proxy for Introspection\n");
				g_object_unref (proxy_tmp);
				continue;
			}

			error = NULL;
			if (dbus_g_proxy_call (proxy_tmp, "Introspect", &error,
					       G_TYPE_INVALID,
					       G_TYPE_STRING, &data,
					       G_TYPE_INVALID)) {
				parse_xml_document (dbus_provider, data);
				g_free (data);
			} else {
				if (error) {
					g_warning ("DBus error: %s\n", error->message);
					g_error_free (error);
				} else
					g_warning ("DBus proxy call failed\n");
			}

			g_object_unref (proxy_tmp);
		}

		g_strfreev (name_list);
	} else {
		if (error) {
			g_warning ("DBus error: %s\n", error->message);
			g_error_free (error);
		} else
			g_warning ("DBus proxy call failed\n");
	}
}

static void
hash_to_slist (gpointer key, gpointer value, gpointer user_data)
{
	GSList **list = (GSList **) user_data;

	*list = g_slist_append (*list, value);
}

static AtomatoMethod
dbus_action_provider_get_method (AtomatoActionProvider *provider)
{
	g_return_val_if_fail (DBUS_IS_ACTION_PROVIDER (provider), ATOMATO_METHOD_UNKNOWN);

	return ATOMATO_METHOD_DBUS;
}

static GValueArray *
dbus_action_provider_run_action (AtomatoActionProvider *provider,
				 AtomatoAction *action,
				 const GValueArray *input_args)
{
	return NULL;
}

static void
dbus_action_provider_interface_init (gpointer g_iface, gpointer iface_data)
{
	AtomatoActionProviderInterface *iface = (AtomatoActionProviderInterface *) g_iface;

	iface->get_method = dbus_action_provider_get_method;
	iface->run_action = dbus_action_provider_run_action;
}

static DBusGProxy *
set_proxy (DBusGConnection *connection)
{
	DBusGProxy *proxy;

	proxy = dbus_g_proxy_new_for_name (connection,
					   DBUS_SERVICE_DBUS,
					   DBUS_PATH_DBUS,
					   DBUS_INTERFACE_DBUS);
	if (!proxy) {
		g_warning ("Could not get proxy for DBus connection\n");
		return NULL;
	}

	return proxy;
}

static void
dbus_action_provider_instance_init (GTypeInstance *instance, gpointer g_class)
{
	DbusActionProvider *provider = (DbusActionProvider *) instance;
	GError *error;

	provider->priv = g_new0 (DbusActionProviderPrivate, 1);

	/* get DBus connections */
	/* error = NULL; */
/* 	if (!(provider->priv->system_connection = dbus_g_bus_get (DBUS_BUS_SYSTEM, &error))) { */
/* 		g_warning ("Could not get the system bus: %s. Not using system services\n", error->message); */
/* 		g_error_free (error); */
/* 	} else { */
/* 		provider->priv->system_proxy = set_proxy (provider->priv->system_connection); */
/* 	} */

	error = NULL;
	if (!(provider->priv->session_connection = dbus_g_bus_get (DBUS_BUS_SESSION, &error))) {
		g_warning ("Could not get the session bus: %s. Not using session services\n", error->message);
		g_error_free (error);
	} else {
		provider->priv->session_proxy = set_proxy (provider->priv->session_connection);
	}
}

static void
dbus_action_provider_finalize (GObject *object)
{
	DbusActionProvider *provider = (DbusActionProvider *) object;

	if (provider->priv) {
		if (provider->priv->names != NULL) {
			g_hash_table_destroy (provider->priv->names);
			provider->priv->names = NULL;
		}

		g_free (provider->priv);
		provider->priv = NULL;
	}

	parent_class->finalize (object);
}

static void
dbus_action_provider_class_init (DbusActionProviderClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS (klass);

	parent_class = g_type_class_ref (G_TYPE_OBJECT);

	object_class->finalize = dbus_action_provider_finalize;
}

GType 
dbus_action_provider_get_type (void)
{
	static GType type = 0;

	if (type == 0) {
		static const GTypeInfo info = {
			sizeof (DbusActionProviderClass),
			NULL,   /* base_init */
			NULL,   /* base_finalize */
		        dbus_action_provider_class_init,   /* class_init */
			NULL,   /* class_finalize */
			NULL,   /* class_data */
			sizeof (DbusActionProvider),
			0,      /* n_preallocs */
			dbus_action_provider_instance_init    /* instance_init */
		};
		static const GInterfaceInfo iap_info = {
			(GInterfaceInitFunc) dbus_action_provider_interface_init,    /* interface_init */
			NULL,               /* interface_finalize */
			NULL                /* interface_data */
		};

		type = g_type_register_static (G_TYPE_OBJECT, "DbusActionProvider", &info, 0);
		g_type_add_interface_static (type, ATOMATO_TYPE_ACTION_PROVIDER, &iap_info);
	}

	return type;
}
