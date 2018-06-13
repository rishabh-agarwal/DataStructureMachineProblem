/* wifi_support.h       <<-- A template
 * Prof. Russell        <<-- some changes needed
 * ECE 223 Spring 2014 
 * MP2
 *
 * Propose: A template for MP2 
 *
 * Assumptions: suggested structure definitions and public functions 
 *              as defined for assignmnet.  
 *
 *              You may change this file if needed for your design.
 *
 * Bugs:
 *
 */

#define MAXLINE 170

/* prototype function definitions */

/* function to compare packet records */
int hpot_compare(packet_t *rec_a, packet_t *rec_b);

/* functions to create and cleanup a Honeypot list */
pList hpot_create();
void hpot_cleanup(pList);

/* Functions to get and print packet information */
void hpot_record_fill(packet_t *rec);   /* collect input from user */
void hpot_record_print(packet_t *rec);  /* print one record */
void hpot_print(pList list_ptr, char *); /* print list of records */
void hpot_stats(pList, pList);            /* prints size of each list */

/* functions for sorted list */
void hpot_add(pList , int);
void hpot_list(pList , int);
void hpot_remove(pList , int);
void hpot_scan(pList , int);

/* functions for unsorted list 
 * inserts at the tail, removes at the head, 
 * Duplicate packets with the same destination IP address are not
 * permitted.  If a new packet is inserted the old one must be 
 * recycled
 */
void hpot_add_tail(pList , int);
packet_t *hpot_remove_head(pList );

/* commands for vim. ts: tabstop, sts: soft tabstop sw: shiftwidth */
/* vi:set ts=8 sts=4 sw=4 et: */
