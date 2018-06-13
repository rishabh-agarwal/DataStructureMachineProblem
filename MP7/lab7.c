/* lab7.c 
 * Lab7: Hash Tables 
 * ECE 223, Fall 2013
 *
 * Version: 1
 *
 * This file contains drivers to test the Hash Table ADT package.
 *
 *   -m to set the table size
 *   -a to set the load factor
 *   -h to set the type of probe sequence {linear|double|chain}
 *
 * There is a driver to build a table using table_insert and then access
 * keys in the table using table_retrieve.  Use
 *   -r run the retrieve driver and specifiy the type of initial table keys 
 *      (rand|seq|fold|worst)
 *   -t to set the number of access trials 
 *
 * Another test driver tests random inserts and deletes.  This driver builds
 * an initial table with random keys, and then performs insertions and deletions
 * with equal probability.
 *   -e run the equilibrium driver
 *
 * To test using the rehash driver.  The table size must be at least 6
 *   -b
 *
 * Bugs: 
 *    rehash driver (-b) does not work with separate chaining
 *
 *    There is no test to verify that the rehash function works correctly
 *    if the size of the table is changed.
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>

#include "table.h"

/* constants used with Global variables */

enum TableType_t {RAND, SEQ, FOLD, WORST};

#define MINID 1000
#define MAXID 999999000

#define TRUE 1
#define FALSE 0

/* Global variables for command line parameters.  */
int Verbose = FALSE;
static int TableSize = 11;
static int ProbeDec = LINEAR;
static double LoadFactor = 0.9;
static int TableType = RAND;
static int RetrieveTest = FALSE;
static int EquilibriumTest = FALSE;
static int RehashTest = FALSE;
static int Trials = 50000;
static int Seed = 19413;

/* prototypes for functions in this file only */
void getCommandLine(int argc, char **argv);
void equilibriumDriver(void);
void RetrieveDriver(void);
void RehashDriver();
int build_random(table_t *T, int ,int);
int build_seq(table_t *T, int, int);
int build_fold(table_t *T, int, int);
int build_worst(table_t *T, int, int);
void performanceFormulas(double);

int main(int argc, char **argv)
{
    getCommandLine(argc, argv);
    printf("Table size (%d), load factor (%g)\n", TableSize, LoadFactor);
    if (ProbeDec == LINEAR)
        printf("Open addressing with linear probe sequence\n");
    else if (ProbeDec == DOUBLE)
        printf("Open addressing with double hashing\n");
    else if (ProbeDec == CHAIN)
        printf("Separate chaining\n");
    else if (ProbeDec == QUAD)
        printf("Open addressing with quadratic probe sequence\n");
    printf("Seed: %d\n", Seed);
    srand48(Seed);

    /* ----- small table tests  ----- */

    if (RehashTest)                         /* enable with -b */
        RehashDriver();

    /* ----- large table tests  ----- */
    if (RetrieveTest)                        /* enable with -r flag */
        RetrieveDriver();

    /* test for performance in equilibrium */
    if (EquilibriumTest)                   /* enable with -e flag */
        equilibriumDriver();

    exit(0);
}

void build_table(table_t *test_table, int num_keys)
{
    int probes = -1;
    printf("  Build table with");
    if (TableType == RAND) {
        printf(" %d random keys\n", num_keys);
        probes = build_random(test_table, TableSize, num_keys);
    } else if (TableType == SEQ) {
        printf(" %d sequential keys\n", num_keys);
        probes = build_seq(test_table, TableSize, num_keys);
    } else if (TableType == FOLD) {
        printf(" %d folded keys\n", num_keys);
        probes = build_fold(test_table, TableSize, num_keys);
    } else if (TableType == WORST) {
        printf(" %d worst keys\n", num_keys);
        probes = build_worst(test_table, TableSize, num_keys);
    } else {
        printf("invalid option for table type\n");
        exit(7);
    }
    printf("    The average number of probes for a successful search = %g\n", 
                    (double) probes/num_keys);

    if (Verbose)
        table_debug_print(test_table);

    int size = table_entries(test_table);
    assert(size == num_keys);
}

