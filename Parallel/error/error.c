//Jacob Holtom - error
//12/12/13
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
//Number defintions
#define NUMPAT 6
#define NUMIN  2
#define NUMHID 4
#define NUMOUT 2
//Function defintions
double bit(){
    return ((double)rand()/((double)(RAND_MAX) + 1.0));
}
double sm( double y ) {
    return 1.0 / (1.0 + exp(-y));
}
//Main
int main(int argc,char* argv[]){
    srand(time(NULL));
    //Local Variables
    int    i, j, k, p, np, op, ranpat[NUMPAT+1], epoch;
    int    npa = NUMPAT, Numin = NUMIN, Numh = NUMHID, Numout = NUMOUT;
    double in[NUMPAT+1][NUMIN+1] = { 0, 0, 0,  0, 0, 0,  0, 1, 0,  0, 0, 1,  0, 1, 1 };
    double epocherr[10000] = {0};
    double targ[NUMPAT+1][NUMOUT+1] = { 0, 0,  0, 0,  0, 1,  0, 1,  0, 0 };
    double sh[NUMPAT+1][NUMHID+1], wih[NUMIN+1][NUMHID+1], h[NUMPAT+1][NUMHID+1];
    double so[NUMPAT+1][NUMOUT+1], who[NUMHID+1][NUMOUT+1], out[NUMPAT+1][NUMOUT+1];
    double deo[NUMOUT+1], sdow[NUMHID+1], dh[NUMHID+1];
    double dwih[NUMIN+1][NUMHID+1], dwho[NUMHID+1][NUMOUT+1];
    double error, eta = 0.5, alpha = 0.9, smallwt = 0.5;
    //Initializer loops
    for( j = 1 ; j <= Numh ; j++ ) {
        for( i = 0 ; i <= Numin ; i++ ) {
            dwih[i][j] = 0.0 ;
            wih[i][j] = 2.0 * ( bit() - 0.5 ) * smallwt ;
        }
    }
    for( k = 1 ; k <= Numout ; k ++ ) {
        for( j = 0 ; j <= Numh ; j++ ) {
            dwho[j][k] = 0.0 ;              
            who[j][k] = 2.0 * ( bit() - 0.5 ) * smallwt ;
        }
    }
    //Main loop
    for( epoch = 0 ; epoch < 10000 ; epoch++) {
        for( p = 1 ; p <= npa ; p++ ) {    
            ranpat[p] = p ;
        }
        for( p = 1 ; p <= npa ; p++) {
            np = p + bit() * ( npa + 1 - p ) ;
            op = ranpat[p] ; ranpat[p] = ranpat[np] ; ranpat[np] = op ;
        }
        error = 0.0 ;
        for( np = 1 ; np <= npa ; np++ ) {
            p = ranpat[np];
            for( j = 1 ; j <= Numh ; j++ ) {
                sh[p][j] = wih[0][j] ;
                for( i = 1 ; i <= Numin ; i++ ) {
                    sh[p][j] += in[p][i] * wih[i][j] ;
                }
                h[p][j] = sm(sh[p][j]) ;
            }
            for( k = 1 ; k <= Numout ; k++ ) {
                so[p][k] = who[0][k] ;
                for( j = 1 ; j <= Numh ; j++ ) {
                    so[p][k] += h[p][j] * who[j][k] ;
                }
                out[p][k] = sm(so[p][k]) ; 
                error += 0.5 * (targ[p][k] - out[p][k]) * (targ[p][k] - out[p][k]) ;
                deo[k] = (targ[p][k] - out[p][k]) * out[p][k] * (1.0 - out[p][k]) ;
            }
            for( j = 1 ; j <= Numh ; j++ ) {    
                sdow[j] = 0.0 ;
                for( k = 1 ; k <= Numout ; k++ ) {
                    sdow[j] += who[j][k] * deo[k] ;
                }
                dh[j] = sdow[j] * h[p][j] * (1.0 - h[p][j]) ;
            }
            for( j = 1 ; j <= Numh ; j++ ) {
                dwih[0][j] = eta * dh[j] + alpha * dwih[0][j] ;
                wih[0][j] += dwih[0][j] ;
                for( i = 1 ; i <= Numin ; i++ ) { 
                    dwih[i][j] = eta * in[p][i] * dh[j] + alpha * dwih[i][j];
                    wih[i][j] += dwih[i][j] ;
                }
            }
            for( k = 1 ; k <= Numout ; k ++ ) {
                dwho[0][k] = eta * deo[k] + alpha * dwho[0][k] ;
                who[0][k] += dwho[0][k] ;
                for( j = 1 ; j <= Numh ; j++ ) {
                    dwho[j][k] = eta * h[p][j] * deo[k] + alpha * dwho[j][k] ;
                    who[j][k] += dwho[j][k] ;
                }
            }
        }
        epocherr[epoch] = error;
    }
    double z = -40;
    int count = 0;
    double x = -1490;
    for(z = -40; z < 40; z += 2.25){
    for(x = -1490; x < 1000; x += 62.25){
    printf("\t%f\t%f\t%f\n",z,x,epocherr[count]);
    count++;
    }
    printf("\n");
    }
    return 0;
}
