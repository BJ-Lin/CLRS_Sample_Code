#include "..\Header.h"




//Create Graph by using adjacency list representation, where the graph is from CLRS 4th,P566. But there is no connection between x and v , and we delete z.
//This is adjacency list.
void TopologicalSort_CreateGraph(struct Graph_Tag* Graph_Pointer)
{
	CreateInitialize_Vertex_and_Adjacency(Graph_Pointer, 5);



	unsigned int MaxArraySize = 10;
	int* VertexIndex_Pointer = (int*)malloc(MaxArraySize * sizeof(int));

	struct AdjacencyInformation_Tag AdjacencyInformation = { .Fill_EdgeValue_Flag = 0,.VertexIndex_Pointer = VertexIndex_Pointer };




	//Set adjacency list for vertex u.
	AdjacencyInformation.AdjacencyIndex = 0;

	AdjacencyInformation.Number_of_Vertices = 2;
	VertexIndex_Pointer[0] = 3;	//Vertex x
	VertexIndex_Pointer[1] = 1;	//Vertex v 


	Fill_Adjacency(Graph_Pointer, &AdjacencyInformation);




	//Set adjacency list for vertex v.
	AdjacencyInformation.AdjacencyIndex = 1;

	AdjacencyInformation.Number_of_Vertices = 1;
	VertexIndex_Pointer[0] = 4;	//Vertex y


	Fill_Adjacency(Graph_Pointer, &AdjacencyInformation);



	//Set adjacency list for vertex w.
	AdjacencyInformation.AdjacencyIndex = 2;

	AdjacencyInformation.Number_of_Vertices = 1;
	VertexIndex_Pointer[0] = 4;	//Vertex y


	Fill_Adjacency(Graph_Pointer, &AdjacencyInformation);




	//Set adjacency list for vertex y.
	AdjacencyInformation.AdjacencyIndex = 4;

	AdjacencyInformation.Number_of_Vertices = 1;
	VertexIndex_Pointer[0] = 3;	//Vertex x


	Fill_Adjacency(Graph_Pointer, &AdjacencyInformation);



	//Free the space of VertexIndex_Pointer
	free(VertexIndex_Pointer);

}

void Topological_Sort_Prepend(struct TopologicalSort_List_Tag* TopologicalSort_List_Pointer, struct ObjectWithVertex_Tag* Insertion_Element_Address)
{
	//Store the addresses of predecessor and successor for Insertion Element
	Insertion_Element_Address->Prev = NULL;
	Insertion_Element_Address->Next = TopologicalSort_List_Pointer->head;  //NULL or The address of first element in the past time


	if (TopologicalSort_List_Pointer->head != NULL) //(1)If there is a first element before prepanding, we need to update Prev of first element (2) before cover TopologicalSort_List_Pointer->head.
	{
		TopologicalSort_List_Pointer->head->Prev = Insertion_Element_Address;
	}

	//Update the head pointer of linked list.
	TopologicalSort_List_Pointer->head = Insertion_Element_Address;

}

struct TopologicalSort_List_Tag* Topological_Sort(struct Graph_Tag* Graph_Pointer)
{
	//Turn on buttom
	Graph_Pointer->DFS_AdditionalResult.TopologicalSort_Flag = 1;


	DFS(Graph_Pointer, Graph_Pointer->Vertex_Pointer);


	//Turn off buttom
	Graph_Pointer->DFS_AdditionalResult.TopologicalSort_Flag = 0;

	return Graph_Pointer->DFS_AdditionalResult.TopologicalSort_List_Pointer;
}