/* driver to test small tables.  This is a series of very
 * simple tests and is not exhaustive.
 *
 * This version does not appear to work with separate chaining
 *
 * What is needed to fix it?
 */
void RehashDriver()
{
    int i, *ip, code;
    table_t *H;

    if (ProbeDec == CHAIN) {
        printf("The rehash driver needs to be fixed to work with separate chaining\n");
        return;
    }
    hashkey_t startkey = MINID + (TableSize - MINID%TableSize);
    assert(startkey%TableSize == 0);
    assert(TableSize > 5);  // tests designed for size at least 6

    H = table_construct(TableSize, ProbeDec);
    // fill table sequentially 
    for (i = 0; i < TableSize-1; i++) {
        ip = (int *) malloc(sizeof(int));
        *ip = 10*i;
        assert(table_full(H) == 0);
        code = table_insert(H, startkey+i, ip);
        ip = NULL;
        assert(code == 0);
        assert(table_entries(H) == i+1);
        assert(table_stats(H) == 1);
        assert(table_peek(H,i,1) == startkey+i);
    }
    if (Verbose) {
        printf("\nfull table, last entry empty\n");
        table_debug_print(H);
    }
    // tests on empty position
    assert(table_peek(H,i,1) == 0);
    assert(NULL == table_retrieve(H, startkey+i));
    assert(table_stats(H) == 1);
    assert(table_full(H) == 1);
    assert(-1 == table_insert(H, MAXID, NULL));
    // retrieve and replace each entry
    for (i = 0; i < TableSize-1; i++) {
        ip = table_retrieve(H, startkey+i);
        assert(*(int *)ip == 10*i);
        ip = NULL;
        assert(table_stats(H) == 1);
        ip = table_retrieve(H, startkey+i+TableSize);
        assert(ip == NULL);
        assert(2 <= table_stats(H) && table_stats(H) <= TableSize);
        if (ProbeDec == LINEAR)
            assert(table_stats(H) == i+2);
        ip = (int *) malloc(sizeof(int));
        *ip = 99*i;
        assert(1 == table_insert(H, startkey+i, ip));
        ip = NULL;
        ip = table_retrieve(H, startkey+i);
        assert(*(int *)ip == 99*i);
        ip = NULL;
    }
    assert(table_entries(H) == TableSize-1);
    assert(table_full(H) == 1);
    // delete tests
    assert(table_deletekeys(H) == 0);
    ip = table_delete(H, startkey+1);
    assert(*(int *)ip == 99);
    free(ip); ip = NULL;
    if (Verbose) {
        printf("\nsecond entry deleted, last entry empty\n");
        table_debug_print(H);
    }
    assert(table_entries(H) == TableSize-2);
    assert(table_full(H) == 0);
    assert(table_peek(H,1,1) == 0);
    assert(table_deletekeys(H) == 1);
    ip = table_retrieve(H, startkey+1);  // check key is not there
    assert(ip == NULL);
    assert(table_stats(H) >= 2);
    // attempt to delete keys not in table 
    assert(NULL == table_delete(H, startkey+1));
    assert(NULL == table_delete(H, startkey+TableSize-1));
    // insert key in its place
    ip = (int *) malloc(sizeof(int));
    *ip = 123;
    assert(0 == table_insert(H, startkey+1+TableSize, ip));
    ip = NULL;
    assert(table_peek(H,1,1) == startkey+1+TableSize);
    ip = table_retrieve(H, startkey+1+TableSize);
    assert(*(int *)ip == 123);
    ip = NULL;
    assert(table_entries(H) == TableSize-1);
    assert(table_full(H) == 1);
    assert(table_deletekeys(H) == 0);
    for (i = 2; i < TableSize-1; i++) {     // clear out all but two keys
        ip = table_delete(H, startkey+i);
        assert(*(int *)ip == 99*i);
        free(ip); ip = NULL;
    }
    assert(table_entries(H) == 2);
    ip = (int *) malloc(sizeof(int));    // fill last empty
    *ip = 456;
    assert(0 == table_insert(H, startkey+TableSize-1, ip));
    ip = NULL;
    assert(table_entries(H) == 3);
    // unsuccessful search when no empty keys
    assert(NULL == table_retrieve(H, startkey+TableSize));

    // two keys the collide in position 0
    ip = (int *) malloc(sizeof(int));
    *ip = 77;
    assert(0 == table_insert(H, startkey+TableSize, ip));
    ip = (int *) malloc(sizeof(int));
    *ip = 88;
    assert(0 == table_insert(H, startkey+10*TableSize, ip));
    ip = NULL;
    assert(table_entries(H) == 5);
    ip = table_delete(H, startkey);  // delete position 0
    assert(*(int *)ip == 0);
    free(ip); ip = NULL;
    assert(table_entries(H) == 4);
    ip = (int *) malloc(sizeof(int));  // replace 
    *ip = 87;
    assert(1 == table_insert(H, startkey+10*TableSize, ip));
    ip = NULL;
    assert(table_entries(H) == 4);
    ip = (int *) malloc(sizeof(int));   // put back position 0
    *ip = 76;
    assert(0 == table_insert(H, startkey+20*TableSize, ip));
    ip = NULL;
    assert(table_entries(H) == 5);
    assert(table_peek(H,0,1) == startkey+20*TableSize);
    assert(table_deletekeys(H) == TableSize-5);
    // rehash
    H = table_rehash(H, TableSize);
    assert(table_entries(H) == 5);
    assert(table_deletekeys(H) == 0);
    if (Verbose) {
        printf("\nfinal table\n");
        table_debug_print(H);
    }
    // other tests, rehash to larger table size
    // verify keys and information not lost during rehash

    // clean up table
    table_destruct(H);
}

