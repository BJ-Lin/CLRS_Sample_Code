#include "..\Header.h"



struct Graph_Tag Graph_Object;

void AdjacencyList_Prepend(struct AdjacencyList_Tag* AdjacencyList_Pointer, struct ObjectWithVertex_Tag* Insertion_Element_Address, struct Graph_Tag* Graph_Pointer)
{
	//Update the number of edges in the graph.
	Graph_Pointer->Number_of_Edge++;

	//Store the addresses of predecessor and successor for Insertion Element
	Insertion_Element_Address->Prev = NULL;
	Insertion_Element_Address->Next = AdjacencyList_Pointer->head;  //NULL or The address of first element in the past time


	if (AdjacencyList_Pointer->head != NULL) //(1)If there is a first element before prepanding, we need to update Prev of first element (2) before cover AdjacencyList_Pointer->head.
	{
		AdjacencyList_Pointer->head->Prev = Insertion_Element_Address;
	}

	//Update the head pointer of linked list.
	AdjacencyList_Pointer->head = Insertion_Element_Address;

}

void CreateInitialize_Vertex_and_Adjacency(struct Graph_Tag* Graph_Pointer, int Number_of_Vertices)
{
	//Allocate the space for the pointers in the graph.
	Graph_Pointer->Number_of_Vertex = Number_of_Vertices;
	Graph_Pointer->Number_of_Edge = 0;
	Graph_Pointer->Vertex_Pointer = (struct Vertex_Tag*)malloc(Number_of_Vertices * sizeof(struct Vertex_Tag));
	Graph_Pointer->AdjacencyList_Pointer = (struct AdjacencyList_Tag*)malloc(Number_of_Vertices * sizeof(struct AdjacencyList_Tag));

	//(1)Initailize the list of edge space, (2)Initailize the vertex content, (3)Initailize head pointer of each linked list. 
	Graph_Pointer->EdgeSpaceAddress_List.head = NULL;

	for (int i = 0; i < Number_of_Vertices; i++)
	{
		Graph_Pointer->Vertex_Pointer[i].Key = i;

		Graph_Pointer->AdjacencyList_Pointer[i].head = NULL;

	}

	//Initialize the additional result flags for DFS.
	Graph_Pointer->DFS_AdditionalResult.OrderDoublyList_Flag = 0;
	Graph_Pointer->DFS_AdditionalResult.TopologicalSort_Flag = 0;
	Graph_Pointer->DFS_AdditionalResult.StronglyConnectedComponent_Flag = 0;

}
void AllocatedEdgeAddress_Prepend(struct EdgeSpaceAddress_List_Tag* LinkedList_Pointer, struct EdgeSpaceAddress_Carrier_Tag* Insertion_Element_Address)
{
	//Store the addresses of predecessor and successor for Insertion Element
	Insertion_Element_Address->Prev = NULL;
	Insertion_Element_Address->Next = LinkedList_Pointer->head;  //NULL or The address of first element in past.


	if (LinkedList_Pointer->head != NULL) //(1)If there is a first element before prepanding, we need to update Prev of first element (2) before cover LinkedList_Pointer->head.
	{
		LinkedList_Pointer->head->Prev = Insertion_Element_Address;
	}

	//Update the head pointer of queue.
	LinkedList_Pointer->head = Insertion_Element_Address;

}
struct ObjectWithVertex_Tag* Fill_Adjacency(struct Graph_Tag* Graph_Pointer, struct AdjacencyInformation_Tag* AdjacencyInformation_Pointer)
{
	int Number_of_Vertices = AdjacencyInformation_Pointer->Number_of_Vertices;
	int* VertexIndex_Pointer = AdjacencyInformation_Pointer->VertexIndex_Pointer;
	int AdjacencyIndex = AdjacencyInformation_Pointer->AdjacencyIndex;

	unsigned char Fill_EdgeValue_Flag = AdjacencyInformation_Pointer->Fill_EdgeValue_Flag;



