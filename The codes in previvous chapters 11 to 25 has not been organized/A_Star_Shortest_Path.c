#include "..\Header.h"





//We make the edge weught ( u , v ) >= Euclidean distance between vertex u and vertex v for every edge ( u , v ) in the graph, 
//and make the heuristic function h(n) be the Euclidean distance from vertex n to destination vertex. Hence the heuristic function is consistent,
//h( u ) <= Euclidean distance for every edge ( u , v ) + h( v ) <= c( u , v ) + h( v )
struct Graph_Tag A_Star_Graph_Object;


//CLRS,4th,P621 ; vertex t¡Bvertex x¡Bvertex y¡Bvertex z¡Bvertex s <----> index = 0th ~ 4th
//This is adjacency list.
//The coordinates of vertices are assigned by my thought.
void  A_Star_CreateGraph(struct Graph_Tag* Graph_Pointer)
{
	CreateInitialize_Vertex_and_Adjacency(Graph_Pointer, 5);


	//Fill the coordinates of vertices for calculating the heuristic function value.
	Graph_Pointer->Vertex_Pointer[0].Coordinate[0] = 1;
	Graph_Pointer->Vertex_Pointer[0].Coordinate[1] = 0;

	Graph_Pointer->Vertex_Pointer[1].Coordinate[0] = 2;
	Graph_Pointer->Vertex_Pointer[1].Coordinate[1] = 0;

	Graph_Pointer->Vertex_Pointer[2].Coordinate[0] = 0;
	Graph_Pointer->Vertex_Pointer[2].Coordinate[1] = -1;

	Graph_Pointer->Vertex_Pointer[3].Coordinate[0] = 1;
	Graph_Pointer->Vertex_Pointer[3].Coordinate[1] = -2;

	Graph_Pointer->Vertex_Pointer[4].Coordinate[0] = 0;
	Graph_Pointer->Vertex_Pointer[4].Coordinate[1] = 0;



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


signed A_Star_QueueMinHeap_DecreaseKey(struct Vertex_Tag* PointerArray[], struct Vertex_Tag* Object_Pointer, float New_f_n, float* f_n_Pointer)
{

	if (New_f_n > f_n_Pointer[Object_Pointer->Key])
	{
		return -1;

	}

	f_n_Pointer[Object_Pointer->Key] = New_f_n;


	size_t i = (*Object_Pointer).Index;

	while (i > 1 && f_n_Pointer[PointerArray[i / 2 - 1]->Key] > f_n_Pointer[PointerArray[i - 1]->Key])
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


	return 0; //New_f_n is smaller than original key
}



void A_Star_QueueMinHeapify(struct Vertex_Tag* PointerArray[], size_t Queue_Size, unsigned Root_Index, float* f_n_Pointer)
{
	//The index is from 4th, textbook p162, index = 1 ~ n for computing its parent and children conveniently in heap.
	unsigned Min_Index = 0;
	unsigned Left_Child_Index = 2 * Root_Index;
	unsigned Right_Child_Index = 2 * Root_Index + 1;


	if (Left_Child_Index <= Queue_Size && *(f_n_Pointer + PointerArray[Left_Child_Index - 1]->Key) < *(f_n_Pointer + PointerArray[Root_Index - 1]->Key))
	{
		Min_Index = Left_Child_Index;
	}
	else
	{
		Min_Index = Root_Index;
	}

	if (Right_Child_Index <= Queue_Size && *(f_n_Pointer + PointerArray[Right_Child_Index - 1]->Key) < *(f_n_Pointer + PointerArray[Min_Index - 1]->Key))
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

		A_Star_QueueMinHeapify(PointerArray, Queue_Size, Min_Index, f_n_Pointer);

	}

}


struct Vertex_Tag* A_Star_QueueMinHeap_ExtractMinimum(struct Vertex_Tag* PointerArray[], size_t* QueueSize_Pointer, float* f_n_Pointer)
{
	struct Vertex_Tag* Temp;
	MiniSpanTree_QueueMinHeap_Minimum(PointerArray, *QueueSize_Pointer, &Temp);  // Reserve minimum value of heap 
	PointerArray[0] = PointerArray[*QueueSize_Pointer - 1]; //Cover the minimum by using leaf( ~ Delete maximun) 

	//The index is from 4th, textbook p162, index = 1 ~ n for computing its parent and children conveniently in heap.
	(*PointerArray[0]).Index = 1;

	*QueueSize_Pointer = *QueueSize_Pointer - 1;
	A_Star_QueueMinHeapify(PointerArray, *QueueSize_Pointer, 1, f_n_Pointer);


	return Temp;
}

