//Jacob Holtom - Oct, 02, 2013
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRX 8
#define ARRY 8
#define PROB 70

int main(void){
    char field[ARRX][ARRY];
    int k;
    int m;
    srand(time(NULL));
    for(k = 0; k < ARRX; k++){
        for(m = 0; m < ARRY; m++)
        {
            if((rand()%100 + 1) < PROB)
            {
                field[k][m] = 'T';
            }
            else{
                field[k][m] = ' ';
            }
        }
    }
    int x,y;
for(x = 0; x < ARRY; x++)
    {
        for(y = 0; y < ARRX; y++)
        {
            printf("%c",field[x][y]);
        }
        printf("\n");
    }
    return 0;
}
