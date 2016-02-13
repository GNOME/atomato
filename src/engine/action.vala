/* GNOME Automation Engine
 * Copyright (C) 2006-2016 The GNOME Foundation
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

namespace Atomato.Engine
{
    public delegate ActionResult ActionFunc (ActionArguments args);

    public class ActionArguments : Object
    {
        public ActionArguments.from_result (ActionResult result)
        {
        }
    }

    public class ActionResult : Object
    {
        private bool _success;
        private string _error_message;

        public ActionResult.with_success ()
        {
            _success = true;
            _error_message = null;
        }

        public ActionResult.with_error (string error)
        {
            _success = false;
            _error_message = error;
        }

        public bool was_successful {
            get {
                return _success;
            }
        }

        public string error_message {
            get {
                return _error_message;
            }
            set {
                _error_message = value;
            }
        }
    }

    public class Action : Object
    {
        string _name;
        ActionFunc _action_func;

        public Action (string name, ActionFunc action_func)
        {
            _name = name;
            _action_func = action_func;
        }

        public virtual ActionResult run (ActionArguments args)
        {
            if (_action_func != null) {
                return _action_func (args);
            }
        }

        public string name {
            get {
                return _name;
            }
        }
    }
}