/* driver to build and test tables. Note this driver  
 * does not delete keys from the table.
 */
void RetrieveDriver()
{
    int i;
    int key_range, num_keys;
    int suc_search, suc_trials, unsuc_search, unsuc_trials;
    table_t *test_table;
    hashkey_t key;
    data_t dp;

    /* print parameters for this test run */
    printf("\n----- Retrieve driver -----\n");
    printf("  Trials: %d\n", Trials);

    num_keys = (int) (TableSize * LoadFactor);
    test_table = table_construct(TableSize, ProbeDec);

    build_table(test_table, num_keys);

    key_range = MAXID - MINID + 1;

    if (Trials > 0) {
        /* access table to measure probes for an unsuccessful search */
        suc_search = suc_trials = unsuc_search = unsuc_trials = 0;
        for (i = 0; i < Trials; i++) {
            /* random key with uniform distribution */
            key = (hashkey_t) (drand48() * key_range) + MINID;
            dp = table_retrieve(test_table, key);
            if (dp == NULL) {
                unsuc_search += table_stats(test_table);
                unsuc_trials++;
            } else {
                // this should be very rare
                suc_search += table_stats(test_table);
                suc_trials++;
                assert(*(int *)dp == key);
            }
        }
        assert(num_keys == table_entries(test_table));
        if (suc_trials > 0)
            printf("    Avg probes for successful search = %g measured with %d trials\n", 
                    (double) suc_search/suc_trials, suc_trials);
        if (unsuc_trials > 0)
            printf("    Avg probes for unsuccessful search = %g measured with %d trials\n", 
                    (double) unsuc_search/unsuc_trials, unsuc_trials);
    }

    /* print expected values from analysis with compare to experimental
     * measurements */
    performanceFormulas(LoadFactor);

    /* remove and free all items from table */
    table_destruct(test_table);
    printf("----- End of access driver -----\n\n");
}

/* driver to test sequence of inserts and deletes.
 */
