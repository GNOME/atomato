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

#ifndef __ATOMATO_GUI_H__
#define __ATOMATO_GUI_H__

#include <gtk/gtktreestore.h>
#include <glade/glade-xml.h>

/*
 * Common GUI operations
 */

void gui_show_error (const gchar *format, ...);

/*
 * Main window operations
 */

typedef struct {
	GObject parent;

	/* private, use accessor methods */
	GladeXML *xml;
	GtkWidget *main_window;

	GtkWidget *actions_list;
	GtkTreeStore *actions_model;
} MainWindow;

typedef struct {
	GObjectClass parent_class;
} MainWindowClass;

GType       main_window_get_type (void);
MainWindow *main_window_new (void);

#endif
