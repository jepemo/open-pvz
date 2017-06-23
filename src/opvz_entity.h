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
#ifndef __OPVZ_ENTITY_H__
#define __OPVZ_ENTITY_H__

#include <stdlib.h>

typedef struct {
  /* Type */
  short type;
  /* unique identifier */
  long id;
  /** Console representation */
  char* repr;
  /* Pointer to a specialized entity */
  void* data;

  /** ---- Common atributes --------- */

  /* Level x position */
  size_t x_pos;
  /* Level y position */
  size_t y_pos;
  /* Healh */
  int health;
  /* Armor */
  int armor;
  /* hit */
  int hit;

} Entity;


char* entity_new_id(void);

#endif /* __OPVZ_ENTITY_H__ */
