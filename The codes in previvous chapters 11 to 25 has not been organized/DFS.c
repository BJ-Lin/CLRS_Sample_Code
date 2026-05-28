#include "..\Header.h"


//The flag of graph object need to be initialized to 0, especially in block scope. In global scope, the flags are 0 without initialization.  
struct Graph_Tag DFS_Graph_Object;

//Create Graph by using adjacency list representation, where the graph is from CLRS 4th,P566.
//This is adjacency list.
void DFS_CreateGraph(struct Graph_Tag* Graph_Pointer)
{
	CreateInitialize_Vertex_and_Adjacency(Graph_Pointer, 6);



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

	AdjacencyInformation.Number_of_Vertices = 2;
	VertexIndex_Pointer[0] = 5;	//Vertex z
	VertexIndex_Pointer[1] = 4;	//Vertex y



	Fill_Adjacency(Graph_Pointer, &AdjacencyInformation);





	//Set adjacency list for vertex x.
	AdjacencyInformation.AdjacencyIndex = 3;

	AdjacencyInformation.Number_of_Vertices = 1;
	VertexIndex_Pointer[0] = 1;	//Vertex v



	Fill_Adjacency(Graph_Pointer, &AdjacencyInformation);




	//Set adjacency list for vertex y.
	AdjacencyInformation.AdjacencyIndex = 4;

	AdjacencyInformation.Number_of_Vertices = 1;
	VertexIndex_Pointer[0] = 3;	//Vertex x



	Fill_Adjacency(Graph_Pointer, &AdjacencyInformation);




	//Set adjacency list for vertex z.
	AdjacencyInformation.AdjacencyIndex = 5;

	AdjacencyInformation.Number_of_Vertices = 1;
	VertexIndex_Pointer[0] = 5;	//Vertex z



	Fill_Adjacency(Graph_Pointer, &AdjacencyInformation);






	//Free the space of VertexIndex_Pointer
	free(VertexIndex_Pointer);



}

