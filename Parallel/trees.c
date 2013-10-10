//Jacob Holtom - Oct, 02, 2013
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ARRX 100
#define ARRY 100

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
    char field_buffer[ARRX][ARRY];

    int k,j;

    for( k = 0; k < ARRX; k++)
    {
        for( j = 0; j < ARRY; j++)
        {
            field_buffer[k][j] = field[k][j];
        }
    }
    //Doesn't work...ask torbert
    //memcpy(&field_buffer,&field,sizeof(field));
    for( k = 0; k < ARRX; k++)
    {
        for( j = 0; j < ARRY; j++)
        {
            if( field[k][j] == '*')
            {
                if( field[k][j+1] == 'T' && (j+1) <= ARRY )
                {
                    field_buffer[k][j+1] = '*'; 
                }  
                if( field[k][j-1] == 'T' && (j-1) >= 0 )
                {
                    field_buffer[k][j-1] = '*';
                }  
                if( field[k+1][j] == 'T' && (k+1) <= ARRX )
                {
                    field_buffer[k+1][j] = '*';
                }  
                if( field[k-1][j] == 'T' && (k-1) >=  0 )
                {
                    field_buffer[k-1][j] = '*';
                } 
                if((field[k][j+1] == '*' || field[k][j+1] == ' ') && (j+1) <= ARRY )
                {
                    field_buffer[k][j] = ' '; 
                }  
                if((field[k][j-1] == '*' || field[k][j-1] == ' ') && (j-1) >= 0 )
                {
                    field_buffer[k][j] = ' ';
                }  
                if((field[k+1][j] == '*' || field[k+1][j] == ' ')  && (k+1) <= ARRX )
                {
                    field_buffer[k][j] = ' ';
                }  
                if((field[k-1][j] == '*' || field[k+1][j] == ' ') && (k-1) >=  0 )
                {
                    field_buffer[k][j] = ' ';
                }
            }
        }
    }

    for( k = 0; k < ARRX; k++)
    {
        for( j = 0; j < ARRY; j++)
        {
            field[k][j] = field_buffer[k][j];
        }
    }
}
int isfire(char[ARRX][ARRY]);
int isfire(char field[ARRX][ARRY])
{
    int l,z;
    for(l = 0; l < ARRX; l++)
    {
        for(z = 0; z < ARRY; z++)
        {
            if(field[l][z] == '*')
            {
                return 1;
            }
        }
    }
    return 0;
}
int compute(int);
int compute(int prob){
    char field[ARRX][ARRY];
    int k;
    int m;
    srand(time(NULL));
    for(k = 0; k < ARRX; k++){
        for(m = 0; m < ARRY; m++)
        {
            if((rand()%100 + 1) < prob)
            {
                field[k][m] = 'T';
            }
            else{
                field[k][m] = ' ';
            }
        }
    }
    //draw_array(field);
    //sleep(2);
    //system("clear");
    int z;
    for(z = 0; z < ARRX; z++)
    {
        if( field[z][0] == 'T' ) field[z][0] = '*';
    }
    //draw_array(field);
    //sleep(2);
    int steps = 0;
    //system("clear");
    while(isfire(field) != 0)
    {
        process_fire(field);
        //ENABLE OR DISABLE DRAWING...
        //draw_array(field);
        //sleep(1);
        //system("clear");
        steps++;
    }
    //draw_array(field);
    //printf("NUMBER OF STEPS IS: %d\n",steps);
    return steps;
}

int main(void){
    int avgs[100];
    int numtrials = 100;
    int i;
    int k = 0;
    for(i = 0; i <= 100; i += 1)
    {
        //printf("PROBABILITY IS: %d\n",i);
        int m,total;
        for( m = 0; m < numtrials; m++){
            total += compute(i);
        }
        avgs[k] = total / numtrials;
        printf("%d %d\n",i,avgs[k]);
        k++;
        total = 0;
    }
    return 0;
}
