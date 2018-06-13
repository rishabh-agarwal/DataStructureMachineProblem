/* list.c
 * Prof. Russell 
 * ECE 223 Fall 2013
 * MP1
 *
 * Propose: A template for list.c. You will make many changes.
 *
 * Assumptions: Many details are incomplete.  
 *
 * Bugs: Many detail have not been implemented.
 */

#include <stdlib.h>
#include <assert.h>
#include "datatypes.h"   /* defines data_t */
#include "list.h"        /* defines public functions for list ADT */

/* definitions for private constants used in list.c only */
#define SORTED_LIST   -123456
#define UNSORTED_LIST -621354

/* prototypes for private functions used in list.c only */
void list_debug_validate(list_t *L);

/* ----- below are the functions  ----- */

/* Allocates a new, empty list 
 *
 * By convention, the list is initially assumed to be sorted.  The field sorted
 * can only take values SORTED_LIST or UNSORTED_LIST
 *
 * The inital empty list must have
 *  . current_list_size = 0
 *  . list_sorted_state = SORTED_LIST
 *
 * Use list_decontruct to remove and deallocate all elements on a list
 * and the header block.
 */
list_t * list_construct(void)
{
    list_t *L;

    L = (list_t *) malloc(sizeof(list_t));
    L->head = NULL;
    L->tail = NULL;
    L->current_list_size = 0;
    L->list_sorted_state = SORTED_LIST;

    /* the last line of this function must call validate */
    list_debug_validate(L);
    return L;
}

/* Deallocates the contents of the specified list, releasing associated memory
 * resources for other purposes.
 *
 * Free all elements in the list, the dummy head and tail, and the header 
 * block.
 */
void list_destruct(list_t *list_ptr)
{
    /* the first line must validate the list */
    list_debug_validate(list_ptr);
    
    list_node_t *temp_node= list_ptr->head;
    while(temp_node !=NULL)
    {
    list_ptr->head = temp_node->next;
    free(temp_node->data_ptr);
    free(temp_node);
    temp_node = list_ptr->head;
    }
    free(list_ptr);
}

/* Return an Iterator that points to the first element in the list.  If the
 * list is empty the value that is returned in NULL.
 */
list_node_t * list_iter_front(list_t *list_ptr)
{
    assert(list_ptr != NULL);
    list_debug_validate(list_ptr);
    return list_ptr->head;

}

/* Return an Iterator that points to the last list_node_t. If the list is empty
 * then the pointer that is returned is NULL.
 */
list_node_t * list_iter_back(list_t *list_ptr)
{
    assert(list_ptr != NULL);
    list_debug_validate(list_ptr);
    return list_ptr->tail;
}

/* Advance the Iterator to the next item in the list.  
 * If the iterator points to the last item in the list, then 
 * this function returns NULL to indicate there is no next item.
 * 
 * It is a catastrophic error to call this function if the
 * iterator, idx_ptr, is null.
 */
list_node_t * list_iter_next(list_node_t * idx_ptr)
{
    assert(idx_ptr != NULL);
    return idx_ptr->next;
}

/* Obtains a pointer to an element stored in the specified list, at the
 * specified Iterator position
 * 
 * list_ptr: pointer to list-of-interest.  A pointer to an empty list is
 *           obtained from list_construct.
 *
 * idx_ptr: pointer to position of the element to be accessed.  This pointer
 *          must be obtained from list_elem_find, list_iter_front, 
 *          list_iter_back, or list_iter_next.  
 *
 * return value: pointer to the data_t element found in the list at the 
 * iterator position. A value NULL is returned if 
 *     1.  the list is empty 
 *     2.  the idx_ptr is NULL.
 */
data_t * list_access(list_t *list_ptr, list_node_t * idx_ptr)
{
    assert(list_ptr != NULL);
    if (idx_ptr == NULL)
	return NULL;
	else if(list_ptr->head==NULL)
	return NULL;
	
	return idx_ptr->data_ptr;
    /* debugging function to verify that the structure of the list is valid */
    list_debug_validate(list_ptr);

  }  

