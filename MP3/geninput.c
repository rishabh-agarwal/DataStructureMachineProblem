/* geninput.c
 * MP3
 * Harlan Russell
 * ECE 223, Spring 2014
 *
 * Compile with (link the math library)
 *     gcc -g -Wall geninput.c -o geninput -lm
 *
 * Purpose: Generate an input file for MP3 
 * Assumptions: Input file is for testing sort.  Creates
 *              an unsorted list, uses APPENDL to insert items, and
 *              calls SORTL to sort the list
 *
 * Command line arguments:
 *    1st -- number of records to create
 *    2nd -- type of list to create
 *           1: random addresses [0, 3/4 number records)
 *           2: assending and sequential
 *           3: descending and sequential
 *    3rd -- type of sort
 *           1: Insertion
 *           2: Recursive Selection
 *           3: Iterative Selection
 *           4: Merge
 *
 * Pipe the output of this program into lab3. For example
 *     ./geninput 10000 1 1 | ./lab3
 *
 * See also mp3test.sh 
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[])
{
    int records, list_type = -1, sort_type = -1;
    int addr_range;
    int eth_addr;

    if (argc !=4) {
        printf("Usage: ./geninput listsize listype sorttype\n");
        printf("\tlistsize: number of records to create\n");
        printf("\tlisttype: {1, 2, 3} for random, ascending or descending\n");
        printf("\tsorttype: 1: Insertion\n");
        printf("\t          2: Recursive Selection\n");
        printf("\t          3: Iterative Selection\n");
        printf("\t          4: Merge\n");
        exit(1);
    }
    records = atoi(argv[1]);
    if (records < 2) {
        printf("genniput has invalid number records: %d\n", records);
        exit(2);
    }
    list_type = atoi(argv[2]);
    sort_type = atoi(argv[3]);
    if (sort_type < 1 || sort_type > 4) {
        printf("genniput has invalid type of sort: %d\n", sort_type);
        exit(2);
    }
    addr_range = records * 0.75;
    srand48(22);

    int i;
    if (list_type == 1) {
        // random addresses, 
        for (i = 0; i < records; i++) {
            eth_addr = (int) (addr_range * drand48()) + 1;
            printf("APPENDL %d\n", eth_addr);
        }
        printf("SORTL %d\n", sort_type);
        int matches = 5;
        if (records >= 1000) {
            matches = log10(records) + 3;
        }
        printf("SCANL %d\n", matches);
        printf("QUIT\n");
    }
    else if (list_type == 2) {
        // ascending addresses
        for (i = 0; i < records; i++) {
            printf("APPENDL %d\n", i+1);
        }
        printf("SORTL %d\n", sort_type);
        printf("QUIT\n");
    }
    else if (list_type == 3) {
        // descending addresses
        for (i = 0; i < records; i++) {
            printf("APPENDL %d\n", records - i);
        }
        printf("SORTL %d\n", sort_type);
        printf("QUIT\n");
    }
    else {
        printf("geninput has invalid list type: %d\n", list_type);
        exit(3);
    }
    exit(0);
}

