//Jacob Holtom - Oct, 02, 2013
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define ARRX 40
#define ARRY 80
#define PROB 70

void draw_array(char[ARRX][ARRY]);
void draw_array(char field[ARRX][ARRY]){
    int x,y;
    for(x = 0; x < ARRX; x++)
    {
        for(y = 0; y < ARRY; y++)
        {
            printf("%c",field[x][y]);
        }
        printf("\n");
    }
}
void process_fire(char[ARRX][ARRY]);
void process_fire(char field[ARRX][ARRY]){
    int k,j;
    for( k = 0; k < ARRX; k++)
    {
        for( j = 0; j < ARRY; j++)
        {
            if( field[k][j] == '*')
            {
                if( field[k][j+1] == 'T' && (j+1) <= ARRY )
                {
                    field[k][j+1] = '*'; 
                }  
                if( field[k][j-1] == 'T' && (j-1) >= 0 )
                {
                    field[k][j-1] = '*';
                }  
                if( field[k+1][j] == 'T' && (k+1) <= ARRX )
                {
                    field[k+1][j] = '*';
                }  
                if( field[k-1][j] == 'T' && (k-1) >=  0 )
                {
                    field[k-1][j] = '*';
                } 
            }
        }
    }
}
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
    draw_array(field);
    sleep(2);
    system("clear");
    int z;
    for(z = 0; z < ARRX; z++)
    {
        if( field[z][0] == 'T' ) field[z][0] = '*';
    }
    draw_array(field);
    sleep(2);
    process_fire(field);
    system("clear");
    draw_array(field);
    return 0;
}
