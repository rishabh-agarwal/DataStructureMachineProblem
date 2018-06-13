/* list.c                  <<-- A template to be updated and 
 * RISHABH AGARWAL        
 * ECE 223 Spring 2014
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

#define LIST_SORTED   -1234
#define LIST_UNSORTED -4132

/* prototypes for private functions used in list.c only */
void list_validate(list_t *L);

/* ----- below are the functions  ----- */

/* Allocates a new, empty list 
 *
 * By convention, the list is initially assumed to be sorted.  The field sorted
 * can only take values LIST_SORTED or LIST_UNSORTED
 *
 * The inital empty list must have
 * 1.  a dummy head llist_node_t
 * 2.  a dummy tail llist_node_t
 * 3.  llist_size = 0
 * 4.  llist_sort = LIST_SORTED
 *
 * Use list_decontruct to remove and deallocate all elements on a list,
 * the dummy head and tail, and the header block.
 */
list_t * list_construct(void)
{
    list_t *L;
    
    L = (list_t *) malloc(sizeof(list_t));
    L->llist_size = 0;
    L->llist_sort = LIST_SORTED;
    L->llist_head=(llist_node_t *)malloc(sizeof(llist_node_t));
    L->llist_tail=(llist_node_t *)malloc(sizeof(llist_node_t));
    
    // making packet next prev and data_t =NULL
    // for head
    L->llist_head->prev=NULL;
    L->llist_head->data_ptr=NULL;
    L->llist_head->next=L->llist_tail;
    // for tail
    L->llist_tail->next=NULL;
    L->llist_tail->data_ptr=NULL;
    L->llist_tail->prev=L->llist_head;
    

    /* the last line of this function must call validate */
    list_validate(L);
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
    list_validate(list_ptr);
    
     llist_node_t * temp_node=list_ptr->llist_head;
     while(list_ptr->llist_head != NULL)
     {
     list_ptr->llist_head=temp_node->next;
     free(temp_node->data_ptr);
     free(temp_node);
     temp_node=list_ptr->llist_head;
     }
     free(list_ptr);

}

/* Return an Iterator that points to the first element in the list.  If the
 * list is empty the pointer that is returned is equal to the dummy tail
 * llist_node_t.
 */
llist_node_t * list_iter_first(list_t *list_ptr)
{
    assert(list_ptr != NULL);
    list_validate(list_ptr);
    return list_ptr->llist_head->next;

}

/* Return an Iterator that always points to the dummy tail llist_node_t. 
 */
llist_node_t * list_iter_tail(list_t *list_ptr)
{
    assert(list_ptr != NULL);
    list_validate(list_ptr);
    return list_ptr->llist_tail;
}

/* Advance the Iterator to the next item in the list.  The Iterator must not be
 * pointing to the dummy tail llist_node_t.
 *
 * To determine if an Iterator is past the last element and pointing to the
 * tail comper the Iterator to list_iter_tail.  Only if they are equal has
 * the Iterator moved past the last element.
 *
 * It is only valid to compare the Iterator to list_iter_first or 
 * list_iter_tail
 *
 * It is a catastrophic error to call this function if the
 * iterator, idx_ptr, is null or points to the tail.
 */
llist_node_t * list_iter_next(llist_node_t * idx_ptr)
{
    assert(idx_ptr != NULL && idx_ptr->next != NULL);
    return idx_ptr->next;
}

/* Obtains a pointer to an element stored in the specified list, at the
 * specified Iterator position
 * 
 * list_ptr: pointer to list-of-interest.  A pointer to an empty list is
 *           obtained from list_construct.
 *
 * idx_ptr: pointer to position of the element to be accessed.  This pointer
 *          must be obtained from list_elem_find, list_iter_first, or
 *          list_iter_next.  
 *
 * return value: pointer to the data_t element found in the list at the 
 * iterator position. A value NULL is returned if 
 *     1.  the list is empty 
 *     2.  the idx_ptr points to the dummy head or dummy tail
 */
data_t * list_access(list_t *list_ptr, llist_node_t * idx_ptr)
{
    assert(list_ptr != NULL);
    //assert(idx_ptr != NULL);
    if(idx_ptr==NULL)
    return NULL;
    else if (list_ptr->llist_head->next==list_ptr->llist_tail && list_ptr->llist_tail->prev==list_ptr->llist_head)
    return NULL;
    /* debugging function to verify that the structure of the list is valid */
    list_validate(list_ptr);

    return idx_ptr->data_ptr;   // you have to fix the return value
}

