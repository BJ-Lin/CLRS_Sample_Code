#include "..\Header.h"



struct Graph_Tag Dijkstra_Graph_Object;


//CLRS,4th,P621 ; vertex t¡Bvertex x¡Bvertex y¡Bvertex z¡Bvertex s <----> index = 0th ~ 4th
//This is adjacency list.
void  Dijkstra_CreateGraph(struct Graph_Tag* Graph_Pointer)
{
	CreateInitialize_Vertex_and_Adjacency(Graph_Pointer, 5);


	unsigned int MaxArraySize = 10;
	int* VertexIndex_Pointer = (int*)malloc(MaxArraySize * sizeof(int));
	int* EdgeWeight_Pointer = (int*)malloc(MaxArraySize * sizeof(int));


	struct AdjacencyInformation_Tag AdjacencyInformation = { .Fill_EdgeValue_Flag = 1,.VertexIndex_Pointer = VertexIndex_Pointer,.EdgeWeight_Pointer = EdgeWeight_Pointer };



	//Set adjacency list for vertex t.
	AdjacencyInformation.AdjacencyIndex = 0;

	AdjacencyInformation.Number_of_Vertices = 2;
	VertexIndex_Pointer[0] = 1;
	VertexIndex_Pointer[1] = 2;
	EdgeWeight_Pointer[0] = 1;
	EdgeWeight_Pointer[1] = 2;


	Fill_Adjacency(Graph_Pointer, &AdjacencyInformation);



	//Set adjacency list for vertex x.
	AdjacencyInformation.AdjacencyIndex = 1;

	AdjacencyInformation.Number_of_Vertices = 1;
	VertexIndex_Pointer[0] = 3;
	EdgeWeight_Pointer[0] = 4;

	Fill_Adjacency(Graph_Pointer, &AdjacencyInformation);


	//Set adjacency list for vertex y.
	AdjacencyInformation.AdjacencyIndex = 2;

	AdjacencyInformation.Number_of_Vertices = 3;
	VertexIndex_Pointer[0] = 0;
	VertexIndex_Pointer[1] = 1;
	VertexIndex_Pointer[2] = 3;
	EdgeWeight_Pointer[0] = 3;
	EdgeWeight_Pointer[1] = 9;
	EdgeWeight_Pointer[2] = 2;

	Fill_Adjacency(Graph_Pointer, &AdjacencyInformation);



	//Set adjacency list for vertex z.
	AdjacencyInformation.AdjacencyIndex = 3;

	AdjacencyInformation.Number_of_Vertices = 2;
	VertexIndex_Pointer[0] = 1;
	VertexIndex_Pointer[1] = 4;
	EdgeWeight_Pointer[0] = 6;
	EdgeWeight_Pointer[1] = 7;

	Fill_Adjacency(Graph_Pointer, &AdjacencyInformation);



	//Set adjacency list for vertex s.
	AdjacencyInformation.AdjacencyIndex = 4;

	AdjacencyInformation.Number_of_Vertices = 2;
	VertexIndex_Pointer[0] = 0;
	VertexIndex_Pointer[1] = 2;
	EdgeWeight_Pointer[0] = 10;
	EdgeWeight_Pointer[1] = 5;

	Fill_Adjacency(Graph_Pointer, &AdjacencyInformation);



	//Free the space of VertexIndex_Pointer and EdgeWeight_Pointer
	free(VertexIndex_Pointer);
	free(EdgeWeight_Pointer);

}
void Dijkstra_QueueMinHeapify(struct Vertex_Tag* PointerArray[], size_t Queue_Size, unsigned Root_Index)
{
	//The index is from 4th, textbook p162, index = 1 ~ n for computing its parent and children conveniently in heap.
	unsigned Min_Index = 0;
	unsigned Left_Child_Index = 2 * Root_Index;
	unsigned Right_Child_Index = 2 * Root_Index + 1;


	if (Left_Child_Index <= Queue_Size && (*PointerArray[Left_Child_Index - 1]).Distance < (*PointerArray[Root_Index - 1]).Distance)
	{
		Min_Index = Left_Child_Index;
	}

	else
	{
		Min_Index = Root_Index;
	}

	if (Right_Child_Index <= Queue_Size && (*PointerArray[Right_Child_Index - 1]).Distance < (*PointerArray[Min_Index - 1]).Distance)
	{
		Min_Index = Right_Child_Index;
	}


	if (Min_Index != Root_Index)
	{
		//Exchange values of PointerArray.
		struct Vertex_Tag* Temp = PointerArray[Root_Index - 1];
		PointerArray[Root_Index - 1] = PointerArray[Min_Index - 1];
		PointerArray[Min_Index - 1] = Temp;

		//Update indices of PointerArray.
		(*PointerArray[Root_Index - 1]).Index = Root_Index;
		(*PointerArray[Min_Index - 1]).Index = Min_Index;

		Dijkstra_QueueMinHeapify(PointerArray, Queue_Size, Min_Index);

	}

}
struct Vertex_Tag* Dijkstra_QueueMinHeap_ExtractMinimum(struct Vertex_Tag* PointerArray[], size_t* QueueSize_Pointer)
{
	struct Vertex_Tag* Temp;
	MiniSpanTree_QueueMinHeap_Minimum(PointerArray, *QueueSize_Pointer, &Temp);  // Reserve minimum value of heap 
	PointerArray[0] = PointerArray[*QueueSize_Pointer - 1]; //Cover the minimum by using leaf( ~ Delete maximun) 

