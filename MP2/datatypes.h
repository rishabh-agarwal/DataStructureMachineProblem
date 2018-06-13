/* datatypes.h 
 * Prof. Russell 
 * ECE 223 Fall 2013 
 * MP2
 *
 * Propose: The data type that is stored in the list ADT is defined here.  We
 * define a single mapping that allows the list ADT to be defined in terms of a
 * generic data_t.
 *
 * Assumptions: 
 *
 * data_t: The type of data that we want to store in the list
 *
 * comp_proc(A, B): function to compare two data_t records
 *
 * Bugs:
 */

typedef struct wifi_info_tag {
    int eth_address;	// mobile's Ethernet address 
    int ip_address;	// mobile's IP address 
    int access_point;	// IP address of access point connected to mobile 
    int authenticated;	// true or false 
    int privacy;	// mode 0 for none, 1 for WEP, 2 for WPA, 3 for WPA2
    int standard_letter;// a, b, e, g, h, n, or s. 
                        //   Convert letter to integer with a=1, b=2, etc. 
    float band;		// 2.4 or 5.0 for the ISM frequency bands (in GHz) 
    int channel;	// 1-11 for 2.4 GHz and 1-24 for 5 GHz 
    float data_rate;	// 1, 2, 5.5, 11 for 2.4 GHz and 
                        // 6, 9, 12, 18, 24, 36, 48, 54 for 5 GHz 
    int time_received;	// time in seconds that information last updated
} wifi_info_t;

/* the list ADT works on packet data of this type */
typedef wifi_info_t data_t;

/* the comparison procedure is found in wifi_support.c */
#define comp_proc(x, y) (wifi_compare(x, y))

/* commands for vim. ts: tabstop, sts: soft tabstop sw: shiftwidth */
/* vi:set ts=8 sts=4 sw=4 et: */