/* Finds an element in a list and returns a pointer to it.
 *
 * list_ptr: pointer to list-of-interest.  
 *
 * elem_ptr: element against which other elements in the list are compared.
 *           Note: uses the compare function defined in datatypes.h
 *
 * The function returns an Iterator pointer to the llist_node_t that contains 
 * the first matching element if a match if found.  If a match is not found 
 * the return value is NULL.
 *
 * Note: to get a pointer to the matching data_t memory block pass the return
 *       value from this function to the list_access function.
 */
llist_node_t * list_elem_find(list_t *list_ptr, data_t *elem_ptr)
{   
    list_validate(list_ptr);
    llist_node_t *fnode;
    fnode=list_ptr->llist_head->next;
    int count, list_size ;
    count = 0;
    list_size = list_ptr->llist_size;
    while(count != list_size)
    {
     if(comp_proc(elem_ptr,fnode->data_ptr)==0)
     {
     return fnode;
     }
     count++;
     fnode=fnode->next;
    }
    
    return NULL;
}

/* Inserts the data element into the list in front of the llist_node_t 
 * iterator position.
 *
 * list_ptr: pointer to list-of-interest.  
 *
 * elem_ptr: pointer to the element to be inserted into list.
 *
 * idx_ptr: pointer to a llist_node_t.  The element is to be inserted as a 
 *          member in the list at the position that is immediately in front 
 *          of the position of the provided Iterator pointer.
 *
 * If idx_ptr is set using 
 *    -- list_iter_first, then the new element becomes the first item in 
 *       the list.
 *    -- list_iter_tail, then the new element becomes the last item in 
 *       the list.
 *    -- for any other idx_ptr, the new element is insert before the 
 *       Iterator
 *
 * For example, to insert at the tail of the list do
 *      list_insert(mylist, myelem, list_iter_tail(mylist))
 * to insert at the front of the list do
 *      list_insert(mylist, myelem, list_iter_first(mylist))
 *
 * Note that use of this function results in the list to be marked as unsorted,
 * even if the element has been inserted in the correct position.  That is, on
 * completion of this subroutine the list_ptr->llist_sort must be equal 
 * to LIST_UNSORTED.                                  
 */
