/* mem.h 
 * Lab4: Dynamic Memory Allocation
 * Version: 1
 * ECE 223, Fall 2013
 */

#define FIRST_FIT 0x5555 
#define BEST_FIT  0xAAAA
#define ROVER     0xCCCC
#define HEAD      0x3333
#define TRUE 1
#define FALSE 0

/* must be FIRST_FIT or BEST_FIT */
int SearchPolicy;

/* must be ROVER or HEAD and determines if a search begins at the 
 * head of the list or at the rover 
 */
int RovingPolicy;

/* TRUE if memory returned to free list is coalesced */
int Coalescing;

/* deallocates the space pointed to by return_ptr; it does nothing if
 * return_ptr is NULL.  
 */
void Mem_free(void *return_ptr);

/* returns a pointer to space for an object of size nbytes, or NULL if the
 * request cannot be satisfied.  The space is uninitialized.
 */
void *Mem_alloc(int nbytes);

/* prints stats about the current free list
 *
 * number of chunks on list
 * min, max, and average size of each chunk in bytes
 * total memory in list in bytes
 * number of calls to sbrk and number of pages requested
 */
void Mem_stats(void);

/* print table of memory in free list 
 * example format
 *     chunk_t *p;
 *     printf("p=%p, size=%d, end=%p, next=%p\n", 
 *              p, p->size, p + p->size, p->next);
 */
void Mem_print(void);

/* vi:set ts=8 sts=4 sw=4 et: */
