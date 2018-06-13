//Rishabh Agarwal

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "bst.h"




void bst_d( bst_node_t *T)
{
 
    if(T == NULL)
    {
        return;
    }
     
    bst_d(T->left);    
    bst_d(T->right);
    free(T->data_ptr);
    T->left=NULL;
    T->right=NULL;
    free(T);
}
 
void bst_destruct (bst_t* tree)
{
if( tree == NULL|| tree->root== NULL || tree->tree_size==0)
return;

 bst_d(tree->root);
 
free(tree);
tree=NULL;
}

data_t access_data(bst_node_t * branch, bst_key_t key, int * branch_comparisons) {


    if(branch == NULL) 
    {
    return NULL;
    }

    (*branch_comparisons)++;

    if(branch->key == key) 
    {
    return branch->data_ptr;
    }
    (*branch_comparisons)++;

    if(branch->key < key)
    {
     return access_data(branch->right,key,branch_comparisons);
    }
    return access_data(branch->left, key, branch_comparisons);
}

data_t bst_access (bst_t *tree,bst_key_t key)
{
  tree->num_recent_key_comparisons = 0;

  return access_data(tree->root,key,&(tree->num_recent_key_comparisons));
}


bst_t *bst_construct (int tree_policy)
{

    bst_t *tree ;
    
    tree=(bst_t *)malloc(sizeof(bst_t));

    tree->tree_policy = BST;

    tree->root=NULL;

    tree->num_recent_key_comparisons = 0;

    return tree;

}

//-------------------------- Inserting ---------------------------------//
int bst_insert (bst_t *tree,bst_key_t key,data_t data)
{ 
  bst_node_t *new_node;
  tree->num_recent_key_comparisons=0;
  bst_node_t *root = tree->root; 
  bst_node_t *rover;
  rover=root;
  
  new_node=(bst_node_t*)malloc(sizeof(bst_node_t));
  new_node->right=NULL;
  new_node->left=NULL;
  new_node->key=key;
  new_node->data_ptr=data;
  
  
  if (tree->root == NULL)
  {
   tree->root=new_node;
   
   tree->tree_size++;
   
   return 1;
  }
  
   while(rover != NULL)
  {
   if(key > rover->key)
  {
   if (rover->right == NULL)
   {
   break;
   }
   
   rover=rover->right;
   tree->num_recent_key_comparisons++;
  }
  
  else if(key < rover->key)
  {
  if (rover->left == NULL)
   {
   break;
   }
  
  rover = rover ->left;
  
  tree->num_recent_key_comparisons++;
  
  }
  
  else if(key == rover->key)
  {
   return 0; // the key is the same //what about the data_ptr
  }
 } 

// Inserting data
  if (new_node->key > rover->key)
  {
  tree->num_recent_key_comparisons++;
  rover->right = new_node;
     tree->tree_size++;
  }
  else if (new_node->key < rover->key)
  {
  tree->num_recent_key_comparisons++;
  rover->left = new_node;
     tree->tree_size++;
  }
  
  return 1;
 }

