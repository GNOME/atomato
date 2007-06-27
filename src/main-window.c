/* GNOME Automator
 * Copyright (C) 2006 The GNOME Foundation
 *
 * Authors:
 *	 Rodrigo Moya (rodrigo@gnome-db.org)
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

#include <stdlib.h>
#include <glib/gi18n.h>
#include <gtk/gtkcellrenderertext.h>
#include <gtk/gtkmain.h>
#include <gtk/gtktreeview.h>
#include "atomato-gui.h"

static GObjectClass *parent_class = NULL;

static void
main_window_class_init (MainWindowClass *klass)
{
	parent_class = g_type_class_peek_parent (klass);
}

static void
main_window_init (MainWindow *window)
{
	GtkCellRenderer *renderer;

	/* Load GUI */
	window->xml = glade_xml_new (ATOMATO_GLADE_DIR "/atomato-gui.glade", "main_window", NULL);
	if (!window->xml) {
		gui_show_error (_("Could not load atomato-gui.glade file"));
		exit (-1);
	}

	/* ... main window ... */
	window->main_window = glade_xml_get_widget (window->xml, "main_window");
	gtk_window_set_default_size (GTK_WINDOW (window->main_window), 650, 400);
	g_signal_connect (G_OBJECT (window->main_window), "destroy",
			  gtk_main_quit, NULL);

	/* ... actions list ... */
	window->actions_model = gtk_tree_store_new (1, G_TYPE_STRING);
	
	window->actions_list = glade_xml_get_widget (window->xml, "actions_list");
	gtk_tree_view_set_model (GTK_TREE_VIEW (window->actions_list), window->actions_model);

	renderer = gtk_cell_renderer_text_new ();
	g_object_set (renderer, "xalign", 0.0, NULL);
	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (window->actions_list), -1,
						     "Library",
						     renderer,
						     "text", 0,
						     NULL);
}

GType
main_window_get_type (void)
{
        static GType module_type = 0;

        if (!module_type) {
                static const GTypeInfo module_info = {
                        sizeof (MainWindowClass),
                        NULL,           /* base_init */
                        NULL,           /* base_finalize */
                        (GClassInitFunc) main_window_class_init,
                        NULL,           /* class_finalize */
                        NULL,           /* class_data */
                        sizeof (MainWindow),
                        0,              /* n_preallocs */
                        (GInstanceInitFunc) main_window_init,
                };

                module_type = g_type_register_static (G_TYPE_OBJECT,
                                                      "MainWindow",
                                                      &module_info, 0);
        }

        return module_type;
}

MainWindow *
main_window_new (void)
{
	MainWindow *window;

	window = g_object_new (main_window_get_type (), NULL);

	return window;
}
