/* GNOME Automation Engine
 * Copyright (C) 2006-2015 The GNOME Foundation
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
	public class Application : Gtk.Application
	{
		const OptionEntry[] option_entries = {
            { "version", 'v', 0, OptionArg.NONE, null, N_("Print version information and exit"), null },
            { null }
        };

        const GLib.ActionEntry[] action_entries = {
            { "quit", on_quit_activate }
        };

		protected override void activate ()
		{
            new MainWindow (this);
        }

		public static new Application get_default ()
		{
            return (Application) GLib.Application.get_default ();
        }

		protected override void startup ()
		{
			base.startup ();
		}

		protected override int handle_local_options (GLib.VariantDict options)
		{
            if (options.contains("version")) {
                print ("%s %s\n", Environment.get_application_name (), Config.VERSION);
                return 0;
            }

            return -1;
        }

		protected override void shutdown ()
		{
			base.shutdown ();
		}

		public Application ()
		{
            Object (application_id: "org.gnome.atomato", flags: ApplicationFlags.HANDLES_OPEN);

            add_main_option_entries (option_entries);
            add_action_entries (action_entries, this);
        }

		void on_quit_activate ()
		{
			quit ();
		}
	}

	public static int main (string[] args)
	{
		Intl.bindtextdomain (Config.GETTEXT_PACKAGE, Config.GNOMELOCALEDIR);
		Intl.bind_textdomain_codeset (Config.GETTEXT_PACKAGE, "UTF-8");
		Intl.textdomain (Config.GETTEXT_PACKAGE);

		var app = new Atomato.Application ();
		return app.run ();
	}
}
