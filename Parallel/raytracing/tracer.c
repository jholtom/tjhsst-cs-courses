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
void init_objects(double spheres[4][7]) {
   // Light
   spheres[0][0] = 0.000000;
   spheres[0][1] = 1.000000;
   spheres[0][2] = -0.500000;
   spheres[0][3] = 0;
   spheres[0][4] = 0;
   spheres[0][5] = 0;
   spheres[0][6] = 0;

   // Sphere 1
   spheres[1][0] = 0.500000;
   spheres[1][1] = 0.500000;
   spheres[1][2] = 0.166667;
   spheres[1][3] = 0.166667;
   spheres[1][4] = 0;
   spheres[1][5] = 0;
   spheres[1][6] = 255;

   // Sphere 2
   spheres[2][0] = 0.833333;
   spheres[2][1] = 0.500000;
   spheres[2][2] = 0.500000;
   spheres[2][3] = 0.166667;
   spheres[2][4] = 0;
   spheres[2][5] = 255;
   spheres[2][6] = 0;

   // Sphere 3
   spheres[3][0] = 0.333333;
   spheres[3][1] = 0.666667;
   spheres[3][2] = 0.666667;
   spheres[3][3] = 0.333333;
   spheres[3][4] = 255;
   spheres[3][5] = 0;
   spheres[3][6] = 0;
}

double fudge(double intersect_point, double center) {
   // This moves the intersection point of the vector and the sphere a bit off the sphere to avoid it colliding with itself
   if(intersect_point > center) {
      return intersect_point - .000001;
   }
   else {
      return intersect_point + .000001;
   }
}

double dot_product(double intersect[3], double spheres[4][7], int sphere) {
   // Create the vector of the normal of the sphere and make it a unit vector
   double ray_x_normal = intersect[0] - spheres[sphere][0];
   double ray_y_normal = intersect[1] - spheres[sphere][1];
   double ray_z_normal = intersect[2] - spheres[sphere][2];

   double magn_ray_normal = sqrt(ray_x_normal*ray_x_normal+ray_y_normal*ray_y_normal+ray_z_normal*ray_z_normal);

   ray_x_normal = ray_x_normal / magn_ray_normal;
   ray_y_normal = ray_y_normal / magn_ray_normal;
   ray_z_normal = ray_z_normal / magn_ray_normal;

   // Do the same thing for the vector of the intersection to the light
   double ray_x_light = spheres[0][0] - intersect[0];
   double ray_y_light = spheres[0][1] - intersect[1];
   double ray_z_light = spheres[0][2] - intersect[2];

   double magn_ray_light = sqrt(ray_x_light*ray_x_light+ray_y_light*ray_y_light+ray_z_light*ray_z_light);

   ray_x_light = ray_x_light / magn_ray_light;
   ray_y_light = ray_y_light / magn_ray_light;
   ray_z_light = ray_z_light / magn_ray_light;

   // Find the dot product
   double dot = (ray_x_normal * ray_x_light) + (ray_y_normal * ray_y_light) + (ray_z_normal * ray_z_light);

   return dot;
}

double floor_dot_product(double intersect[3], double spheres[4][7], double floor_y) {
   // Create the normal vector of the floor
   double ray_x_normal = 0;
   double ray_y_normal = 1;
   double ray_z_normal = 0;
   
   // Create the vector from the intersection to the light and make it a unit vector
   double ray_x_light = spheres[0][0] - intersect[0];
   double ray_y_light = spheres[0][1] - intersect[1];
   double ray_z_light = spheres[0][2] - intersect[2];

   double magn_ray_light = sqrt(ray_x_light*ray_x_light+ray_y_light*ray_y_light+ray_z_light*ray_z_light);

   ray_x_light = ray_x_light / magn_ray_light;
   ray_y_light = ray_y_light / magn_ray_light;
   ray_z_light = ray_z_light / magn_ray_light;

   // Find and return the dot product
   double dot = (ray_x_normal * ray_x_light) + (ray_y_normal * ray_y_light) + (ray_z_normal * ray_z_light);

   return dot;
}

double distance_to_object(double start_x, double start_y, double start_z, double end_x, double end_y, double end_z, double spheres[4][7], int sphere, double intersect[3]) {
   // Vector from start to end point
   double ray_x = end_x - start_x;
   double ray_y = end_y - start_y;
   double ray_z = end_z - start_z;

   // Magnitude of vector
   double magn_ray = sqrt(ray_x*ray_x+ray_y*ray_y+ray_z*ray_z);

   // Make it a unit vector
   ray_x = ray_x / magn_ray;
   ray_y = ray_y / magn_ray;
   ray_z = ray_z / magn_ray;

   // Ignore this, it's for the next part
   double coefficient_1 = start_x - spheres[sphere][0];
   double coefficient_2 = start_y - spheres[sphere][1];
   double coefficient_3 = start_z - spheres[sphere][2];

   // Create a quadratic
   double a = (ray_x*ray_x)+(ray_y*ray_y)+(ray_z*ray_z);
   double b = 2*((coefficient_1*ray_x)+(coefficient_2*ray_y)+(coefficient_3*ray_z));
   double c = (coefficient_1*coefficient_1)+(coefficient_2*coefficient_2)+(coefficient_3*coefficient_3)-(spheres[sphere][3]*spheres[sphere][3]);

   // Find the discriminant
   double discrim = ((b*b)-4*a*c);

   if(discrim < 0) {
      return -1;
   }
   else {
      double T = ((b*-1)-sqrt((b*b)-4*a*c))/(2*a);

      intersect[0] = fudge(((T * ray_x) + start_x), spheres[sphere][0]);
      intersect[1] = fudge(((T * ray_y) + start_y), spheres[sphere][1]);
      intersect[2] = fudge(((T * ray_z) + start_z), spheres[sphere][2]);
      
      return T;
   }
}

