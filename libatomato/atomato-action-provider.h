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

#ifndef __ATOMATO_ACTION_PROVIDER_H__
#define __ATOMATO_ACTION_PROVIDER_H__

#include <glib-object.h>
#include "atomato-action.h"

G_BEGIN_DECLS

#define ATOMATO_TYPE_ACTION_PROVIDER                (atomato_action_provider_get_type ())
#define ATOMATO_ACTION_PROVIDER(obj)                (G_TYPE_CHECK_INSTANCE_CAST ((obj), ATOMATO_TYPE_ACTION_PROVIDER, AtomatoActionProvider))
#define ATOMATO_IS_ACTION_PROVIDER(obj)             (G_TYPE_CHECK_INSTANCE_TYPE ((obj), ATOMATO_TYPE_ACTION_PROVIDER))
#define ATOMATO_ACTION_PROVIDER_GET_INTERFACE(inst) (G_TYPE_INSTANCE_GET_INTERFACE ((inst), ATOMATO_TYPE_ACTION_PROVIDER, AtomatoActionProviderInterface))

typedef struct _AtomatoActionProvider AtomatoActionProvider;
typedef struct _AtomatoActionProviderInterface AtomatoActionProviderInterface;

struct _AtomatoActionProvider {
};

struct _AtomatoActionProviderInterface {
	GTypeInterface parent;

	GList * (* get_actions) (AtomatoActionProvider *provider);
};

GType   atomato_action_provider_get_type (void);

GSList *atomato_action_provider_get_actions (AtomatoActionProvider *provider);

G_END_DECLS

#endif