//---------------------Insert function End------------------------------//
//---------------------Remove function starts---------------------------//
data_t bst_remove(bst_t *tree , bst_key_t key)
{  
   bst_node_t *rover,*current,*prev,*leaf_ptr,*leaf_prev,*temp,*temp3;
   data_t *data;
   rover=tree->root;
   data_t *vapis;
   temp3=NULL;
   if(tree->root==NULL)
   return NULL;
   
 
   
   while (rover != NULL && key != rover->key)
     {  
    
              if (key < rover->key)
              {  tree->num_recent_key_comparisons++;
               prev=rover;
               rover = rover->left;
              }
           
              else if(key > rover->key)
              {  tree->num_recent_key_comparisons++;
               prev=rover;
               rover = rover->right;
              } 
     }

// returning rover and prev
  current=rover;
if(current == NULL)
return NULL;
 //No child 
  
  if (current->right==NULL && current->left==NULL)
  {
            if (key == tree->root->key)
            {  tree->num_recent_key_comparisons++;
                    current=tree->root;   
                    tree->num_recent_key_comparisons++;
                    vapis = tree->root->data_ptr;
                    free(tree->root);
                    tree->tree_size=0;
                    return vapis;
            }
            else if(current->key > prev->key)
            {  tree->num_recent_key_comparisons++;
                    prev->right=NULL;
            }
            else if(current->key < prev->key)
            {  tree->num_recent_key_comparisons++;
                    prev->left=NULL;
            }
            temp=current;
  }
  
  
// one child
  else if( current->right == NULL || current->left == NULL)
  {  tree->num_recent_key_comparisons++;
           if (key == tree->root->key)
            {  tree->num_recent_key_comparisons++;
                    current=tree->root;   
                    tree->num_recent_key_comparisons++;
                    if(current->left ==NULL)
                      {tree->root = current->right;}
                    else
                      {tree->root = current->left;}
            }
           else if(current->left ==NULL)
           {  tree->num_recent_key_comparisons++;
                   if (current->key < prev->key)     
                        prev->left = current->right;
                   else
                        prev->right = current->right;
           }
           else if (current->right ==NULL)
           {  tree->num_recent_key_comparisons++;
                   if (current->key < prev->key)     
                        prev->left = current->left;
                   else
                        prev->right = current->left; //******************
           }  
           temp=current;
  }
// two child or grand parent
   else
   {
  tree->num_recent_key_comparisons++;
           temp=current; //temp equal to current
           
           if(current->right->left ==NULL)
           {  tree->num_recent_key_comparisons++;
                   leaf_prev=current;
                   leaf_ptr=current->right;
           }
           
           else
          {   tree->num_recent_key_comparisons++;
                   leaf_ptr=current->right;
                   while(leaf_ptr->left != NULL) //finding leaf_ptr and its prev
                   {
                           leaf_prev=leaf_ptr;
                           leaf_ptr=leaf_ptr->left;
                   }
           }
           temp3 = leaf_ptr->right; // leaf_ptr right saved
           
           if (key == tree->root->key)
            {
                    tree->num_recent_key_comparisons++;
                    current=tree->root;   
                    tree->num_recent_key_comparisons++;
                    tree->root = leaf_ptr;
            }
            else if(current->key < prev->key) //left part
            {  tree->num_recent_key_comparisons++;
             prev->left = leaf_ptr;

            }
            else //right part
            {  tree->num_recent_key_comparisons++;
                prev->right = leaf_ptr;
            }
            leaf_ptr->left = current->left;
            
            if(leaf_ptr!=leaf_prev->right)
            {  tree->num_recent_key_comparisons++;
                leaf_ptr->right = current->right;    
            }
           
            leaf_prev->left = temp3;
   }
   
  
    vapis = temp->data_ptr;
    free(temp); 
    tree->tree_size--;
   
   data=vapis;
   return data;
} 
//-----------------------Remove function Ends----------------------------
int bst_stats (bst_t *tree)
{
return tree->num_recent_key_comparisons;
}

int bst_size(bst_t *tree)
{
return tree->tree_size;
}

int bst_l_mp5(bst_node_t *node , int c)
  { 
    if(node==NULL ) return 0;
    return  ( c+ ( bst_l_mp5(node->left , c+1)) + (bst_l_mp5(node->right ,c+1)));   
  } 
  
int bst_int_path_len(bst_t *T)
{
if(T->root==NULL) return 0;
int p_len=0;
p_len=bst_l_mp5(T->root,0);
return p_len;
}
 



void bst_debug_print_tree(bst_t *T)
{ 
ugly_print(T->root,0);
}

//--------------//
void ugly_print(bst_node_t *N, int level) 
{
int i;
if (N == NULL) return ;
ugly_print(N->right, level+1) ;
for (i=0; i<level; i++) printf("     ");

printf("%5d\n", N->key);
ugly_print(N->left, level+1);
}

//--------------//

int bst_debug_validate_rec(bst_node_t *N)
{
if (N == NULL) return 0;
if (N->left != NULL)
/* assert that left key is less than N's key */
assert(N->left->key < N->key);
if (N->right != NULL)
/* assert that right key is greater than N's key */
assert(N->right->key > N->key);
assert(N->data_ptr != NULL);
return 1 + bst_debug_validate_rec(N->left) +
bst_debug_validate_rec(N->right);
}
void bst_debug_validate(bst_t *T)
{
int size;
size = bst_debug_validate_rec(T->root);
size = T->tree_size;
assert(size == T->tree_size);
}
