#include "..\Header.h"



void MiniSpanTree_QueueMinHeapify(struct Vertex_Tag* PointerArray[], size_t Queue_Size, unsigned Root_Index)
{
	//The index is from 4th, textbook p162, index = 1 ~ n for computing its parent and children conveniently in heap.
	unsigned Min_Index = 0;
	unsigned Left_Child_Index = 2 * Root_Index;
	unsigned Right_Child_Index = 2 * Root_Index + 1;


	if (Left_Child_Index <= Queue_Size && (*PointerArray[Left_Child_Index - 1]).EdgeWeight < (*PointerArray[Root_Index - 1]).EdgeWeight)
	{
		Min_Index = Left_Child_Index;
	}

	else
	{
		Min_Index = Root_Index;
	}

	if (Right_Child_Index <= Queue_Size && (*PointerArray[Right_Child_Index - 1]).EdgeWeight < (*PointerArray[Min_Index - 1]).EdgeWeight)
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

		MiniSpanTree_QueueMinHeapify(PointerArray, Queue_Size, Min_Index);

	}

}

signed char MiniSpanTree_QueueMinHeap_Minimum(struct Vertex_Tag* PointerArray[], size_t Queue_Size, struct Vertex_Tag** MinnimumAddress_Pointer)
{
	if (Queue_Size < 1)
	{
		return -1;
	}

	*MinnimumAddress_Pointer = PointerArray[0];

	return 0;
}

struct Vertex_Tag* QueueMinHeap_ExtractMinimum(struct Vertex_Tag* PointerArray[], size_t* QueueSize_Pointer)
{
	struct Vertex_Tag* Temp;
	MiniSpanTree_QueueMinHeap_Minimum(PointerArray, *QueueSize_Pointer, &Temp);  // Reserve minimum value of heap 
	PointerArray[0] = PointerArray[*QueueSize_Pointer - 1]; //Cover the minimum by using leaf( ~ Delete maximun) 

	//The index is from 4th, textbook p162, index = 1 ~ n for computing its parent and children conveniently in heap.
	(*PointerArray[0]).Index = 1;

	*QueueSize_Pointer = *QueueSize_Pointer - 1;
	MiniSpanTree_QueueMinHeapify(PointerArray, *QueueSize_Pointer, 1);

	Temp->VertexInQueue_Flag = 0;

	return Temp;
}

signed MiniSpanTree_QueueMinHeap_DecreaseKey(struct Vertex_Tag* PointerArray[], struct Vertex_Tag* Object_Pointer, int New_EdgeWeight)
{
	if (New_EdgeWeight > (*Object_Pointer).EdgeWeight)
	{
		return -1;

	}

	(*Object_Pointer).EdgeWeight = New_EdgeWeight;


	size_t i = (*Object_Pointer).Index;

	while (i > 1 && (*PointerArray[i / 2 - 1]).EdgeWeight > (*PointerArray[i - 1]).EdgeWeight)
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

	return 0; //New_EdgeWeight is smaller than original key
}

void MiniSpanTree_Prim(struct Graph_Tag* Graph_Pointer, struct Vertex_Tag* SourceVertex_Pointer)
{

	//Create a empty Min-Priority Queue
	int Number_of_Vertex = Graph_Pointer->Number_of_Vertex;
	struct Vertex_Tag** VertexAddress_Array = (struct Vertex_Tag**)malloc(Number_of_Vertex * sizeof(struct Vertex_Tag*));




	for (int i = 0; i < Number_of_Vertex; i++)
	{
		//Initialize all the vertices for Prim's algorithm usage.
		Graph_Pointer->Vertex_Pointer[i].EdgeWeight = INT_MAX;
		Graph_Pointer->Vertex_Pointer[i].Parent = NULL;

		//Initialize queue attributes in all vertices.
		Graph_Pointer->Vertex_Pointer[i].Index = i + 1; //The index is from 4th, textbook p162, index = 1 ~ n for computing its parent and children conveniently in heap.
		Graph_Pointer->Vertex_Pointer[i].VertexInQueue_Flag = 1; // 1 : i'th vertex is in the queue , 0 : i'th vertex isn't in the queue


		//Insert the vertices into Min-Priority Queue
		VertexAddress_Array[i] = Graph_Pointer->Vertex_Pointer + i;
	}


	//Assign the value of beginning vertex.
	SourceVertex_Pointer->EdgeWeight = 0;


	//Put the beginning verte into the root
	VertexAddress_Array[SourceVertex_Pointer->Index - 1] = VertexAddress_Array[0];
	VertexAddress_Array[0] = SourceVertex_Pointer;

	//Update the attributes of exchange vertices.
	VertexAddress_Array[SourceVertex_Pointer->Index - 1]->Index = SourceVertex_Pointer->Index;
	VertexAddress_Array[0]->Index = 1;


	size_t QueueSize = Graph_Pointer->Number_of_Vertex;


	struct Vertex_Tag* Vertex_u_Pointer;
	struct Vertex_Tag* Vertex_v_Pointer;
	struct ObjectWithVertex_Tag* ObjectWithVertex_v;
	while (QueueSize != 0)
	{
		//Choose the vertex u with the minimum weight of edge between the subtree and the other vertices. 
		Vertex_u_Pointer = QueueMinHeap_ExtractMinimum(VertexAddress_Array, &QueueSize);


		ObjectWithVertex_v = Graph_Pointer->AdjacencyList_Pointer[Vertex_u_Pointer->Key].head;


		while (ObjectWithVertex_v != NULL)
		{
			Vertex_v_Pointer = ObjectWithVertex_v->Vertex_Pointer;

			if (Vertex_v_Pointer->VertexInQueue_Flag == 1 && ObjectWithVertex_v->EdgeWeight < Vertex_v_Pointer->EdgeWeight)
			{
				Vertex_v_Pointer->Parent = Vertex_u_Pointer;
				MiniSpanTree_QueueMinHeap_DecreaseKey(VertexAddress_Array, Vertex_v_Pointer, ObjectWithVertex_v->EdgeWeight);
			}

			ObjectWithVertex_v = ObjectWithVertex_v->Next;
		}

	}

	free(VertexAddress_Array);

}


