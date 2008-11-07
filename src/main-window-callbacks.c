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

#include <gtk/gtkmenu.h>
#include <gtk/gtkstock.h>
#include <gtk/gtktreeview.h>
#include "atomato-gui.h"

gboolean
actions_list_button_release_cb (GtkWidget *widget, GdkEventButton *event, gpointer user_data)
{
	gboolean has_selection;
	GtkWidget *menu, *menu_item;
	MainWindow *main_window = (MainWindow *) user_data;

	if (event->button != 3)
		return FALSE;

	has_selection = gtk_tree_selection_count_selected_rows (
		gtk_tree_view_get_selection (GTK_TREE_VIEW (main_window->actions_list))) > 0 ? TRUE : FALSE;

	/* create the menu */
	menu = gtk_menu_new ();

	menu_item = gtk_image_menu_item_new_from_stock (GTK_STOCK_PROPERTIES, NULL);
	gtk_widget_set_sensitive (menu_item, has_selection);
	gtk_widget_show (menu_item);
	gtk_menu_append (GTK_MENU (menu), menu_item);

	/* popup the menu */
	gtk_menu_popup (GTK_MENU (menu), NULL, NULL, NULL, main_window, event->button, event->time);

	return TRUE;
}