	//Create a space for edges of graph and add the edge space address into the list of graph.
	struct ObjectWithVertex_Tag* ObjectWithVertex_Pointer = (struct ObjectWithVertex_Tag*)malloc(Number_of_Vertices * sizeof(struct ObjectWithVertex_Tag));
	struct EdgeSpaceAddress_Carrier_Tag* EdgeSpaceAddress_Carrier_Pointer = (struct EdgeSpaceAddress_Carrier_Tag*)malloc(sizeof(struct EdgeSpaceAddress_Carrier_Tag));
	EdgeSpaceAddress_Carrier_Pointer->EdgeSpaceAddress = ObjectWithVertex_Pointer;
	AllocatedEdgeAddress_Prepend(&Graph_Pointer->EdgeSpaceAddress_List, EdgeSpaceAddress_Carrier_Pointer);


	//Fill the adjacency list.
	if (Fill_EdgeValue_Flag == 0)
	{
		for (int i = 0; i < Number_of_Vertices; i++)
		{
			ObjectWithVertex_Pointer[i].Vertex_Pointer = Graph_Pointer->Vertex_Pointer + *(VertexIndex_Pointer + i);
			AdjacencyList_Prepend(Graph_Pointer->AdjacencyList_Pointer + AdjacencyIndex, ObjectWithVertex_Pointer + i, Graph_Pointer);

		}
	}
	else if (Fill_EdgeValue_Flag == 1)
	{
		int* EdgeWeight_Pointer = AdjacencyInformation_Pointer->EdgeWeight_Pointer;

		for (int i = 0; i < Number_of_Vertices; i++)
		{
			ObjectWithVertex_Pointer[i].Vertex_Pointer = Graph_Pointer->Vertex_Pointer + *(VertexIndex_Pointer + i);
			AdjacencyList_Prepend(Graph_Pointer->AdjacencyList_Pointer + AdjacencyIndex, ObjectWithVertex_Pointer + i, Graph_Pointer);



			ObjectWithVertex_Pointer[i].EdgeWeight = EdgeWeight_Pointer[i];

		}
	}
	else if (Fill_EdgeValue_Flag == 2)
	{
		int* EdgeCapacity_Pointer = AdjacencyInformation_Pointer->EdgeCapacity_Pointer;

		for (int i = 0; i < Number_of_Vertices; i++)
		{
			ObjectWithVertex_Pointer[i].Vertex_Pointer = Graph_Pointer->Vertex_Pointer + *(VertexIndex_Pointer + i);
			AdjacencyList_Prepend(Graph_Pointer->AdjacencyList_Pointer + AdjacencyIndex, ObjectWithVertex_Pointer + i, Graph_Pointer);



			ObjectWithVertex_Pointer[i].EdgeCapacity = EdgeCapacity_Pointer[i];

		}

	}

	return ObjectWithVertex_Pointer;
}

