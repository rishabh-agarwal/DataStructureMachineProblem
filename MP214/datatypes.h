/* datatypes.h 
 * Prof. Russell 
 * ECE 223 Spring 2014 
 * MP2
 *
 * Propose: The data type that is stored in the list ADT is defined here.  We
 *          define a single mapping that allows the list ADT to be defined in
 *          terms of a generic data_t.
 *
 * Assumptions: 
 *
 *     data_t: The type of data that we want to store in the list
 *
 *     comp_proc(A, B): function to compare two data_t records
 *
 * Bugs:
 * 
 */
typedef struct packet_tag {
    int dest_ip_addr;       /* IP address of destination */
    int src_ip_addr;        /* IP address of source */
    int dest_port_num;      /* port number at destination */
    int src_port_num;       /* port number at source host*/
    int hop_count;          /* number of routers in route */
    int protocol;           /* TCP=1, UDP=2, SSL=3, RTP=4 */
    float threat_score;     /* rating of source host */
    int time_received;      /* time in seconds packet received */
} packet_t;

/* the list ADT works on packet data of this type */
typedef packet_t data_t;

/* the comparison procedure is found in hpot_support.c */
#define comp_proc(x, y) (hpot_compare(x, y))

/* commands for vim. ts: tabstop, sts: soft tabstop sw: shiftwidth */
/* vi:set ts=8 sts=4 sw=4 et: */
