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

#include <gtk/gtkmessagedialog.h>
#include "atomato-gui.h"

void
gui_show_error (const gchar *format, ...)
{
	va_list args;
	gchar *msg;
	GtkWidget *dialog;

	if (!format)
		return;

	va_start (args, format);
	msg = g_strdup_vprintf (format, args);
	va_end (args);

	/* Create and show the dialog */
	dialog = gtk_message_dialog_new (NULL,
					 GTK_DIALOG_NO_SEPARATOR,
					 GTK_MESSAGE_ERROR,
					 GTK_BUTTONS_CLOSE,
					 msg);

	gtk_dialog_run (GTK_DIALOG (dialog));
	g_free (msg);
}
