#include "..\Header.h"




void OrderDoublyList_Prepend(struct OrderDoublyList_Tag* OrderDoublyList, struct ObjectWithVertex_Tag* Insertion_Element_Address)
{

	//Store the addresses of predecessor and successor for Insertion Element
	Insertion_Element_Address->Prev = NULL;
	Insertion_Element_Address->Next = OrderDoublyList->head;  //NULL or The address of first element in the past time


	if (OrderDoublyList->head != NULL) //(1)If there is a first element before prepanding, we need to update Prev of first element (2) before cover OrderDoublyList->head.
	{
		OrderDoublyList->head->Prev = Insertion_Element_Address;
	}

	//Update the head pointer of linked list.
	OrderDoublyList->head = Insertion_Element_Address;

}
void OrderDoublyList_Delete(struct OrderDoublyList_Tag* OrderDoublyList_Pointer, struct ObjectWithVertex_Tag* Delete_Element_Address)
{

	if (Delete_Element_Address->Prev != NULL)
	{
		Delete_Element_Address->Prev->Next = Delete_Element_Address->Next;

	}
	else
	{
		OrderDoublyList_Pointer->head = Delete_Element_Address->Next;
	}

	if (Delete_Element_Address->Next != NULL)
	{
		Delete_Element_Address->Next->Prev = Delete_Element_Address->Prev;
	}


}
struct OrderDoublyList_Tag* CreateDoublyList_FinishTimeOrder_DFS(struct Graph_Tag* Graph_Pointer)
{
	Graph_Pointer->DFS_AdditionalResult.OrderDoublyList_Flag = 1;


	DFS(Graph_Pointer, Graph_Pointer->Vertex_Pointer);



	Graph_Pointer->DFS_AdditionalResult.OrderDoublyList_Flag = 0;

	return  Graph_Pointer->DFS_AdditionalResult.OrderDoublyList_Pointer;
}
struct Graph_Tag* CreateReverseDirectedGraph(struct Graph_Tag* Graph_Pointer)
{
	//Create transpose graph.
	int Number_of_Vertex = Graph_Pointer->Number_of_Vertex;
	int Number_of_Edge = Graph_Pointer->Number_of_Edge;

	struct Graph_Tag* New_Graph_Pointer = (struct Graph_Tag*)malloc(sizeof(struct Graph_Tag));
	Graph_Pointer->TransposeGraph_Pointer = New_Graph_Pointer;



	//Create the space of adjacency lists and vertices ; Space Complexity : Theta(|V|)
	CreateInitialize_Vertex_and_Adjacency(New_Graph_Pointer, Number_of_Vertex);
	struct Vertex_Tag* New_Vertext_Pointer = New_Graph_Pointer->Vertex_Pointer;
	struct AdjacencyList_Tag* New_AdjacencyList_Pointer = New_Graph_Pointer->AdjacencyList_Pointer;



	//Initialize the pointer of previous original graph 
	New_Graph_Pointer->UnTransposeGraph_Pointer = Graph_Pointer;



	//Create a space for edges of reverse directed graph and add the edge space address into the list of reverse directed graph.
	struct ObjectWithVertex_Tag* New_Edge_Pointer = (struct ObjectWithVertex_Tag*)malloc(Number_of_Edge * sizeof(struct ObjectWithVertex_Tag));
	struct EdgeSpaceAddress_Carrier_Tag* EdgeSpaceAddress_Carrier_Pointer = (struct EdgeSpaceAddress_Carrier_Tag*)malloc(sizeof(struct EdgeSpaceAddress_Carrier_Tag));
	EdgeSpaceAddress_Carrier_Pointer->EdgeSpaceAddress = New_Edge_Pointer;
	AllocatedEdgeAddress_Prepend(&Graph_Pointer->EdgeSpaceAddress_List, EdgeSpaceAddress_Carrier_Pointer);


