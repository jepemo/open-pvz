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
#include "opvz_entity.h"
#include <stdio.h>

static long last_id = 1;

long
entity_new_id(void)
{
  //char *new_id = (char *) malloc(256);

  //sprintf(new_id, "%d", last_id);

  //last_id++;
  return last_id++;

  //return new_id;
}

void
update_repr(Entity * entity)
{
    char prefix = entity->clazz == ZOMBIE
        ? 'Z'
        : 'P';

    int type = entity->type;
    sprintf(entity->repr, "%c(%d/%d)", prefix, type, entity->health);
}
