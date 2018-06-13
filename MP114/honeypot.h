/*RISHABH AGARWAL       MP1
 honeypot.h template
 *
 * ECE 223 Spring 2014 
 * MP1
 *
 * Purpose: A template for MP1 
 *          You may change this file if needed for your design.
 *
 * Assumptions: structure definitions and public functions as defined for
 * assignmnet.  There are no extensions.
 *
 * Bugs:
 */

#define MAXLINE 80

struct honeypot_t {
    int pot_size;         // size of array 
    int pot_entries;      // current number of records in the list
    int intial_size;      //Intial size
    struct packet_t **hpot_ptr;
};
struct packet_t {
    int dest_ip_addr;   // IP address of destination
    int src_ip_addr;    // IP address of source 
    int dest_port_num;  // port number at destination
    int src_port_num;   // port number at source host
    int hop_count;      // number of routers in route
    int protocol;       // TCP=1, UDP=2, SSL=3, RTP=4
    float threat_score; // rating of source host
    int time_received;  // time in seconds packet received
};

//  The sequential list ADT must have the following interface.  You 
//  cannot change the interface for any of these functions

struct honeypot_t *hpot_construct(int);
void hpot_destruct(struct honeypot_t *);
int hpot_add(struct honeypot_t *, struct packet_t *);
int hpot_lookup(struct honeypot_t *, int);
struct packet_t *hpot_access(struct honeypot_t *, int);
struct packet_t *hpot_remove(struct honeypot_t *, int);
int hpot_empty(struct honeypot_t *);
int hpot_count(struct honeypot_t *);
void hpot_record_fill(struct packet_t *);
void hpot_print_rec(struct packet_t *);

/* commands specified to vim. ts: tabstop, sts: soft tabstop sw: shiftwidth */
/* vi:set ts=8 sts=4 sw=4 et: */
