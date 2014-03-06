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
double dtf(double sx, double sy, double sz, double enx, double eny, double enz, double floh, double intersect[3]) {
    double rx = enx - sx;
    double ry = eny - sy;
    double rz = enz - sz;
    double mr = sqrt(rx*rx+ry*ry+rz*rz);
    rx = rx / mr;
    ry = ry / mr;
    rz = rz / mr;
    if(ry > 0)
    {
        return -1;
    }
    else 
    {
        double T = (floh - sy) / ry;
        intersect[0] = (T * rx) + sx;
        intersect[1] = (T * ry) + sy;
        intersect[2] = (T * rz) + sz;     
        return T;
    }
}
double dto(double sx, double sy, double sz, double enx, double eny, double enz, double intersect[3],sphere s) {
    double rx = enx - sx;
    double ry = eny - sy;
    double rz = enz - sz;
    double mr = sqrt(rx*rx+ry*ry+rz*rz);
    rx = rx / mr;
    ry = ry / mr;
    rz = rz / mr;
    double c1 = sx - s.x;
    double c2 = sy - s.y;
    double c3 = sz - s.z;
    double a = (rx*rx)+(ry*ry)+(rz*rz);
    double b = 2*((c1*rx)+(c2*ry)+(c3*rz));
    double c = (c1*c1)+(c2*c2)+(c3*c3)-(s.rad*s.rad);
    double discrim = ((b*b)-4*a*c);
    if(discrim < 0) 
    {
        return -1;
    }
    else 
    {
        double T = ((b*-1)-sqrt((b*b)-4*a*c))/(2*a);
        intersect[0] = (T * rx) + sx;
        intersect[1] = (T * ry) + sy;
        intersect[2] = (T * rz) + sz;
        return T;
    }
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
    s0.x = 0.500000; 
    s0.y = 0.500000;
    s0.z = 0.166667;
    s0.rad = 0.166667;
    s0.r = 0;
    s0.g = 0;
    s0.b = 255;
    s1.x = 0.833333; 
    s1.y = 0.500000;
    s1.z = 0.500000;
    s1.rad = 0.166667;
    s1.r = 0;
    s1.g = 255;
    s1.b = 0;
    s2.x = 0.333333;
    s2.y = 0.666667;
    s2.z = 0.666667;
    s2.rad = 0.333333;
    s2.r = 255;
    s2.g = 0;
    s2.b = 0;
    r0.x = 0.000000; 
    r0.y = 1.000000;
    r0.z = -0.500000;
    double ex = 0.500000;
    double ey = 0.500000;
    double ez = -1.000000;
    double sz = 0.000000;
    double fy = 0.333333;
    int current = 1;
    double mv = 999;
    int mi = -1;
    double px, py, pz, T;
    double intersect[3];
    int y, x,q,k;
    for_yx {
        double mv = 999;
        int mi = -1;
        for(q=0; q<3; q++) {
            current = q;
            py = 1-(y*1.0/H);
            px = (x*1.0/W);
            pz = sz;
            if( q == 0){
                T = dto(ex, ey, ez, px, py, pz,intersect, s0);
            }
            if( q == 1){
                T = dto(ex, ey, ez, px, py, pz, intersect, s1);
            }
            if( q == 2){
                T = dto(ex, ey, ez, px, py, pz, intersect, s2);
            }
            if (T > 0 && T < mv) {
                mi = current;
                mv = T;
            }
        }
        if (mi == -1) {
            T = dtf(ex, ey, ez, px, py, pz, fy, intersect);
            int color;
            int current_color;
            if (dtf(ex, ey, ez, px, py, pz, fy, intersect) == -1) {
                rgb[y][x][0] = 0;
                rgb[y][x][1] = 0;
                rgb[y][x][2] = 0;
            }
            else {
                pixel(rgb,y,x,0,0,255);    
            }
        }
    }
    if(mi+1 == 0){ T = dto(ex, ey, ez, px, py, pz, intersect, s0); 
    pixel(rgb,y,x,s0.r,s0.g,s0.b);
    }
    if(mi+1 == 1){ T = dto(ex, ey, ez, px, py, pz, intersect, s1); 
    pixel(rgb,y,x,s1.r,s1.g,s1.b);
    }
    if(mi+1 == 2){ T = dto(ex, ey, ez, px, py, pz, intersect, s2); 
    pixel(rgb,y,x,s2.r,s2.g,s2.b);
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
