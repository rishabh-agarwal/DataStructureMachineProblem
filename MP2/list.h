/* list.h 
 *
 * Public functions for two-way linked list
 *
 * You should not need to change any of the code this file.  If you do, you
 * must get permission from the instructor.
 */

typedef struct list_node_tag {
    // private members for list.c only
    data_t *data_ptr;
    struct list_node_tag *prev;
    struct list_node_tag *next;
} list_node_t;

typedef struct list_tag {
    // private members for list.c only
    list_node_t *head;
    list_node_t *tail;
    int current_list_size;
    int list_sorted_state;
} list_t;

/* public definition of pointer into linked list */
typedef list_node_t * Iterator;
typedef list_t * List;

/* public prototype definitions for list.c */

/* build and cleanup lists */
List list_construct(void);
void list_destruct(List list_ptr);

/* iterators into positions in the list */
Iterator list_iter_front(List list_ptr);
Iterator list_iter_back(List list_ptr);
Iterator list_iter_next(Iterator idx_ptr);

data_t * list_access(List list_ptr, Iterator idx_ptr);
Iterator list_elem_find(List list_ptr, data_t *elem_ptr);

void list_insert(List list_ptr, data_t *elem_ptr, Iterator idx_ptr);
void list_insert_sorted(List list_ptr, data_t *elem_ptr);

data_t * list_remove(List list_ptr, Iterator idx_ptr);

int list_size(List list_ptr);
int comp_proc(data_t *, data_t *);

/* commands for vim. ts: tabstop, sts: soft tabstop sw: shiftwidth */
/* vi:set ts=8 sts=4 sw=4 et: */