void equilibriumDriver(void)
{
    int i, code;
    int key_range, num_keys;
    int size;
    int ran_index;
    int suc_search, suc_trials, unsuc_search, unsuc_trials;
    int keys_added, keys_removed;
    int *ip;
    table_t *test_table;
    hashkey_t key;
    data_t dp;
    clock_t start, end;

    /* print parameters for this test run */
    printf("\n----- Equilibrium test driver -----\n");
    printf("  Trials: %d\n", Trials);

    test_table = table_construct(TableSize, ProbeDec);
    num_keys = (int) (TableSize * LoadFactor);

    /* build a table as starting point */
    build_table(test_table, num_keys);
    size = num_keys;

    key_range = MAXID - MINID + 1;
    /* in equilibrium make inserts and removes with equal probability */
    suc_search = suc_trials = unsuc_search = unsuc_trials = 0;
    keys_added = keys_removed = 0;
    start = clock();
    for (i = 0; i < Trials; i++) {
        if (drand48() < 0.5 && table_full(test_table) == FALSE) {
            // insert only if table not full
            // for separate chaining table is never full
            key = (hashkey_t) (drand48() * key_range) + MINID;
            ip = (int *) malloc(sizeof(int));
            *ip = key;
            /* insert returns 0 if key not found, 1 if older key found */
            if (Verbose) printf("Trial %d, Insert Key %u", i, key);
            code = table_insert(test_table, key, ip);
            if (code == 0) {
                /* key was not in table so added */
                unsuc_search += table_stats(test_table);
                unsuc_trials++;
                keys_added++;
                if (Verbose) printf(" added\n");
            } else if (code == 1) {
                suc_search += table_stats(test_table);
                suc_trials++;
                if (Verbose) printf(" replaced (rare!)\n");
            } else {
                printf("!!!Trial %d failed to insert key (%u) with code (%d)\n", i, key, code);
                exit(10);
            }
        } else if (table_entries(test_table) > TableSize/4) {
            // delete only if table is at least 25% full
            // why 25%?  Would 10% be better?  Lower than 10% will
            // be computationally expensive
            do {
                ran_index = (int) (drand48() * TableSize);
                key = table_peek(test_table, ran_index, 1);
            } while (key == 0);
            if (Verbose) printf("Trial %d, Delete Key %u", i, key);
            if (key < MINID || MAXID < key)
            {
                printf("\n\n  table peek failed: invalid key (%u) during trial (%d)\n", key, i);
                exit(12);
            }
            dp = table_delete(test_table, key);
            if (dp != NULL) {
                if (Verbose) printf(" removed\n");
                suc_search += table_stats(test_table);
                suc_trials++;
                keys_removed++;
                assert(*(int *)dp == key);
                free(dp);
            } else {
                printf("!!! failed to find key (%u) in table, trial (%d)!\n", key, i);
                printf("this is a catastrophic error!!!\n");
                exit(11);
            }
        }
    }
    end = clock();

    if (Verbose) {
        printf("Table after equilibrium trials\n");
        table_debug_print(test_table);
    }

    size += keys_added - keys_removed;
    printf("  Keys added (%d), removed (%d) new size should be (%d) and is (%d)\n",
            keys_added, keys_removed, size, table_entries(test_table));
    assert(size == table_entries(test_table));
    printf("  After exercise, time=%g \n",
            1000*((double)(end-start))/CLOCKS_PER_SEC);
    printf("  successful searches during exercise=%g, trials=%d\n", 
            (double) suc_search/suc_trials, suc_trials);
    printf("  unsuccessful searches during exercise=%g, trials=%d\n", 
            (double) unsuc_search/unsuc_trials, unsuc_trials);


    /* test access times for new table */

    /* separate chaining handled differently
     * should improve design of table_peek function so it 
     * returns 0 if count is invalid when using open addressing.  
     * In current design it is ignored
     */

    suc_search = suc_trials = unsuc_search = unsuc_trials = 0;
    start = clock();
    /* check each position in table for key */
    if (ProbeDec == CHAIN) {
        for (i = 0; i < TableSize; i++) {
            int count = 1;
            key = table_peek(test_table, i, count);
            while (key != 0) {
                assert(MINID <= key && key <= MAXID);
                dp = table_retrieve(test_table, key);
                if (dp == NULL) {
                    printf("Failed key (%u) should be at (%d)\n", key, i);
                    exit(15);
                } else {
                    suc_search += table_stats(test_table);
                    suc_trials++;
                    assert(*(int *)dp == key);
                }
                key = table_peek(test_table, i, ++count);
            }
        }
    }
    else {
        for (i = 0; i < TableSize; i++) {
            key = table_peek(test_table, i, 1);
            if (key != 0) {
                assert(MINID <= key && key <= MAXID);
                dp = table_retrieve(test_table, key);
                if (dp == NULL) {
                    printf("Failed to find key (%u) but it is in location (%d)\n", 
                            key, i);
                    exit(16);
                } else {
                    suc_search += table_stats(test_table);
                    suc_trials++;
                    assert(*(int *)dp == key);
                }
            }
        }
    }
    for (i = 0; i < Trials; i++) {
        /* random key with uniform distribution */
        key = (hashkey_t) (drand48() * key_range) + MINID;
        dp = table_retrieve(test_table, key);
        if (dp == NULL) {
            unsuc_search += table_stats(test_table);
            unsuc_trials++;
        } else {
            // this should be very rare
            assert(*(int *)dp == key);
        }
    }
    end = clock();
    size = table_entries(test_table);
    printf("  After retrieve experiment, time=%g\n",
            1000*((double)(end-start))/CLOCKS_PER_SEC);
    printf("  New load factor = %g\n", (double) size/TableSize);
    printf("  Percent empty locations marked deleted = %g\n",
            (double) 100.0 * table_deletekeys(test_table)
            / (TableSize - table_entries(test_table)));

    printf("   Measured avg probes for successful search=%g, trials=%d\n", 
            (double) suc_search/suc_trials, suc_trials);

    if (ProbeDec == CHAIN && LoadFactor > 0.5  && LoadFactor < 1.5)
    {
        printf("     ** This measure is biased.  See comments\n\n");
        /* The design of the equilibirum driver depends on the uniform
         * selection of keys to insert and remove.  For linear, double, and
         * quadratic probing selecting a key to remove is done with a uniform
         * distribution among all possible keys.  However, for separate
         * chaining, the algorithm simply picks a table location with a uniform
         * distribution, but this is not the same as picking a key with a
         * uniform distribution.  So, there is a bias that a key in a table
         * location with fewer other keys is more likely to be selected.  This
         * causes the average number of probes for a successful search to
         * increase as the equilibrium driver runs for a long time.  To remove
         * the bias, a solution is needed to pick a key with a uniform
         * distribution when chaining is used.  It is not clear how to select a
         * key with low computational cost.
         */
    }
    printf("   Measured avg probes for unsuccessful search=%g, trials=%d\n", 
            (double) unsuc_search/unsuc_trials, unsuc_trials);
    printf("    Do deletions increase avg number of probes?\n");
    performanceFormulas((double) size/TableSize);

    /* rehash and retest table */
    printf("  Rehash table\n");
    test_table = table_rehash(test_table, TableSize);
    /* number entries in table should not change */
    assert(size == table_entries(test_table));
    /* rehashing must clear all entries marked for deletion */
    assert(0 == table_deletekeys(test_table));

    /* test access times for rehashed table */

    suc_search = suc_trials = unsuc_search = unsuc_trials = 0;
    start = clock();
    /* check each position in table for key */
    if (ProbeDec == CHAIN) {
        for (i = 0; i < TableSize; i++) {
            int count = 1;
            key = table_peek(test_table, i, count);
            while (key != 0) {
                assert(MINID <= key && key <= MAXID);
                dp = table_retrieve(test_table, key);
                if (dp == NULL) {
                    printf("Failed key (%u) should be at (%d)\n", key, i);
                    exit(25);
                } else {
                    suc_search += table_stats(test_table);
                    suc_trials++;
                    assert(*(int *)dp == key);
                }
                key = table_peek(test_table, i, ++count);
            }
        }
    }
    else {
        for (i = 0; i < TableSize; i++) {
            key = table_peek(test_table, i, 1);
            if (key != 0) {
                assert(MINID <= key && key <= MAXID);
                dp = table_retrieve(test_table, key);
                if (dp == NULL) {
                    printf("Failed to find key (%u) after rehash but it is in location (%d)\n", 
                            key, i);
                    exit(26);
                } else {
                    suc_search += table_stats(test_table);
                    suc_trials++;
                    assert(*(int *)dp == key);
                }
            }
        }
    }
    for (i = 0; i < Trials; i++) {
        /* random key with uniform distribution */
        key = (hashkey_t) (drand48() * key_range) + MINID;
        dp = table_retrieve(test_table, key);
        if (dp == NULL) {
            unsuc_search += table_stats(test_table);
            unsuc_trials++;
        } else {
            // this should be very rare
            assert(*(int *)dp == key);
        }
    }
    end = clock();
    size = table_entries(test_table);
    printf("  After rehash, time=%g\n",
            1000*((double)(end-start))/CLOCKS_PER_SEC);
    printf("   Measured avg probes for successful search=%g, trials=%d\n", 
            (double) suc_search/suc_trials, suc_trials);

    printf("   Measured avg probes for unsuccessful search=%g, trials=%d\n", 
            (double) unsuc_search/unsuc_trials, unsuc_trials);

    /* remove and free all items from table */
    table_destruct(test_table);

    printf("----- End of equilibrium test -----\n\n");
}

