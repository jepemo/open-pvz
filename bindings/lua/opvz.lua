--
-- open-pvz - Tower Defense Game Engine inspired by "Plantz Vz Zombiez",
--            implemented in C with differents bindings for other languages.
--
-- Copyright (C) 2017-present Jeremies Pérez Morata
--
-- This program is free software: you can redistribute it and/or modify
-- it under the terms of the GNU General Public License as published by
-- the Free Software Foundation, either version 3 of the License, or
-- (at your option) any later version.
--
-- This program is distributed in the hope that it will be useful,
-- but WITHOUT ANY WARRANTY; without even the implied warranty of
-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
-- GNU General Public License for more details.
--
-- You should have received a copy of the GNU General Public License
-- along with this program.  If not, see <http://www.gnu.org/licenses/>.
--
require("libopvz_lua")

local function Level(args)
  -- Default arguments
  args = args or {}
  setmetatable(args, {__index={ rows = 5, cols = 9}})
  local rows, cols =
    args[1] or args.rows,
    args[2] or args.cols

  local self = {
    ident = create_new_level(rows, cols),
    rows = rows,
    cols = cols
  }

  function self.step()
    level_step(self.ident)
  end

  function self.add_plant(plant)
  end

  function self.add_zombie(zombie)
  end

  return self
end

l1 = Level{}
print(l1.ident)
print(l1.rows)
print(l1.cols)
