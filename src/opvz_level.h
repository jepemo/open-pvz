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
#ifndef __OPVZ_LEVEL_H__
#define __OPVZ_LEVEL_H__

#include <stdlib.h>
#include <stdbool.h>
#include "hashmap.h"
#include "opvz_plant.h"
#include "opvz_zombie.h"

#define MAX_ENTITIES 1024

typedef struct {
  /* Number of map rows */
  size_t n_rows;
  /* Number of map cols */
  size_t n_cols;
  /* Default value to init depth */
  short init_depth;
} LevelConfig;

typedef struct {
  /* Level configuration*/
  LevelConfig *config;
  /* Surface profundity. Default is 0 */
  short *depth;
  /* Game objects in the level */
  map_t *entities;

  long last_id;
} Level;

LevelConfig * level_config_new(size_t rows, size_t cols, short depth);

Level * level_new        (LevelConfig *config);
Level * level_new_default(void);
void    level_destroy    (Level *level);
void    level_print_debug(Level *level);

void    level_add_zombie (Level *level, Zombie *zombie, size_t xpos, size_t ypos);
void    level_add_plant  (Level *level, Plant *plant, size_t xpos, size_t ypos);

Level * level_step       (Level *level);
bool    level_all_dead_zombies (Level *level);

#endif /* __OPVZ_LEVEL_H__ */
