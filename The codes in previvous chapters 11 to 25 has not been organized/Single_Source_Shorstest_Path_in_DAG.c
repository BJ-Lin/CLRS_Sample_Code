#include "..\Header.h"






struct Graph_Tag DAG_ShortestPath_Graph_Object;
//CLRS,4th,P618 ; vertex r ~ vertex z <----> index = 0th ~ 5th
//This is adjacency list.
void DAG_ShortestPath_CreateGraph(struct Graph_Tag* Graph_Pointer)
{
	CreateInitialize_Vertex_and_Adjacency(Graph_Pointer, 6);


	unsigned int MaxArraySize = 10;
	int* VertexIndex_Pointer = (int*)malloc(MaxArraySize * sizeof(int));
	int* EdgeWeight_Pointer = (int*)malloc(MaxArraySize * sizeof(int));


	struct AdjacencyInformation_Tag AdjacencyInformation = { .Fill_EdgeValue_Flag = 1,.VertexIndex_Pointer = VertexIndex_Pointer,.EdgeWeight_Pointer = EdgeWeight_Pointer };



	//Set adjacency list for vertex r.
	AdjacencyInformation.AdjacencyIndex = 0;

	AdjacencyInformation.Number_of_Vertices = 2;
	VertexIndex_Pointer[0] = 1;
	VertexIndex_Pointer[1] = 2;
	EdgeWeight_Pointer[0] = 5;
	EdgeWeight_Pointer[1] = 3;

	Fill_Adjacency(Graph_Pointer, &AdjacencyInformation);


	//Set adjacency list for vertex s.
	AdjacencyInformation.AdjacencyIndex = 1;

	AdjacencyInformation.Number_of_Vertices = 2;
	VertexIndex_Pointer[0] = 2;
	VertexIndex_Pointer[1] = 3;
	EdgeWeight_Pointer[0] = 2;
	EdgeWeight_Pointer[1] = 6;

	Fill_Adjacency(Graph_Pointer, &AdjacencyInformation);


	//Set adjacency list for vertex t.
	AdjacencyInformation.AdjacencyIndex = 2;

	AdjacencyInformation.Number_of_Vertices = 3;
	VertexIndex_Pointer[0] = 3;
	VertexIndex_Pointer[1] = 4;
	VertexIndex_Pointer[2] = 5;
	EdgeWeight_Pointer[0] = 7;
	EdgeWeight_Pointer[1] = 4;
	EdgeWeight_Pointer[2] = 2;

	Fill_Adjacency(Graph_Pointer, &AdjacencyInformation);


	//Set adjacency list for vertex x.
	AdjacencyInformation.AdjacencyIndex = 3;

	AdjacencyInformation.Number_of_Vertices = 2;
	VertexIndex_Pointer[0] = 4;
	VertexIndex_Pointer[1] = 5;
	EdgeWeight_Pointer[0] = -1;
	EdgeWeight_Pointer[1] = 1;

	Fill_Adjacency(Graph_Pointer, &AdjacencyInformation);



	//Set adjacency list for vertex y.
	AdjacencyInformation.AdjacencyIndex = 4;

	AdjacencyInformation.Number_of_Vertices = 1;
	VertexIndex_Pointer[0] = 5;
	EdgeWeight_Pointer[0] = -2;

	Fill_Adjacency(Graph_Pointer, &AdjacencyInformation);



	//Free the space of VertexIndex_Pointer and EdgeWeight_Pointer
	free(VertexIndex_Pointer);
	free(EdgeWeight_Pointer);

}
void DAG_Shortest_Path(struct Graph_Tag* Graph_Pointer, struct Vertex_Tag* SourceVertex_Pointer)
{
	Topological_Sort(Graph_Pointer);
	Initialize_Single_Source(Graph_Pointer, SourceVertex_Pointer);


	struct ObjectWithVertex_Tag* Next = SourceVertex_Pointer->Object_in_TopologicallySort_Pointer;
	struct ObjectWithVertex_Tag* Next_In_Adjacency;
	struct Vertex_Tag* Vertex_Pointer = Graph_Pointer->Vertex_Pointer;
	struct Vertex_Tag* u_Pointer, * v_Pointer;
	int EdgeWeight_u_v;

	while (Next != NULL)
	{

		u_Pointer = Next->Vertex_Pointer;
		//Avoid the overflow of integer addition for relaxing the edge ( u , v ).
		if (u_Pointer->Distance == INT_MAX)
		{
			Next = Next->Next;
			continue;
		}

		Next_In_Adjacency = (Graph_Pointer->AdjacencyList_Pointer + Next->Vertex_Pointer->Key)->head;
		while (Next_In_Adjacency != NULL)
		{
			v_Pointer = Next_In_Adjacency->Vertex_Pointer;
			EdgeWeight_u_v = Next_In_Adjacency->EdgeWeight;
			Relax(u_Pointer, v_Pointer, EdgeWeight_u_v);

			Next_In_Adjacency = Next_In_Adjacency->Next;
		}
		Next = Next->Next;
	}
}