	//Construct the adjacency lists for transpose graph.
	struct ObjectWithVertex_Tag* CurrentEdge_Pointer, * NextEdge_Pointer;
	struct Vertex_Tag* CurrentVertex_Pointer;
	int NewEdgeLocation = 0;
	for (int i = 0; i < Number_of_Vertex; i++)  //Time Complexity : Theta(|V|)
	{
		CurrentEdge_Pointer = (Graph_Pointer->AdjacencyList_Pointer + i)->head;
		CurrentVertex_Pointer = Graph_Pointer->Vertex_Pointer + i;
		while (CurrentEdge_Pointer != NULL) //Time Complexity : Theta(|E|)
		{
			//Record the address of next object
			NextEdge_Pointer = CurrentEdge_Pointer->Next;




			//Main Mission : Insert the created object to another adjacency list and fill the new vertex
			(New_Edge_Pointer + NewEdgeLocation)->Vertex_Pointer = New_Vertext_Pointer + i;
			AdjacencyList_Prepend(New_AdjacencyList_Pointer + CurrentEdge_Pointer->Vertex_Pointer->Key, New_Edge_Pointer + NewEdgeLocation, New_Graph_Pointer);




			//Update the location for next new object.
			NewEdgeLocation++;
			CurrentEdge_Pointer = NextEdge_Pointer;
		}
	}

	return New_Graph_Pointer;
}
struct ObjectWithVertex_Tag* RetrieveListHead(struct OrderDoublyList_Tag* LinkedList_Pointer)
{
	struct ObjectWithVertex_Tag* head = LinkedList_Pointer->head;


	return head;

}
struct VertexSet_Tag* CreateInit_List(void)
{
	//Create a linked list and initialize it.
	struct VertexSet_Tag* VertexSet_Pointer = (struct VertexSet_Tag*)malloc(sizeof(struct VertexSet_Tag));
	VertexSet_Pointer->head = NULL;
	VertexSet_Pointer->tail = NULL;
	VertexSet_Pointer->VertexCounter = 0;

	return VertexSet_Pointer;
}
void VertexCarrier_Prepend(struct VertexSet_Tag* VertexSet_Pointer, struct VertexCarrier_Tag* VertexCarrier_Pointer)
{


	//Store the addresses of SetObject and successor into the Insertion Element
	VertexCarrier_Pointer->Prev = NULL;
	VertexCarrier_Pointer->Next = VertexSet_Pointer->head;  //NULL or The address of first element in the past time
	VertexCarrier_Pointer->VertexSet_Pointer = VertexSet_Pointer; //The part_1 of difference compared to DoublyList_Prepend.

	//Update the pointer to the set object in the set member 
	VertexCarrier_Pointer->Vertex_Pointer->StrongConnectComponent_Pointer = VertexSet_Pointer; //The part_2 of difference compared to DoublyList_Prepend.



	//(1)If there is a first element before prepanding, we need to update Prev of first element (2) before cover VertexSet_Pointer->head.
	if (VertexSet_Pointer->head != NULL)
	{
		VertexSet_Pointer->head->Prev = VertexCarrier_Pointer;
	}
	//Update the tail pointer of list.
	else
	{
		VertexSet_Pointer->tail = VertexCarrier_Pointer; //The part_3 of difference compared to DoublyList_Prepend.
	}



	//Update the head pointer of list.
	VertexSet_Pointer->head = VertexCarrier_Pointer;



	//Update the number of vertices in the vertex set.
	VertexSet_Pointer->VertexCounter++;

}
struct VertexSet_Tag* Make_VertexSet(struct Vertex_Tag* Vertex_Pointer)
{
	//Create a linked list and initialize it.
	struct VertexSet_Tag* VertexSet_Pointer = CreateInit_List();


	//Create a disjoint object.
	struct VertexCarrier_Tag* VertexCarrier_Pointer = (struct VertexCarrier_Tag*)malloc(sizeof(struct VertexCarrier_Tag));

	//Fill the content into disjoint object.
	VertexCarrier_Pointer->Vertex_Pointer = Vertex_Pointer;

	//Insert the disjoint object.
	VertexCarrier_Prepend(VertexSet_Pointer, VertexCarrier_Pointer);