/* Finds an element in a list and returns a pointer to it.
 *
 * list_ptr: pointer to list-of-interest.  
 *
 * elem_ptr: element against which other elements in the list are compared.
 *           Note: uses the compare function defined in datatypes.h
 *
 * The function returns an Iterator pointer to the list_node_t that contains 
 * the first matching element if a match if found.  If a match is not found 
 * the return value is NULL.
 *
 * Note: to get a pointer to the matching data_t memory block pass the return
 *       value from this function to the list_access function.
 */
list_node_t * list_elem_find(list_t *list_ptr, data_t *elem_ptr)
{
    list_debug_validate(list_ptr);
    list_node_t *fnode;
    fnode=list_ptr->head;
    
    if(comp_proc(elem_ptr,fnode->data_ptr)==0)
    {
    return fnode;
    } 
    fnode=fnode->next;  
    return NULL;
}

/* Inserts the data element into the list in front of the iterator 
 * position.
 *
 * list_ptr: pointer to list-of-interest.  
 *
 * elem_ptr: pointer to the memory block to be inserted into list.
 *
 * idx_ptr: pointer to a list_node_t.  The element is to be inserted as a 
 *          member in the list at the position that is immediately in front 
 *          of the position of the provided Iterator pointer.
 *
 * If the idx_ptr pointer is NULL, the the new memory block is
 *          inserted after the last element in the list.  That is, a null
 *          iterator pointer means make the element the new tail.
 *
 * If idx_ptr is set using 
 *    -- list_iter_front, then the new element becomes the first item in 
 *       the list.
 *    -- list_iter_back, then the new element is inserted before the last item 
 *       in the list.
 *    -- for any other idx_ptr, the new element is insert before the 
 *       Iterator
 *
 * For example, to insert at the tail of the list do
 *      list_insert(mylist, myelem, NULL)
 * to insert at the front of the list do
 *      list_insert(mylist, myelem, list_iter_front(mylist))
 *
 * Note that use of this function results in the list to be marked as unsorted,
 * even if the element has been inserted in the correct position.  That is, on
 * completion of this subroutine the list_ptr->list_sorted_state must be equal 
 * to UNSORTED_LIST.
 */
void list_insert(list_t *list_ptr, data_t *elem_ptr, list_node_t * idx_ptr)
{
    assert(list_ptr != NULL);
//Creating a new node
        list_node_t *new_node;
	new_node=(list_node_t *)malloc(sizeof(list_node_t));
  
    // Insert if list is empty
    if(list_ptr->current_list_size==0)
    {
	
	new_node->next=NULL;
	new_node->prev=NULL;
	new_node->data_ptr=elem_ptr;
	
	list_ptr->head=new_node;
	list_ptr->tail=new_node;
	list_ptr->current_list_size++;
    }
   // Insert after tail
    else if(idx_ptr==NULL)
    {
    
     new_node->prev=list_ptr->tail;
     new_node->next=NULL;
     new_node->data_ptr=elem_ptr;
     list_ptr->current_list_size++;
     list_ptr->tail=new_node;
     new_node->prev->next=new_node;
    
    }
//Insert before idx pointer 
     else
    {
    
     
     new_node->prev=NULL;
     new_node->next=idx_ptr;
     idx_ptr->prev=new_node;
     new_node->data_ptr=elem_ptr;
     list_ptr->head=new_node;
     list_ptr->current_list_size++;
     
     
   }
    
/* the last two lines of this function must be the following */
    if (list_ptr->list_sorted_state == SORTED_LIST) 
	list_ptr->list_sorted_state = UNSORTED_LIST;
    list_debug_validate(list_ptr);
}

