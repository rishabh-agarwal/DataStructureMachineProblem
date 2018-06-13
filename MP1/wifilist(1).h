/* wifilist.h 
 * Prof. Russell 
 * ECE 223 Fall 2013 
 * MP1
 *
 * Propose: A template for MP1 
 *
 * Assumptions: structure definitions and public functions as defined for
 * assignmnet.  There are no extensions.
 *
 * Bugs:
 */

struct wifilist_t {
    int wlist_array_size;  // size of array given by user
    int wlist_entries;     // current number of records in WiFi list
    struct wifi_info_t **wlist_ptr;
};

struct wifi_info_t {
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
};

//  The sequential list ADT must have the following interface:

struct wifilist_t *wifilist_construct(int);
void wifilist_destruct(struct wifilist_t *);
int wifilist_add(struct wifilist_t *, struct wifi_info_t *);
struct wifi_info_t *wifilist_lookup(struct wifilist_t *, int);
struct wifi_info_t *wifilist_access(struct wifilist_t *, int);
struct wifi_info_t *wifilist_remove(struct wifilist_t *, int);
int wifilist_arraysize(struct wifilist_t *);
int wifilist_number_entries(struct wifilist_t *);