	return VertexSet_Pointer;

}
struct VertexSet_Tag* Union_VertexSet(struct Vertex_Tag* Vertex_Pointer, struct Vertex_Tag* AppendedVertex_Pointer)
{
	//Assign the set object in the appended list to the local variable;
	struct VertexSet_Tag* AppendedSetObject = AppendedVertex_Pointer->StrongConnectComponent_Pointer;

	//Assign both the tail object and set object to the local variables;
	struct VertexSet_Tag* FollowedSetObject = Vertex_Pointer->StrongConnectComponent_Pointer;


	//Union the two sets.
	struct VertexCarrier_Tag* FollowedTail = FollowedSetObject->tail;
	FollowedTail->Next = AppendedSetObject->head;
	AppendedSetObject->head->Prev = FollowedTail;

	//Update the attributes for each object in the appended linked list.
	struct VertexCarrier_Tag* Next = FollowedTail->Next;
	while (Next != NULL)
	{
		//Update the pointers to set for each object.
		Next->VertexSet_Pointer = FollowedSetObject;
		Next->Vertex_Pointer->StrongConnectComponent_Pointer = FollowedSetObject;

		//Update tail for each loop.
		FollowedSetObject->tail = Next;


		//Update the new checked object.
		Next = Next->Next;

	}

	//Update the number of vertices in the the vertex set.
	FollowedSetObject->VertexCounter = FollowedSetObject->VertexCounter + AppendedSetObject->VertexCounter;

	//Destroy the appended set for disjoint sets property.
	free(AppendedSetObject);

	return FollowedSetObject;
}
struct ComponentCollection_Tag* TransposeGraph_DFS(struct Graph_Tag* Graph_Pointer)
{
	struct Graph_Tag* TransposeGraph_Pointer = Graph_Pointer->TransposeGraph_Pointer;

	struct Vertex_Tag* TransposeGraph_Vertex_Pointer = TransposeGraph_Pointer->Vertex_Pointer;

	TransposeGraph_Pointer->DFS_AdditionalResult.StronglyConnectedComponent_Flag = 1;



	//Assign pointer of order doubly list to a variable.
	struct OrderDoublyList_Tag* OrderDoublyList_Pointer = Graph_Pointer->DFS_AdditionalResult.OrderDoublyList_Pointer;




	//Create and initialize a component collection, and innstruct to create a new component to collect a set of vertices before executing DFS.
	TransposeGraph_Pointer->DFS_AdditionalResult.ComponentCollection_Pointer = (struct ComponentCollection_Tag*)malloc(sizeof(struct ComponentCollection_Tag));
	TransposeGraph_Pointer->DFS_AdditionalResult.ComponentCollection_Pointer->head = NULL;
	TransposeGraph_Pointer->DFS_AdditionalResult.ComponentCollection_Pointer->ComponentCounter = 0;
	TransposeGraph_Pointer->DFS_AdditionalResult.CreateComponent_Instruction = 1;





	//To do DFS for Transpose Graph.
	DFS(TransposeGraph_Pointer, TransposeGraph_Vertex_Pointer + RetrieveListHead(OrderDoublyList_Pointer)->Vertex_Pointer->Key);



	TransposeGraph_Pointer->DFS_AdditionalResult.StronglyConnectedComponent_Flag = 0;