//Create Graph by using adjacency list representation, where the graph is from CLRS 4th,P557.
//This is adjacency list.
void CreateGraph(struct Graph_Tag* Graph_Pointer)
{

	CreateInitialize_Vertex_and_Adjacency(Graph_Pointer, 9);


	unsigned int MaxArraySize = 10;
	int* VertexIndex_Pointer = (int*)malloc(MaxArraySize * sizeof(int));

	struct AdjacencyInformation_Tag AdjacencyInformation = { .Fill_EdgeValue_Flag = 0,.VertexIndex_Pointer = VertexIndex_Pointer };



	//Set adjacency list for vertex s.
	AdjacencyInformation.AdjacencyIndex = 0;

	AdjacencyInformation.Number_of_Vertices = 3;
	VertexIndex_Pointer[0] = 2;	//Vertex v
	VertexIndex_Pointer[1] = 3;	//Vertex u 
	VertexIndex_Pointer[2] = 1;	//Vertex r 


	Fill_Adjacency(Graph_Pointer, &AdjacencyInformation);





	//Set adjacency list for vertex r.
	AdjacencyInformation.AdjacencyIndex = 1;

	AdjacencyInformation.Number_of_Vertices = 3;
	VertexIndex_Pointer[0] = 5;	//Vertex w
	VertexIndex_Pointer[1] = 4;	//Vertex t 
	VertexIndex_Pointer[2] = 0;	//Vertex s 


	Fill_Adjacency(Graph_Pointer, &AdjacencyInformation);





	//Set adjacency list for vertex v.
	AdjacencyInformation.AdjacencyIndex = 2;

	AdjacencyInformation.Number_of_Vertices = 3;
	VertexIndex_Pointer[0] = 5;	//Vertex w
	VertexIndex_Pointer[1] = 6;	//Vertex y 
	VertexIndex_Pointer[2] = 0;	//Vertex s 


	Fill_Adjacency(Graph_Pointer, &AdjacencyInformation);






	//Set adjacency list for vertex u.
	AdjacencyInformation.AdjacencyIndex = 3;

	AdjacencyInformation.Number_of_Vertices = 3;
	VertexIndex_Pointer[0] = 0;	//Vertex s
	VertexIndex_Pointer[1] = 6;	//Vertex y 
	VertexIndex_Pointer[2] = 4;	//Vertex t 


	Fill_Adjacency(Graph_Pointer, &AdjacencyInformation);






	//Set adjacency list for vertex t.
	AdjacencyInformation.AdjacencyIndex = 4;

	AdjacencyInformation.Number_of_Vertices = 2;
	VertexIndex_Pointer[0] = 1;	//Vertex r
	VertexIndex_Pointer[1] = 3;	//Vertex u 



	Fill_Adjacency(Graph_Pointer, &AdjacencyInformation);




	//Set adjacency list for vertex w.
	AdjacencyInformation.AdjacencyIndex = 5;

	AdjacencyInformation.Number_of_Vertices = 4;
	VertexIndex_Pointer[0] = 8;	//Vertex z
	VertexIndex_Pointer[1] = 7;	//Vertex x 
	VertexIndex_Pointer[2] = 2;	//Vertex v 
	VertexIndex_Pointer[3] = 1;	//Vertex r 



	Fill_Adjacency(Graph_Pointer, &AdjacencyInformation);





	//Set adjacency list for vertex y.
	AdjacencyInformation.AdjacencyIndex = 6;

	AdjacencyInformation.Number_of_Vertices = 3;
	VertexIndex_Pointer[0] = 2;	//Vertex v
	VertexIndex_Pointer[1] = 7;	//Vertex x 
	VertexIndex_Pointer[2] = 3;	//Vertex u 



	Fill_Adjacency(Graph_Pointer, &AdjacencyInformation);







	//Set adjacency list for vertex x.
	AdjacencyInformation.AdjacencyIndex = 7;

	AdjacencyInformation.Number_of_Vertices = 3;
	VertexIndex_Pointer[0] = 5;	//Vertex w
	VertexIndex_Pointer[1] = 8;	//Vertex z 
	VertexIndex_Pointer[2] = 6;	//Vertex y 



	Fill_Adjacency(Graph_Pointer, &AdjacencyInformation);





	//Set adjacency list for vertex z.
	AdjacencyInformation.AdjacencyIndex = 8;

	AdjacencyInformation.Number_of_Vertices = 2;
	VertexIndex_Pointer[0] = 5;	//Vertex w
	VertexIndex_Pointer[1] = 7;	//Vertex x 




	Fill_Adjacency(Graph_Pointer, &AdjacencyInformation);



	//Free the space of VertexIndex_Pointer
	free(VertexIndex_Pointer);

}

void QueueList_Prepend(struct QueueList_Tag* QueueList_Pointer, struct ObjectWithVertex_Tag* Insertion_Element_Address)
{
	//Update tail pointer.
	if (QueueList_Pointer->head == NULL)
	{
		QueueList_Pointer->tail = Insertion_Element_Address;
	}


	//Store the addresses of predecessor and successor for Insertion Element
	Insertion_Element_Address->Prev = NULL;
	Insertion_Element_Address->Next = QueueList_Pointer->head;  //NULL or The address of first element in the past time


	if (QueueList_Pointer->head != NULL) //(1)If there is a first element before prepanding, we need to update Prev of first element (2) before cover QueueList_Pointer->head.
	{
		QueueList_Pointer->head->Prev = Insertion_Element_Address;
	}


	QueueList_Pointer->VertexCounter++;


	//Update the head pointer of linked list.
	QueueList_Pointer->head = Insertion_Element_Address;

}