/* build a table with random keys.  The keys are generated with a uniform
 * distribution.  
 */
int build_random(table_t *T, int table_size, int num_addr)
{
    hashkey_t key;
    int i, range, code;
    int probes = 0;
    int *ip;
    range = MAXID - MINID + 1;
    for (i = 0; i < num_addr; i++) {
        key = (hashkey_t) (drand48() * range) + MINID;
        assert(MINID <= key && key <= MAXID);
        ip = (int *) malloc(sizeof(int));
        *ip = key;
        code = table_insert(T, key, ip);
        if (code == 1) {
            i--;   // since does not increase size of table
            // replaced.  The chances should be very small
            printf("during random build generated duplicate key (%u) on trial (%d)\n", key, i);
            printf("this should be unlikely: if see more than a few you have a problem\n");
        }
        else if (code != 0) {
            printf("build of random table failed code (%d) index (%d) key (%u)\n",
                    code, i, key);
            exit(2);
        }
        probes += table_stats(T);
    }
    return probes;
}

/* build a table with sequential keys.  The starting address is random.  The
 * keys are are in adjacent table locations.
 */
int build_seq(table_t *T, int table_size, int num_addr)
{
    hashkey_t key;
    int i, range, starting, code;
    int *ip;
    int probes = 0;
    range = MAXID - MINID + 1;
    starting = (int) (drand48() * range) + MINID;
    if (starting >= MAXID - table_size)
        starting -= table_size;
    for (i = starting; i < starting + num_addr; i++) {
        assert(MINID <= i && i <= MAXID);
        key = i;
        ip = (int *) malloc(sizeof(int));
        *ip = i;
        code = table_insert(T, key, ip);
        if (code != 0) {
            printf("build of sequential table failed code (%d) index (%d) key (%u)\n",
                    code, i - starting, key);
            exit(3);
        }
        probes += table_stats(T);
    }
    return probes;
}

