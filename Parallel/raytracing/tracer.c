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
typedef struct sphere {
    int r,g,b;
    float x,y,z,rad;
} sphere;
typedef struct light {
    float x,y,z;
} light;
void pixel(int rgb[H][W][3], int x, int y, int r, int g, int b)
{
        rgb[y][x][0] = r; // red
        rgb[y][x][1] = g; // green
        rgb[y][x][2] = b; // blue
}
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
    sphere s0,s1,s2;
    light r0;
    //Sphere 0
    s0.x = 0.500000; 
    s0.y = 0.500000;
    s0.z = 0.166667;
    s0.rad = 0.166667;
    s0.r = 0;
    s0.g = 0;
    s0.b = 255;
    //Sphere 1
    s1.x = 0.833333; 
    s1.y = 0.500000;
    s1.z = 0.500000;
    s1.rad = 0.166667;
    s1.r = 0;
    s1.g = 255;
    s1.b = 0;
    //Sphere 2
    s2.x = 0.333333;
    s2.y = 0.666667;
    s2.z = 0.666667;
    s2.rad = 0.333333;
    s2.r = 255;
    s2.g = 0;
    s2.b = 0;
    //Light
    r0.x = 0.000000; 
    r0.y = 1.000000;
    r0.z = -0.500000;

    int y, x;
    for_yx {
        float px, py, pz;
        px = (x * 1.0) / W; 
        py = (y * 1.0) / H;
        pz = 0.0; 

        float rx, ry, rz;
        rx = (px - ex); 
        ry = (py - ey);
        rz = (pz - ez);

        float mx, my, mz;
        mx = ex + T * rx;
        my = ey + T * ry;
        mz = ez + T * rz;
        
        float a = 0.0;
        float b = 0.0;
        float c = 0.0;
        float T = 0.0; 
        // (-b + sqrt(b^2 - 4ac)) / 2a if discriminant is less than 0 then it misses
        //(mx - cx)^2 + (my - cy)^2 + (mz - cz)^2 = r^2
        if ((square(b) - (4*a*c)) < 0 ){
        pixel(rgb,y,x,255,0,0); 
        }
        else
        {
        pixel(rgb,y,x,0,255,0); 
        }
    }
}
void black(int rgb[H][W][3]){
    int y, x;
    for_yx {
        pixel(rgb,y,x,0,0,0);
    }
}
int main(void){
    black(rgb);
    tracer(rgb);
    write(rgb);
    return 0;
}
