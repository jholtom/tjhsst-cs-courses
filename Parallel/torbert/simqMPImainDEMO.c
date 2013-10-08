//
// Torbert, 7 October 2013
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//
#include "mpi.h"
//
#define M 100
#define N 100
//
int main( int argc , char* argv[] )
{
	//
	// MPI
	//
	int         rank , size ;
	MPI_Status  status ;
	int         tag = 0 ;
	int         worker ;
	//
	double prob ;
	//
	double delprob = 0.1 ;
	double minprob = 0.0 ;
	double maxprob = 1.0 ;
	//
	double nextprob ;
	//
	int step ;
	int j ;
	//
	char t[M][N] ;   // allocate only once - main - each node!
	//
	int trial ;
	int numtrials = 10000 ;
	//
	// MPI
	//
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&size); // assume size is four
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	//
	// if each worker does all trials for a given probability
	// then this is OK... but if not then we get same trials!
	//
	srand( 12345 ) ; // only once and remember it
	//
	if( rank == 0 ) // manager
	{
		//
		// send - loop better , queue size limited , balance workload
		//
		prob = 0.1 ;
		MPI_Send( &prob , 1 , MPI_DOUBLE , 1 , tag , MPI_COMM_WORLD ) ;
		//
		prob = 0.2 ;
		MPI_Send( &prob , 1 , MPI_DOUBLE , 2 , tag , MPI_COMM_WORLD ) ;
		//
		prob = 0.3 ;
		MPI_Send( &prob , 1 , MPI_DOUBLE , 3 , tag , MPI_COMM_WORLD ) ;
		//
		prob = 0.4 ;
		MPI_Send( &prob , 1 , MPI_DOUBLE , 1 , tag , MPI_COMM_WORLD ) ;
		//
		prob = 0.5 ;
		MPI_Send( &prob , 1 , MPI_DOUBLE , 2 , tag , MPI_COMM_WORLD ) ;
		//
		prob = 0.6 ;
		MPI_Send( &prob , 1 , MPI_DOUBLE , 3 , tag , MPI_COMM_WORLD ) ;
		//
		prob = 0.7 ;
		MPI_Send( &prob , 1 , MPI_DOUBLE , 1 , tag , MPI_COMM_WORLD ) ;
		//
		prob = 0.8 ;
		MPI_Send( &prob , 1 , MPI_DOUBLE , 2 , tag , MPI_COMM_WORLD ) ;
		//
		prob = 0.9 ;
		MPI_Send( &prob , 1 , MPI_DOUBLE , 3 , tag , MPI_COMM_WORLD ) ;
		//
		//
		// recv - loop better , MPI_ANY_SOURCE , status.MPI_SOURCE
		//      - in which case we also send/recv back the probability
		//      - and the results may be printed out of order... sort! (post)
		//
		step = 0 ;
		printf( "%20.16f %20.16f\n" , 0.0 , (1.0*step)/(N*numtrials) ) ;
		//
		MPI_Recv( &step , 1 , MPI_INT    , 1 , tag , MPI_COMM_WORLD , &status ) ;
		printf( "%20.16f %20.16f\n" , 0.1 , (1.0*step)/(N*numtrials) ) ;
		//
		MPI_Recv( &step , 1 , MPI_INT    , 2 , tag , MPI_COMM_WORLD , &status ) ;
		printf( "%20.16f %20.16f\n" , 0.2 , (1.0*step)/(N*numtrials) ) ;
		//
		MPI_Recv( &step , 1 , MPI_INT    , 3 , tag , MPI_COMM_WORLD , &status ) ;
		printf( "%20.16f %20.16f\n" , 0.3 , (1.0*step)/(N*numtrials) ) ;
		//
		MPI_Recv( &step , 1 , MPI_INT    , 1 , tag , MPI_COMM_WORLD , &status ) ;
		printf( "%20.16f %20.16f\n" , 0.4 , (1.0*step)/(N*numtrials) ) ;
		//
		MPI_Recv( &step , 1 , MPI_INT    , 2 , tag , MPI_COMM_WORLD , &status ) ;
		printf( "%20.16f %20.16f\n" , 0.5 , (1.0*step)/(N*numtrials) ) ;
		//
		MPI_Recv( &step , 1 , MPI_INT    , 3 , tag , MPI_COMM_WORLD , &status ) ;
		printf( "%20.16f %20.16f\n" , 0.6 , (1.0*step)/(N*numtrials) ) ;
		//
		MPI_Recv( &step , 1 , MPI_INT    , 1 , tag , MPI_COMM_WORLD , &status ) ;
		printf( "%20.16f %20.16f\n" , 0.7 , (1.0*step)/(N*numtrials) ) ;
		//
		MPI_Recv( &step , 1 , MPI_INT    , 2 , tag , MPI_COMM_WORLD , &status ) ;
		printf( "%20.16f %20.16f\n" , 0.8 , (1.0*step)/(N*numtrials) ) ;
		//
		MPI_Recv( &step , 1 , MPI_INT    , 3 , tag , MPI_COMM_WORLD , &status ) ;
		printf( "%20.16f %20.16f\n" , 0.9 , (1.0*step)/(N*numtrials) ) ;
		//
		step = N * numtrials ;
		printf( "%20.16f %20.16f\n" , 1.0 , (1.0*step)/(N*numtrials) ) ;
	}
	else            // worker
	{
		//
		// loop - need a "kill signal" to tell us when we are all done
		//
		MPI_Recv( &prob , 1 , MPI_DOUBLE , 0 , tag , MPI_COMM_WORLD , &status ) ;
		step = 0 ;
		for( trial = 1 ; trial <= numtrials ; trial++ )
		{
			step += runone( t , prob ) ;
		}
		MPI_Send( &step , 1 , MPI_INT    , 0 , tag , MPI_COMM_WORLD ) ;
		//
		MPI_Recv( &prob , 1 , MPI_DOUBLE , 0 , tag , MPI_COMM_WORLD , &status ) ;
		step = 0 ;
		for( trial = 1 ; trial <= numtrials ; trial++ )
		{
			step += runone( t , prob ) ;
		}
		MPI_Send( &step , 1 , MPI_INT    , 0 , tag , MPI_COMM_WORLD ) ;
		//
		MPI_Recv( &prob , 1 , MPI_DOUBLE , 0 , tag , MPI_COMM_WORLD , &status ) ;
		step = 0 ;
		for( trial = 1 ; trial <= numtrials ; trial++ )
		{
			step += runone( t , prob ) ;
		}
		MPI_Send( &step , 1 , MPI_INT    , 0 , tag , MPI_COMM_WORLD ) ;
	}
	//
	// MPI
	//
	MPI_Finalize();
	//
	return 0 ;
}
//
// end of file
//
