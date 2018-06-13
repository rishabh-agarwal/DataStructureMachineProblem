//
//  hash.c
//  
//
//  Created by Rishabh Agarwal on 12/1/13.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "hash.h"

table_t*table_construct(int table_size, int probe_type)
{
    table_t *hash;
    
    hash=(table_t *)malloc(sizeof(table_t));
    hash->num_entries=0;
    hash->table_size=table_size;
    hash->num_comp=0;
    hash->index=0;
    
    hash->data_t=(data_t *)malloc(sizeof(data_t));//change
    hash->probe_type=probe_type;

    
    for(i=0;i<table_size;i++)
    {
        hash->array[i]=NULL;
        hash->array[i]->next=NULL; //doublt should be hash or chain
        hash->array[i]->key=0;
        table->data_t[i]=NULL;
    }
}
//----------------------------------------------------------------------//
table_t*table_rehash(table_t*table,int new_table_size)
{
    
    table_t* new_ptr;
    new_ptr=table_construct(new_table_size,table->probe_type);
    
    new_ptr->num_entries=table->num_entries;
    new_ptr->num_comp=table->num_comp;
    
    if(table==NULL)
    {
        return 0;
    }
    else
    {
        
        for(i=0;i<table->table_size;i++)
        {
            new_ptr->array[i]=table->array[i];
            
        }
    }

    table_destruct(table);
    
    return new_ptr;
}
//--------------------------------------------------------------------//
int table_entries(table_t*node)
{
    return node->num_entries;
}
//-----------------------------------------------------------------------//
int table_full(table_t*table)
{
    
    if(table->num_entries==table->table_size);
    return 1;
    else
        return 0;
}
//------------------------------------------------------------------------//
int table_deletekeys(table_t*table)
{
    int count=0;
    for(int i=0;-<table->table_size;i++)
    {
    if (table->array[i]==-1) {
        count++;
    }
    }
    return count;
    }


//-----------------------------------------------------------------------------------------------//
int table_insert(table_t*table ,hashkey_t key,data_t *data)
{
    int count=0;
    int p=0;
    
    if(table->table_size==NULL || table == NULL) // if table size is null
    {
        return NULL;
        
    }
  
    for(i=0;i=table->table_size;i++) // total number of key in array
    {
        if (table->array[i]!=NULL && table->array[i]->key != -1 )
        {
            count++;
        }
        num_comp++
    }
    if(table_size == count) // if array is full
    {
        return -1;
    }
    
    // ------------------------Linear--------------------------//
    if(probe_type==LINEAR)
    {

                 int index= table->key % table->table_size; // hash formula
                
                if(table->array[index]!= NULL) // if space not empty
                {
                     while(table->array[index]->key != NULL) //till index not empty
                     {
                         if(table->array[index]->key == -1 || table->array[index]->key==key)
                             break;
                         
                         index++; //probe=1;
                         num_comp++;
                         if(index>=table-> table_size)
                             index=0;
                     }
                }
             table->array[index]->key=key; // if index found place key
        table->data_t[i]=data;
        if( table->array[index]->key==key)
        return 1;
        
        
        num_entries++;
        
    }
    
    //-------------------------Double--------------------------//
    
    else if(probe_type==DOUBLE)
    {
        int index= table->key % table->table_size; // hash formula
        int probe =(table->key / table->table_size)%table->table_size;
        
        if(probe<1)
            probe=1;
        
        
        if(table->array[index]!= NULL) // if space not empty
        {
            while(table->array[index]->key != NULL) //till index not empty
            {
                if(table->array[index]->key == -1 ||table->array[index]->key==key)
                    break;
                
                index=index+probe;
                
                //index++;
                num_comp++;
                if(index>=table-> table_size)
                    index=0;
                
            }
        }
        table->array[index]->key=key; // if index found place key
           table->data_t[i]=data;
        if( table->array[index]->key==key)
            return 1;

        num_entries++;
    }
    //----------------------Seperate chaining------------------------//
    else
    {
        chain *node , *fill;
        
        node = (chain *)malloc(sizeof(chain));
        node->next=NULL;
        node->key=key;
        
            int index= key % table->table_size;//finding index
            
        
            if(table->array[index]->next==NULL) // if table ki index is null
            {
                num_comp++;
                table->array[index]->next=node;// place at the index
            }
            else
            {
                fill =table->array[index]->next;
                
                while(fill->next!=NULL) // move until it is NULL
                {
                    fill=fill->next;
                    num_comp++;
                }
                fill->next=node;
                num_entries++;
                
            }
}
    return 0;
}

//-----------------------------------------------------------------------------------//
data_t table_delete(table_t*table,hashkey_t)
{
    
    for(i=0;i=table->table_size;i++)
    {
        if(table->array[i]->key==key) // if key matches
        {
            
            table->array[i]->key=-1;  //subsituting -1 in place of deleted keys
            num_entries --;
            num_comp++;
        }
        else if(table->array[i]->key != key && i== table->table_size ) // if array is full
        {
            num_comp++;
         return NULL;
        }
    
    }
}
 //-------------------------------------------------------------------------------------//
    
data_t table_retrieve(table*table,haskey_tK)
{
    
    for(i=0;i=table->table_size;i++)
    {
        if(table->array[i]->key == key) // if array ki key equal to key
        {
            return i;
        }
       
    }
    return NULL;
}
    
//--------------------------------------------------------------------------------------//
void table_destruct(table_t*table)
{
    for(i=0;i<table->table_size;i++)
    {
        free(table->array[i]->key)
    }
      free(table->index);
      free(table->array);
    free(table);
}
//------------------------------------------------------------------------------------//
int table_stats(table_t*table)
{
    return(table->num_comp);
}
//-----------------------------------------------------------------------------------//
void table_debug_print(table_t*table)
{
    for (i=0;i=table->table_size;i++)
    {
        printf( "index = %d  ",i);
        printf("key = %d ", table->array[i]->key);
    }

}
//----------------------------------------------------------------------------------//

hashkey_t table_peek(table_t*T,int index,int list_positio)
    {
      if(list_positio < 0 && T->table_size)
     return 0;
        
        if((T->array[list_positio]->key != 0) && (T->array[list_positio]->key != -1))
        {
            return T->array[list_positio]->key;
        }
        
        return 0;
    }