struct ObjectWithVertex_Tag* QueueList_Dequeue(struct QueueList_Tag* QueueList_Pointer)
{
	struct ObjectWithVertex_Tag* Delete_Element_Address = QueueList_Pointer->tail;

	if (Delete_Element_Address == NULL)
	{
		return Delete_Element_Address; //Empty queue
	}


	if (Delete_Element_Address->Prev != NULL)
	{
		Delete_Element_Address->Prev->Next = Delete_Element_Address->Next;
	}
	else
	{
		QueueList_Pointer->head = Delete_Element_Address->Next;
	}

	if (Delete_Element_Address->Next != NULL)
	{
		Delete_Element_Address->Next->Prev = Delete_Element_Address->Prev;
	}
	else
	{
		QueueList_Pointer->tail = Delete_Element_Address->Prev; //Address of previous object or NULL.
	}


	QueueList_Pointer->VertexCounter--;

	return Delete_Element_Address;

}

void BFS(struct Graph_Tag* Graph_Pointer, struct Vertex_Tag* SourceVertex_Pointer)
{

	Initialize_Single_Source(Graph_Pointer, SourceVertex_Pointer);


	//Create a queue list and an source object of queue.
	struct QueueList_Tag QueueList = { .head = NULL,.tail = NULL,.VertexCounter = 0 };
	struct ObjectWithVertex_Tag* Insertion_ObjectForQueue_Pointer = (struct ObjectWithVertex_Tag*)malloc(sizeof(struct ObjectWithVertex_Tag));

	//Initialize the source object of queue.
	Insertion_ObjectForQueue_Pointer->Vertex_Pointer = SourceVertex_Pointer;

	//Enqueue the source object of queue
	QueueList_Prepend(&QueueList, Insertion_ObjectForQueue_Pointer);


	struct ObjectWithVertex_Tag* Object_u;
	struct ObjectWithVertex_Tag* Object_v;


	while (QueueList.head != NULL)
	{
		Object_u = QueueList_Dequeue(&QueueList);
		struct Vertex_Tag* Vertex_u_Pointer = Object_u->Vertex_Pointer;

		Object_v = Graph_Pointer->AdjacencyList_Pointer[Vertex_u_Pointer->Key].head;
		while (Object_v != NULL)
		{
			if (Object_v->Vertex_Pointer->Distance == INT_MAX)
			{

				Object_v->Vertex_Pointer->Distance = Vertex_u_Pointer->Distance + 1;
				Object_v->Vertex_Pointer->Parent = Vertex_u_Pointer;


				//Create a object of queue.
				Insertion_ObjectForQueue_Pointer = (struct ObjectWithVertex_Tag*)malloc(sizeof(struct ObjectWithVertex_Tag));

				//Initialize the object of queue.
				Insertion_ObjectForQueue_Pointer->Vertex_Pointer = Object_v->Vertex_Pointer;

				//Enqueue the discoverd object of queue
				QueueList_Prepend(&QueueList, Insertion_ObjectForQueue_Pointer);

			}

			Object_v = Object_v->Next;

		}

		//The pointer has finished its purpose, so we free the space.
		free(Object_u);

	}

}

void Print_Path(struct Vertex_Tag* SourceVertex_Pointer, struct Vertex_Tag* DestinationVertex_Pointer)
{
	if (DestinationVertex_Pointer == SourceVertex_Pointer)
	{
		printf("%d ", SourceVertex_Pointer->Key);
	}
	else if (DestinationVertex_Pointer->Parent == NULL)
	{
		printf("There is no connection between Source Vertex and Destination Vertex ");
	}
	else
	{
		Print_Path(SourceVertex_Pointer, DestinationVertex_Pointer->Parent);
		printf("%d ", DestinationVertex_Pointer->Key);

	}

}