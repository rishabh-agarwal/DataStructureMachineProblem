/* 

   Writing and debugging MP2 is challenging, and it is particularly hard if you
   try and write all the code before you do any testing. It is much easier to
   break the problem into small pieces and test each piece. 

   For MP2, one approach is to write list_insert first, since it might be the
   easiest algorithm and it depends only on list_construct.

   Then add a main section to list.c. This main is for testing only, and you
   will delete it before moving on to test wifi_support.c or lab2.c. Below is a
   simple example that allocates a few structures and inserts them into a list.

   Note we are "cheating" in that this test code uses eth_address, and code
   in list.c is not permitted to access the elements in a data_t structure.
   However, you will delete this test code before submitting, so during
   development it is a convenient shortcut.

   With the main section added to list.c, you can compile and run list.c on its
   own using 
   gcc -Wall -g list.c wifi_support.c -o listtest

   The linker needs to find the comp_proc function and it is found in the 
   template wifi_support.c file (with no changes) 

*/

#include <stdlib.h>
#include <stdio.h>
#include "datatypes.h"
#include "list.h"

/* prototype for list debug print */
void list_debug_print(list_t *list_ptr);

int main(void)
{
    data_t *datap, *foundp;
    list_t *Lunsortedp;
    Lunsortedp = list_construct();

    // create item to test list_insert
    datap = (data_t *) malloc(sizeof(data_t));
    datap->eth_address = 555;
    list_insert(Lunsortedp, datap, list_iter_front(Lunsortedp));
    datap = NULL;

    // test list_access 
    datap = list_access(Lunsortedp, list_iter_front(Lunsortedp));
    printf("first test should find 555 and found (%d)\n\n", datap->eth_address);
    datap = NULL;

    // insert in front of the item at the back
    datap = (data_t *) malloc(sizeof(data_t));
    datap->eth_address = 444;
    list_insert(Lunsortedp, datap, list_iter_back(Lunsortedp));
    datap = NULL;

    // insert as the new tail 
    datap = (data_t *) malloc(sizeof(data_t));
    datap->eth_address = 500;
    list_insert(Lunsortedp, datap, NULL);
    datap = NULL;


    // Test use of Iterator to find all three and print 
    Iterator my_index;
    my_index = list_iter_front(Lunsortedp);

    datap = list_access(Lunsortedp, my_index); 
    printf("Second test\nPosition 0 should find 444 and found (%d)\n", datap->eth_address);
    my_index = list_iter_next(my_index);
    datap = list_access(Lunsortedp, my_index);
    printf("Position 1 should find 555 found (%d)\n", datap->eth_address);
    my_index = list_iter_next(my_index);
    datap = list_access(Lunsortedp, my_index);
    printf("Position 2 should find 500 and found (%d)\n", datap->eth_address);

    // Next try to use list_debug_print 
    printf("\nTest of list print\n\n");
    list_debug_print(Lunsortedp);

    // list element find example 

    /* Uncomment this section when you are ready to test list_elem_find 

       datap = (data_t *) malloc(sizeof(data_t));
       datap->eth_address = 444;
       my_index = list_elem_find(Lunsortedp, datap);
       foundp = list_access(Lunsortedp, my_index);
       printf("\nTest of list elem find\n");
       if (my_index != NULL)
       printf("looked for %d and found %d\n",
       datap->eth_address, foundp->eth_address);
       else
       printf("looked for %d and did not find \n", datap->eth_address);
       free(datap);  // but not foundp
       datap = foundp = NULL;
       */

    list_destruct(Lunsortedp);
    return 0;
}

/*

   Next you will want to write your own list_debug_print function to print a
   list. Then you can do "before and after" testing. That is, print the list
   before a change, and print the list after the change to verify that the
   change worked.

   Something like

*/

void list_debug_print(list_t *list_ptr) {
    list_node_t *L;
    int count;

    printf("List size: %d\n", list_ptr->current_list_size);
    L = list_ptr->head;
    count = 0;
    while(L != NULL) {
        printf("Pos: %d contains IP: %d\n", count, L->data_ptr->eth_address);
        L = L->next;
        count++;
    }
    if (count != list_ptr->current_list_size)
        printf("Hey!! the list size is wrong! count is %d\n", count);
}