void list_insert(list_t *list_ptr, data_t *elem_ptr, llist_node_t * idx_ptr)
{
    assert(list_ptr != NULL);
    llist_node_t *new_node;
    new_node=(llist_node_t *)malloc(sizeof(llist_node_t));
    // --------------------If the list is EMPTY-------------------
    if(list_ptr->llist_size==0)
    {
      new_node->next=list_ptr->llist_tail;
      new_node->prev=list_ptr->llist_head;
      new_node->data_ptr=elem_ptr;
      list_ptr->llist_head->next=new_node;
      list_ptr->llist_tail->prev=new_node;
      list_ptr->llist_size++;
    }
    //-------------------INSERTING AFTER idx_ptr------------------
    else{
    new_node->next=idx_ptr;
    new_node->prev=idx_ptr->prev;
    new_node->data_ptr=elem_ptr;
    idx_ptr->prev->next=new_node;
    idx_ptr->prev=new_node;
    list_ptr->llist_size++;
    }
    /* the last two lines of this function must be the following */
    if (list_ptr->llist_sort == LIST_SORTED) 
        list_ptr->llist_sort = LIST_UNSORTED;
        list_validate(list_ptr);
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
 * must generate a system error and the program should immediately stop.
 *
 * The comparison procedure must accept two arguments (A and B) which are both
 * pointers to elements of type data_t.  The comparison procedure returns an
 * integer code which indicates the precedence relationship between the two
 * elements.  The integer code takes on the following values:
 *    1: A should be closer to the list head than B
 *   -1: B should be closer to the list head than A
 *    0: A and B are equal in rank
 *
 * Note: if the element to be inserted is equal in rank to an element already
 * in the list, the newly inserted element will be placed after all the
 * elements of equal rank that are already in the list.
 */
void list_insert_sorted(list_t *list_ptr, data_t *elem_ptr)
{   
   
    assert(list_ptr != NULL);
    assert(list_ptr->llist_sort == LIST_SORTED);
    
   
    llist_node_t * temp_node;
    temp_node=(llist_node_t *)malloc(sizeof(llist_node_t));
    
    // Insert a new node if no node
   if(list_ptr->llist_size==0)
	{
	temp_node->next=list_ptr->llist_tail;
	temp_node->prev=list_ptr->llist_head;
	temp_node->data_ptr=elem_ptr;
	list_ptr->llist_head->next=temp_node;
	list_ptr->llist_tail->prev=temp_node;
	list_ptr->llist_size++;
	}
	     
	
    else{  // if having more than one 1 node
        llist_node_t *rover;
        rover=list_ptr->llist_head->next;
       
      	 while(rover != list_ptr->llist_tail)
      	 {
      	  if(comp_proc(elem_ptr,rover->data_ptr)==1)
      	    {
      	      temp_node->data_ptr=elem_ptr;
      	      temp_node->next=rover;
      	      temp_node->prev=rover->prev;
      	      rover->prev->next=temp_node;
	      rover->prev=temp_node;
	      list_ptr->llist_size++;       
	      break;
            }
       
            rover=rover->next;
         
          if(rover==list_ptr->llist_tail)
           {
              temp_node->data_ptr=elem_ptr;
      	      temp_node->next=rover;
      	      temp_node->prev=rover->prev;
      	      rover->prev->next=temp_node;
	      rover->prev=temp_node;
	      list_ptr->llist_size++; 
           }
         }
        }
       
     
  if (list_ptr->llist_sort == LIST_UNSORTED) 
        list_ptr->llist_sort = LIST_SORTED;
    /* the last line of this function must be the following */
    list_validate(list_ptr);
}

/* Removes the element from the specified list that is found at the 
 * Iterator llist_node_t index.  A pointer to the data element is returned.
 *
 * list_ptr: pointer to list-of-interest.  
 *
 * idx_ptr: pointer to position of the element to be accessed.  This pointer
 *          must be obtained from list_elem_find, list_iter_first, 
 *          list_iter_next, or list_iter_tail.  
 *
 * If the list is empty, then the function should return NULL.
 *
 * Note: it is easy to remove the element at the front of the list using
 *     list_remove(mylist, list_iter_first(mylist))
 *
 * However, removing the element at the end of the list is not easy since
 * there is no way to get the pointer to the last element in the list.  
 * Notice that list_iter_tail returns a pointer to the dummy tail, not the 
 * last element in the list.
 *
 * Note: a significant danger with this function is that once
 * an element is removed from the list, the idx_ptr is dangling.  That
 * is, the idx_ptr now points to memory that is no longer valid.
 * You should not call list_iter_next on an iterator after there
 * has been a call to list_remove with the same iterator.
 *
 * When you remove the llist_node_t in this function, you should null the next
 * and prev pointers before you free the memory block to avoid accidental use
 * of these now invalid pointers. 
 */
data_t * list_remove(list_t *list_ptr, llist_node_t * idx_ptr)
{
    if (idx_ptr == NULL || list_ptr->llist_size==0)
        return NULL;
    assert(idx_ptr != list_ptr->llist_head && idx_ptr != list_ptr->llist_tail);
        
          llist_node_t* new_node;
        
        if (list_ptr->llist_size==1)
        {
        new_node=idx_ptr;
        list_ptr->llist_head->next=list_ptr->llist_tail;
        list_ptr->llist_tail->prev=list_ptr->llist_head;
        free(new_node->data_ptr);
        free(new_node);       
        }
        else{
          new_node=idx_ptr;
          idx_ptr->next->prev=idx_ptr->prev;
          idx_ptr->prev->next=idx_ptr->next;
          idx_ptr->next=NULL;
          idx_ptr->prev=NULL;
          free(new_node->data_ptr);
          free(new_node);
          }
          list_ptr->llist_size =  list_ptr->llist_size -1; 

    /* the last line should verify the list is valid after the remove */
    list_validate(list_ptr);
    return idx_ptr->data_ptr;  // you must fix the return value
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
    assert(list_ptr->llist_size >= 0);
    return list_ptr->llist_size;
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
void list_validate(list_t *L)
{
    llist_node_t *N;
    int count = 0;
    assert(L != NULL && L->llist_head != NULL && L->llist_tail != NULL);
    assert(L->llist_head != L->llist_tail);
    assert(L->llist_head->prev == NULL && L->llist_tail->next == NULL);
    assert(L->llist_head->data_ptr == NULL && L->llist_tail->data_ptr == NULL);
    assert(L->llist_head->next != NULL && L->llist_tail->prev != NULL);
    assert(L->llist_sort == LIST_SORTED || L->llist_sort == LIST_UNSORTED);

    N = L->llist_head->next;
    assert(N->prev == L->llist_head);
    while (N != L->llist_tail) {
        assert(N->data_ptr != NULL);
        assert(N->next->prev == N);
        count++;
        N = N->next;
    }
    assert(count == L->llist_size);
    if (L->llist_sort == LIST_SORTED && L->llist_size > 0) {
        N = L->llist_head->next;
        while (N->next != L->llist_tail) {
            assert(comp_proc(N->data_ptr, N->next->data_ptr) != -1);
            N = N->next;
        }
    }
}
/* commands for vim. ts: tabstop, sts: softtabstop sw: shiftwidth */
/* vi:set ts=8 sts=4 sw=4 et: */

