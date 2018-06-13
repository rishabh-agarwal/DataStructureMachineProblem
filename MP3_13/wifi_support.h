/* wifi_support.h 
 * Prof. Russell 
 * ECE 223 Fall 2013 
 * MP2
 *
 * Propose: A template for MP2 
 *
 * Assumptions: structure definitions and public functions as defined for
 * assignmnet.  There are no extensions.
 *
 * Bugs:
 *
 * You may change this file if needed for your design.
 */

#define MAXLINE 180

/* prototype function definitions */

/* function to compare WiFi records */
int wifi_compare(wifi_info_t *rec_a, wifi_info_t *rec_b);

/* functions to create and cleanup a WiFi list */
List wifi_create();
void wifi_cleanup(List);

/* Functions to get and print WiFi information */
void wifi_record_fill(wifi_info_t *rec);   /* collect input from user */
void wifi_record_print(wifi_info_t *rec);  /* print one record */
void wifi_print(List list_ptr, char *);      /* print list of records */

/* functions for sorted list with a maximum size */
void wifi_add(List , int, int);
void wifi_lookup(List , int);
void wifi_remove(List , int);
void wifi_stats(List , List );

/* functions for unsorted FIFO list that has no limit of the size of the list,
 * inserts at the tail, removes at the head, 
 */
void wifi_add_tail(List , int);
void wifi_remove_head(List );
void wifi_drop_max(List);

/* commands specified to vim. ts: tabstop, sts: soft tabstop sw: shiftwidth */
/* vi:set ts=8 sts=4 sw=4 et: */