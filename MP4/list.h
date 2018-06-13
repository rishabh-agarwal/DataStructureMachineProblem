/* list.h 
 * RISHABH AGARWAL
 * Public functions for two-way linked list
 *
 * You should not need to change any of the code this file.  If you do, you
 * must get permission from the instructor.
 */

typedef struct llist_node_tag {
    // Private members for list.c only
    data_t *data_ptr;
    struct llist_node_tag *prev;
    struct llist_node_tag *next;
} llist_node_t;

typedef struct list_tag {
    // Private members for list.c only
    llist_node_t *llist_head;
    llist_node_t *llist_tail;
    int llist_size;     // number of items in list
    int llist_sort;     // a flag if list is sorted or unsorted
} list_t;

// Public definition of pointer into linked list
typedef llist_node_t * pIterator;
typedef list_t * pList;

// Public prototype definitions for list.c

// build and cleanup lists
pList list_construct(void);
void list_destruct(pList list_ptr);
void list_sort(list_t *,int );
// iterators into positions in the list
pIterator list_iter_first(pList list_ptr);
pIterator list_iter_tail(pList list_ptr);
pIterator list_iter_next(pIterator idx_ptr);

data_t * list_access(pList list_ptr, pIterator idx_ptr);
pIterator list_elem_find(pList list_ptr, data_t *elem_ptr);
void list_insert(pList list_ptr, data_t *elem_ptr, pIterator idx_ptr);
void list_insert_sorted(pList list_ptr, data_t *elem_ptr);


data_t * list_remove(pList list_ptr, pIterator idx_ptr);

int list_size(pList list_ptr);
int comp_proc(data_t *, data_t *);

/* commands for vim. ts: tabstop, sts: soft tabstop sw: shiftwidth */
/* vi:set ts=8 sts=4 sw=4 et: */
