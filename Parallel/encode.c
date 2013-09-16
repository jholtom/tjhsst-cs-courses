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
node arr[7];
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
      node x;
      arr[num] = x;
      arr[num].key = c+'A';
      arr[num].freq = count[c];
      num += 1;
      }
  }
}
}
