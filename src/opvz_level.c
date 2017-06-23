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
#include <string.h>
#include "opvz_level.h"

LevelConfig *
level_config_new(size_t rows, size_t cols, short depth)
{
  LevelConfig *config = malloc(sizeof(LevelConfig));
  config->n_rows = rows;
  config->n_cols = cols;
  config->init_depth = depth;

  return config;
}

Level *
level_new (LevelConfig *config)
{
  Level *level = malloc(sizeof(Level));

  level->config = config;

  short dimension = (level->config->n_rows * level->config->n_cols);

  level->depth = malloc(dimension * sizeof(short));
  memset(level->depth, 0, dimension);

  level->last_id = 1;
  /*
  level->entities = malloc(MAX_ENTITIES * sizeof(short));
  memset(level->entities, 0, MAX_ENTITIES);
  */
  level->entities = hashmap_new();

  return level;
}

/**
 * Create a map of 5x9, with depth 0
 */
Level *
level_new_default(void)
{
  LevelConfig * config = level_config_new(5, 9, 0);
  return level_new(config);
}

void
level_destroy(Level *level)
{
  free(level->depth);
  hashmap_free(level->entities);
}

void
level_add_zombie (Level *level, Zombie *zombie, size_t xpos, size_t ypos)
{
  zombie->entity->x_pos = xpos;
  zombie->entity->y_pos = ypos;
  zombie->entity->id = entity_new_id();

  hashmap_put(level->entities, zombie->entity->id, zombie);
}

void level_add_plant  (Level *level, Plant *plant, size_t xpos, size_t ypos)
{
  plant->entity->x_pos = xpos;
  plant->entity->y_pos = ypos;
  plant->entity->id = entity_new_id();

  hashmap_put(level->entities, plant->entity->id, plant);
}

Level *
level_step(Level *level)
{
  return level;
}


Entity*
get_entities_by_pos(Level * level, int x, int y)
{
  int i;

	/* Cast the hashmap */
	map_t* m = (map_t*) level->entities;

	/* On empty hashmap, return immediately */
	if (hashmap_length(m) <= 0)
		return NULL;

	/* Linear probing */
	for(i = 0; i< m->table_size; i++) {
		if(m->data[i].in_use != 0) {
			any_t data = (any_t) (m->data[i].data);

      Entity* entity = data->entity;
      if (entity->x == x && entity->y == y) {
        printf("OK");
      }
		}
  }

	return NULL;
}

void
level_print_debug(Level *level)
{
  for(int y=0; y < level->config->n_rows; ++y) {
    for(int x=0; x < level->config->n_cols; ++x) {
      Entity* entities = get_entities_by_pos(level, x, y);
      //printf("");
    }
  }
}