/* Inserts the element into the specified sorted list at the proper position,
 * as defined by the compare_proc.
 *
 * list_ptr: pointer to list-of-interest.  
 *
 * elem_ptr: pointer to the element to be inserted into list.
 *
 * If you use list_insert_sorted, the list preserves its sorted nature.
 *
 * If you use list_insert, the list will be considered to be unsorted, even
 * if the element has been inserted in the correct position.
 *
 * If the list is not sorted and you call list_insert_sorted, this subroutine
 * must generate a system serted element will be placed after all the
 * elements of equal rank that are already in the list.
 *
 * The comparison procedure must accept two arguments (A and B) which are both
 * pointers to elements of type data_t.  The comparison procedure returns an
 * integer code which indicates the precedence relationship between the two
 * elements.  The integer code takes on the following values:
 *    1: A should be closer to the front of the list than B
 *   -1: B should be closer to the front of the list than A
 *    0: A and B are equal in rank
 *
 * Note: if the element to be inserted is equal in rank to an element already
 * in the list, the newly in*/
void list_insert_sorted(list_t *list_ptr, data_t *elem_ptr)
{
    assert(list_ptr != NULL);
    assert(list_ptr->list_sorted_state == SORTED_LIST);
   // Creating a New Node
     list_node_t *temp_node;
     temp_node=(list_node_t *)malloc(sizeof(list_node_t));
   // Insert a new node if no node
       if(list_ptr->current_list_size==0)
    {
	
	temp_node->next=NULL;
	temp_node->prev=NULL;
	temp_node->data_ptr=elem_ptr;
	
	list_ptr->head=temp_node;
	list_ptr->tail=temp_node;
	list_ptr->current_list_size++;
    }
    else{
  list_node_t *rover;
  list_node_t *rover_next;
  rover= list_ptr->head;
  while (rover!=NULL)
    {
    rover_next = rover->next;
/*      if (comp_proc(elem_ptr,rover->data_ptr)==1)     // If A<B
         {
           temp_node->prev=rover->prev;
           temp_node->next=rover;
           temp_node->data_ptr=elem_ptr;
           list_ptr->head=temp_node;
           rover->prev=temp_node;
           list_ptr->head=temp_node;
           list_ptr->current_list_size++;
           break;
         }
    
*/    
    
     if (comp_proc(elem_ptr,rover->data_ptr)==-1)        //A>B
         {  
         if(rover_next != NULL)
            {
            if(comp_proc(elem_ptr,rover_next->data_ptr) ==1)
                {
         
                 temp_node->prev=rover;
                 temp_node->next=rover->next;
                 rover->next=temp_node;
                 temp_node->next->prev=temp_node;
                 temp_node->data_ptr=elem_ptr;
                 list_ptr->current_list_size++;
                 break;
                }
            }
          else
            {
            list_insert(list_ptr, elem_ptr, NULL);
            list_ptr->list_sorted_state = SORTED_LIST;
            break;
            }
          }
     if (comp_proc(elem_ptr,rover->data_ptr)==0)//comparing node
         {
           free(rover->data_ptr);
           rover->data_ptr=elem_ptr;
           break;
        }
     
     if (comp_proc(elem_ptr,rover->data_ptr)==1)        //A<B
     {
     list_insert(list_ptr, elem_ptr, rover);
     list_ptr->list_sorted_state = SORTED_LIST;
     break;
     }
    
    rover=rover->next;
        
    }
}

    
    list_debug_validate(list_ptr);
 }

/* Removes the element from the specified list that is found at the 
 * iterator pointer.  A pointer to the data element is returned.
 *
 * list_ptr: pointer to list-of-interest.  
 *
 * idx_ptr: pointer to position of the element to be accessed.  This pointer
 *          must be obtained from list_elem_find, list_iter_front, or
 *          list_iter_next, or list_iter_back.  
 *
 *          If the ndx_ptr is null, then assume that the first item
 *          at the head is to be removed.
 *
 * If the list is empty, then the function should return NULL.  Note: if
 *    the list is empty, then the iterator should be a NULL pointer.
 *
 * Note to remove the element at the front of the list use either
 *     list_remove(mylist, list_iter_front(mylist))
 *  or
 *     list_remove(mylist, NULL);
 *
 * Note: a significant danger with this function is that once
 * an element is removed from the list, the idx_ptr is dangling.  That
 * is, the idx_ptr now points to memory that is no longer valid.
 * You should not call list_iter_next on an iterator after there
 * has been a call to list_remove with the same iterator.
 *
 * When you remove the list_node_t in this function, you should null the next
 * and prev pointers before you free the memory block to avoid accidental use
 * of these now invalid pointers. 
 */
