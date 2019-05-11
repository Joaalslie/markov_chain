#ifndef LIST_H_
#define LIST_H_

/*
 * List interface
 */

struct list;
typedef struct list list_t;

/*
 * Returns a newly created, empty list.
 */
list_t *list_create(void);

/*
 * Frees the list; list and nodes, but not the items it holds.
 */
void list_destroy(list_t *list);

/*
 * Adds an item last in the provided list.
 */
void list_addlast(list_t *list, int item);

/*
 * Removes an item from the provided list, only freeing the node.
 */
void list_remove(list_t *list, int item);

/*
 * Return the number of items in the list.
 */
int list_size(list_t *list);

/*
 * List iterator interface
 */
struct list_iterator;
typedef struct list_iterator list_iterator_t;

/*
 * Return a newly created list iterator for the given list.
 */
list_iterator_t *list_createiterator(list_t *list);

/*
 * Free the memory for the given list iterator.
 */
void list_destroyiterator(list_iterator_t *iter);

/*
 * Move iterator to next item in list and return current.
 */
int list_next(list_iterator_t *iter);

/*
 * Let iterator point to first item in list again.
 */
void list_resetiterator(list_iterator_t *iter);

/*
 * Iterates over the list, printing out the values of it. 
 */
void print_list(list_t *list, int length);

#endif /*LIST_H_*/