/* build a table with folded keys.  The starting address is random.  The first
 * set of keys are sequential, and the second set hashes to the same table
 * locations as the first set.
 */
int build_fold(table_t *T, int table_size, int num_addr)
{
    int i, range, starting, code;
    int probes = 0;
    int *ip;
    range = MAXID - MINID + 1;
    starting = (int) (drand48() * range) + MINID;
    if (starting <= MINID + table_size)
        starting += table_size;
    if (starting >= MAXID - table_size)
        starting -= table_size;
    for (i = starting; i > starting - num_addr/2; i--) {
        assert(MINID <= i && i <= MAXID);
        ip = (int *) malloc(sizeof(int));
        *ip = i;
        code = table_insert(T, i, ip);
        if (code != 0) {
            printf("build of first phase of folded table failed code (%d) index (%d) key (%d)\n",
                    code, i - starting, i);
            exit(4);
        }
        probes += table_stats(T);
    }
    for (i = starting + table_size; i > starting + table_size - (num_addr+1)/2; i--) {
        assert(MINID <= i && i <= MAXID);
        ip = (int *) malloc(sizeof(int));
        *ip = i;
        code = table_insert(T, i, ip);
        if (code != 0) {
            printf("build of second phase of folded table failed code (%d) index (%d) key (%d)\n",
                    code, i - starting, i);
            exit(5);
        }
        probes += table_stats(T);
    }
    return probes;
}

