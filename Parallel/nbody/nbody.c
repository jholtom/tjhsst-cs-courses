#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#define N  3
#define DT 0.00005
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
int md=0,xscrd,yscrd,running=0;
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
        if( j > 0 )
        {
            glBegin(GL_LINES);
            glVertex3f(nbody[j-1].x,nbody[j-1].y,nbody[j-1].z);
            glVertex3f(nbody[j  ].x,nbody[j  ].y,nbody[j  ].z);
            glEnd();
        }
    }
    glutSwapBuffers();
}
void idle(void)
{
    int j,k;
    double dx,dy,dz,dmag,fmag;
    double ax[N]={0},ay[N]={0},az[N]={0};
    if(running == 1){ 
        for(j=0;j<N-1;j++){
            for(k=0;k<N;k++){
                dx = nbody[j].x - nbody[k].x;
                dy = nbody[j].y - nbody[k].y;
                dz = nbody[j].z - nbody[k].z;
                dmag = sqrt((dx * dx) + (dy * dy) + (dz * dz));
                fmag = (nbody[j].m * nbody[k].m) / (dmag*dmag);
                ax[j] += -1 * (fmag * (dx / dmag)) / nbody[j].m;
                ay[j] += -1 * (fmag * (dy / dmag)) / nbody[j].m;
                az[j] += -1 * (fmag * (dz / dmag)) / nbody[j].m;
                ax[k] += (fmag * (dx / dmag)) / nbody[k].m;
                ay[k] += (fmag * (dy / dmag)) / nbody[k].m;
                az[k] += (fmag * (dz / dmag)) / nbody[k].m; 
            }
        }
        for(j=0;j<N;j++)
        {
            nbody[j].vx += ax[j] * DT;
            nbody[j].vy += ay[j] * DT;
            nbody[j].vz += az[j] * DT;
            nbody[j].x += nbody[j].vx * DT;
            nbody[j].y += nbody[j].vy * DT;
            nbody[j].z += nbody[j].vz * DT;
        }

    }
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
    if(md == 0)
    {
        md = 1;
        xscrd = xscr;
        yscrd = yscr;
    }
    if(md == 1 && (abs(xscrd - xscr) > 2 || abs(yscrd - yscr) > 2))
    {
        md = 0;
    }
    if(md == 1)
    {
        theta += .005 * (yscrd - yscr);
        phi += .005 * (xscrd - xscr);
        xscrd = xscr;
        yscrd = yscr;
    } 
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
    if(key=='r')
    {
        running = (running + 1) % 2;
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
    nbody[1].vz=149.0711985;
    nbody[2].m=1.0; // moon
    nbody[2].r=0.005;
    nbody[2].x=0.5;
    nbody[2].y=0.0;
    nbody[2].z=0.0;
    nbody[2].vx=0.0;
    nbody[2].vy=0.0;
    nbody[2].vz=100;
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
