//
//  hash.h
//  
//
//  Created by Rishabh Agarwal on 12/1/13.
//
//

#define LINEAR l
#define DOUBLE d
#define CHAIN c
typedef void *data_t;
typedef unsigned hashkey;

typedef struct hash_node_tag
{
  
    chain *array;
    int table_size;
    int num_entries;
    data_t *data_t;
    int probe_type;
    int num_comp;
}table_t;

typedef struct sep_chain
{
    chain *next;
   hash_key key
    
}chain;


table_t *table_construct(int table_size, int probe_type);
table_t*table_rehash(table_t*,int new_table_size);
int table_entries(table_t*);
int table_full(table_t);
int table_deletekeys(table_t*);
int table_insert(table_t* hashkey_tK,data_tI);
data_t table_delete(table*,hashkey_t);
data_t table_retrieve(table*,haskey_tK);
void table_destruct(table_t*);
int table_stats(table_t*);
void table_debug_print(table_t*);