/**
 * open-pvz - Tower Defense Game Engine inspired by "Plantz Vz Zombiez",
 *            implemented in C with differents bindings for other languages.
 *
 * Copyright (C) 2017-present Jeremies Pérez Morata
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "test_utils.h"
#include "opvz.h"
#include <stdio.h>

void level_init (Level *level)
{
  // plants
  level_add_plant(level, PLANT_SUNFLOWER, 0, 0);
  level_add_plant(level, PLANT_SUNFLOWER, 0, 1);
  level_add_plant(level, PLANT_SUNFLOWER, 0, 2);
  level_add_plant(level, PLANT_SUNFLOWER, 0, 3);
  level_add_plant(level, PLANT_SUNFLOWER, 0, 4);

  level_add_plant(level, PLANT_PEASHOOTER, 1, 0);
  level_add_plant(level, PLANT_PEASHOOTER, 2, 1);
  level_add_plant(level, PLANT_PEASHOOTER, 3, 2);
  level_add_plant(level, PLANT_PEASHOOTER, 4, 3);
  level_add_plant(level, PLANT_PEASHOOTER, 5, 4);

  // Zombies
  level_add_zombie(level, ZOMBIE_REGULAR, 8, 0)
  level_add_zombie(level, ZOMBIE_REGULAR, 8, 1)
  level_add_zombie(level, ZOMBIE_REGULAR, 8, 2)
  level_add_zombie(level, ZOMBIE_REGULAR, 8, 3)
  level_add_zombie(level, ZOMBIE_REGULAR, 8, 4)
}

void simple_game () {
  Level *level = level_new_default();

  level_init(level);

  while(level_all_dead_zombies(level) == false) {
    level_print_debug(level);
    level = level_step(level);
  }

  level_destroy(level);
}

int main (int argc, char **argv) {
  START_TEST("SIMPLE_GAME")

  simple_game();

  return 0;
}