double distance_to_floor(double start_x, double start_y, double start_z, double end_x, double end_y, double end_z, double floor_y, double intersect[3]) {
   // Creat vector from start to end and make it a unit vector
   double ray_x = end_x - start_x;
   double ray_y = end_y - start_y;
   double ray_z = end_z - start_z;

   double magn_ray = sqrt(ray_x*ray_x+ray_y*ray_y+ray_z*ray_z);

   ray_x = ray_x / magn_ray;
   ray_y = ray_y / magn_ray;
   ray_z = ray_z / magn_ray;

   // If the ray is pointing up do nothing, otherwise calculate intersection and return distance
   if(ray_y > 0) {
      return -1;
   }
   else {
      double T = (floor_y - start_y) / ray_y;

      intersect[0] = (T * ray_x) + start_x;
      intersect[1] = (T * ray_y) + start_y;
      intersect[2] = (T * ray_z) + start_z;     

      return T;
   }
}

int in_shadow(double start_x, double start_y, double start_z, double spheres[4][7], int ignore) {
   int sphere;
   double intersect[3];
   // See if a ray hits anything on its way towards the light
   for(sphere = 0; sphere < 3; sphere++) {
      double T = distance_to_object(start_x, start_y, start_z, spheres[0][0], spheres[0][1], spheres[0][2], spheres, sphere+1, intersect);
      if(T > 0 && sphere+1 != ignore) {
         return 1;
      }
   }
   return 0;
}

int main(void) {
   // Some variables
   int rgb[H][W][3];
   int y, x, q, k;
   double spheres[4][7];

   // Eye
   double ex = 0.500000;
   double ey = 0.500000;
   double ez = -1.000000;

   // Screen
   double sz = 0.000000;

   // Floor
   double fy = 0.333333;

   init_objects(spheres);

   FILE* fout ;

   // More variables
   int current = 1;
   double min_val = 999;
   int min_index = -1;
   double px, py, pz, T;
   double intersect[3];

   // For each pixel
   for(y=0; y<H; y++) {
      for(x=0; x<W; x++) {
         double min_val = 999;
         int min_index = -1;

         // For each object
         for(q=0; q<3; q++) {
            current = q;
            py = 1-(y*1.0/H);
            px = (x*1.0/W);
            pz = sz;

            T = distance_to_object(ex, ey, ez, px, py, pz, spheres, q+1, intersect);

            // Pick which ovject is closest
            if (T > 0 && T < min_val) {
               min_index = current;
               min_val = T;
            }
         }

         // If the ray misses the stuff
         if (min_index == -1) {
            T = distance_to_floor(ex, ey, ez, px, py, pz, fy, intersect);
            int shadow = in_shadow(intersect[0], intersect[1], intersect[2], spheres, -1);
            double dot_p = floor_dot_product(intersect, spheres, fy);
            int color;
            int current_color;

            // If it misses the floor too
            if (distance_to_floor(ex, ey, ez, px, py, pz, fy, intersect) == -1) {
               rgb[y][x][0] = 0;
               rgb[y][x][1] = 0;
               rgb[y][x][2] = 0;
            }

            // If it hits the floor, figure out the color
            else {

               int floor_coord_x = (int)(intersect[0]/.05);
               int floor_coord_z = (int)(intersect[2]/.05);

               for(color = 0; color < 3; color++) {
                  if((floor_coord_z+floor_coord_x) % 2 == 0) {
                     if(color == 2) {
                        current_color = 0;
                     }
                     else {
                        current_color = 255;
                     }
                  }
                  else {
                     if(color == 1) {
                        current_color = 0;
                     }
                     else {
                        current_color = 255;
                     }
                  }
                  if(shadow == 1) {
                     rgb[y][x][color] = current_color * .5;
                  }
                  else {
                     rgb[y][x][color] = current_color * (.5 * (1 - shadow) + .5 * dot_p);
                  }
               }
            }
         }
         // If it hits a sphere
         else {
            T = distance_to_object(ex, ey, ez, px, py, pz, spheres, min_index+1, intersect);

            // Calculate some stuff about where it hits
            int shadow = in_shadow(intersect[0], intersect[1], intersect[2], spheres, min_index+1);
            double dot_p = dot_product(intersect, spheres, min_index+1);

            int color;

            for(color = 0; color < 3; color++) {
               int current_color = spheres[min_index+1][color+4];
               if(shadow == 1) {
                  rgb[y][x][color] = current_color * .5;
               }
               else {
                  rgb[y][x][color] = current_color * (.5 * (1 - shadow) + .5 * dot_p);
               }
            }
         }
      }
   }

   fout = fopen( "raytrace.ppm" , "w" ) ;
   
   fprintf( fout , "P3\n" ) ;
   fprintf( fout , "%d %d\n" , W , H ) ;
   fprintf( fout , "255\n" ) ;
   
   for( y = 0 ; y < H ; y++ )
   {
      for( x = 0 ; x < W ; x++)
      {
         fprintf( fout , "%d %d %d\n" ,
          rgb[y][x][0] , rgb[y][x][1] , rgb[y][x][2] ) ;
      }
   }
   close( fout ) ;
   
   return 0 ;
}
