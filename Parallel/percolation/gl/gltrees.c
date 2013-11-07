// Jacob Holtom - 11/02/13
#include <stdio.h>
#include <GL/glut.h>
#define N 600
#define ARRX N
#define ARRY N
#define DIETAG 2
#define WORKTAG 0
void process_fire(char[ARRX][ARRY]);
void process_fire(char field[ARRX][ARRY]){
    char field_buffer[ARRX][ARRY];

    int k,j;

    for( k = 0; k < ARRX; k++)
    {
        for( j = 0; j < ARRY; j++)
        {
            field_buffer[k][j] = field[k][j];
        }
    }
    for( k = 0; k < ARRX; k++)
    {
        for( j = 0; j < ARRY; j++)
        {
            if( field[k][j] == '*')
            {
                if(field[k-1][j] == 'T' && k-1 > 0){
                    field_buffer[k-1][j] = '*';
                }
                if(field[k+1][j] == 'T' && k+1 < ARRX){
                    field_buffer[k+1][j] = '*';
                }
                if(field[k][j-1] == 'T' && j-1 > 0){
                    field_buffer[k][j-1] = '*';
                }
                if(field[k][j+1] == 'T' && j+1 < ARRY){
                    field_buffer[k][j+1] = '*';
                }
                field_buffer[k][j] = ' ';
            }
        }
    }

    for( k = 0; k < ARRX; k++)
    {
        for( j = 0; j < ARRY; j++)
        {
            field[k][j] = field_buffer[k][j];
        }
    }
}
int isfire(char[ARRX][ARRY]);
int isfire(char field[ARRX][ARRY])
{
    int l,z;
    for(l = 0; l < ARRX; l++)
    {
        for(z = 0; z < ARRY; z++)
        {
            if(field[l][z] == '*')
            {
                return 1;
            }
        }
    }
    return 0;
}
int compute( char[ARRX][ARRY], int);
int compute(char field[ARRX][ARRY], int prob){
    int k;
    int m;
    for(k = 0; k < ARRX; k++){
        for(m = 0; m < ARRY; m++)
        {
            if((rand()%100 + 1) < prob)
            {
                field[k][m] = 'T';
            }
            else{
                field[k][m] = ' ';
            }
        }
    }
    int z;
    for(z = 0; z < ARRX; z++)
    {
        if( field[z][0] == 'T' ) field[z][0] = '*';
    }
    int steps = 0;
    while(isfire(field) != 0)
    {
        process_fire(field);
        steps++;
    }
    return steps;
}
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
    glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18 , (char)ascii ) ;
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
    int count = 0;
    int step,j,result;
    int TRIALS_EACH = 100;
    int numtrials = 10000;
    int totals[numtrials/TRIALS_EACH];
    char t[ARRX][ARRY];
    int trial,iter;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    srand(time(NULL));
    if( rank == 0 ) // manager  - I AM VERY GL
    {
        //seed them
        for (iter = 1; iter < size; iter++){
            prob = (int)floor(count % TRIALS_EACH);
            MPI_Send(&prob, 1, MPI_INT, iter, WORKTAG, MPI_COMM_WORLD);
            count++;
        }
        //feed them
        while (count < numtrials){
            MPI_Recv(&result, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            MPI_Recv(&prob2, 1, MPI_INT, status.MPI_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            totals[prob2] += result;
            prob = floor(count / TRIALS_EACH);
            MPI_Send(&prob, 1, MPI_INT, status.MPI_SOURCE, WORKTAG, MPI_COMM_WORLD);
            count++;
        }
        //get stuff
        for (iter = 1; iter < size; iter++){
            MPI_Recv(&result, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            MPI_Recv(&prob2, 1, MPI_INT, status.MPI_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            totals[prob2] += result;
        }
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
