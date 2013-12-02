// Jacob Holtom - 11/02/13
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#define N 600
#define MAXITER 100
double magnify = 1.0;
int scalex(int x){
    double cx = (((float)x)/((float)N)-0.5)/magnify*3.0-0.7;
    double xStep = cx / N;
    double cxMaxNew = (x * xStep) + cx;
    return (int) cxMaxNew;
}
int scaley(int y){
    double cy = (((float)y)/((float)N)-0.5)/magnify*3.0;
    double yStep = cy / N;
    double cyMaxNew = ((N-y) * yStep) + cy;
    return (int) cyMaxNew;
}
int isMandel(int hx, int hy, double magnify,double cm, double cl)
{
    double x,xx,y,cx,cy;
    int iteration;
    if(cm = 0.0 || cl == 0.0)
    {
        cx = (((float)hx)/((float)N)-0.5)/magnify*3.0-0.7;
        cy = (((float)hy)/((float)N)-0.5)/magnify*3.0;
    }
    else {
        cx = cm; 
        cy = cl;
    }
    x = 0.0; y = 0.0;
    for(iteration = 1; iteration < MAXITER;iteration++){   
        xx = x*x-y*y+cx;
        y = 2.0*x*y+cy;
        x = xx;
        if (x*x+y*y>100.0)  return iteration;
    }
    return 1;
}
void drawSet(int x, int y, int hx, int hy){
    glClear(GL_COLOR_BUFFER_BIT);
    for( x = 0 ; x < N ; x++ )
    {
        for( y = 0 ; y < N ; y++ )
        { 
            int m = isMandel(x,y,magnify,hx,hy);
            if(m != 1) 
            {
                double shade = 1.0-(m*1.0/MAXITER);
                glColor3f( 0.0 ,shade , 0.0 );
            }
            else glColor3f( 0.0 , 0.0 , 0.0 );
            glBegin(GL_POINTS);
            glVertex2f(x,y);
            glEnd();
        }
    }
    glutSwapBuffers() ;
}
void displayfunc(void)
{
    drawSet(0,0,0,0);
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
    magnify *= 2.0;
    drawSet(0,0,scalex(xscr),scaley(yscr));
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
