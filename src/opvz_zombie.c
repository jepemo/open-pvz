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

#include <stdio.h>
#include "opvz_zombie.h"

Entity*
zombie_new(int type, int health, int armor, int hit, int speed)
{
  Entity* entity = malloc(sizeof(Entity));
  Zombie* zombie = malloc(sizeof(Zombie));

  entity->clazz = ZOMBIE;
  entity->type = type;
  entity->data = zombie;

  entity->health = health;
  entity->armor = armor;
  entity->hit = hit;
  entity->repr = malloc(sizeof(char) * 32);

  zombie->speed = speed;

  //sprintf(entity->repr, "Z(%d/%d)", type, entity->health);
  update_repr(entity);
    

  return entity;
}


