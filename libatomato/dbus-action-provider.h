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

#ifndef __DBUS_ACTION_PROVIDER_H__
#define __DBUS_ACTION_PROVIDER_H__

#include "atomato-action-provider.h"

#define DBUS_TYPE_ACTION_PROVIDER             (dbus_action_provider_get_type ())
#define DBUS_ACTION_PROVIDER(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), DBUS_TYPE_ACTION_PROVIDER, DbusActionProvider))
#define DBUS_ACTION_PROVIDER_CLASS(vtable)    (G_TYPE_CHECK_CLASS_CAST ((vtable), DBUS_TYPE_ACTION_PROVIDER, DbusActionProviderClass))
#define DBUS_IS_ACTION_PROVIDER(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), DBUS_TYPE_ACTION_PROVIDER))
#define DBUS_IS__ACTION_PROVIDER_CLASS(vtable) (G_TYPE_CHECK_CLASS_TYPE ((vtable), DBUS_TYPE_ACTION_PROVIDER))
#define DBUS_ACTION_PROVIDER_GET_CLASS(inst)  (G_TYPE_INSTANCE_GET_CLASS ((inst), DBUS_TYPE_ACTION_PROVIDER, DbusActionProviderClass))

typedef struct _DbusActionProvider DbusActionProvider;
typedef struct _DbusActionProviderPrivate DbusActionProviderPrivate;
typedef struct _DbusActionProviderClass DbusActionProviderClass;

struct _DbusActionProvider {
	GObject parent;
	DbusActionProviderPrivate *priv;
};

struct _DbusActionProviderClass {
	GObjectClass parent_class;
};

GType dbus_action_provider_get_type (void);

#endif