	//The index is from 4th, textbook p162, index = 1 ~ n for computing its parent and children conveniently in heap.
	(*PointerArray[0]).Index = 1;

	*QueueSize_Pointer = *QueueSize_Pointer - 1;
	Dijkstra_QueueMinHeapify(PointerArray, *QueueSize_Pointer, 1);

	return Temp;
}
signed Dijkstra_QueueMinHeap_DecreaseKey(struct Vertex_Tag* PointerArray[], struct Vertex_Tag* Object_Pointer, int New_VertexDistance)
{

	if (New_VertexDistance > (*Object_Pointer).Distance)
	{
		return -1;

	}

	(*Object_Pointer).Distance = New_VertexDistance;


	size_t i = (*Object_Pointer).Index;

	while (i > 1 && (*PointerArray[i / 2 - 1]).Distance > (*PointerArray[i - 1]).Distance)
	{

		//Exchange pointer values of array
		struct Vertex_Tag* Temp = PointerArray[i / 2 - 1];
		PointerArray[i / 2 - 1] = PointerArray[i - 1];
		PointerArray[i - 1] = Temp;

		//Update index 
		(*PointerArray[i / 2 - 1]).Index = i / 2;
		(*PointerArray[i - 1]).Index = i;


		//Assign new i
		i = i / 2;

	}


	return 0; //New_VertexDistance is smaller than original key
}
void Dijkstra(struct Graph_Tag* Graph_Pointer, struct Vertex_Tag* SourceVertex_Pointer)
{
	Initialize_Single_Source(Graph_Pointer, SourceVertex_Pointer);


	//Create a empty Min-Priority Queue
	int Number_of_Vertex = Graph_Pointer->Number_of_Vertex;
	struct Vertex_Tag** VertexAddress_Array = (struct Vertex_Tag**)malloc(Number_of_Vertex * sizeof(struct Vertex_Tag*));


	for (int i = 0; i < Number_of_Vertex; i++)
	{
		//Initialize queue attributes in all vertices.
		Graph_Pointer->Vertex_Pointer[i].Index = i + 1; //The index is from 4th, textbook p162, index = 1 ~ n for computing its parent and children conveniently in heap.


		//Insert the vertices into Min-Priority Queue
		VertexAddress_Array[i] = Graph_Pointer->Vertex_Pointer + i;
	}


	//Put the beginning vertex into the root
	VertexAddress_Array[SourceVertex_Pointer->Index - 1] = VertexAddress_Array[0];
	VertexAddress_Array[0] = SourceVertex_Pointer;

	//Update the attributes of exchange vertices.
	VertexAddress_Array[SourceVertex_Pointer->Index - 1]->Index = SourceVertex_Pointer->Index;
	VertexAddress_Array[0]->Index = 1;



	size_t QueueSize = Graph_Pointer->Number_of_Vertex;



	struct Vertex_Tag* Vertex_u_Pointer;
	struct Vertex_Tag* Vertex_v_Pointer;
	struct ObjectWithVertex_Tag* ObjectWithVertex_v;
	int EdgeWeight_u_v;

	unsigned char VertexWeightDecrease_Flag;
	int New_VertexDistance;
	while (QueueSize != 0)
	{

		//Choose the vertex u with the minimum distance in the set V - S. 
		Vertex_u_Pointer = Dijkstra_QueueMinHeap_ExtractMinimum(VertexAddress_Array, &QueueSize);


		//Checking if all of the remainning vertices are non-reachable.
		//And avoid the overflow of integer addition for relaxing the edge ( u , v ).
		if (Vertex_u_Pointer->Distance == INT_MAX)
		{
			break;
		}


		ObjectWithVertex_v = Graph_Pointer->AdjacencyList_Pointer[Vertex_u_Pointer->Key].head;
		while (ObjectWithVertex_v != NULL)
		{
			Vertex_v_Pointer = ObjectWithVertex_v->Vertex_Pointer;
			EdgeWeight_u_v = ObjectWithVertex_v->EdgeWeight;


			VertexWeightDecrease_Flag = Relax(Vertex_u_Pointer, Vertex_v_Pointer, EdgeWeight_u_v);


			if (VertexWeightDecrease_Flag == 1)
			{
				New_VertexDistance = Vertex_v_Pointer->Distance;

				Vertex_v_Pointer->Distance = Vertex_v_Pointer->Distance + 1;
				Dijkstra_QueueMinHeap_DecreaseKey(VertexAddress_Array, Vertex_v_Pointer, New_VertexDistance);

			}

			ObjectWithVertex_v = ObjectWithVertex_v->Next;
		}



	}

	free(VertexAddress_Array);

}