	return TransposeGraph_Pointer->DFS_AdditionalResult.ComponentCollection_Pointer;
}
void ComponentCollection_Prepend(struct ComponentCollection_Tag* ComponentCollection_Pointer, struct ComponentCarrier_Tag* ComponentCarrier_Pointer)
{


	//Store the addresses of predecessor and successor for Insertion Element
	ComponentCarrier_Pointer->Prev = NULL;
	ComponentCarrier_Pointer->Next = ComponentCollection_Pointer->head;  //NULL or The address of first element in the past time



	if (ComponentCollection_Pointer->head != NULL) //(1)If there is a first element before prepanding, we need to update Prev of first element (2) before cover ComponentCollection_Pointer->head.
	{
		ComponentCollection_Pointer->head->Prev = ComponentCarrier_Pointer;
	}

	//Update the head pointer of queue.
	ComponentCollection_Pointer->head = ComponentCarrier_Pointer;


	//Increase the counter of component collection by one.
	ComponentCollection_Pointer->ComponentCounter++;

}
void ComponentCollection_Delete(struct ComponentCollection_Tag* LinkedList_Pointer, struct ComponentCarrier_Tag* Delete_Element_Address)
{
	if (Delete_Element_Address->Prev != NULL)
	{
		Delete_Element_Address->Prev->Next = Delete_Element_Address->Next;
	}
	else
	{
		LinkedList_Pointer->head = Delete_Element_Address->Next;
	}

	if (Delete_Element_Address->Next != NULL)
	{
		Delete_Element_Address->Next->Prev = Delete_Element_Address->Prev;
	}

	//Decrease the counter of component collection by one.
	LinkedList_Pointer->ComponentCounter--;

}
//Transfer the date of fragment memory in component collection to a contiguous memory space.
//Release the fragment space of original component collection which include component carrier, component, vertex carrier.
struct ComponentCollection_Tag* TransferToContiguousSpace(struct Graph_Tag* Graph_Pointer)
{

	struct ComponentCollection_Tag* ComponentCollection_Pointer = Graph_Pointer->TransposeGraph_Pointer->DFS_AdditionalResult.ComponentCollection_Pointer;

	//Create a contiguous space for component carrier, component, vertex carrier.
	int ComponentCounter = ComponentCollection_Pointer->ComponentCounter;

	int VertexCounter = 0;
	struct ComponentCarrier_Tag* Next_CompCarrier = ComponentCollection_Pointer->head;
	while (Next_CompCarrier != NULL)
	{
		VertexCounter = VertexCounter + Next_CompCarrier->StronglyConnectedComponent_Pointer->VertexCounter;
		Next_CompCarrier = Next_CompCarrier->Next;
	}

	struct ComponentCarrier_Tag* ContiguousComponentCarrier_Pointer = (struct ComponentCarrier_Tag*)malloc(ComponentCounter * sizeof(struct ComponentCarrier_Tag));
	Graph_Pointer->DFS_AdditionalResult.ReleaseCompCarrierAddress = ContiguousComponentCarrier_Pointer; //Record the address of contiguous component carrier for releasing the space.
	struct VertexSet_Tag* ContiguousComponent_Pointer = (struct VertexSet_Tag*)malloc(ComponentCounter * sizeof(struct VertexSet_Tag));
	Graph_Pointer->DFS_AdditionalResult.ReleaseCompAddress = ContiguousComponent_Pointer; //Record the address of contiguous component for releasing the space.
	struct VertexCarrier_Tag* ContiguousVertexCarrier_Pointer = (struct VertexCarrier_Tag*)malloc(VertexCounter * sizeof(struct VertexCarrier_Tag));
	Graph_Pointer->DFS_AdditionalResult.ReleaseVertexCarrierAddress = ContiguousVertexCarrier_Pointer; //Record the address of contiguous vertex carrier for releasing the space.


	//Initialize the heads for each contiguous component.
	for (int i = 0; i < ComponentCounter; i++)
	{
		(ContiguousComponent_Pointer + i)->head = NULL;
		(ContiguousComponent_Pointer + i)->VertexCounter = 0;
	}


	//Transfer the date of fragment memory in component collection to a contiguous memory space.
	//Release the fragment space of original component collection which include component carrier, component, vertex carrier.
	//Time Complexity : Theta(V)
	Next_CompCarrier = ComponentCollection_Pointer->head;


	int EmptyCompCarrier_Location = 0;
	int EmptyVertexCarrier_Location = 0;

