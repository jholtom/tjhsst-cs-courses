//
// Torbert, 7 October 2013
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//
#define M 100
#define N 100
//
int main( void )
{
	double prob ;
	//
	double delprob = 0.1 ;
	double minprob = 0.0 ;
	double maxprob = 1.0 ;
	//
	int step ;
	//
	char t[M][N] ;   // allocate only once - main
	//
	int trial ;
	int numtrials = 10000 ;
	//
	srand( 12345 ) ; // only once and remember it
	//
	for( prob = minprob ; prob <= maxprob ; prob += delprob )
	{
		step = 0 ;
		//
		for( trial = 1 ; trial <= numtrials ; trial++ )
		{
			step += runone( t , prob ) ;
		}
		//
		printf( "%20.16f %20.16f\n" , 
		           prob , (1.0*step)/(N*numtrials) ) ;
	}
	//
	return 0 ;
}
//
// end of file
//
