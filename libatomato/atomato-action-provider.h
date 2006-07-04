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

#ifndef __GNOME_AUTOMATOR_ACTION_PROVIDER_H__
#define __GNOME_AUTOMATOR_ACTION_PROVIDER_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define GNOME_AUTOMATOR_TYPE_ACTION_PROVIDER                (gnome_automator_action_provider_get_type ())
#define GNOME_AUTOMATOR_ACTION_PROVIDER(obj)                (G_TYPE_CHECK_INSTANCE_CAST ((obj), GNOME_AUTOMATOR_TYPE_ACTION_PROVIDER, GnomeAutomatorActionProvider))
#define GNOME_AUTOMATOR_IS_ACTION_PROVIDER(obj)             (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GNOME_AUTOMATOR_TYPE_ACTION_PROVIDER))
#define GNOME_AUTOMATOR_ACTION_PROVIDER_GET_INTERFACE(inst) (G_TYPE_INSTANCE_GET_INTERFACE ((inst), GNOME_AUTOMATOR_TYPE_ACTION_PROVIDER, GnomeAutomatorActionProviderInterface))

typedef struct _GnomeAutomatorActionProvider GnomeAutomatorActionProvider;
typedef struct _GnomeAutomatorActionProviderInterface GnomeAutomatorActionProviderInterface;

struct _GnomeAutomatorActionProvider {
};

struct _GnomeAutomatorActionProviderInterface {
	GTypeInterface parent;

	GSList * (* list_actions) (GnomeAutomatorActionProvider *provider);
	GValueArray * (* run_action) (GnomeAutomatorActionProvider *provider,
				      const gchar *action_name,
				      const GValueArray *input_args);
};

GType        gnome_automator_action_provider_get_type (void);

GSList      *gnome_automator_action_provider_list_actions (GnomeAutomatorActionProvider *provider);
GValueArray *gnome_automator_action_provider_run_action (GnomeAutomatorActionProvider *provider,
							 const gchar *action_name,
							 const GValueArray *input_args);

G_END_DECLS

#endif
