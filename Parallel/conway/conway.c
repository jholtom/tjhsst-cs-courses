//Jacob Holtom - 01/16/14
//Conway's Game of Life
#include <stdio.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
//#include "mpi.h"
#define N 600
#define S 5
#define for_x for (int x = 0; x < N/S; x++)
#define for_y for (int y = 0; y < N/S; y++)
#define for_xy for_x for_y
unsigned univ[N][N];
void evolve(void *u, int w, int h)
{
    unsigned (*univ)[w] = u;
    unsigned new[h][w];
    for_y for_x {
        int n = 0;
        for (int y1 = y - 1; y1 <= y + 1; y1++)
            for (int x1 = x - 1; x1 <= x + 1; x1++)
                if (univ[(y1 + h) % h][(x1 + w) % w])
                    n++;

        if (univ[y][x]) n--;
        new[y][x] = (n == 3 || (n == 2 && univ[y][x]));
    }
    for_y for_x univ[y][x] = new[y][x];
}
void displayfunc(void)
{
    evolve(univ,N/S,N/S);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f( 1.0 , 1.0 , 1.0);
    for_y {
        for_x {
            if(univ[y][x] == 1)
            {
                glBegin(GL_QUADS);
                glVertex2f(x,y);
                glVertex2f(x+S,y+S);
                glVertex2f(x,y+S);
                glVertex2f(x+S,y);
                glEnd();
            }
        }
    }
    glutSwapBuffers();
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
    int rank,size;
    unsigned univ[N/S][N/S];
    /*MPI_Status status;
      MPI_Init(&argc,&argv);
      MPI_Comm_size(MPI_COMM_WORLD,&size);
      MPI_Comm_rank(MPI_COMM_WORLD,&rank);
      if(rank == 0){ //I'm the master */
    for_xy univ[y][x] = rand() < RAND_MAX / 10 ? 1 : 0;
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
    glutIdleFunc(glutPostRedisplay);
    glutMainLoop();
    return 0;
}
/*else { //I'm a worker
  return 0; 
  }
  }*/
