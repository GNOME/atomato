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
    public delegate bool ActionConditionFunc (ActionArguments args);
    
    public class ConditionalAction : Action
    {
        ActionConditionFunc _condition_func;
        Action _action_to_invoke;

        public ConditionalAction (ActionConditionFunc condition, Action action)
        {
            base ("Condition");

            _condition_func = condition;
            _action_to_invoke = action;
        }

        public override ActionResult run (ActionArguments args)
        {
            if (_condition_func != null) {
                if (!_condition_func (args)) {
                    return new ActionResult ();
                }
            }

            return _action_to_invoke.run (args);
        }
    }
}