	Graph_Pointer->DFS_AdditionalResult.ComponentCollection_Pointer = ComponentCollection_Pointer; //Update the pointer of component collection in original graph.
	while (Next_CompCarrier != NULL)
	{
		//Reserve the next component carrier address before modifying the current component carrier.
		struct ComponentCarrier_Tag* ReserveCompCarrier = Next_CompCarrier->Next;


		//Add the contiguous component carrier into the component collection.
		struct ComponentCarrier_Tag* EmptyCompCarrier_Pointer = ContiguousComponentCarrier_Pointer + EmptyCompCarrier_Location;
		struct VertexSet_Tag* EmptyComp_Pointer = ContiguousComponent_Pointer + EmptyCompCarrier_Location;
		EmptyCompCarrier_Pointer->StronglyConnectedComponent_Pointer = EmptyComp_Pointer;
		ComponentCollection_Delete(ComponentCollection_Pointer, Next_CompCarrier);
		ComponentCollection_Prepend(ComponentCollection_Pointer, EmptyCompCarrier_Pointer);


		//Transfer the data of vertex carrier from fragment memory to contiguous memory.
		struct VertexCarrier_Tag* NextVertexCarrier = Next_CompCarrier->StronglyConnectedComponent_Pointer->head;
		while (NextVertexCarrier != NULL)
		{
			struct VertexCarrier_Tag* ReserveVertexCarrier = NextVertexCarrier->Next;


			//Add the contiguous vertex carrier into the component.
			struct VertexCarrier_Tag* EmptyVertexCarrier_Pointer = ContiguousVertexCarrier_Pointer + EmptyVertexCarrier_Location;
			struct Vertex_Tag* Vertex_Pointer = Graph_Pointer->Vertex_Pointer + NextVertexCarrier->Vertex_Pointer->Key;  //Notice: The fragment-carrier and carried vertex are in transpose graph. 

			EmptyVertexCarrier_Pointer->Vertex_Pointer = Vertex_Pointer;
			VertexCarrier_Prepend(EmptyComp_Pointer, EmptyVertexCarrier_Pointer);



			EmptyVertexCarrier_Location++;


			free(NextVertexCarrier);
			NextVertexCarrier = ReserveVertexCarrier;
		}


		EmptyCompCarrier_Location++;


		free(Next_CompCarrier->StronglyConnectedComponent_Pointer);
		free(Next_CompCarrier);
		Next_CompCarrier = ReserveCompCarrier;
	}


	return ComponentCollection_Pointer;
}

//The function free the space of adjacency list, vertex, edges, edge carrier of graph,but doesn't free graph itself.  
void FreeGraph(struct Graph_Tag* Graph_Pointer)
{
	struct EdgeSpaceAddress_Carrier_Tag* EdgeSpaceAddress_Carrier_Pointer = Graph_Pointer->EdgeSpaceAddress_List.head;


	while (EdgeSpaceAddress_Carrier_Pointer != NULL)
	{
		struct EdgeSpaceAddress_Carrier_Tag* Next = EdgeSpaceAddress_Carrier_Pointer->Next;
		free(EdgeSpaceAddress_Carrier_Pointer->EdgeSpaceAddress);
		free(EdgeSpaceAddress_Carrier_Pointer);

		EdgeSpaceAddress_Carrier_Pointer = Next;
	}

	free(Graph_Pointer->AdjacencyList_Pointer);
	free(Graph_Pointer->Vertex_Pointer);
	free(Graph_Pointer);

}
struct ComponentCollection_Tag* CreateStronglyConnectedComponent(struct Graph_Tag* Graph_Pointer)
{

	(void)CreateDoublyList_FinishTimeOrder_DFS(Graph_Pointer);



	(void)CreateReverseDirectedGraph(Graph_Pointer);



	(void)TransposeGraph_DFS(Graph_Pointer);


	//Transfer the date of fragment memory in component collection to a contiguous memory space.
	//Release the fragment space of original component collection which include component carrier, component, vertex carrier.
	(void)TransferToContiguousSpace(Graph_Pointer);



	//Release the space of order doubly list.
	free(Graph_Pointer->DFS_AdditionalResult.OrderDoublyList_Pointer->ReleaseAddrress);
	free(Graph_Pointer->DFS_AdditionalResult.OrderDoublyList_Pointer);

	//Release the space of transpose graph.
	FreeGraph(Graph_Pointer->TransposeGraph_Pointer);


	//If we want to release the space/subspace of component collection, 
	//we need to free component collection pointer, component carrier pointer, strongly connected component pointer, and vertex carrier pointer.
	return Graph_Pointer->DFS_AdditionalResult.ComponentCollection_Pointer;

}