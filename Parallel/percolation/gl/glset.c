// Jacob Holtom - 11/02/13
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#define N 600
#define MAXITER 100
int isMandel(int hx, int hy, double magnify)
{
    double x,xx,y,cx,cy;
    int iteration;
    cx = (((float)hx)/((float)N)-0.5)/magnify*3.0-0.7;
    cy = (((float)hy)/((float)N)-0.5)/magnify*3.0;
    x = 0.0; y = 0.0;
    for(iteration = 1; iteration < MAXITER;iteration++){   
        xx = x*x-y*y+cx;
        y = 2.0*x*y+cy;
        x = xx;
        if (x*x+y*y>100.0)  return 0;
    }
    return 1;
}
void drawSet(int x, int y, int hx, int hy){
    double magnify = 1.0;
    glClear(GL_COLOR_BUFFER_BIT);
    for( x = 0 ; x < N ; x++ )
    {
        for( y = 0 ; y < N ; y++ )
        { 
            if(isMandel(x,y,magnify) == 0) glColor3f( 0.0 , 0.0 , 0.0 );
            else glColor3f( 1.0 , 1.0 , 1.0 );
            glBegin(GL_POINTS);
            glVertex2f(x,y);
            glEnd();
        }
    }
    glutSwapBuffers() ;
}
void displayfunc(void)
{
    int x =0 , y = 0;
    drawSet(x,y,0,0);
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
        printf("Selection made. ");
        printf("At: %d,%d \n",xscr,yscr);
    }
    drawSet(0,0,xscr,yscr);
}
void motionfunc(int xscr,int yscr){
}
void keyfunc(unsigned char key,int xscr,int yscr){
}
void specialfunc(int key,int xscr,int yscr){
}
void closefunc(void){
}
int main(int argc,char* argv[]){  
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(N,N);
    glutInitWindowPosition(100,50);
    glutCreateWindow("");
    glClearColor(1.0,1.0,1.0,0.0);
    glShadeModel(GL_SMOOTH);
    glutDisplayFunc(displayfunc);
    glutReshapeFunc(reshapefunc);
    glutMouseFunc(mousefunc);
    glutMotionFunc(motionfunc);
    glutKeyboardFunc(keyfunc);
    glutSpecialFunc(specialfunc);
    glutWMCloseFunc(closefunc);
    glutMainLoop();
    return 0;
}
