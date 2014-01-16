//Jacob Holtom - 01/16/14
//Conway's Game of Life
#include <stdio.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "mpi.h"
#define N 600
void displayfunc(void)
{

}
void mousefunc(int button, int state, int xscr, int yscr)
{

}
void reshapefunc(int wscr,int hscr)
{
    glViewport(0,0,(GLsizei)N,(GLsizei)N);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,1.0*N,0.0,1.0*N);
    glMatrixMode(GL_MODELVIEW);
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
        return 0;
    }
    else { //I'm a worker
        return 0; 
    }
}