void DFS(struct Graph_Tag* Graph_Pointer, struct Vertex_Tag* SourceVertex_Pointer)
{
	int Number_of_Vertex = Graph_Pointer->Number_of_Vertex;



	/*************************Only For Topological Sort*********************************/
	if (Graph_Pointer->DFS_AdditionalResult.TopologicalSort_Flag == 1)
	{

		//Create the linked list for topological sort.
		Graph_Pointer->DFS_AdditionalResult.TopologicalSort_List_Pointer = (struct TopologicalSort_List_Tag*)malloc(sizeof(struct TopologicalSort_List_Tag));

		//Initialize linked list
		Graph_Pointer->DFS_AdditionalResult.TopologicalSort_List_Pointer->head = NULL;

		//Create a space for insertion object.
		Graph_Pointer->DFS_AdditionalResult.TopologicalSort_List_Pointer->EmptyObject_Pointer = (struct ObjectWithVertex_Tag*)malloc(Number_of_Vertex * sizeof(struct ObjectWithVertex_Tag)) + (Number_of_Vertex - 1);


	}
	/*************************Only For Topological Sort*********************************/




	/*************************Only For Order doubly List*********************************/
	if (Graph_Pointer->DFS_AdditionalResult.OrderDoublyList_Flag == 1)
	{

		//Create the linked list for topological sort.
		Graph_Pointer->DFS_AdditionalResult.OrderDoublyList_Pointer = (struct OrderDoublyList_Tag*)malloc(sizeof(struct OrderDoublyList_Tag));


		//Initialize linked list
		Graph_Pointer->DFS_AdditionalResult.OrderDoublyList_Pointer->head = NULL;


		//Create a space for insertion object.
		Graph_Pointer->DFS_AdditionalResult.OrderDoublyList_Pointer->ReleaseAddrress = (struct ObjectWithVertex_Tag*)malloc(Number_of_Vertex * sizeof(struct ObjectWithVertex_Tag));
		Graph_Pointer->DFS_AdditionalResult.OrderDoublyList_Pointer->EmptyObject_Pointer = Graph_Pointer->DFS_AdditionalResult.OrderDoublyList_Pointer->ReleaseAddrress + (Number_of_Vertex - 1);

	}
	/*************************Only For Order doubly List*********************************/





	//Initialize the attributes of vertices.
	for (int i = 0; i < Number_of_Vertex; i++)
	{
		Graph_Pointer->Vertex_Pointer[i].DiscoveryTime = INT_MAX;
		Graph_Pointer->Vertex_Pointer[i].Parent = NULL;
	}

	int Time = 0;



	if (SourceVertex_Pointer->DiscoveryTime == INT_MAX)
	{

		DFS_VISIT(Graph_Pointer, SourceVertex_Pointer, &Time);
	}


	/*************************Only For TransposeGraph_DFS*********************************/
	if (Graph_Pointer->DFS_AdditionalResult.StronglyConnectedComponent_Flag == 1)
	{
		//Retreive the head for knowing which vertex of transpose graph that we are going to search.
		struct OrderDoublyList_Tag* PrevGraph_List_Pointer = Graph_Pointer->UnTransposeGraph_Pointer->DFS_AdditionalResult.OrderDoublyList_Pointer;

		while (RetrieveListHead(PrevGraph_List_Pointer) != NULL)
		{
			//Instruct to create a new component to collect a set of vertices before execting DFS_VISIT.
			Graph_Pointer->DFS_AdditionalResult.CreateComponent_Instruction = 1;

			DFS_VISIT(Graph_Pointer, Graph_Pointer->Vertex_Pointer + RetrieveListHead(PrevGraph_List_Pointer)->Vertex_Pointer->Key, &Time);
		}

	}
	/*************************Only For TransposeGraph_DFS*********************************/
	else
	{
		for (int i = 0; i < Number_of_Vertex; i++)
		{

			if ((Graph_Pointer->Vertex_Pointer + i)->DiscoveryTime == INT_MAX)
			{
				DFS_VISIT(Graph_Pointer, Graph_Pointer->Vertex_Pointer + i, &Time);
			}

		}

	}


}

