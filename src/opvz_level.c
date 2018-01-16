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

  level->entities = list_create();

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
  list_free(level->entities);
}

void
level_add_entity (Level *level, Entity *entity, size_t xpos, size_t ypos)
{
  entity->x_pos = xpos;
  entity->y_pos = ypos;
  entity->id = entity_new_id();

  list_add_elem(level->entities, entity->id, entity);
}

Level *
level_step(Level *level)
{
  /** GAME LOGIC */
  node* ptr = level->entities->first;
  while (ptr != NULL) {
    Entity * entity = ((Entity*) ptr->data);


    if (entity->clazz == ZOMBIE) {
          entity->x_pos = entity->x_pos - 1;
    }

    ptr = ptr->next;
  }

  return level;
}


List*
get_entities_by_pos(Level * level, int x, int y)
{
  List * result = list_create();

  if (level->entities == NULL || level->entities->num_elements == 0)
	    return result;

  node* ptr = level->entities->first;
  while (ptr != NULL) {
      Entity * entity = ((Entity*) ptr->data);
      if (entity->x_pos == x && entity->y_pos == y) {
          list_add_elem(result, entity->id, entity);
      }
      ptr = ptr->next;
  }

  return result;
}

bool
level_all_dead_zombies (Level *level)
{
  if (level->entities == NULL || level->entities->num_elements == 0)
    return true;

  bool all_dead = true;
  node* ptr = level->entities->first;
  while (ptr != NULL) {
      Entity * entity = ((Entity*) ptr->data);
      if (entity->clazz == ZOMBIE) {
        all_dead = false;
        break;
      }

      ptr = ptr->next;
  }

  return all_dead;
}

void
level_print_debug(Level *level)
{
  node *ptr = NULL;

  size_t n_rows = level->config->n_rows;
  size_t n_cols = level->config->n_cols;

  // printf("Board (%ld, %ld)\n", n_rows, n_cols);

  for(int y=0; y < n_rows; ++y) {
    for(int x=0; x < n_cols; ++x) {
      // printf("(%d, %d)\n", x, y);
      List* entities = get_entities_by_pos(level, x, y);

      if (entities->num_elements > 0) {
          ptr = entities->first;
          printf("[");
          while (ptr != NULL) {
              Entity * entity = ((Entity*) ptr->data);
              printf("%s", entity->repr);
              ptr = ptr->next;
          }
          printf("] ");
      }
      else {
          printf("[    ] ");
      }
    }

    printf("\n");
  }

  getchar();
}
