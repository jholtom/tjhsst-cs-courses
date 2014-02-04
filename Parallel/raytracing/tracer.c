//Jacob Holtom
//
#include <stdio.h>
#define WIDTH 640
#define HIGHT 480
void write(int rgb[HIGHT][WIDTH][3])
{
   int y , x ;
   FILE* fout ;
   fout = fopen( "output.ppm" , "w" ) ;
   fprintf( fout , "P3\n" ) ;
   fprintf( fout , "%d %d\n" , WIDTH , HIGHT ) ;
   fprintf( fout , "255\n" ) ;
   for( y = 0 ; y < HIGHT ; y++ )
   {
      for( x = 0 ; x < WIDTH ; x++)
      {
         fprintf( fout , "%d %d %d\n" ,
          rgb[y][x][0] , rgb[y][x][1] , rgb[y][x][2] ) ;
      }
   }
   close( fout ) ;
}
int main(void){
   int y, x;
   int rgb[HIGHT][WIDTH][3];
    for( y = 0 ; y < HIGHT ; y++ )
   {
      for( x = 0 ; x < WIDTH ; x++)
      {
         rgb[y][x][0] = 0   ; // red
         rgb[y][x][1] = 255 ; // green
         rgb[y][x][2] = 0   ; // blue
      }
   }
   write(rgb);
   return 0;
}
