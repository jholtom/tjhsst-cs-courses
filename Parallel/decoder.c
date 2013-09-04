// Decoder.c - First AI Program
// Jacob Holtom, Sept 3, 2013
//
//Define the treenode struct
struct node
{
        char key_value;
        struct node *left;
        struct node *right;
};
struct listnode {
        char x;
        struct node *next;
};
#include <stdio.h>
int k;
char ch;
int stuff = 0;
int main (){
        FILE* src = fopen("decode.txt","r");
        struct node *root = 0;
        struct listnode *temp;
        temp = malloc( sizeof(struct node) );
        temp->next = 0;
        //Print the contents of the file, char by char
           while(stuff < 518)
           {
           fread(&ch,1,1,src);
           printf("%s",&ch);
           stuff++;
           } 
        temp->x = "1";
        searchpath(temp,root);
        //End the program
        return 0;
}

//Methods to work with Binary Tree's
void destroy_tree(struct node *leaf)
{
        if( leaf != 0 )
        {
                destroy_tree(leaf->left);
                destroy_tree(leaf->right);
                free( leaf );
        }
}
insert(char key, struct node **leaf)
{
        if( *leaf == 0 )
        {
                *leaf = (struct node*) malloc( sizeof( struct node ) );
                (*leaf)->key_value = key;
                /* initialize the children to null */
                (*leaf)->left = 0;    
                (*leaf)->right = 0;  
        }
        else if(key < (*leaf)->key_value)
        {
                insert( key, &(*leaf)->left );
        }
        else if(key > (*leaf)->key_value)
        {
                insert( key, &(*leaf)->right );
        }
}
struct node *search(int key, struct node *leaf)
{
        if( leaf != 0 )
        {
                if(key==leaf->key_value)
                {
                        return leaf;
                }
                else if(key<leaf->key_value)
                {
                        return search(key, leaf->left);
                }
                else
                {
                        return search(key, leaf->right);
                }
        }
        else return 0;
}
//Search function to go by path, not searching for value
int searchpath(struct listnode *path, struct node **leaf)
{
        if(path == 0){
                return &(*leaf);}
        else if(&(*leaf)->right->key_value == 0){
            printf("%s", "I did something right!");
        }
        else if(&(*leaf)->left->key_value == 1){
            printf("%s", "I turned left instead!");
        }
     return 0;
}
