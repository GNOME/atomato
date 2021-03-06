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

#include <libatomato/atomato.h>

int
main (int argc, char **argv)
{
	GSList *names;

	g_type_init ();

	names = atomato_list_actions ();
	while (names != NULL) {
		AtomatoAction *action = names->data;
		g_printf ("Action: %s.%s: %s\n",
			  atomato_action_get_section (action),
			  atomato_action_get_name (action),
			  atomato_action_get_description (action));
		names = names->next;
	}

	return 0;
}
