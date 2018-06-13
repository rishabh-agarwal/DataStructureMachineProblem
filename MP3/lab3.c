/* lab2.c
 * RISHABH AGARWAL
 * ECE 223 Spring 2014
 * MP2
 *
 * Propose: A template for MP2 
 *
 * Assumptions: This file is simple.  Input is collected and the
 * appropriate wifi function is called.
 *
 * The program accepts one command line arguement that is the size of the 
 * sorted list.
 *
 * The interactive menu input is provided.  
 *
 * Bugs: Some details have not been implemented.
 *
 * See the ECE 223 programming guide
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "datatypes.h"
#include "list.h"
#include "hpot_support.h"
clock_t start,end;
double elapse_time;


int main(int argc, char * argv[])
{
    list_t *list_sorted;
    list_t *list_unsorted;
    list_t *list_un_sorted;
    char line[MAXLINE];
    char command[MAXLINE];
    char junk[MAXLINE];
    int num_items;
    int sorted_size=0;
    int id;
     clock_t start,end;
    double elapse_time;

   
    printf("Welcome to lab2. Using list size: %d\n", sorted_size);
    
    /* this list should be sorted and the size of the list is limited */
    list_sorted = hpot_create();

    /* this list is unsorted and the list size is not limited */
    list_unsorted = hpot_create();

    list_un_sorted=hpot_create();
    /* remember fgets includes newline \n unless line too long */
    while (fgets(line, MAXLINE, stdin) != NULL) {
        num_items = sscanf(line, "%s%d%s", command, &id, junk);
        if (num_items == 1 && strcmp(command, "QUIT") == 0) {
            hpot_cleanup(list_sorted);
            hpot_cleanup(list_unsorted);
            hpot_cleanup(list_un_sorted);
            printf("Goodbye\n");
            break;
        } else if (num_items == 2 && strcmp(command, "INSERT") == 0) {
	    hpot_add(list_sorted,id);
	    
        } else if (num_items == 2 && strcmp(command, "LIST") == 0) {
	    hpot_list(list_sorted, id);
	    
        } else if (num_items == 2 && strcmp(command, "REMOVE") == 0) {
	    hpot_remove(list_sorted,id);
	    
        } else if (num_items == 2 && strcmp(command, "SCAN") == 0) {
	   hpot_scan(list_sorted,id);
	  
	} else if (num_items == 2 && strcmp(command, "SCANL") == 0) {
	   hpot_scanl(list_un_sorted,id);
	   
        } else if (num_items == 1 && strcmp(command, "STATS") == 0) {
	     hpot_stats(list_sorted, list_unsorted, list_un_sorted);
       
        } else if (num_items == 1 && strcmp(command, "PRINT") == 0) {
            hpot_print(list_sorted, "List"); 
        
        } else if (num_items == 1 && strcmp(command, "PRINTL") == 0) {
            hpot_print(list_un_sorted, "SQueue"); 
	    
        } else if (num_items == 2 && strcmp(command, "ADDTAIL") == 0) {
            hpot_add_tail(list_unsorted,id);
         
        } else if (num_items == 2 && strcmp(command, "APPENDL") == 0) {
            hpot_tail(list_un_sorted,id);
            
        } else if (num_items == 1 && strcmp(command, "RMHEAD") == 0) {
            hpot_remove_head(list_unsorted);
            
        } else if (num_items == 1 && strcmp(command, "PRINTQ") == 0) {
            hpot_print(list_unsorted, "Queue");
            
        } else if (num_items == 2 && strcmp(command, "SORTL") == 0) {
            int initialsize = list_size(list_un_sorted);
            start = clock();
            list_sort(list_un_sorted, id);
            end = clock();
            elapse_time = 1000.0 * ((double) (end - start)) / CLOCKS_PER_SEC;
            assert(list_size(list_un_sorted) == initialsize);
            printf("%d\t%f\t%d\n", initialsize, elapse_time, id);

         }else{
            printf("# %s", line);
        }
    }
    exit(0);
}
/* commands specified to vim. ts: tabstop, sts: soft tabstop sw: shiftwidth */
/* vi:set ts=8 sts=4 sw=4 et: */
