/* RISHABH AGARWAL       MP1
   lab1.c template
 * 
 * ECE 223 Spring 2014
 * MP1
 * Subject: ECE223-1,#1
 *
 * Version 1
 *
 * Purpose: A template for MP1 
 *
 * Assumptions: Many details are incomplete.  The functions to collect input
 * for a record and to print a record specify the format that is required for
 * grading.
 *
 * The program accepts one command line arguement that is the size of the list.
 *
 * An outline for the interactive menu input is provided.  Details need to be
 * completed but the format of the commands and the prints found in 
 * hpot_record_fill hpot_print_rec should not be changed.
 *
 * Bugs: Many detail have not been implemented.
 *
 * See the ECE 223 programming guide
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "honeypot.h"

int main(int argc, char **argv)
{
    struct packet_t *new_rec;
    char line[MAXLINE];
    char command[MAXLINE];
    char junk[MAXLINE];
    int num_items;
    int ip_add;
    int index;
    int list_size;
    struct honeypot_t *list;
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
     list=hpot_construct(list_size);
    while (fgets(line, MAXLINE, stdin) != NULL) {
        num_items = sscanf(line, "%s%d%s", command, &ip_add, junk);
        if (num_items == 1 && strcmp(command, "QUIT") == 0) {
            hpot_destruct(list);
             free(new_rec);
            printf("cleanup\n");
            break;
        } else if (num_items == 2 && strcmp(command, "INSERT") == 0) {
            int add_return = -3;
            new_rec = (struct packet_t *) malloc(sizeof(struct packet_t));
            new_rec->dest_ip_addr=ip_add;
            hpot_record_fill(new_rec);
            add_return=hpot_add(list , new_rec);
            if (add_return == 1) {
                printf("\nAdded: %d and doubled list size\n",ip_add);
            } else if (add_return == 0) {
                printf("\nAdded: %d\n",ip_add);
            } else {
                printf("\n\nError with hpot_add return value\n");
                exit(1);
            }
        } else if (num_items == 2 && strcmp(command, "LIST") == 0) {
            index=hpot_lookup(list,ip_add);
            new_rec=hpot_access(list,index);
            if (index == -1 ) {
                printf("Did not find: %d\n", ip_add);
            } else {
                hpot_print_rec(new_rec);
                printf("Found %d packets matching %d\n", index, ip_add);
            }
        } else if (num_items == 2 && strcmp(command, "REMOVE") == 0) {
            index=hpot_lookup(list,ip_add);
            new_rec=hpot_remove(list,ip_add);
            if (index == -1) {
                printf("Did not remove: %d\n", ip_add);
            } else {
                printf("Removed %d packets matching %d\n", index, ip_add);
            }
        } else if (num_items == 2 && strcmp(command, "SCAN") == 0) {
            
            int groups = 0;
            int i=0,count=1,number_n=0,flag=0;
            // for each group that is removed print how many removed
            
            for(i=0;i<list->pot_entries;i++)
            {
            flag=0;
            new_rec=hpot_access(list,i);
            
            if(new_rec!=NULL && hpot_access(list,i+1)!= NULL  &&  new_rec->dest_ip_addr == hpot_access(list,i+1)->dest_ip_addr )
                {
                
                count++;
                  if(count >=ip_add)
                  {
                    number_n=count;
                    //number_n++;
                    
                  }          
                }
            if (new_rec!=NULL  && hpot_access(list,i+1)!= NULL && new_rec->dest_ip_addr != hpot_access(list,i+1)->dest_ip_addr && number_n >= ip_add && count!=1)
            {
              printf("A set with address %d has %d packets\n", new_rec->dest_ip_addr, number_n);
            // after all sets have been removed print how many sets
            groups++;
              count = 1;
              flag=1;
            }
            if(number_n >= ip_add && hpot_access(list,i+1)== NULL)
                 {
                    printf("A set with address %d has %d packets\n", new_rec->dest_ip_addr, number_n);
                    groups++;
                    // after all sets have been removed print how many sets
                count = 1;
                flag=1;
                 }
                if(new_rec!=NULL  && hpot_access(list,i+1)!= NULL && new_rec->dest_ip_addr != hpot_access(list,i+1)->dest_ip_addr && flag==0)count=1;
           }
            if (groups > 0) 
                printf("Found %d sets\n", groups);
            else
                printf("No records with >= %d matches\n", ip_add);
        } else if (num_items == 1 && strcmp(command, "PRINT") == 0) {
            int num_in_list = 0;
            num_in_list= hpot_count(list);
            if (num_in_list == 0) {
                printf("List empty\n");
            } else {
                printf("%d records\n", num_in_list);
                int i;
                for (i = 0; i < num_in_list; i++) {
                    printf("%d: ", i+1);
                    // you must use this function to format output for a record
                    hpot_print_rec(list->hpot_ptr[i]);
                }
            }
        } else {
            printf("# %s", line);
        }
    }
    exit(0);
}

