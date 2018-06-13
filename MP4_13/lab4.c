/* lab4.c
 * Lab4: Dynamic Memory Allocation
 * Version: 1
 * ECE 223, Fall 2013
 *
 * This file contains drivers to test the mem.c package for dynamic memory
 * allocation.
 * 
 * The following parameters can be set on the command line.  If not set,
 * default values are used.  
 *
 * If different options are implemented for the memory package, this provides a
 * simple mechanism to change the options.  
 *
 * -f best|first  search policy to find memory block (first by default)
 * -c             turn on coalescing (off by default)
 *
 * General options for all test drivers
 * -s 19283  random number generator seed
 * -v        verbose
 *
 * The Unit test drivers.  Two example drivers are provided.  You MUST
 *           add one or more additional unit drivers for more detailed testing
 * 
 * -u 0      Tests one allocation for 16 bytes
 * -u 1      Tests 4 allocations including a new page
 *           The student must update this driver to match the details of
 *           his or her design.
 *
 * -u ?      The student is REQUIRED to add additional drivers
 *
 * The equilibrium test driver.  See comments with equilibriumDriver below for
 * additional options.
 * -e        run equilibrium test driver
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <ctype.h>
#include <malloc.h>    // OSX users may need to comment out this include
#include <time.h>

#include "datatypes.h"
#include "list.h"
#include "mem.h"

// Global variables first defined in mem.h 
int SearchPolicy = BEST_FIT;
int RovingPolicy = ROVER;
int Coalescing = FALSE;

// structure for equilibrium driver parameters 
typedef struct {
    int Seed;
    int Verbose;
    int EquilibriumTest;
    int WarmUp;
    int Trials;
    int AvgNumInts;
    int RangeInts;
    int SysMalloc;
    int UnitDriver;
} driver_params;

// prototypes for functions in this file only 
void getCommandLine(int argc, char **argv, driver_params *ep);
void equilibriumDriver(driver_params *ep);

int main(int argc, char **argv)
{
    driver_params dprms;
    getCommandLine(argc, argv, &dprms);
    printf("Seed: %d\n", dprms.Seed);
    srand48(dprms.Seed);

    // The three major choices: search policy, starting location, and 
    // coalescing option 
    if (SearchPolicy == BEST_FIT) printf("Best-fit search policy");
    else if (SearchPolicy == FIRST_FIT) printf("First-fit search policy");
    else {
        fprintf(stderr, "Error with undefined search policy\n");
        exit(1);
    }
    if (RovingPolicy == ROVER) printf(" starting at rover");
    else if (RovingPolicy == HEAD) printf(" starting at head");
    else {
        fprintf(stderr, "Error with undefined roving policy\n");
        exit(1);
    }
    if (Coalescing == TRUE) printf(" using coalescing\n");
    else if (Coalescing == FALSE) printf(" without coalescing\n");
    else {
        fprintf(stderr, "Error specify coalescing policy\n");
        exit(1);
    }



    // unit driver 0: basic test with one allocation and free
    if (dprms.UnitDriver == 0)
    {
        printf("\n----- Begin unit test driver 0 -----\n");
        char *string;
        const char msg[] = "hello world 15c";
        // add one for null character at end of string 
        string = (char *) Mem_alloc((strlen(msg)+1) * sizeof(char));
        int len = strlen(msg);
        strcpy(string, msg);
        printf("string length=%d\n:%s:\n", len, string);
        printf("\nFree list after first allocation\n");
        Mem_stats();
        Mem_print();
        Mem_free(string);
        printf("\nFree list after first free\n");
        Mem_stats();
        Mem_print();
        string = NULL;
        printf("\n----- End unit test driver 0 -----\n");
    }
    else if (dprms.UnitDriver == 1)
    {
        /* Here is an example of a unit test driver.

           This is a specific example of the general statement made in the
           MP4.pdf file, in the section "Testing and performance evaluation".
           This test makes three allocations from the free list with the goal
           of making the third allocation the correct size so that the free
           list is left empty. To get this test to work with your code you need
           to determine two values.

           First, what size is your chunk_t?  It is the result of this: 
               printf("The size of chunk_t is %d bytes\n", sizeof(chunk_t)); 

           Next, how many units are in the free list if you start with one page?
           a.  if your chunk_t is 8 bytes, then 4096/8 = 512 units
           b.  if you chunk_t is 16 bytes, then 4096/16 = 256
           c.  if you made a one unit dummy entry for your circular linked 
               list then the units available is one less than in a, or b.

           so set 
           unit_size = 8 or 16 depending on your chunk_t size
           init_size_free_list = 512, 511, 256, or 255 
               depending on your implementation
        */

        // you must modify this driver for your design

        // unit_size is 8 or 16 depending on your chunk_t size
        int unit_size = 8;
        // init_size_free_list might be 512, 511, 256, or 255 
        // depending on your implementation
        int init_size_free_list = 512;

        int *p1, *p2, *p3, *p4;
        int num_bytes_1, num_bytes_2, num_bytes_3;
        int num_bytes_4;

        // allocate 1st pointer
        num_bytes_1 = 99*unit_size;
        p1 = (int *) Mem_alloc(num_bytes_1 );
        printf("first allocation of %d bytes p=%p \n", num_bytes_1, p1);
        Mem_print();

        // allocate for 2nd pointer
        num_bytes_2 = 49*unit_size;
        p2 = (int *) Mem_alloc(num_bytes_2);
        printf("second allocation of %d bytes p=%p\n", num_bytes_2, p2);
        Mem_print();

        // allocate remaining memory in free list
        // for example, if your chunk_t is 8 and 511 unit on free list
        // then request  511 - (99+1) - (49+1) -1 = 360 units
        num_bytes_3 = init_size_free_list - num_bytes_1/unit_size 
            - num_bytes_2/unit_size - 3;
        num_bytes_3 *= unit_size;
        p3 = (int *) Mem_alloc(num_bytes_3);
        printf("third allocation of %d bytes p=%p\n", num_bytes_3, p3);
        Mem_print();

        // allocate for 4th pointer when free list is empty
        num_bytes_4 = 127*unit_size;
        p4 = (int *) Mem_alloc(num_bytes_4);
        printf("fourth allocation of %d bytes p=%p\n", num_bytes_4, p4);
        Mem_print();

        // the above Mem_print should show the free list as empty
        // next put the memory back into the free list:

        printf("first free of p=%p \n", p1);
        Mem_free(p1);
        Mem_print();

        printf("second free of p=%p \n", p3);
        Mem_free(p3);
        Mem_print();

        printf("third and fourth free of p=%p and %p\n", p2, p4);
        Mem_free(p2);
        Mem_free(p4);
        Mem_print();
    }


    // add your unit test drivers here 

    // test for performance in equilibrium 
    if (dprms.EquilibriumTest)
        equilibriumDriver(&dprms);

    exit(0);
}