/* build a table with worst keys.  Insert keys that hash to the same table
 * location.  Protects against invalid keys by wrapping around if the total
 * number of addresses times the table size is large.
 */
int build_worst(table_t *T, int table_size, int num_addr)
{
    hashkey_t key = MAXID;
    int i, batches = 0, code;
    int probes = 0;
    int *ip;
    for (i = 0; i < num_addr; i++) {
        assert(MINID <= key && key <= MAXID);
        ip = (int *) malloc(sizeof(int));
        *ip = key;
        code = table_insert(T, key, ip);
        if (code != 0) {
            printf("build of worst table failed: code (%d) index (%d) key (%u) batch (%d)\n",
                    code, i, key, batches);
            exit(6);
        }
        if (key < MINID + table_size) {
            batches++;
            printf("batch %d\n", batches);
            key = MAXID - batches;
        }
        else
            key -= table_size;
        probes += table_stats(T);
    }
    return probes;
}

/* print performance evaulation formulas from Standish pg. 479 and pg 484
 *
 * Added additional formulas for linear probing and sequential, folded, and
 * worst addressing.  Also, for quadratic with worst addressing since it
 * behaves the same as linear in this case.  Formulas for the other cases
 * are unknown.
 */
void performanceFormulas(double load_factor)
{
    int n = TableSize * load_factor;
    if (TableType == RAND) {
        if (ProbeDec == LINEAR) {
            printf("--- Linear probe sequence performance formulas ---\n");
            printf("    Expected probes for successful search %g\n",
                    0.5 * (1.0 + 1.0/(1.0 - load_factor)));
            printf("    Expected probes for unsuccessful search %g\n",
                    0.5 * (1.0 + pow(1.0/(1.0 - load_factor),2)));
        }
        else if (ProbeDec == DOUBLE) {
            printf("--- Double hashing performance formulas ---\n");
            printf("    Expected probes for successful search %g\n",
                    (1.0/load_factor) * log(1.0/(1.0 - load_factor)));
            printf("    Expected probes for unsuccessful search %g\n",
                    1.0/(1.0 - load_factor));
        }
        else if (ProbeDec == QUAD) {
            printf("--- Quadratic probe sequence performance formulas ---\n");
            printf("    Expected probes for successful search %g\n",
                    1.0 - log(1.0 - load_factor) - load_factor/2.0);
            printf("    Expected probes for unsuccessful search %g\n",
                    1.0/(1.0 - load_factor) - load_factor - log(1.0 - load_factor));
        }
        else if (ProbeDec == CHAIN) {
            printf("--- Separate chaining performance formulas ---\n");
            printf("    Expected probes for successful search %g\n",
                    1.0 + 0.5 * load_factor);
            printf("    Expected probes for unsuccessful search %g\n", 
                    load_factor);
        }
    }
    else if (TableType == SEQ) {
        if (ProbeDec == LINEAR) {
            printf("--- Linear probe sequence performance formulas ---\n");
            printf("    Expected probes for successful search 1\n");
            printf("    Expected probes for unsuccessful search %g\n",
                    n * load_factor / 2.0 + load_factor/2.0 + 1);
        }
    }
    else if (TableType == FOLD) {
        if (ProbeDec == LINEAR) {
            printf("--- Linear probe sequence performance formulas ---\n");
            printf("    Expected probes for successful search %g\n",
                    n / 4.0 + 1);
            printf("    Expected probes for unsuccessful search %g\n",
                    n * load_factor / 2.0 + load_factor/2.0 + 1);
        }
    }
    else if (TableType == WORST) {
        if (ProbeDec == LINEAR) {
            printf("--- Linear probe sequence performance formulas ---\n");
            printf("    Expected probes for successful search %g\n",
                    n / 2.0 + 0.5);
            printf("    Expected probes for unsuccessful search %g\n",
                    n * load_factor / 2.0 + load_factor/2.0 + 1);
        }
        else if (ProbeDec == QUAD) {
            printf("--- Quadratic probe sequence performance formulas ---\n");
            printf("    Expected probes for successful search %g\n",
                    n / 2.0 + 0.5);
        }
    }
}

