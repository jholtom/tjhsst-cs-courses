//Jacob Holtom - Sept 10, 2013
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct TreeNode {
    char key;
    int freq;
    struct TreeNode* left;
    struct TreeNode* right;
} node;
void main(void)
{
char* msg = "HELLOWORLD";
node* arr[7];
int c = 0, count[26] = {0};
while( msg[c] != '\0')
{
   if( msg[c] >= 'a' && msg[c] <= 'z' )
       count[msg[c]-'a']++;

   c++;
}
for(c = 0; c < 26; c++)
{
  if( count[c] != 0 )
      printf("%c occured %d times.\n",c+'a',count[c]);
}
int num = 7;
int i;
for(i = 0; i<7;i++)
{
}
}
