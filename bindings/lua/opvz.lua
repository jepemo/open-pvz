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

-- ZOMBIES
ZOMBIE_REGULAR = { type = 0, health = 10, hit = 2, speed = 2}

-- PLANTS
PLANT_SUNFLOWER   = { type = 0, health = 5,   hit = 0}
PLANT_PEASHOOTER  = { type = 1, health = 5,   hit =1}
PLANT_CHERRYBOMB  = { type = 2, health = 999, hit =60}
PLANT_WALLNUT     = { type = 3, health = 15,  hit =0}

function Level(args)
  -- Default arguments
  args = args or {}
  setmetatable(args, {__index={ rows = 5, cols = 9}})
  local rows, cols =
    args[1] or args.rows,
    args[2] or args.cols

  local self = {
    ident = level_new(rows, cols),
    rows = rows,
    cols = cols
  }

  function self.step()
    level_step(self.ident)
  end

  function self.add_plant(plant, x, y)
    level_add_plant(
      self.ident,
      plant.type,
      plant.health,
      plant.hit,
      x,
      y)
  end

  function self.add_zombie(zombie, x, y)
    level_add_zombie(
      self.ident,
      zombie.type,
      zombie.health,
      zombie.hit,
      zombie.speed,
      x,
      y
    )
  end

  function self.destroy()
    level_destroy(self.ident)
  end

  return self
end

--[[
l = Level{}
l:add_plant(PLANT_SUNFLOWER, 0, 0)
l:add_zombie(ZOMBIE_REGULAR, 1, 1)
l:destroy()
]]--
