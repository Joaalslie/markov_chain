#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/*
 * List implementation
 */

typedef struct listnode listnode_t;

struct listnode {
    listnode_t  *next;
    void        *item;
};

struct list {
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
      if(list == NULL){
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
void list_destroy(list_t *list){
  //frigjør nodene via list->head, til slutt frigjøres lista:
  while(list->head != NULL){
        listnode_t *temp = list->head->next;
        free(list->head);
        list->head = temp;
  }
  free(list);
}

/*
 * Adds an item first in the provided list.
 */
void list_addfirst(list_t *list, void *item){
  listnode_t *newelement = malloc(sizeof(listnode_t));
  if(newelement == NULL){
    printf("Out of memory!");
    return;
  }
  if (newelement!=NULL){
    newelement->item = item;
    if(list->head!=NULL){
      listnode_t *temp = list->head;
      list->head = newelement;
      newelement->next = temp;
    }
    else{
        list->head = newelement;
        newelement->next = NULL;
    }
    list->numitems++;
  }
}

/*
 * Adds an item last in the provided list.
 */
void list_addlast(list_t *list, void *item){
  listnode_t *lastelement = malloc(sizeof(listnode_t));
  listnode_t *temp = list->head;

  if(lastelement == NULL){
    printf("Out of memory!\n");
    return;
  }

  while(list->numitems > 0){
    if(temp->next == NULL){
      temp->next = lastelement;
      break;
    }
    else{
      temp = temp->next;
    }
  }
  if(list->numitems == 0){
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
void list_remove(list_t *list, void *item){
  listnode_t *current = list->head;
  listnode_t *previous = NULL;

  if(list->numitems != 0){
    while(current != NULL){
      if(current->item == item){
        if(previous == NULL){
          list->head = current->next;
          free(current);
        }
        else{
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
int list_size(list_t *list){
    return list->numitems;
}


/*
 * Iterator implementation
 */

struct list_iterator {
    listnode_t *next;
    list_t *list;
};


/*
 * Return a newly created list iterator for the given list.
 */
list_iterator_t *list_createiterator(list_t *list){
    list_iterator_t *newiterator = malloc(sizeof(list_iterator_t));
    if(newiterator == NULL){
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
void list_destroyiterator(list_iterator_t *iter){
    free(iter);
  }


/*
 * Move iterator to next item in list and return current.
 */
void *list_next(list_iterator_t *iter){
      if(iter->next != NULL){
        void *current = iter->next->item;
        iter->next = iter->next->next;
        return current;
      }
      else{
        return NULL;
      }
}


/*
 * Let iterator point to first item in list again.
 */
void list_resetiterator(list_iterator_t *iter)
{
    iter->next = iter->list->head;
}
