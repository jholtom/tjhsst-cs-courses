//Jacob Holtom - Oct, 02, 2013
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRX 80
#define ARRY 40
#define PROB 70

void draw_array(char[ARRX][ARRY]);
void draw_array(char field[ARRX][ARRY]){
    int x,y;
    for(x = 0; x < ARRY; x++)
    {
        for(y = 0; y < ARRX; y++)
        {
            printf("%c",field[x][y]);
        }
        printf("\n");
    }
}
void process_fire(char[ARRX][ARRY]);
void process_fire(char field[ARRX][ARRY])
{

}
int main(void){
    char field[ARRX][ARRY];
    int k;
    int m;
    srand(time(NULL));
    for(k = 0; k < ARRY; k++){
        for(m = 0; m < ARRX; m++)
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
    draw_array(field);
    return 0;
}
