#include "..\Header.h"




struct Graph_Tag BellmanFord_Graph_Object;


//CLRS,4th,P613 ; vertex t¡Bvertex x¡Bvertex y¡Bvertex z¡Bvertex s <----> index = 0th ~ 4th
//This is adjacency list.
void BellmanFord_CreateGraph(struct Graph_Tag* Graph_Pointer)
{
	CreateInitialize_Vertex_and_Adjacency(Graph_Pointer, 5);


	unsigned int MaxArraySize = 10;
	int* VertexIndex_Pointer = (int*)malloc(MaxArraySize * sizeof(int));
	int* EdgeWeight_Pointer = (int*)malloc(MaxArraySize * sizeof(int));


	struct AdjacencyInformation_Tag AdjacencyInformation = { .Fill_EdgeValue_Flag = 1,.VertexIndex_Pointer = VertexIndex_Pointer,.EdgeWeight_Pointer = EdgeWeight_Pointer };



	//Set adjacency list for vertex t.
	AdjacencyInformation.AdjacencyIndex = 0;

	AdjacencyInformation.Number_of_Vertices = 3;
	VertexIndex_Pointer[0] = 1;
	VertexIndex_Pointer[1] = 2;
	VertexIndex_Pointer[2] = 3;
	EdgeWeight_Pointer[0] = 5;
	EdgeWeight_Pointer[1] = 8;
	EdgeWeight_Pointer[2] = -4;

	Fill_Adjacency(Graph_Pointer, &AdjacencyInformation);



	//Set adjacency list for vertex x.
	AdjacencyInformation.AdjacencyIndex = 1;

	AdjacencyInformation.Number_of_Vertices = 1;
	VertexIndex_Pointer[0] = 0;
	EdgeWeight_Pointer[0] = -2;

	Fill_Adjacency(Graph_Pointer, &AdjacencyInformation);


	//Set adjacency list for vertex y.
	AdjacencyInformation.AdjacencyIndex = 2;

	AdjacencyInformation.Number_of_Vertices = 2;
	VertexIndex_Pointer[0] = 1;
	VertexIndex_Pointer[1] = 3;
	EdgeWeight_Pointer[0] = -3;
	EdgeWeight_Pointer[1] = 9;

	Fill_Adjacency(Graph_Pointer, &AdjacencyInformation);



	//Set adjacency list for vertex z.
	AdjacencyInformation.AdjacencyIndex = 3;

	AdjacencyInformation.Number_of_Vertices = 2;
	VertexIndex_Pointer[0] = 1;
	VertexIndex_Pointer[1] = 4;
	EdgeWeight_Pointer[0] = 7;
	EdgeWeight_Pointer[1] = 2;

	Fill_Adjacency(Graph_Pointer, &AdjacencyInformation);



	//Set adjacency list for vertex s.
	AdjacencyInformation.AdjacencyIndex = 4;

	AdjacencyInformation.Number_of_Vertices = 2;
	VertexIndex_Pointer[0] = 0;
	VertexIndex_Pointer[1] = 2;
	EdgeWeight_Pointer[0] = 6;
	EdgeWeight_Pointer[1] = 7;

	Fill_Adjacency(Graph_Pointer, &AdjacencyInformation);



	//Free the space of VertexIndex_Pointer and EdgeWeight_Pointer
	free(VertexIndex_Pointer);
	free(EdgeWeight_Pointer);

}
void Initialize_Single_Source(struct Graph_Tag* Graph_Pointer, struct Vertex_Tag* SourceVertex_Pointer)
{
	int Number_of_Vertices = Graph_Pointer->Number_of_Vertex;
	struct Vertex_Tag* Vertex_Pointer = Graph_Pointer->Vertex_Pointer;
	for (int i = 0; i < Number_of_Vertices; i++)
	{
		(Vertex_Pointer + i)->Distance = INT_MAX;
		(Vertex_Pointer + i)->Parent = NULL;
	}

	SourceVertex_Pointer->Distance = 0;

}
unsigned char Relax(struct Vertex_Tag* u_Pointer, struct Vertex_Tag* v_Pointer, int EdgeWeight_u_v)
{

	int New_Distance = u_Pointer->Distance + EdgeWeight_u_v;

	if (New_Distance < v_Pointer->Distance)
	{
		v_Pointer->Distance = New_Distance;
		v_Pointer->Parent = u_Pointer;

		return true;
	}

	return false;
}
unsigned char Bellman_Ford(struct Graph_Tag* Graph_Pointer, struct Vertex_Tag* SourceVertex_Pointer)
{

	Initialize_Single_Source(Graph_Pointer, SourceVertex_Pointer);


	int Number_of_Vertex = Graph_Pointer->Number_of_Vertex;
	int MaxIterationNumber = Number_of_Vertex - 1;
	struct Vertex_Tag* Vertex_Pointer = Graph_Pointer->Vertex_Pointer;
	struct ObjectWithVertex_Tag* Next;

	struct Vertex_Tag* u_Pointer, * v_Pointer;
	int EdgeWeight_u_v;

	unsigned int Counter = 0, CounterRecord_Iteration = 1;
	for (int i = 0; i < MaxIterationNumber && CounterRecord_Iteration != Counter; i++)
	{
		CounterRecord_Iteration = Counter;

		//Traverse every edges reachable from source vertex for relaxing.		
		for (int j = 0; j < Number_of_Vertex; j++)// j is the index adjacency list.
		{
			u_Pointer = Vertex_Pointer + j; // j is the index of vertex u.

			// u_Pointer->Distance == INT_MAX means  we do not need to relax the edges of the vertex for Infinity plusing any finite value.
			// And avoid the overflow of integer addition for relaxing the edge ( u , v ).
			if (u_Pointer->Distance == INT_MAX)
			{
				continue;
			}

			Next = (Graph_Pointer->AdjacencyList_Pointer + j)->head;
			while (Next != NULL)
			{
				v_Pointer = Vertex_Pointer + Next->Vertex_Pointer->Key; // Next->Vertex_Pointer->Key is the index of vertex v.
				EdgeWeight_u_v = Next->EdgeWeight;


				Counter = Counter + Relax(u_Pointer, v_Pointer, EdgeWeight_u_v);

				Next = Next->Next;
			}

		}


	}


	//Traverse every edges reachable from source vertex for checking if there are the negative-weight cycles.
	for (int j = 0; j < Number_of_Vertex; j++)// j is the index adjacency list.
	{
		Next = (Graph_Pointer->AdjacencyList_Pointer + j)->head;
		while (Next != NULL)
		{
			u_Pointer = Vertex_Pointer + j; // j is the index of vertex u.
			v_Pointer = Vertex_Pointer + Next->Vertex_Pointer->Key; // Next->Vertex_Pointer->Key is the index of vertex v.
			EdgeWeight_u_v = Next->EdgeWeight;

			if (u_Pointer->Distance + EdgeWeight_u_v < v_Pointer->Distance)
			{
				return false;
			}

			Next = Next->Next;
		}
	}

	return true;
}