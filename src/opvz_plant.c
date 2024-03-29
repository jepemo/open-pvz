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
#include "opvz_plant.h"

Entity *
plant_new(int type, int health, int hit)
{
  Entity * entity = malloc(sizeof(Entity));
  Plant* plant = malloc(sizeof(Plant));

  entity->clazz = PLANT;
  entity->type = type;
  entity->data = plant;

  entity->health = health;
  entity->hit = hit;
  entity->repr = malloc(sizeof(char) * 32);
  entity->distance = -1;

  //sprintf(entity->repr, "P(%d/%d)", type, entity->health);
  update_repr(entity);

  return entity;
}
