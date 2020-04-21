#pragma once

typedef struct tagListItem
{
	int n_Key;					// Numer wierzcho³ka
	double Length;				// Odleg³oœæ
	double Time;				// Czas dojœcia
	tagListItem* pNext;			// Kolejny s¹siad
}ListItem;

typedef struct
{
	ListItem* pHead;
	ListItem* pTail;
}List;

typedef struct MyStruct
{
	int VertexNumber;
	List* pListOfNeighbours;	// Lista sasiadow
	int Type;					// 0 - sklep, 1 - dom
	int ShopVertex;				// Najblizszy sklep
	double DistanceToShop;		// Dystans do najbli¿szego sklepu
	int* RoadToShop;			// Sciezka do sklepu
	double TimeToShop;			// Czas dojscia do najblizszego sklepu
	int NumOfNeighbours;		// Liczba sasiadow
}Vertex;

double Dijkstra(Vertex* city, int nSize, int nFirst);
void DFS( Vertex* city, int v, int* visited );