/* read in command line arguments and store in global variables for easy
 * access by other functions.
 */
void getCommandLine(int argc, char **argv)
{
    /* optopt--if an unknown option character is found
     * optind--index of next element in argv 
     * optarg--argument for option that requires argument 
     * "x:" colon after x means argument required
     */
    int c;
    int index;

    while ((c = getopt(argc, argv, "m:a:h:i:t:s:erbv")) != -1)
        switch(c) {
            case 'm': TableSize = atoi(optarg);      break;
            case 'a': LoadFactor = atof(optarg);     break;
            case 's': Seed = atoi(optarg);           break;
            case 't': Trials = atoi(optarg);         break;
            case 'v': Verbose = TRUE;                break;
            case 'e': EquilibriumTest = TRUE;        break;
            case 'r': RetrieveTest = TRUE;           break;
            case 'b': RehashTest = TRUE;             break;
            case 'h':
                if (strcmp(optarg, "linear") == 0)
                    ProbeDec = LINEAR;
                else if (strcmp(optarg, "double") == 0)
                    ProbeDec = DOUBLE;
                else if (strcmp(optarg, "quad") == 0)
                    ProbeDec = QUAD;
                else if (strcmp(optarg, "chain") == 0)
                    ProbeDec = CHAIN;
                else {
                    fprintf(stderr, "invalid type of probing decrement: %s\n", optarg);
                    fprintf(stderr, "must be {linear | double | chain}\n");
                    exit(1);
                }
                break;
            case 'i':
                if (strcmp(optarg, "rand") == 0)
                    TableType = RAND;
                else if (strcmp(optarg, "seq") == 0)
                    TableType = SEQ;
                else if (strcmp(optarg, "fold") == 0)
                    TableType = FOLD;
                else if (strcmp(optarg, "worst") == 0)
                    TableType = WORST;
                else {
                    fprintf(stderr, "invalid type of address generation: %s\n", optarg);
                    fprintf(stderr, "must be {rand | seq | fold | worst}\n");
                    exit(1);
                }
                break;
            case '?':
                if (isprint(optopt))
                    fprintf(stderr, "Unknown option %c.\n", optopt);
                else
                    fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
            default:
                printf("Lab7 command line options\n");
                printf("General options ---------\n");
                printf("  -m 11     table size\n");
                printf("  -a 0.9    load factor\n");
                printf("  -h linear|double|chain\n");
                printf("            Type of probing decrement\n");
                printf("  -r        run retrieve test driver \n");
                printf("  -b        run basic test driver \n");
                printf("  -e        run equilibrium test driver\n");
                printf("  -i rand|seq|fold|worst\n");
                printf("            type of keys for retrieve test driver \n");
                printf("\nOptions for test driver ---------\n");
                printf("  -t 50000  number of trials in drivers\n");
                printf("  -v        turn on verbose prints (default off)\n");
                printf("  -s 19413  seed for random number generator\n");
                exit(1);
        }
    for (index = optind; index < argc; index++)
        printf("Non-option argument %s\n", argv[index]);
}

/* vi:set ts=8 sts=4 sw=4 et: */