//Here, we implement improved version of Dijksta algorithm, which is called A*( A-Star ) search algorithm, for finding the shortest path between source vertex and destination vertex.
//g(n) is the actual distance from source vertex to vertex n, and h(n) is the estimated distance from vertex n to destination vertex.
//f(n) = g(n) + h(n) is the estimated total cost from source vertex to destination vertex through vertex n.
//The meaning of extended vertex is the vertex which is taken from the priority queue and its adjacent vertices are examined for relaxing.
//(1) We assume that the heuristic function is consistent, which means h(u)<= h(v) + weight(u, v) for every edge (u, v) in the graph.
//We can deduce an inequality eazily : h(u)<= h(v) + weight(u, v) ---> h(u) + g(u) <= h(v) + g(u) + weight(u, v) ---> f(u) <= f(v) for every edge (u, v) in the graph. 
//The consistent heuristic function make a shortest path between source vertex amd each extended vertex at the first time. Hence the behavior of A* is similar to Dijkstra algorithm, which means the extended vertex will not be revisited( extended vertex not be inserted to the priority queue again ).
//(2) The weaker condition is admissible heuristic function, which means h(n) <= actual distance from vertex n to destination vertex for every vertex n in the graph. The extended vertex may be revisited( extended vertex may be inserted to the priority queue again ) and the shortest path between source vertex and each discovered vertex at the first time is not guaranteed. 
//But the destination vertex was extended at the first time, the shortest path is guaranteed.
//(3) We use Euclidean distance to compute the heuristic function for this graph, that the heuristic is consistent and admissible.
//(4) The time complexity of A* with priority queue is O((E + V)log V) in the worst case, where E is the number of edges and V is the number of vertices in the graph.
//(5) If we find the destination vertex in the graph, we return the pointer of destination vertex. Otherwise, we return NULL.
struct Vertex_Tag* A_Star(struct Graph_Tag* Graph_Pointer, struct Vertex_Tag* SourceVertex_Pointer, struct Vertex_Tag* DestinationVertex_Pointer)
{
	Initialize_Single_Source(Graph_Pointer, SourceVertex_Pointer);


	//Create a empty Min-Priority Queue
	int Number_of_Vertex = Graph_Pointer->Number_of_Vertex;
	struct Vertex_Tag** VertexAddress_Array = (struct Vertex_Tag**)malloc(Number_of_Vertex * sizeof(struct Vertex_Tag*));

	//Compute the heuristic value of each vertex.
	float* HeuristicValue_Pointer = (float*)malloc(Number_of_Vertex * sizeof(float));
	for (int i = 0; i < Number_of_Vertex; i++)
	{
		int x = Graph_Pointer->Vertex_Pointer[i].Coordinate[0];
		int y = Graph_Pointer->Vertex_Pointer[i].Coordinate[1];

		int Destination_x = DestinationVertex_Pointer->Coordinate[0];
		int Destination_y = DestinationVertex_Pointer->Coordinate[1];

		//Euclidean distance is used for heuristic function.
		HeuristicValue_Pointer[i] = sqrt((x - Destination_x) * (x - Destination_x) + (y - Destination_y) * (y - Destination_y));
	}


	//Assign values to the used properties for priority queue.
	float* f_n_Pointer = (float*)malloc(Number_of_Vertex * sizeof(float));
	for (int i = 0; i < Number_of_Vertex; i++)
	{
		//Initialize queue attributes in all vertices.
		Graph_Pointer->Vertex_Pointer[i].Index = i + 1; //The index is from 4th, textbook p162, index = 1 ~ n for computing its parent and children conveniently in heap.

		//Initialize f(n) with infinity for each vertex. 
		f_n_Pointer[i] = FLT_MAX;

		//Insert the vertices into Min-Priority Queue
		VertexAddress_Array[i] = Graph_Pointer->Vertex_Pointer + i;
	}


	//Put the beginning vertex into the root
	VertexAddress_Array[SourceVertex_Pointer->Index - 1] = VertexAddress_Array[0];
	VertexAddress_Array[0] = SourceVertex_Pointer;

	//Update the attributes of exchange vertices.
	VertexAddress_Array[SourceVertex_Pointer->Index - 1]->Index = SourceVertex_Pointer->Index;
	VertexAddress_Array[0]->Index = 1;


	//Initialize f(n) of source vertex.
	f_n_Pointer[SourceVertex_Pointer->Key] = SourceVertex_Pointer->Distance + HeuristicValue_Pointer[SourceVertex_Pointer->Key];



	size_t QueueSize = Graph_Pointer->Number_of_Vertex;


	struct Vertex_Tag* Vertex_u_Pointer;
	struct Vertex_Tag* Vertex_v_Pointer;
	struct ObjectWithVertex_Tag* ObjectWithVertex_v;
	struct Vertex_Tag* FoundVertex_Pointer = NULL;
	int EdgeWeight_u_v;

	unsigned char VertexWeightDecrease_Flag;
	float New_f_n;
	while (QueueSize != 0)
	{

		//Choose the vertex u with the minimum distance in the set V - S. 
		Vertex_u_Pointer = A_Star_QueueMinHeap_ExtractMinimum(VertexAddress_Array, &QueueSize, f_n_Pointer);


		//Checking if all of the remainning vertices are non-reachable.
		//And avoid the overflow of integer addition for relaxing the edge ( u , v ).
		if (Vertex_u_Pointer->Distance == INT_MAX)
		{
			break;
		}


		//Judge if the destination vertex is found.
		if (Vertex_u_Pointer == DestinationVertex_Pointer)
		{
			FoundVertex_Pointer = DestinationVertex_Pointer;
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
				//Update f(v).
				f_n_Pointer[Vertex_v_Pointer->Key] = Vertex_v_Pointer->Distance + HeuristicValue_Pointer[Vertex_v_Pointer->Key];


				New_f_n = f_n_Pointer[Vertex_v_Pointer->Key];

				f_n_Pointer[Vertex_v_Pointer->Key] = f_n_Pointer[Vertex_v_Pointer->Key] + 1;

				A_Star_QueueMinHeap_DecreaseKey(VertexAddress_Array, Vertex_v_Pointer, New_f_n, f_n_Pointer);
			}

			ObjectWithVertex_v = ObjectWithVertex_v->Next;
		}



	}

	free(VertexAddress_Array);
	free(HeuristicValue_Pointer);
	free(f_n_Pointer);


	//If we find the DestinationVertex_Pointer in the grath, we return the pointer of DestinationVertex_Pointer. Otherwise, we return NULL.
	return FoundVertex_Pointer;
}