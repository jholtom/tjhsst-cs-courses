#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#define N  2
#define DT 0.00001
typedef struct
{
   double vx , vy , vz ;
   double  x ,  y ,  z ;
   double r ;
   double m ;
} Body;
Body nbody[N];
double rho,phi,theta,up=1.0;
double xc,yc,zc,xe,ye,ze;
void look()
{
   xe=xc+rho*sin(theta)*cos(phi);
   ye=zc+rho*cos(theta);
   ze=yc+rho*sin(theta)*sin(phi);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt(xe,ye,ze, xc,yc,zc, 0.0,up,0.0);
}
void display(void)
{
   int j;
   glMatrixMode(GL_MODELVIEW);
   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(0.0,0.0,0.0);
   for(j=0;j<N;j++)
   { 
      glPushMatrix();
      glTranslated(nbody[j].x,nbody[j].y,nbody[j].z);
      glRotated(90.0,1.0,0.0,0.0);
      glutWireSphere(nbody[j].r,24,12);
      //glutWireTeapot(nbody[j].r);
      glPopMatrix();
   }
   glutSwapBuffers();
}
void idle(void)
{
   int j,k;
   double dx,dy,dz,dmag,fmag;
   double ax[N],ay[N],az[N];
   // vx += ax * DT
   //  x += vx * DT
   look();
   glutPostRedisplay();
}
void mouse(int button,int state,int xscr,int yscr)
{
   look();
   glutPostRedisplay();
}
void motion(int xscr,int yscr)
{
   // change phi ... or theta and up
   printf("%d, %d\n",xscr,yscr);

   look();
   glutPostRedisplay();
}
void mouse_wheel(int wheel,int direction,int xscr,int yscr)
{
   // change rho
   printf("wheel: %d; direc: %d, xscr: %d, yscr: %d\n",wheel,direction,xscr,yscr);
   look();
   glutPostRedisplay();
}
void keyfunc(unsigned char key,int xscr,int yscr)
{
   if(key=='q')
   {
      exit(0);
   }
}
void reshape(int wscr,int hscr)
{
   GLfloat aspect_ratio;
   aspect_ratio=(GLfloat)wscr/(GLfloat)hscr;
   glViewport(0,0,(GLsizei)wscr,(GLsizei)hscr);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(60.0,aspect_ratio,0.1,500.0);
   look();
}
int main(int argc,char* argv[])
{  
   rho=1.0;
   phi=0.5*M_PI;
   theta=0.5*M_PI;
   xc=yc=zc=0.0;
   nbody[0].m=10000.0; // sun
   nbody[0].r=0.2;
   nbody[0].x=0.0;
   nbody[0].y=0.0;
   nbody[0].z=0.0;
   nbody[0].vx=0.0;
   nbody[0].vy=0.0;
   nbody[0].vz=0.0;
   nbody[1].m=100.0; // earth
   nbody[1].r=0.01;
   nbody[1].x=0.45;
   nbody[1].y=0.0;
   nbody[1].z=0.0;
   nbody[1].vx=0.0;
   nbody[1].vy=0.0;
   nbody[1].vz=0.0;
   glutInit(&argc,argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize(800,600);
   glutInitWindowPosition(100,50);
   glutCreateWindow("Sun Earth Moon");
   glClearColor(1.0,1.0,1.0,0.0);
   glShadeModel(GL_SMOOTH);
   glutDisplayFunc(display);
   glutIdleFunc(idle);
   glutMouseFunc(mouse);
   glutMotionFunc(motion);
   glutMouseWheelFunc(mouse_wheel);
   glutKeyboardFunc(keyfunc);
   glutReshapeFunc(reshape);
   glutMainLoop();
   return 0;
}
