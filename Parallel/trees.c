//Jacob Holtom - Oct, 02, 2013
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRX 80
#define ARRY 80

void draw_array(char[][]);
void draw_array(char arr[][]){
int x = 0;
int y = 0;
for(x = 0; x < ARRY; x++)
{
for(y = 0; y < ARRX; y++)
{
printf("%s",arr[x][y]);
}
printf("\n");
}
} 

void main(void){

}
