// Jacob Holtom - 11/02/13
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#define N 600
#define DIETAG 2
#define WORKTAG 0
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
    int iter = 0;
    for( x = 0 ; x < width ; x++ )
    {
        for( y = 0 ; y < height ; y++ )
        { 
            cx = (x * xStep) + cxm;
            cy = (y * yStep) + cym;
            a  = 0.0 ;
            b  = 0.0 ;
            t  = 0.0 ;
            if(iter < size){
            iter++;
            }
            if(iter == size){
            iter = 1;
            } 
            MPI_Send(&x,1,MPI_INT,iter,WORKTAG,MPI_COMM_WORLD);
            MPI_Send(&y,1,MPI_INT,iter,WORKTAG,MPI_COMM_WORLD);
            MPI_Send(&cx,1,MPI_DOUBLE,iter,WORKTAG,MPI_COMM_WORLD);
            MPI_Send(&cy,1,MPI_DOUBLE,iter,WORKTAG,MPI_COMM_WORLD);
            //MPI-ify this bit
            /*         while ((a*a+b*b < 4) && t < itermax) {
                       a2 = a;
                       b2 = b;
                       a = (a2*a2) - (b2*b2) + cx;
                       b = (2 * a2 * b2) + cy;
                       t += 1.0;
                       }*/
            //stop MPI calculation magic
            MPI_Recv(&x , 1, MPI_INT , MPI.ANY_SOURCE , MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            MPI_Recv(&y , 1, MPI_INT , status.MPI_SOURCE , MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            MPI_Recv(&t , 1, MPI_DOUBLE , status.MPI_SOURCE , MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            glColor3f( 0.0 , 1 - t/itermax, 0.0 ) ;
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
    int rank,size,prob,prob2;
    MPI_Status status;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    if(rank == 0){ //I'm the master
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
        for(iter = 1, iter < size; iter++)
        {
        MPI_Send(0,0,MPI_INT,iter,DIETAG,MPI_COMM_WORLD);
        }
        return 0;
    }
    else { //I'm a worker
        while(1){
            double t = 0.0;
            MPI_Recv(&x , 1, MPI_INT , 0 , MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            if(status.MPI_TAG == DIETAG)
            { break;} 
            MPI_Recv(&cx , 1, MPI_DOUBLE , 0 , MPI_ANY_TAG, MPI_COMM_WORLD, &status); 
            MPI_Recv(&y , 1, MPI_INT , 0 , MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            MPI_Recv(&cy , 1, MPI_DOUBLE , 0 , MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            while ((a*a+b*b < 4) && t < itermax) {
                a2 = a;
                b2 = b;
                a = (a2*a2) - (b2*b2) + cx;
                b = (2 * a2 * b2) + cy;
                t += 1.0;
            }
            MPI_Send(&t , 1 , MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
        }
        return 0; 
    }
}