/* ----- equilibriumDriver -----
 *
 * This is a driver to test the performance of the dynamic memory allocation
 * and free calls in equilibrium.  This code assumes that the functions are
 * defined in mem.h 
 *
 * The driver allocates dynamic memory for variable sized arrays of integers.
 * The size of an array is uniformly distributed in the range [avg-range,
 * avg+range].  The average size and range can be specified on the command
 * line.
 *
 * During a warmup phase, calls are made to allocate the integer arrays and
 * the arrays are stored in an unsorted list using the list.c module.  
 *
 * During the equilibrium phase, the code randomly chooses to either allocate a
 * new array, or delete one of the arrays stored in the list.  The events are
 * equally likely.  If an array is removed from the list and freed, one of the
 * list items is choosen with an equal probability over all items in the list.
 *
 * Finally, the last phase frees all arrays stored in the list.
 *
 * At the end of each phase, Mem_stats is called to print information about
 * the size of the free list.  In verbose mode, Mem_print is called to print
 * the address and size of each item in the free list.  Only enable verbose
 * mode when testing with small warmup and trial phases.
 *
 * The following parameters can be set on the command line.  If not set,
 * default values are used.
 *
 * -w 1000   number of warmup allocations
 * -t 100000 number of trials in equilibrium
 * -a 128    average size of interger array
 * -r 127    range for average size of interger array
 * -d        use system malloc/free instead of MP4 versions
 */
