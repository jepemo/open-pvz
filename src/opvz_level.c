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

void
update_zombie_hit(Level *level, size_t x, size_t y, int distance, int hit)
{
    int max_distance = level->config->n_cols;
    if (distance > 0) {
        max_distance = x + distance;
        if (max_distance > level->config->n_cols)
            max_distance = level->config->n_cols;
    }

    for (int xini=x; xini < max_distance; ++xini) {
        int yy = (int)y;
        List* entities = get_entities_by_pos(level, xini, yy);

        if (entities->num_elements > 0) {
            node *ptr = entities->first;
            while (ptr != NULL) {
                Entity * entity = ((Entity*) ptr->data);

                if (entity->clazz == ZOMBIE) {
                    entity->health -= hit;
                    update_repr(entity);

                    if (entity->health <= 0) {
                        list_rem_elem(level->entities, entity->id);
                    }

                    break;
                }

                ptr = ptr->next;
            }
        }
    }
}

int
plant_attacked(Level *level, Entity * zombie)
{
    int attacked = 0;

    // Si el zombie esta en la misma casilla que una planta, consumir vida planta
    List* entities = get_entities_by_pos(level, zombie->x_pos, zombie->y_pos);
    if (entities->num_elements > 0) {
        node *ptr = entities->first;
        while (ptr != NULL) {
            Entity * entity = ((Entity*) ptr->data);
            if (entity->clazz == PLANT) {
                entity->health -= zombie->hit;
                update_repr(entity);

                if (entity->health <= 0) {
                    list_rem_elem(level->entities, entity->id);
                }

                attacked = 1;
                break;
            }
            ptr = ptr->next;
        }
    }

    return attacked;
}

LevelStatus *
level_status_init()
{
  LevelStatus * status = (LevelStatus *) malloc(1);
  status->finished = false;
  status->who_won = 0;
  status->num_entities_dead = 0;
  status->entities_dead = NULL;

  return status;
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

LevelStatus *
level_step(Level *level)
{
  LevelStatus * status = level_status_init();

  /** GAME LOGIC */
  node* ptr = level->entities->first;
  while (ptr != NULL) {
    Entity * entity = ((Entity*) ptr->data);


    if (entity->clazz == ZOMBIE) {
        if (plant_attacked(level, entity) == 0) {
            entity->x_pos = entity->x_pos - 1;
        }
    }
    else if (entity->clazz == PLANT) {
        // Si la planta puede disparar, quitar una vida del primer zombie del carril
        if (entity->hit > 0) {
            update_zombie_hit(level, entity->x_pos, entity->y_pos, entity->distance, entity->hit);
        }
    }

    ptr = ptr->next;
  }

  if (level_all_dead_zombies(level)) {
    status->finished = true;
    status->who_won = -1;
  }

  return status;
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
