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

#include <libxml/parser.h>
#include "atomato.h"

static AtomatoAction *
read_action_from_xml_node (xmlNodePtr node)
{
	AtomatoAction *action = NULL;
	gchar *str;

	if (!node->name || strcmp (node->name, "action")) {
		g_warning ("Invalid action node");
		return NULL;
	}

	action = g_new0 (AtomatoAction, 1);
	action->section = (gchar *) xmlGetProp (node, "section");
	action->name = (gchar *) xmlGetProp (node, "name");

	str = (gchar *) xmlGetProp (node, "method");
	if (!strcmp (str, "shell"))
		action->method = ATOMATO_METHOD_SHELL;
	else if (!strcmp (str, "dbus"))
		action->method = ATOMATO_METHOD_DBUS;
	else {
		atomato_action_free (action);
		return NULL;
	}

	action->command = (gchar *) xmlGetProp (node, "command");

	return action;
}

/**
 * atomatio_read_action_file:
 * @filename: Full path of the file to parse.
 *
 * Read a .atomato file and converts it to a list of AtomatoAction objects.
 *
 * Return value: A list containing all actions in the file.
 */
GSList *
atomato_read_action_file (const gchar *filename)
{
	GSList *list = NULL;
	xmlDocPtr doc;
	xmlNodePtr root, current_node;

	doc = xmlParseFile (filename);
	if (!doc) {
		g_warning ("Could not read %s file", filename);
		return NULL;
	}

	root = xmlDocGetRootElement (doc);
	if (!root) {
		g_warning ("Cannot get root element for %s", filename);
		xmlFreeDoc (doc);
		return NULL;
	}

	if (!root->name || strcmp ((const char *) root->name, "atomato")) {
		g_warning (" %s is not a valid Atomato XML file", filename);
		xmlFreeDoc (doc);
		return NULL;
	}

	/* now read the actions */
	for (current_node = root->xmlChildrenNode;
	     current_node != NULL;
	     current_node = current_node->next) {
		AtomatoAction *action;

		action = read_action_from_xml_node (current_node);
		if (action)
			list = g_slist_append (list, action);
	}

	return list;
}

void
atomato_action_argument_free (AtomatoActionArgument *argument)
{
	g_return_if_fail (argument != NULL);

	g_free (argument->name);
	g_free (argument);
}

/**
 * atomato_action_free:
 */
void
atomato_action_free (AtomatoAction *action)
{
	g_return_if_fail (action != NULL);

	g_free (action->section);
	g_free (action->name);

	while (action->args != NULL) {
		atomato_action_argument_free ((AtomatoActionArgument *) action->args->data);

		action->args = g_slist_remove (action->args, action->args);
	}

	g_free (action);
}
