//Jacob Holtom
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define W 640
#define H 480
#define for_x for (int x = 0; x < W; x++)
#define for_y for (int y = 0; y < H; y++)
#define for_yx for_y for_x
int rgb[H][W][3];
void write(int rgb[H][W][3])
{
    int y , x ;
    FILE* fout ;
    fout = fopen( "output.ppm" , "w" ) ;
    fprintf( fout , "P3\n" ) ;
    fprintf( fout , "%d %d\n" , W , H ) ;
    fprintf( fout , "255\n" ) ;
    for( y = 0 ; y < H ; y++ )
    {
        for( x = 0 ; x < W ; x++)
        {
            fprintf( fout , "%d %d %d\n" , rgb[y][x][0] , rgb[y][x][1] , rgb[y][x][2] ) ;
        }
    }
    close( fout ) ;
}
void tracer(int rgb[H][W][3]){
    float s0cx = 0.5;
    float s0cy = 0.5;
    float s0cz = 0.166667;

    float s1cx = 0.833333;
    float s1cy = 0.5;
    float s1cz = 0.5;

    float s2cx = 0.333333;
    float s2cy = 0.666667;
    float s2cz = 0.666667;

    float floh = 0.333333;

    float ex = 0.5;
    float ey = 0.5;
    float ez = 1.0;

}
int main(void){
    int y, x;
    for_yx {
        rgb[y][x][0] = 0   ; // red
        rgb[y][x][1] = 255 ; // green
        rgb[y][x][2] = 0   ; // blue
    }
    write(rgb);
    return 0;
}
