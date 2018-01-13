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

#endif /* __OPVZ_LIST_H__ */