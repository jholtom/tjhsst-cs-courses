// Jacob Holtom - 11/02/13
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#define N 600
#define MAXITER 100
#define magnify 1.0 //Magnifies at the origin (center of graph)
int isMandel(int hx, int hy)
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
void displayfunc(void)
{
    int x , y ;
    glClear(GL_COLOR_BUFFER_BIT);
    for( x = 0 ; x < N ; x++ )
    {
        for( y = 0 ; y < N ; y++ )
        { 
            if(isMandel(x,y) == 0) glColor3f( 0.0 , 0.0 , 0.0 );
            else glColor3f( 1.0 , 1.0 , 1.0 );
            glBegin(GL_POINTS);
            glVertex2f(x,y);
            glEnd();
        }
    }
    glutSwapBuffers() ;
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
        printf("Selection Started.\n");
        printf("Started at: %d,%d",xscr,yscr);
        while(state == GLUT_DOWN)
        {
        
        }
    }
    if(button==GLUT_LEFT_BUTTON && state==GLUT_UP){
        printf("Selection Ended.\n");
        printf("Ended at: %d,%d",xscr,yscr);
    }
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
