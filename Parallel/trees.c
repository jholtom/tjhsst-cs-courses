//Jacob Holtom - Oct, 02, 2013
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mpi.h"
#define ARRX 100
#define ARRY 100
#define DIETAG 2

void draw_array(char[ARRX][ARRY]);
void draw_array(char field[ARRX][ARRY]){
	int x,y;
	for(x = 0; x < ARRX; x++)
	{
		for(y = 0; y < ARRY; y++)
		{
			printf("%c",field[x][y]);
		}
		printf("\n");
	}
}
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
	//Doesn't work...ask torbert
	//memcpy(&field_buffer,&field,sizeof(field));
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
int selectnode(int);
int selectnode(int np)
{
	return rand() % (np - 1) + 1;
}
void main( int argc , char* argv[] ){
	int rank,size,prob,prob2;
	MPI_Status status;
	int tag = 0;
	int step,j;
	char t[ARRX][ARRY];
	int trial,iter;
	int numtrials = 100;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	srand(time(NULL));
	if( rank == 0 ) // manager
	{

		for (rank = 1; rank < ntasks; rank++){
			prob = (int)floor(count % TRIALS_EACH);

			MPI_Send(&prob, 1, MPI_INT, rank, WORKTAG, MPI_COMM_WORLD);
			count++;
		}

		while (count < TRIALS){
			MPI_Recv(&result, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			MPI_Recv(&probab, 1, MPI_INT, status.MPI_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			totals[probab] += result;
			prob = floor(count / TRIALS_EACH);
			MPI_Send(&prob, 1, MPI_INT, status.MPI_SOURCE, WORKTAG, MPI_COMM_WORLD);
			count++;
		}

		for (rank = 1; rank < ntasks; rank++){
			MPI_Recv(&result, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			MPI_Recv(&probab, 1, MPI_INT, status.MPI_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			totals[probab] += result;
		}

		for (rank = 1; rank < ntasks; rank++){
			MPI_Send(0, 0, MPI_INT, rank, DIETAG, MPI_COMM_WORLD);
		}

		for (count = 0; count < (TRIALS/TRIALS_EACH); count++){
			//printf("%.2f %.2f\n", (double)count/100, (double)totals[count]/100);
		}

		return 0;
	}
	else            // worker
	{
		MPI_Recv( &prob , 1 , MPI_DOUBLE , 0 , tag , MPI_COMM_WORLD , &status ) ;
		if(status.MPI_TAG == DIETAG)
			exit(0);
		step = 0 ;
		for( trial = 1 ; trial <= numtrials ; trial++ )
		{
			step += compute( t , prob ) ;
		}
		MPI_Send( &prob , 1 , MPI_INT , 0 , tag , MPI_COMM_WORLD );
		MPI_Send( &step , 1 , MPI_INT    , 0 , tag , MPI_COMM_WORLD ) ;
	}
	MPI_Finalize();
}
