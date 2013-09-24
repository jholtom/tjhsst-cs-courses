//Jacob Holtom - Sept 10, 2013
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MSGLEN 30
typedef struct TreeNode {
    char key;
    int freq;
    struct TreeNode* left;
    struct TreeNode* right;
} node;
void bubble_sort(node*[], int);
void bubble_sort(node* targ[], int n)
{
    int c,d;
    node* t;
    for(c = 0; c < (n-1); c++)
    {
        for(d = 0; d < n - c -1; d++){
            if(targ[d]->freq < targ[d+1]->freq){
                t = targ[d];
                targ[d] = targ[d+1];
                targ[d+1] = t;
            }
        }
    }
}
char* traverse(node*,int,char[][MSGLEN*sizeof(char)],char*);
char* traverse(node* root,int depth, char* codeword[][MSGLEN*sizeof(char)],char* path)
{
if( root->left == NULL && root->right == NULL)
{
  path[depth] = '\0';
  sprintf(codword[(int)root->key], "%s", path );
}
else
{
path[depth] = '0';
traverse(root->left,depth+1,codeword,path);
path[depth] = '1';
traverse(root->right,depth+1,codeword,path);
}
}
void main(void)
{
    char cw[256][MSGLEN * sizeof(char)];
    char p[MSGLEN*sizeof(char)];
    char* msg = "HELLOWORLD";
    node* arr[7];
    int c = 0;
    int count[26] = {0};
    while( msg[c] != '\0')
    {
        if( msg[c] >= 'A' && msg[c] <= 'Z' )
        {
            count[msg[c]-'A']++;
        }
        c++;
    }
    int num = 0;
    for(c = 0; c < 26; c++)
    {
        if( count[c] != 0 ){
            printf("%c occured %d times.\n",c+'A',count[c]);
            if(num <  7){
                node* x = malloc(sizeof(*x));
                arr[num] = x;
                arr[num]->key = c+'A';
                arr[num]->freq = count[c];
                num += 1;
            }
        }
    }
    bubble_sort(arr,7);
    int i = 0;
    for(i = 0; i < 7; i++)
    {
        printf("Character: %c Position: %d Frequency: %d \n",arr[i]->key,i,arr[i]->freq); 
    }
   node* root = malloc(sizeof(*root));
   root->key = '*';
   root->freq = 10; 
   int m = 6;
   while(m >= 0)
   {
       struct TreeNode* replace = malloc(sizeof(*replace));
       replace->key = '*';
       replace->freq = (arr[m]->freq + arr[m-1]->freq);
       replace->left = arr[m-1];
       replace->right = arr[m];
       if(m != 0){arr[m] = NULL;}
       arr[m-1] = replace;
       m--;
   }
   
   // printf("TEST DATA: %c",arr[0]->left->key);
}
