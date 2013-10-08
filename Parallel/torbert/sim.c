//
// Torbert, 30 Sept 2013
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//
#define M 20
#define N 80
//
double r()
{
	return ( 1.0 * rand() ) / RAND_MAX ;
}
//
int s( char t[][N] )
{
	return 106 ; // number of steps, not really
}
//
void g( char t[][N] )
{
	int j ;
	//
	// light on fire
	//
	for( j=0 ; j<M ; j++ )
	{
		if( t[j][0] == 1 ) t[j][0] = 2 ;
	}
}
//
void d( char t[][N] )
{
	int j , k ;
	//
	time_t tic , toc ;
	//
	system( "clear" ) ;
	//
	for( j=0 ; j<M ; j++ )
	{
		for( k=0 ; k<N ; k++ )
		{
			if( t[j][k] == 0 )
			{
				printf( " " ) ;
			}
			else if( t[j][k] == 1 )
			{
				printf( "T" ) ;
			}
			else if( t[j][k] == 2 )
			{
				printf( "*" ) ;
			}
			else
			{
				printf( "?" ) ; // this should not happen
			}
		}
		printf( "\n" ) ;
	}
	//
	time( &tic ) ;
	time( &toc ) ;
	while( toc - tic < 5 ) time( &toc ) ; // sleep pause wait
}
//
void main( void )
{
	char t[M][N] ;
	//
	int j , k ;
	//
	double prob = 0.75 ;
	//
	srand( 1234 ) ; // only once and remember it
	//
	for( j=0 ; j<M ; j++ )
	for( k=0 ; k<N ; k++ )
	{
		if( r() < prob )
		{
			t[j][k] = 1 ; //    tree
		}
		else
		{
			t[j][k] = 0 ; // no tree
		}
	}
	//
	d( t ) ;
	//
	g( t ) ;
	//
	d( t ) ;
	//
}
//
// end of file
//
