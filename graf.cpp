#include "stdafx.h"
#include "graf.h"
#include "pQ.h"
#include "data.h"

double Dijkstra( Vertex* city, int nSize, int nFirst )
{
	PQueue* pQ = PQInit( nSize );
	double* distance = ( double* )calloc( 1, nSize * sizeof( double ) );

	city[nFirst].RoadToShop = ( int* )calloc( nSize, sizeof( int ) );

	if( !distance || !(city[ nFirst ].RoadToShop) )
	{
		printf( "Blad! distance lub city[ nFirst ].RoadToShop\n (Dijkstra)" );
		return 1;
	}

	for( int i = 0; i < nSize; i++ )
	{
		distance[i] = INT_MAX;	// Dystans ustawiony na "nieskonczonosc"
		city[nFirst].RoadToShop[i] = -1;
	}

	double length = 0;
	distance[ nFirst ] = 0;
	PQEnqueue( pQ, nFirst, 0 );
	while( !PQisEmpty( pQ ) )
	{
		int u = PQDequeue( pQ );
		
		if( city[ u ].Type )
		{
			city[ nFirst ].ShopVertex = u;
			length = distance[ u ];
			PQRelease( &pQ ); 
			break;
		}
		else
		{
			ListItem* neighbour = city[ u ].pListOfNeighbours->pHead;
			while( neighbour )
			{
				int i = neighbour->n_Key;
				if( distance[ i ] > distance[ u ] + neighbour->Length )
				{
					distance[ i ] = distance[ u ] + neighbour->Length; //dystans
					city[ nFirst ].RoadToShop[ i ] = u; //poprzednik
					PQEnqueue( pQ, i, distance[ i ] );
				}
				neighbour = neighbour->pNext;
			}
		}
	}
	free( distance );
	return length;
}


void DFS( Vertex* city, int v, int* visited )
{
	ListItem* u = city[ v ].pListOfNeighbours->pHead;
	visited[ v ] = 1;
	while( u )
	{
		u->Time = u->Length / SPEED;
		if( !visited[ u->n_Key ] )
			DFS( city, u->n_Key, visited );
		u = u->pNext;
	}
}
