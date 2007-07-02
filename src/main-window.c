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

/* Callbacks: in main-window-callbacks.c */
gboolean actions_list_button_release_cb (GtkWidget *widget, GdkEventButton *event, gpointer user_data);

static GObjectClass *parent_class = NULL;

static void
main_window_class_init (MainWindowClass *klass)
{
	parent_class = g_type_class_peek_parent (klass);
}

static void
populate_actions_model (MainWindow *window)
{
	GSList *list, *sl;

	list = atomato_list_actions ();
	for (sl = list; sl != NULL; sl = sl->next) {
		GtkTreeIter iter, section_iter;
		GtkTreePath *section_path;
		AtomatoAction *action = sl->data;

		/* 1st add the section parent node if not present yet */
		section_path = g_hash_table_lookup (window->sections, action->section);
		if (section_path) {
			gtk_tree_model_get_iter (GTK_TREE_MODEL (window->actions_model),
						 &section_iter,
						 section_path);
		} else {
			gchar *section_name;

			gtk_tree_store_append (window->actions_model, &section_iter, NULL);
			gtk_tree_store_set (window->actions_model, &section_iter, 0, action->section, -1);

			section_name = g_strdup (action->section);
			section_path = gtk_tree_model_get_path (GTK_TREE_MODEL (window->actions_model),
								&section_iter);
			g_hash_table_insert (window->sections, section_name, section_path);
		}

		/* now add the action to the tree */
		gtk_tree_store_append (window->actions_model, &iter, &section_iter);
		gtk_tree_store_set (window->actions_model, &iter, 0, action->description, -1);
		/* FIXME: associate AtomatoAction with added row */
	}

	g_slist_free (list);
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
	window->sections = g_hash_table_new_full (g_str_hash, g_str_equal, g_free, gtk_tree_path_free);
	populate_actions_model (window);
	
	window->actions_list = glade_xml_get_widget (window->xml, "actions_list");
	g_signal_connect (G_OBJECT (window->actions_list), "button_release_event",
			  G_CALLBACK (actions_list_button_release_cb), window);
	gtk_tree_view_set_model (GTK_TREE_VIEW (window->actions_list),
				 GTK_TREE_MODEL (window->actions_model));

	renderer = gtk_cell_renderer_text_new ();
	g_object_set (renderer, "xalign", 0.0, NULL);
	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (window->actions_list), -1,
						     "Library",
						     renderer,
						     "text", 0,
						     NULL);

	/* script vertical box */
	window->script_vbox = glade_xml_get_widget (window->xml, "script_vbox");
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
