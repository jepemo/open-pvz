local ffi = require "ffi"
ffi.cdef[[
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

#define PLANT 0
#define ZOMBIE 1

typedef struct {
  /* class (0 plant, 1 zombie) */
  short clazz;
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
  /* hit */
  int hit;
  /* distance */
  int distance;
  /* wait */
  int wait;

} Entity;


long entity_new_id (void);
void update_repr   (Entity * entity);

#endif /* __OPVZ_ENTITY_H__ */
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
#ifndef __OPVZ_H__
#define __OPVZ_H__

#include "opvz_entity.h"
#include "opvz_zombie.h"
#include "opvz_zombie_types.h"
#include "opvz_plant.h"
#include "opvz_plant_types.h"
#include "opvz_level.h"
#include "opvz_list.h"

#endif /* __OPVZ_H__ */
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
#include "opvz_list.h"
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
  List *entities;

  long last_id;
} Level;

typedef struct {
  /* True if level game have finished */
  bool finished;
  /* winned (-1 = zombies, 1 = plants) */
  int who_won;
  /* Entities dead */
  Entity * entities_dead;
  int num_entities_dead;
} LevelStatus;

LevelConfig * level_config_new(size_t rows, size_t cols, short depth);

Level * level_new        (LevelConfig *config);
Level * level_new_default(void);
void    level_destroy    (Level *level);
void    level_print_debug(Level *level);

void    level_add_entity (Level *level, Entity *entity, size_t xpos, size_t ypos);

LevelStatus * level_step  (Level *level);

#endif /* __OPVZ_LEVEL_H__ */
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

#ifndef __OPVZ_LIST_H__
#define __OPVZ_LIST_H__

/** Node of a double linked list */
typedef struct _node {
  int ident;
  void *data;
  struct _node *prev;
  struct _node *next;
} node;

typedef struct {		
	node *first;
	node *last;
	int num_elements;
} List;

List* list_create  (void);
void  list_add_elem(List* list, int ident, void *elem);
void  list_rem_elem(List* list, int ident);
void  list_free    (List* list);

#endif /* __OPVZ_LIST_H__ *//**
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
#ifndef __OPVZ_PLANT_H__
#define __OPVZ_PLANT_H__

#include <stdlib.h>
#include "opvz_entity.h"

typedef struct {
} Plant;

Entity * plant_new(int type, int health, int hit);

#endif /* __OPVZ_PLANT_H__ */
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
#ifndef __OPVZ_PLANT_TYPES_H__
#define __OPVZ_PLANT_TYPES_H__

#include "opvz_plant.h"
                                   /* type,  health,      hit */
#define PLANT_SUNFLOWER  plant_new(    0,      5,     0)
#define PLANT_PEASHOOTER plant_new(    1,      5,     1)
#define PLANT_CHERRYBOMB plant_new(    2,      999,  60)
#define PLANT_WALLNUT    plant_new(    3,      15,    0)

#endif /* __OPVZ_PLANT_TYPES_H__ */
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
#ifndef __OPVZ_ZOMBIE_H__
#define __OPVZ_ZOMBIE_H__

#include "opvz_entity.h"

typedef struct {
  int speed;
} Zombie;

Entity* zombie_new(int type, int health, int hit, int speed);

#endif /* __OPVZ_ZOMBIE_H__ */
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

#ifndef __OPVZ_ZOMBIE_TYPES_H__
#define __OPVZ_ZOMBIE_TYPES_H__

#include "opvz_zombie.h"

                                   /* type, health, hit,  speed */
#define ZOMBIE_REGULAR zombie_new(    0,     10,     2,     2    )

#endif /* __OPVZ_ZOMBIE_TYPES_H__ */

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
            if (entity->x_pos == 0) {
              status->finished = true;
              status->who_won = -1;
            }
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
    status->who_won = 1;
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

#include <stdlib.h>
#include "opvz_list.h"

List * 
list_create(void)
{
	List *list = malloc(sizeof(List));
	
	list->first = NULL;
	list->last  = NULL;
	list->num_elements = 0;
	
	return list;
}

void  
list_add_elem(List* list, int ident, void *elem)
{
	if (list == NULL)
		return;
		
	node *root = malloc(sizeof(node));
	
	root->ident = ident;
	root->data = elem;
	
	if (list->num_elements == 0) {
		list->first = root;	
		root->prev = NULL;	
	}
	else {
		list->last->next = root;	
		root->prev = list->last;	
	}
	
	list->last = root;
	list->num_elements++;
}

// Seeing: https://codereview.stackexchange.com/questions/30536/simple-linked-list-implementation
void  
list_rem_elem(List* list, int ident)
{
	if (list == NULL)
		return;
	if (list->num_elements == 0)
		return;
		
	node *ptr = list->first;
	while (ptr != NULL) {
		if (ptr->ident == ident) {
			
			// First element
			if (ptr->prev == NULL) {
				ptr->next->prev = NULL;
				list->first = ptr->next;
			}
			// Last element
			else if (ptr->next == NULL) {
				ptr->prev->next = NULL;
				list->last = ptr->prev;
			}
			else {
				ptr->prev->next = ptr->next;
				ptr->next->prev = ptr->prev;
			}
			
			free(ptr);
			
			break;
		}
		
		ptr = ptr->next;
	}	
		
	list->num_elements--;
}

void  
list_free (List* list)
{
	if (list == NULL)
		return;
		
	// Iterate & free every element of the list
	if (list->num_elements > 0) {
		node *ptr = list->first;
		node *aux = NULL;
		while (ptr != NULL) {
			aux = ptr->next;
			
			free(ptr);
			
			ptr = aux;
		}
	}
	
	// Free the list
	free(list);
}
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
zombie_new(int type, int health, int hit, int speed)
{
  Entity* entity = malloc(sizeof(Entity));
  Zombie* zombie = malloc(sizeof(Zombie));

  entity->clazz = ZOMBIE;
  entity->type = type;
  entity->data = zombie;

  entity->health = health;
  entity->hit = hit;
  entity->repr = malloc(sizeof(char) * 32);

  zombie->speed = speed;

  //sprintf(entity->repr, "Z(%d/%d)", type, entity->health);
  update_repr(entity);
    

  return entity;
}



]]

level_step = ffi.C.level_step
level_add_plant = ffi.C.level_add_plant
level_add_zombie = ffi.C.level_add_zombie
level_destroy = ffi.C.level_destroy

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

print("Start")
l = Level{}
l:add_plant(PLANT_SUNFLOWER, 0, 0)
l:add_zombie(ZOMBIE_REGULAR, 1, 1)
l:destroy()
print("End")