void equilibriumDriver(driver_params *ep)
{
    int i, index;
    int range_num_ints;
    int min_num_ints;
    int *ptr;
    int size;
    int pos;
    List mem_list;
    Iterator idx_ptr;
    clock_t start, end;

    // print parameters for this test run 
    printf("\nEquilibrium test driver using ");
    if (ep->SysMalloc)
        printf("system malloc and free\n");
    else
        printf("Mem_alloc and Mem_free from mem.c\n");
    printf("  Trials in equilibrium: %d\n", ep->Trials);
    printf("  Warmup allocations: %d\n", ep->WarmUp);
    printf("  Average array size: %d\n", ep->AvgNumInts);
    printf("  Range for average array size: %d\n", ep->RangeInts);

    mem_list = list_construct();
    // the size of the integer array is uniformly distributed in the range
    // [avg-range, avg+range]

    range_num_ints = 2 * ep->RangeInts + 1;
    min_num_ints = ep->AvgNumInts - ep->RangeInts;
    if (min_num_ints < 1 || ep->AvgNumInts < 1 || ep->RangeInts < 0) {
        printf("The average array size must be positive and greater than the range\n");
        exit(1);
    }

    // warmup by allocating memory and storing in list 
    for (i = 0; i < ep->WarmUp; i++) {
        // random size of array 
        size = ((int) (drand48() * range_num_ints)) + min_num_ints;
        if (ep->SysMalloc)
            ptr = (int *) malloc(size * sizeof(int));
        else
            ptr = (int *) Mem_alloc(size * sizeof(int));
        assert(ptr != NULL);
        // first position is size of array.  fill rest with numbers 
        ptr[0] = size;
        for (index = 1; index < size; index++)
            ptr[index] = index;   // same as *(ptr+index)=index 
        list_insert(mem_list, (data_t *) ptr, NULL);
        ptr = NULL;
    }
    printf("After warmup\n");
    if (!ep->SysMalloc) {
        Mem_stats();
        if (ep->Verbose) Mem_print();
    } else {
        // OSX users: comment out next three lines
        struct mallinfo mi = mallinfo();
        printf("arena=%dB, chunks=%d, alloc=%d, free=%d\n", 
                mi.arena, mi.ordblks, mi.uordblks, mi.fordblks);
    }

    // in equilibrium make allocations and frees with equal probability 
    start = clock();
    for (i = 0; i < ep->Trials; i++) {
        if (drand48() < 0.5) {
            size = ((int) (drand48() * range_num_ints)) + min_num_ints;
            if (ep->Verbose) {
                // uncomment following print for more detail
                //printf("  allocating array size %d\n", size); 
                //Mem_print();
            }
            if (ep->SysMalloc)
                ptr = (int *) malloc(size * sizeof(int));
            else
                ptr = (int *) Mem_alloc(size * sizeof(int));
            assert(ptr != NULL);
            ptr[0] = size;
            for (index = 1; index < size; index++)
                ptr[index] = index;
            list_insert(mem_list, (data_t *) ptr, NULL);
            ptr = NULL;
        } else if (list_size(mem_list) > 0) {
            pos = (int) (drand48() * list_size(mem_list));
            idx_ptr = list_iter_front(mem_list);
            for (index = 0; index < pos; index++)
                idx_ptr = list_iter_next(idx_ptr);
            ptr = (int *) list_remove(mem_list, idx_ptr);
            assert(ptr != NULL);
            size = ptr[0];
            if (ep->Verbose) {
                // uncomment following print for more detail
                //printf("  returning array in position %d with size %d\n", pos, size); 
                //Mem_print();
            }
            assert(min_num_ints <= size && size <= ep->AvgNumInts+ep->RangeInts);
            for (index = 1; index < size; index++)
                assert(ptr[index] == index);
            if (ep->SysMalloc)
                free(ptr);
            else
                Mem_free(ptr);
            ptr = NULL;
        }
    }
    end = clock();
    printf("After exercise, time=%g\n",
            1000*((double)(end-start))/CLOCKS_PER_SEC);
    if (!ep->SysMalloc) {
        Mem_stats();
        if (ep->Verbose) Mem_print();
    } else {
        // OSX users: comment out next three lines
        struct mallinfo mi = mallinfo();
        printf("arena=%dB, chunks=%d, alloc=%d, free=%d\n", mi.arena,
                mi.ordblks, mi.uordblks, mi.fordblks);
    }

    // remove and free all items from mem_list
    pos = list_size(mem_list);
    for (i = 0; i < pos; i++) {
        ptr = (int *) list_remove(mem_list, NULL);
        assert(ptr != NULL);
        size = ptr[0];
        assert(min_num_ints <= size && size <= ep->AvgNumInts+ep->RangeInts);
        for (index = 1; index < size; index++)
            assert(ptr[index] == index);
        if (ep->SysMalloc)
            free(ptr);
        else
            Mem_free(ptr);
        ptr = NULL;
    }
    free(mem_list);

    printf("After cleanup\n");
    if (!ep->SysMalloc) {
        Mem_stats();
        if (ep->Verbose) Mem_print();
    } else {
        // OSX users: comment out next three lines
        struct mallinfo mi = mallinfo();
        printf("arena=%dB, chunks=%d, alloc=%d, free=%d\n", mi.arena,
                mi.ordblks, mi.uordblks, mi.fordblks);
    }
    printf("----- End of equilibrium test -----\n\n");
}


