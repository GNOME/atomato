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
	public class MainWindow : Gtk.ApplicationWindow
	{
		Gtk.Paned main_container;
		LibraryList library_list;
		WorkflowEditor workflow_editor;

		public MainWindow (Atomato.Application app)
		{
			Object (application: app);

			main_container = new Gtk.Paned (Gtk.Orientation.HORIZONTAL);
			add (main_container);

			library_list = new LibraryList ();
			main_container.add1 (library_list);

			workflow_editor = new WorkflowEditor ();
			main_container.add2 (workflow_editor);

			main_container.show ();
			show ();
		}
	}
}
