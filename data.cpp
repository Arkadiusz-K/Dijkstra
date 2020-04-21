#include "stdafx.h"
#include <stdlib.h>
#include "graf.h"
#include "data.h"

int ReadData( const char* sFileName, Vertex** city )
{
	FILE* fin = NULL;
	if( ( fin = fopen( sFileName, "r" ) ) == NULL )
	{
		printf( "Blad odczytu pliku! (ReadData)\n" );
		return -1;
	}

	int VertexNumber = 0; //Liczba wierzcho³ków
	int tabSize = 0; //aktualny rozmiar tablicy

	Vertex* pCopyCity = *city;
	
	while( !feof( fin ) )
	{
		if( VertexNumber == tabSize )
		{
			tabSize += AllocAddMem( &pCopyCity, VertexNumber );
			if( VertexNumber == tabSize ) break;
		}

		Vertex* newVertex = &( pCopyCity[ VertexNumber++ ] );
		fscanf( fin, "%d %d %d", &newVertex->VertexNumber, &newVertex->Type, &newVertex->NumOfNeighbours );
	
		newVertex->pListOfNeighbours = ( List* )calloc( 1, sizeof( List ) );
		if( !newVertex->pListOfNeighbours )
		{
			printf( "Blad! pListOfNeighbours (ReadData)\n" );
			return -1;
		}
		List* pList = newVertex->pListOfNeighbours;
		char c;

		while( ( ( c = fgetc( fin ) ) != '\n' ) && ( c != EOF ) )
		{
			ungetc( c, fin );
			ListItem* neighbour = (ListItem*)calloc( 1, sizeof( ListItem ) );
			if( !neighbour )
			{
				printf( "Blad! neighbour (ReadData)\n" );
				return -1;
			}
			fscanf( fin, "%d %lf", &neighbour->n_Key, &neighbour->Length );

			if( !pList->pHead )			//Jeœli nie ma ¿adnego s¹siada
				pList->pHead = neighbour;
			else
				pList->pTail->pNext = neighbour;
			pList->pTail = neighbour;
		}
	}
	fclose( fin );
	*city = pCopyCity;
	return VertexNumber;
}


int AllocAddMem( Vertex** city, int nCurrentSize )
{
	int newSize = nCurrentSize + REALLOC;
	Vertex* pTemp = ( Vertex* )realloc( *city, newSize * sizeof( Vertex ) );
	if( !pTemp )
	{
		printf( "Blad! pTemp (AllocAddMem)\n" );
		return 0;
	}
	*city = pTemp;
	memset( *city + nCurrentSize, 0, REALLOC * sizeof( Vertex ) );
	return REALLOC;
}


void PrintData( Vertex* city, int nSize )
{
	FILE* fout = NULL;
	if( ( fout = fopen( "results.txt", "w" ) ) == NULL )
	{
		printf( "Blad przy zapisie do pliku! (PrintData)\n" );
		return;
	}
	fprintf( fout, "Vertex:  Shop:  Distance: \t Time: \t\tPath:" );
	for( int i = 0; i < nSize; i++ )
	{
		if( city[ i ].Type ) continue;
		fprintf( fout, "\n%d\t", city[ i ].VertexNumber );
		fprintf( fout, "%d\t", city[ i ].ShopVertex );
		fprintf( fout, "%.2lf km\t\t", city[ i ].DistanceToShop );
		fprintf( fout, "%.2lf\tmin\t", city[ i ].TimeToShop * 60 );
		int j = 0;

		while( city[ i ].RoadToShop[j] != city[ i ].ShopVertex )
			fprintf( fout, "%d -> ", city[ i ].RoadToShop[ j++ ] );
		fprintf( fout, "%d ", city[ i ].RoadToShop[ j ] );
	}
	fclose( fout );
}
