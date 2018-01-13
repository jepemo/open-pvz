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
#include "test_utils.h"
#include "opvz.h"

void printList(List *l1)
{
  int i=0;
  node* ptr = l1->first;
  while(ptr != NULL) {
	  printf("%d - %d - %s\n", i, ptr->ident, (char*)ptr->data);
	  ptr = ptr->next;
	  i++;
  }
}

void list0 () {
  List * l1 = list_create();
  
  char *data = "0123456789";
  
  list_add_elem(l1, 0, data);
  list_add_elem(l1, 1, data);
  list_add_elem(l1, 2, data);
  list_add_elem(l1, 3, data);
  list_add_elem(l1, 4, data);
  
  printList(l1);
  
  list_rem_elem(l1, 2);
  
  printList(l1);
  
  list_free(l1);
}

int main (int argc, char **argv) {
  START_TEST("LISTS")

  list0();

  return 0;
}