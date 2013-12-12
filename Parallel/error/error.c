//Jacob Holtom - Error and whatnot
//12/12/13
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
double sm( double y ) {
return 1.0 / (1.0 + exp(-y));
}
int bit( double x ) {
if(((double)rand() / (double)(RAND_MAX - 1)) < x) return 1;
return 0;
}
int main(void){
    srand(time(NULL));
    return 0;
}
