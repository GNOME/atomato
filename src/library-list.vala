/* GNOME Automation Engine
 * Copyright (C) 2006-2016 The GNOME Foundation
 *
 * Authors:
 *	 Rodrigo Moya (rodrigo@gnome.org)
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this Library; see the file COPYING.  If not,
 * write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

using Gtk;

namespace Atomato
{
	public class LibraryList : Gtk.Box
	{
		Gtk.TreeView library_list;
		Gtk.TreeView action_list;

		public LibraryList ()
		{
			Object (orientation: Gtk.Orientation.HORIZONTAL);

			library_list = new Gtk.TreeView ();
			library_list.insert_column_with_attributes (-1, "Library", new Gtk.CellRendererText (), "text", 0);
			library_list.show ();
			pack_start (library_list);

			action_list = new Gtk.TreeView ();
			action_list.insert_column_with_attributes (-1, "Action", new Gtk.CellRendererText (), "text", 0);
			action_list.show ();
			pack_start (action_list);

			show ();
		}
	}
}
