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
    public class AggregateAction : Action
    {
        List<Action> _actions = new List<Action> ();

        public AggregateAction ()
        {
            base ("AggregateAction");
        }

        public void add_action (Action action)
        {
            _actions.append (action);
        }

        public override ActionResult run (ActionArguments args)
        {
            ActionResult result = null;
            ActionArguments action_args = args;

            // Execute all actions in order
            foreach (var action in _actions) {
                stdout.printf ("Running action %s\n", action.name);
                result = action.run (action_args);
                if (result == null || !result.was_successful) {
                    // If one action fails, stop
                    stdout.printf ("Action %s failed\n", action.name);
                    break;
                }

                action_args = new ActionArguments.from_result (result);
            }

            return result;
        }
    }
}