data_t * list_remove(list_t *list_ptr, list_node_t * idx_ptr)
{
    assert(list_ptr != NULL);
    list_node_t *new_node;
    data_t *hold;
    
    if(idx_ptr==list_ptr->head)
    {
     new_node=list_ptr->head;
     hold=list_ptr->head->data_ptr;
     list_ptr->head->data_ptr = NULL;
     list_ptr->head=list_ptr->head->next;
     list_ptr->head->prev=NULL;
     new_node->next=NULL;
     free(new_node);
     
    }
    else if (idx_ptr==list_ptr->tail)
    { 
     new_node=list_ptr->tail;
     hold=list_ptr->tail->data_ptr;
     list_ptr->tail=new_node->prev;
     new_node->next=NULL;
     free(new_node);
     
     }
    else{
          new_node=idx_ptr;
          idx_ptr->next->prev=idx_ptr->prev;
          idx_ptr->prev->next=idx_ptr->next;
          free(new_node);
          
        }
   list_ptr->current_list_size =  list_ptr->current_list_size -1; 
    return hold;  // you must fix the return value
}

/* Obtains the length of the specified list, that is, the number of elements
 * that the list contains.
 *
 * list_ptr: pointer to list-of-interest.  
 *
 * Returns an integer equal to the number of elements stored in the list.  An
 * empty list has a size of zero.
 */
int list_size(list_t *list_ptr)
{
    assert(list_ptr != NULL);
    assert(list_ptr->current_list_size >= 0);
    return list_ptr->current_list_size;
}


/* This function verifies that the pointers for the two-way linked list are
 * valid, and that the list size matches the number of items in the list.
 *
 * If the linked list is sorted it also checks that the elements in the list
 * appear in the proper order.
 *
 * The function produces no output if the two-way linked list is correct.  It
 * causes the program to terminate and print a line beginning with "Assertion
 * failed:" if an error is detected.
 *
 * The checks are not exhaustive, so an error may still exist in the
 * list even if these checks pass.
 *
 * YOU MUST NOT CHANGE THIS FUNCTION.  WE USE IT DURING GRADING TO VERIFY THAT
 * YOUR LIST IS CONSISTENT.
 */
void list_debug_validate(list_t *L)
{
    list_node_t *N;
    int count = 0;
    assert(L != NULL); 
    if (L->head == NULL) 
	assert(L->tail == NULL && L->current_list_size == 0);
    else
	assert(L->head->prev == NULL);
    if (L->tail == NULL) 
	assert(L->head == NULL && L->current_list_size == 0);
    else
	assert(L->tail->next == NULL);
    if (L->current_list_size == 0) assert(L->head == NULL && L->tail == NULL);
    if (L->current_list_size == 1) {
        assert(L->head == L->tail && L->head != NULL);
        assert(L->head->next == NULL && L->head->prev == NULL);
        assert(L->head->data_ptr != NULL);
    }
    if (L->head == L->tail && L->head != NULL) assert(L->current_list_size == 1);
    assert(L->list_sorted_state == SORTED_LIST || L->list_sorted_state == UNSORTED_LIST);
    if (L->current_list_size > 1) {
        assert(L->head != L->tail && L->head != NULL && L->tail != NULL);
        N = L->head;
        while (N != NULL) {
            assert(N->data_ptr != NULL);
            if (N->next != NULL) assert(N->next->prev == N);
            else assert(N == L->tail);
            count++;
            N = N->next;
        }
        assert(count == L->current_list_size);
    }
    if (L->list_sorted_state == SORTED_LIST && L->head != NULL) {
        N = L->head;
        while (N->next != NULL) {
            assert(comp_proc(N->data_ptr, N->next->data_ptr) != -1);
            N = N->next;
        }
    }
}
/* commands for vim. ts: tabstop, sts: softtabstop sw: shiftwidth */
/* vi:set ts=8 sts=4 sw=4 et: */

