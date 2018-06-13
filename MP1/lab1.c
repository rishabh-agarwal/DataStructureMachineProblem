/* lab1.c
 * Prof. Russell 
 * ECE 223 Fall 2013
 * MP1
 *
 * Propose: A template for MP1 
 *
 * Assumptions: Many details are incomplete.  The functions to collect input
 * for a record and to print a record specify the format that is required for
 * grading.
 *
 * The program accepts one command line arguement that is the size of the list.
 *
 * An outline for the interactive menu input is provided.  Details need to be
 * completed but format of the commands and the responses should not be
 * changed.
 *
 * Bugs: Many detail have not been implemented.
 *
 * See the ECE 223 programming guide
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "wifilist.h"

#define MAXLINE 256

// function prototypes for lab1.c
void fill_wifi_record(struct wifi_info_t *new);
void print_wifi_rec(struct wifi_info_t *rec);

int main(int argc, char *argv[])
{
    char line[MAXLINE];
    char command[MAXLINE];
    char junk[MAXLINE];
    int list_size = -1;
    int num_items;
    int wifi_id;
    int i;
    struct wifi_info_t *rec_ptr = NULL;

    if (argc != 2) {
        printf("Usage: ./lab1 list_size\n");
        exit(1);
    }
    list_size = atoi(argv[1]);
    if (list_size < 1) {
        printf("lab1 has invalid list size: %d\n", list_size);
        exit(2);
    }
    printf("Welcome to lab1. Using list size: %d\n", list_size);

    /* remember fgets includes newline \n unless line too long */
    while (fgets(line, MAXLINE, stdin) != NULL) {
        num_items = sscanf(line, "%s%d%s", command, &wifi_id, junk);
        if (num_items == 1 && strcmp(command, "QUIT") == 0) {
            printf("Goodbye\n");
            break;
        } else if (num_items == 2 && strcmp(command, "ADD") == 0) {
            int added_return = -2;
            rec_ptr = (struct wifi_info_t *) malloc(sizeof(struct wifi_info_t));
            fill_wifi_record(rec_ptr);
            if (added_return == 1) {
                printf("Inserted: %d\n", wifi_id);
            } else if (added_return == 0) {
                printf("Updated: %d\n", wifi_id);
            } else if (added_return == -1) {
                printf("Rejected: %d\n", wifi_id);
            } else {
                printf("Error with return value!\n");
            }
        } else if (num_items == 2 && strcmp(command, "FIND") == 0) {
            if (rec_ptr == NULL) {
                printf("Did not find: %d\n", wifi_id);
            } else {
                /* print items in structure */
                print_wifi_rec(rec_ptr);
            }
            rec_ptr = NULL;
        } else if (num_items == 2 && strcmp(command, "DEL") == 0) {
            rec_ptr = NULL;
            if (rec_ptr == NULL) {
                printf("Did not remove: %d\n", wifi_id);
            } else {
                printf("Removed: %d\n", wifi_id);
            }
            rec_ptr = NULL;
        } else if (num_items == 1 && strcmp(command, "STATS") == 0) {
            // get the number in list and size of the list
            int num_in_list = 0;
            int size_of_list = 0;
            printf("Number records: %d, Array size: %d\n", 
                    num_in_list, size_of_list);
        } else if (num_items == 1 && strcmp(command, "PRINT") == 0) {
            int num_in_list = 0;
            if (num_in_list == 0) {
		printf("List empty\n");
	    } else {
                printf("%d records\n", num_in_list);
                for (i = 0; i < num_in_list; i++) {
                    printf("%d: ", i+1);
                    // you must use this function to format output for a record
                    // print_wifi_rec(rec_ptr);
                }
            }
        } else {
            printf("# %s", line);
        }
    }
    exit(0);
}

/* Prompts user for WiFi record input starting with the Mobile's IP address.
 * The input is not checked for errors but will default to an acceptable value
 * if the input is incorrect or missing.
 *
 * The input to the function assumes that the structure has already been
 * created.  The contents of the structure are filled in.
 *
 * There is no output.
 */
void fill_wifi_record(struct wifi_info_t *new)
{
    char line[MAXLINE];
    char str[MAXLINE];
    char letter;
    assert(new != NULL);

    printf("IP address:");
    fgets(line, MAXLINE, stdin);
    sscanf(line, "%d", &new->ip_address);
    printf("Access point IP address:");
    fgets(line, MAXLINE, stdin);
    sscanf(line, "%d", &new->access_point);

    printf("Authenticated (T/F):");
    fgets(line, MAXLINE, stdin);
    sscanf(line, "%s", str);
    if (strcmp(str, "T")==0 || strcmp(str, "t")==0)
	new->authenticated = 1;
    else
	new->authenticated = 0;

    printf("Privacy (none|WEP|WPA|WPA2):");
    fgets(line, MAXLINE, stdin);
    sscanf(line, "%s", str);
    if (strcmp(str, "WEP")==0)
	new->privacy = 1;
    else if (strcmp(str, "WPA")==0)
	new->privacy = 2;
    else if (strcmp(str, "WPA2")==0)
	new->privacy = 3;
    else
	new->privacy = 0;


    printf("Standard letter (a b e g h n s):");
    fgets(line, MAXLINE, stdin);
    sscanf(line, "%c", &letter);
    if (letter < 'a' || letter > 'z')
	letter = 'a';
    new->standard_letter = letter - 'a';

    printf("Band (2.4|5.0):");
    fgets(line, MAXLINE, stdin);
    sscanf(line, "%f", &new->band);

    printf("Channel:");
    fgets(line, MAXLINE, stdin);
    sscanf(line, "%d", &new->channel);

    printf("Data rate:");
    fgets(line, MAXLINE, stdin);
    sscanf(line, "%f", &new->data_rate);

    printf("Time received (int):");
    fgets(line, MAXLINE, stdin);
    sscanf(line, "%d", &new->time_received);
    printf("\n");
}

/* print the information for a particular WiFi record 
 *
 * Input is a pointer to a record, and no entries are changed.
 *
 */
void print_wifi_rec(struct wifi_info_t *rec)
{
    const char *pri_str[] = {"none", "WEP", "WPA", "WPA2"};
    assert(rec != NULL);
    printf("eth: %d,", rec->eth_address);
    printf(" MIP: %d, AID: %d,", rec->ip_address, 
            rec->access_point);
    printf(" Auth: %s,", rec->authenticated ? "T" : "F"); 
    printf(" Pri: %s, L: %c, B: %g, C: %d,", pri_str[rec->privacy], 
            (char) (rec->standard_letter + 'a'), rec->band, rec->channel);
    printf(" R: %g", rec->data_rate);
    printf(" Time: %d\n", rec->time_received);
}


/* commands specified to vim. ts: tabstop, sts: soft tabstop sw: shiftwidth */
/* vi:set ts=8 sts=4 sw=4 et: */