void DFS_VISIT(struct Graph_Tag* Graph_Pointer, struct Vertex_Tag* FrontierVertex_Pointer, int* Time_Pointer)
{
	*Time_Pointer = *Time_Pointer + 1;
	FrontierVertex_Pointer->DiscoveryTime = *Time_Pointer;


	//Time Complexity : Theta( | E | + | V | )
	struct ObjectWithVertex_Tag* ObjectWithVertex_Pointer = Graph_Pointer->AdjacencyList_Pointer[FrontierVertex_Pointer->Key].head;


	while (ObjectWithVertex_Pointer != NULL)
	{
		struct Vertex_Tag* Vertex_v_Pointer = ObjectWithVertex_Pointer->Vertex_Pointer;

		if (Vertex_v_Pointer->DiscoveryTime == INT_MAX)
		{
			Vertex_v_Pointer->Parent = FrontierVertex_Pointer;
			DFS_VISIT(Graph_Pointer, Vertex_v_Pointer, Time_Pointer);

		}

		ObjectWithVertex_Pointer = ObjectWithVertex_Pointer->Next;
	}


	*Time_Pointer = *Time_Pointer + 1;
	FrontierVertex_Pointer->FinishTime = *Time_Pointer;


	/*************************Only For Topological Sort*********************************/
	if (Graph_Pointer->DFS_AdditionalResult.TopologicalSort_Flag == 1)  // Time Complexity : Theta(| V |) , which is | V | vertices, finish.
	{
		//Insert the object into list
		struct ObjectWithVertex_Tag* EmptyObject_Pointer = Graph_Pointer->DFS_AdditionalResult.TopologicalSort_List_Pointer->EmptyObject_Pointer;
		EmptyObject_Pointer->Vertex_Pointer = FrontierVertex_Pointer;
		FrontierVertex_Pointer->Object_in_TopologicallySort_Pointer = EmptyObject_Pointer; //Record the address of object into vertex for finding out the corresponding object of source vertex in DAG_Shortest_Path.
		Topological_Sort_Prepend(Graph_Pointer->DFS_AdditionalResult.TopologicalSort_List_Pointer, EmptyObject_Pointer);


		//Modify the pointer to the next empty address.
		Graph_Pointer->DFS_AdditionalResult.TopologicalSort_List_Pointer->EmptyObject_Pointer--;
	}
	/*************************Only For Topological Sort*********************************/


	/*************************Only For Order Doubly List*********************************/
	if (Graph_Pointer->DFS_AdditionalResult.OrderDoublyList_Flag == 1) // Time Complexity : Theta(| V |) , which is | V | vertices, finish.
	{

		//Doubly link between object and vertex for Order Doubly List.
		struct ObjectWithVertex_Tag* EmptyObject_Pointer = Graph_Pointer->DFS_AdditionalResult.OrderDoublyList_Pointer->EmptyObject_Pointer;
		EmptyObject_Pointer->Vertex_Pointer = FrontierVertex_Pointer;
		FrontierVertex_Pointer->Object_in_OrderDoublyList_Pointer = EmptyObject_Pointer;

		//Insert the object into list
		OrderDoublyList_Prepend(Graph_Pointer->DFS_AdditionalResult.OrderDoublyList_Pointer, EmptyObject_Pointer);

		//Modify the pointer to the next empty address.
		Graph_Pointer->DFS_AdditionalResult.OrderDoublyList_Pointer->EmptyObject_Pointer--;

	}
	/*************************Only For Order Doubly List*********************************/


	/*************************Only For TransposeGraph_DFS*********************************/
	if (Graph_Pointer->DFS_AdditionalResult.StronglyConnectedComponent_Flag == 1)  // Time Complexity : Theta(| V |) , which is | V | vertices, finish.
	{


		//Classify all vercies into different components.
		if (Graph_Pointer->DFS_AdditionalResult.CreateComponent_Instruction == 1)
		{

			//Create a new component
			struct VertexSet_Tag* StronglyConnectedComponent_Pointer = Make_VertexSet(FrontierVertex_Pointer);


			//Create a new component carrier, and fill the component into component carrier.
			struct ComponentCarrier_Tag* ComponentCarrier_Pointer = (struct ComponentCarrier_Tag*)malloc(sizeof(struct ComponentCarrier_Tag));
			ComponentCarrier_Pointer->StronglyConnectedComponent_Pointer = StronglyConnectedComponent_Pointer;


			//Insert the component to Component Collection.
			ComponentCollection_Prepend(Graph_Pointer->DFS_AdditionalResult.ComponentCollection_Pointer, ComponentCarrier_Pointer);

			//Acheive the task of creating a component, so we set the instruction off.
			Graph_Pointer->DFS_AdditionalResult.CreateComponent_Instruction = 0;

		}
		else
		{
			//The meaning of argument "head" in Union_VertexSet function is carrier of component or vertex. 
			Union_VertexSet(Graph_Pointer->DFS_AdditionalResult.ComponentCollection_Pointer->head->StronglyConnectedComponent_Pointer->head->Vertex_Pointer, Make_VertexSet(FrontierVertex_Pointer)->head->Vertex_Pointer);

		}


		//Delete the object of discovered vertex in the order doublly list 
		struct Graph_Tag* PreviousGraph_Pointer = Graph_Pointer->UnTransposeGraph_Pointer;

		struct OrderDoublyList_Tag* PrevGraph_List_Pointer = PreviousGraph_Pointer->DFS_AdditionalResult.OrderDoublyList_Pointer;
		struct ObjectWithVertex_Tag* ObjectAddress_In_List = (PreviousGraph_Pointer->Vertex_Pointer + FrontierVertex_Pointer->Key)->Object_in_OrderDoublyList_Pointer;
		OrderDoublyList_Delete(PrevGraph_List_Pointer, ObjectAddress_In_List);

	}
	/*************************Only For TransposeGraph_DFS*********************************/



}