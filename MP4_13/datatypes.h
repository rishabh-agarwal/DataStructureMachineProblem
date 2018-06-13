/* datatypes.h 
 * Lab4: Dynamic Memory Allocation
 * Version: 1
 * ECE 223, Fall 2013
 *
 * The list ADT is needed to support the equilibrium test driver.
 * 
 * We need to set up two definitions to use the list ADT defined in list.c and
 * list.h
 *
 * data_t: The type of data that we want to store in the list
 *
 * comp_proc(A, B): the function to compare two data_t structures 
 */

/* include the definitions of the data we want to store in the list */

/* a dummy definition as MP4 creates arrays with a dynamic size */
typedef struct int_tab {
    int i;
} int_t;

/* the list ADT works on data of this type */
typedef int_t data_t;

/* the comparison procedure is found in lab4.c */
#define comp_proc(x, y) (int_compare(x, y))

/* commands specified to vim. ts: tabstop, sts: soft tabstop sw: shiftwidth */
/* vi:set ts=8 sts=4 sw=4 et: */
