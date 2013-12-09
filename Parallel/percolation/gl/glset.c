// Jacob Holtom - 11/02/13
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#define N 600
int zoomStatus = 0;
int xA, yA;
int xB, yB;
double itermax = 256.0;
int w = N;
int h = N;
double cxm = -2.0;
double cxx =  2.0;
double cym = -1.5;
double cyx =  1.5;
void displayfunc(void)
{
   int x, y;
   glClear(GL_COLOR_BUFFER_BIT);
   int width = N;
   int height = N;
   double t = 0.0;
   double xStep = (cxx - cxm) / width;
   double yStep = (cyx - cym) / height;
   double cx, cy;
   double a,b;
   double a2, b2;
   for( x = 0 ; x < width ; x++ )
   {
	  for( y = 0 ; y < height ; y++ )
      { 
		 cx = (x * xStep) + cxm;
		 cy = (y * yStep) + cym;
		 a  = 0.0 ;
		 b  = 0.0 ;
		 t  = 0.0 ;
		 while ((a*a+b*b < 4) && t < itermax) {
			a2 = a;
			b2 = b;
			a = (a2*a2) - (b2*b2) + cx;
			b = (2 * a2 * b2) + cy;
			t += 1.0;
		 }
		 glColor3f( 0.0 , 0.0 , 1 - t/itermax ) ;
         glBegin(GL_POINTS);
         glVertex2f(x,y);
         glEnd();
      }
   }
   glutSwapBuffers() ;
   printf("cxm: %E; cxx: %E\n", cxm, cxx);
   printf("cym: %E; cyx: %E\n", cym, cyx);
}
void reshapefunc(int wscr,int hscr)
{
    glViewport(0,0,(GLsizei)N,(GLsizei)N);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,1.0*N,0.0,1.0*N);
    glMatrixMode(GL_MODELVIEW);
}
void mousefunc(int button,int state,int xscr,int yscr){
   if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
   {
	  if (zoomStatus == 0) {
	     xA = xscr;
		 yA = N - yscr;
		 zoomStatus = 1;
		 itermax = 256.0;
	  }
	  else if (zoomStatus == 1) {
	     zoomStatus = 0;
		 xB = xscr;
		 yB = N - yscr;
		 int width = N;
		 int height = N;
		 w = (xB-xA);
		 h = (3.0/4.0) * w;
		 yB = yA - h;
		 double xStep = (cxx - cxm) / width;
		 double yStep = (cyx - cym) / height;
		 double cxmNew = (xA * xStep) + cxm;
		 double cymNew = (yB * yStep) + cym;
		 double cxxNew = (xB * xStep) + cxm;
		 double cyxNew = (yA * yStep) + cym;
		 cxm = cxmNew;
		 cxx = cxxNew;
		 cym = cymNew;
		 cyx = cyxNew;
		 glutPostRedisplay();
	  }
   }
   else if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
   {
	  itermax *= 2;
	  glutPostRedisplay();
   }
}
int main(int argc,char* argv[]){  
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(N,N);
    glutInitWindowPosition(100,50);
    glutCreateWindow("");
    glClearColor(0.0,0.0,0.0,0.0);
    glShadeModel(GL_SMOOTH);
    glutDisplayFunc(displayfunc);
    glutReshapeFunc(reshapefunc);
    glutMouseFunc(mousefunc);
    glutMainLoop();
    return 0;
}
