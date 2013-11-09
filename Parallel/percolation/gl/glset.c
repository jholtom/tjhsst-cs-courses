// Jacob Holtom - 11/02/13
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <GL/glut.h>
#include <math.h>
#include "mpi.h"
#define N 600
#define ARRX N
#define ARRY N
#define DIETAG 2
#define WORKTAG 0
void idlefunc(void)
{


}
void displayfunc(void)
{
    int x , y ;
    glClear(GL_COLOR_BUFFER_BIT);
    for( x = 0 ; x < N ; x++ )
    {
        for( y = 0 ; y < N ; y++ )
        { 
            glColor3f( 0.2 , 1 , 0.2 ) ;
            glBegin(GL_POINTS);
            glVertex2f(x,y);
            glEnd();
        }
    }
    glColor3f( 0.0 , 0.0 , 0.0 ) ;
    glColor3f( 1.0 , 1.0 , 1.0 ) ;
    glRasterPos2f( 0.85*N , 0.9*N ) ;
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
void mousefunc(int button,int state,int xscr,int yscr)
{
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        printf("Left mouse clicked.\n");
    }
    else if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
    {
        printf("Right mouse clicked.\n");
    }
}
void motionfunc(int xscr,int yscr)
{
    printf("Motion ( %d , %d ).\n" , xscr , yscr ) ;
}
void keyfunc(unsigned char key,int xscr,int yscr)
{
    printf("Key %c pressed.\n" , key);
}
void specialfunc(int key,int xscr,int yscr)
{
    if( key == GLUT_KEY_UP )
    {
        printf("Up arrow pressed.\n");
    }
}
void closefunc(void)
{
    printf("Window closed.\n");
}
int main(int argc,char* argv[])
{  
    int rank,size,prob,prob2;
    MPI_Status status;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    srand(time(NULL));
    if( rank == 0 ) // manager  - I AM VERY GL
    {
        glutInit(&argc,argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
        glutInitWindowSize(N,N);
        glutInitWindowPosition(100,50);
        glutCreateWindow("");
        glClearColor(1.0,1.0,1.0,0.0);
        glShadeModel(GL_SMOOTH);
        glutIdleFunc(idlefunc);
        glutDisplayFunc(displayfunc);
        glutReshapeFunc(reshapefunc);
        glutMouseFunc(mousefunc);
        glutMotionFunc(motionfunc);
        glutKeyboardFunc(keyfunc);
        glutSpecialFunc(specialfunc);
        glutWMCloseFunc(closefunc);
        glutMainLoop();
        for (iter = 1; iter < size; iter++){
            MPI_Send(0, 0, MPI_INT, iter, DIETAG, MPI_COMM_WORLD);
        }
    }
	else // worker - I DONT DO GL
	{
		while(1)
		{
		MPI_Recv( &prob , 1 , MPI_INT , 0 , MPI_ANY_TAG , MPI_COMM_WORLD , &status ) ;
		if(status.MPI_TAG == DIETAG)
		{
			break;
		}
		step = 0 ;
		step += compute( t , prob ) ;
		MPI_Send( &step , 1 , MPI_INT , 0 , 0 , MPI_COMM_WORLD );
		MPI_Send( &prob , 1 , MPI_INT    , 0 , 0 , MPI_COMM_WORLD ) ;
		}
	}
	MPI_Finalize();
    return 0;
}