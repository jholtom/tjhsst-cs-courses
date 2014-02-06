//Jacob Holtom
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define W 640
#define H 480
#define for_x for (int x = 0; x < W; x++)
#define for_y for (int y = 0; y < H; y++)
#define for_xy for_x for_y
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

}
int main(void){
   int y, x;
    for( y = 0 ; y < H ; y++ )
   {
      for( x = 0 ; x < W ; x++)
      {
         rgb[y][x][0] = 0   ; // red
         rgb[y][x][1] = 255 ; // green
         rgb[y][x][2] = 0   ; // blue
      }
   }
   write(rgb);
   return 0;
}
