//Jacob Holtom - Error
//12/12/13
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#define LEN 41
#define LEN2 1000
double sm( double y ) {
    return 1.0 / (1.0 + exp(-y));
}
int bit( double x ) {
    if(((double)rand() / (double)(RAND_MAX - 1)) < x) return 1;
    return 0;
}
int main(int argc,char* argv[]){
    srand(time(NULL));
    double i = 0.0;
    for(i = (-1.0)*LEN; i <= LEN; i += 0.25)
    {
        double x = 0.0;
        int k = 0;
        int c = 0;
        for(k = 0; k < LEN; k++)
        {
            if(bit(i) == 1) c++;
        }
        for(x = (-1.0)*LEN2; x <= LEN2; x += 63.25)
        {
            double gen = 0.0;
            gen = sm(c/100.0);
            printf("\t%f\t%f\t%f\n",i,x,gen);
        }
        printf("\n");
    }
    return 0;
}
