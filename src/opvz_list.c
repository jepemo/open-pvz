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

List * 
list_create  (void)
{
	List *list = malloc(sizeof(struct List));
	
	list->first = NULL;
	list->last  = NULL;
	list->num_elements = 0;
	
	return list;
}

void  
list_add_elem(List* list, int ident, void *elem)
{
	if (list == null)
		return;
		
	node *root = malloc(sizeof(struct node));
	
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
	if (list == null)
		return;
	if (list->num_elements == 0)
		return;
		
	node *ptr = list->first;
	while (ptr != list->last) {
		if (ptr->ident == ident) {
			
			break;
		}
		
		ptr = ptr->next;
	}	
		
	list->num_elements--;
}

void  
list_free (List* list)
{
	if (list == null)
		return;
		
	// Iterate & free every element of the list
	if (list->num_elements > 0) {
		node *ptr = list->first;
		while (ptr->next == NULL) {
			
		}
	}
	
	// Free the list
	free(list);
}
