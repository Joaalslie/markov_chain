#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/*
 * List implementation
 */

typedef struct listnode listnode_t;

struct listnode
{
	listnode_t *next;
	int item;
};

struct list
{
	listnode_t *head;
	int numitems;
};

/*
 * Returns a newly created, empty list.
 */
list_t *list_create(void)
{
	//Holder av plass i dynamisk minne og lagrer adresse i en peker:
	list_t *list = malloc(sizeof(list_t));
	if (list == NULL)
	{
		printf("Out of memory!\n");
		return 0;
	}
	list->head = NULL;
	list->numitems = 0;

	return list;
}

/*
 * Frees the list; list and nodes, but not the items it holds.
 */
void list_destroy(list_t *list)
{
	while (list->head != NULL)
	{
		listnode_t *temp = list->head->next;
		free(list->head);
		list->head = temp;
	}
	free(list);
}

/*
 * Adds an item last in the provided list.
 */
void list_addlast(list_t *list, int item)
{
	listnode_t *lastelement = malloc(sizeof(listnode_t));
	if (lastelement == NULL)
	{
		printf("Out of memory!\n");
		return;
	}

	listnode_t *temp = list->head;

	while (list->numitems > 0)
	{
		if (temp->next == NULL)
		{
			temp->next = lastelement;
			break;
		}
		else
		{
			temp = temp->next;
		}
	}
	if (list->numitems == 0)
	{
		list->head = lastelement;
		lastelement->next = NULL;
	}
	lastelement->next = NULL;
	lastelement->item = item;
	list->numitems++;
}

/*
 * Removes an item from the provided list, only freeing the node.
 */
void list_remove(list_t *list, int item)
{
	listnode_t *current = list->head;
	listnode_t *previous = NULL;

	if (list->numitems != 0)
	{
		while (current != NULL)
		{
			if (current->item == item)
			{
				if (previous == NULL)
				{
					list->head = current->next;
					free(current);
				}
				else
				{
					previous->next = current->next;
					free(current);
				}
				break;
			}
			previous = current;
			current = current->next;
		}
		list->numitems--;
	}
}

/*
 * Return the number of items in the list.
 */
int list_size(list_t *list)
{
	return list->numitems;
}

/*
 * Iterator implementation
 */

struct list_iterator
{
	listnode_t *next;
	list_t *list;
};

/*
 * Return a newly created list iterator for the given list.
 */
list_iterator_t *list_createiterator(list_t *list)
{
	list_iterator_t *newiterator = malloc(sizeof(list_iterator_t));
	if (newiterator == NULL)
	{
		printf("Out of memory!\n");
		return 0;
	}
	newiterator->next = list->head;
	newiterator->list = list;

	return newiterator;
}

/*
 * Free the memory for the given list iterator.
 */
void list_destroyiterator(list_iterator_t *iter)
{
	free(iter);
}

/*
 * Move iterator to next item in list and return current.
 */
int list_next(list_iterator_t *iter)
{
	if (iter->next != NULL)
	{
		int current = iter->next->item;
		iter->next = iter->next->next;
		return current;
	}
	else
	{
		return -1;
	}
}

/*
 * Let iterator point to first item in list again.
 */
void list_resetiterator(list_iterator_t *iter)
{
	iter->next = iter->list->head;
}

void print_list(list_t *list, int length)
{
	int elem, i;

	list_iterator_t *iter = list_createiterator(list);

	// Iterate over the chains list, printing out number of elements
	for (i = 0; i < length; i++)
	{
		elem = list_next(iter);
		if (!elem)
		{
			break;
		}
		printf("%d\n", elem);
	}

	list_destroyiterator(iter);
}