/* read in command line arguments.  Note that Coalescingr, SearchPolicy, and
 * RovingPolicy are stored in global variables for easy access by other 
 * functions.
 *
 * -u 0  is for the unit drivers, starting with driver 0
 *
 * Other command line arguments are for the equilibrium driver parameters.
 */
void getCommandLine(int argc, char **argv, driver_params *ep)
{
    /* The geopt function creates three global variables:
     *    optopt--if an unknown option character is found
     *    optind--index of next element in argv 
     *    optarg--argument for option that requires argument 
     *
     * The third argument to getopt() specifies the possible argument flags
     *   If an argument flag is followed by a colon, then an argument is 
     *   expected. E.g., "x:y" means -x must have an argument but not -y
     */
    int c;
    int index;

    ep->Seed = 54321;
    ep->Verbose = FALSE;
    ep->EquilibriumTest = FALSE;
    ep->WarmUp = 1000;
    ep->Trials = 100000;
    ep->AvgNumInts = 128;
    ep->RangeInts = 127;
    ep->SysMalloc = FALSE;
    ep->UnitDriver = -1;

    while ((c = getopt(argc, argv, "w:t:s:a:r:f:h:u:cdve")) != -1)
        switch(c) {
            case 'u': ep->UnitDriver = atoi(optarg);   break;
            case 'w': ep->WarmUp = atoi(optarg);       break;
            case 't': ep->Trials = atoi(optarg);       break;
            case 's': ep->Seed = atoi(optarg);         break;
            case 'a': ep->AvgNumInts = atoi(optarg);   break;
            case 'r': ep->RangeInts = atoi(optarg);    break;
            case 'd': ep->SysMalloc = TRUE;            break;
            case 'v': ep->Verbose = TRUE;              break;
            case 'e': ep->EquilibriumTest = TRUE;      break;
            case 'c': Coalescing = TRUE;               break;
            case 'f':
                  if (strcmp(optarg, "best") == 0)
                      SearchPolicy = BEST_FIT;
                  else if (strcmp(optarg, "first") == 0)
                      SearchPolicy = FIRST_FIT;
                  else {
                      fprintf(stderr, "invalid search policy: %s\n", optarg);
                      exit(1);
                  }
                  break;
            case 'h':
                  if (strcmp(optarg, "rove") == 0)
                      RovingPolicy = ROVER;
                  else if (strcmp(optarg, "head") == 0)
                      RovingPolicy = HEAD;
                  else {
                      fprintf(stderr, "invalid roving policy: %s\n", optarg);
                      exit(1);
                  }
                  break;
            case '?':
                  if (isprint(optopt))
                      fprintf(stderr, "Unknown option %c.\n", optopt);
                  else
                      fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
            default:
                  printf("Lab4 command line options\n");
                  printf("General options ---------\n");
                  printf("  -v        turn on verbose prints (default off)\n");
                  printf("  -s 54321  seed for random number generator\n");
                  printf("  -c        turn on coalescing (default off)\n");
                  printf("  -f best|first\n");
                  printf("            search policy to find memory block (first by default)\n");
                  printf("  -h rove|head\n");
                  printf("            roving policy for starting search location (rove by default)\n");
                  printf("  -u 0      run unit test driver\n");
                  printf("  -e        run equilibrium test driver\n");
                  printf("\nOptions for equilibrium test driver ---------\n");
                  printf("  -w 1000   number of warmup allocations\n");
                  printf("  -t 100000 number of trials in equilibrium\n");
                  printf("  -a 128    average size of interger array\n");
                  printf("  -r 127    range for average size of array\n");
                  printf("  -d        use system malloc/free instead of MP4 versions\n");
                  exit(1);
        }
    for (index = optind; index < argc; index++)
        printf("Non-option argument %s\n", argv[index]);
}

/* dummy function for the list.c package.  sorted lists are not used in this
 * program, so this function is never called.
 */
int int_compare(int_t *a, int_t *b)
{
    if (a->i < b->i)
        return 1;
    else if (a->i > b->i)
        return -1;
    else
        return 0;
}
/* vi:set ts=8 sts=4 sw=4 et: */
