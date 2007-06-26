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

#ifndef __SHELL_ACTION_PROVIDER_H__
#define __SHELL_ACTION_PROVIDER_H__

#include "atomato-action-provider.h"

#define SHELL_TYPE_ACTION_PROVIDER             (shell_action_provider_get_type ())
#define SHELL_ACTION_PROVIDER(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), SHELL_TYPE_ACTION_PROVIDER, ShellActionProvider))
#define SHELL_ACTION_PROVIDER_CLASS(vtable)    (G_TYPE_CHECK_CLASS_CAST ((vtable), SHELL_TYPE_ACTION_PROVIDER, ShellActionProviderClass))
#define SHELL_IS_ACTION_PROVIDER(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), SHELL_TYPE_ACTION_PROVIDER))
#define SHELL_IS__ACTION_PROVIDER_CLASS(vtable) (G_TYPE_CHECK_CLASS_TYPE ((vtable), SHELL_TYPE_ACTION_PROVIDER))
#define SHELL_ACTION_PROVIDER_GET_CLASS(inst)  (G_TYPE_INSTANCE_GET_CLASS ((inst), SHELL_TYPE_ACTION_PROVIDER, ShellActionProviderClass))

typedef struct _ShellActionProvider ShellActionProvider;
typedef struct _ShellActionProviderPrivate ShellActionProviderPrivate;
typedef struct _ShellActionProviderClass ShellActionProviderClass;

struct _ShellActionProvider {
	GObject parent;
	ShellActionProviderPrivate *priv;
};

struct _ShellActionProviderClass {
	GObjectClass parent_class;
};

GType shell_action_provider_get_type (void);

#endif
