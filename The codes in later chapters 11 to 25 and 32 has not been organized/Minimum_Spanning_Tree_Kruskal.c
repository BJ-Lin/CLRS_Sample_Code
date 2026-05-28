#include "..\Header.h"




struct Graph_Tag MST_Graph_Object;

//CLRS,4th,P593 ; vertex a ~ vertex i <----> index = 0th ~ 8th
//This is adjacency list.
void MiniSpanTree_CreateGraph(struct Graph_Tag* Graph_Pointer)
{

	CreateInitialize_Vertex_and_Adjacency(Graph_Pointer, 9);

	unsigned int MaxArraySize = 10;
	int* VertexIndex_Pointer = (int*)malloc(MaxArraySize * sizeof(int));
	int* EdgeWeight_Pointer = (int*)malloc(MaxArraySize * sizeof(int));


	struct AdjacencyInformation_Tag AdjacencyInformation = { .Fill_EdgeValue_Flag = 1,.VertexIndex_Pointer = VertexIndex_Pointer,.EdgeWeight_Pointer = EdgeWeight_Pointer };



	//Set adjacency list for vertex a.
	AdjacencyInformation.AdjacencyIndex = 0;

	AdjacencyInformation.Number_of_Vertices = 2;
	VertexIndex_Pointer[0] = 1;
	VertexIndex_Pointer[1] = 7;
	EdgeWeight_Pointer[0] = 4;
	EdgeWeight_Pointer[1] = 8;

	Fill_Adjacency(Graph_Pointer, &AdjacencyInformation);



	//Set adjacency list for vertex b.
	AdjacencyInformation.AdjacencyIndex = 1;

	AdjacencyInformation.Number_of_Vertices = 3;
	VertexIndex_Pointer[0] = 0;
	VertexIndex_Pointer[1] = 2;
	VertexIndex_Pointer[2] = 7;
	EdgeWeight_Pointer[0] = 4;
	EdgeWeight_Pointer[1] = 8;
	EdgeWeight_Pointer[2] = 11;

	Fill_Adjacency(Graph_Pointer, &AdjacencyInformation);



	//Set adjacency list for vertex c.
	AdjacencyInformation.AdjacencyIndex = 2;

	AdjacencyInformation.Number_of_Vertices = 4;
	VertexIndex_Pointer[0] = 1;
	VertexIndex_Pointer[1] = 3;
	VertexIndex_Pointer[2] = 5;
	VertexIndex_Pointer[3] = 8;
	EdgeWeight_Pointer[0] = 8;
	EdgeWeight_Pointer[1] = 7;
	EdgeWeight_Pointer[2] = 4;
	EdgeWeight_Pointer[3] = 2;

	Fill_Adjacency(Graph_Pointer, &AdjacencyInformation);



	//Set adjacency list for vertex d.
	AdjacencyInformation.AdjacencyIndex = 3;

	AdjacencyInformation.Number_of_Vertices = 3;
	VertexIndex_Pointer[0] = 2;
	VertexIndex_Pointer[1] = 4;
	VertexIndex_Pointer[2] = 5;
	EdgeWeight_Pointer[0] = 7;
	EdgeWeight_Pointer[1] = 9;
	EdgeWeight_Pointer[2] = 14;

	Fill_Adjacency(Graph_Pointer, &AdjacencyInformation);


	//Set adjacency list for vertex e.
	AdjacencyInformation.AdjacencyIndex = 4;

	AdjacencyInformation.Number_of_Vertices = 2;
	VertexIndex_Pointer[0] = 3;
	VertexIndex_Pointer[1] = 5;
	EdgeWeight_Pointer[0] = 9;
	EdgeWeight_Pointer[1] = 10;

	Fill_Adjacency(Graph_Pointer, &AdjacencyInformation);




	//Set adjacency list for vertex f.
	AdjacencyInformation.AdjacencyIndex = 5;

	AdjacencyInformation.Number_of_Vertices = 4;
	VertexIndex_Pointer[0] = 2;
	VertexIndex_Pointer[1] = 3;
	VertexIndex_Pointer[2] = 4;
	VertexIndex_Pointer[3] = 6;
	EdgeWeight_Pointer[0] = 4;
	EdgeWeight_Pointer[1] = 14;
	EdgeWeight_Pointer[2] = 10;
	EdgeWeight_Pointer[3] = 2;

	Fill_Adjacency(Graph_Pointer, &AdjacencyInformation);


	//Set adjacency list for vertex g.
	AdjacencyInformation.AdjacencyIndex = 6;

	AdjacencyInformation.Number_of_Vertices = 3;
	VertexIndex_Pointer[0] = 5;
	VertexIndex_Pointer[1] = 7;
	VertexIndex_Pointer[2] = 8;
	EdgeWeight_Pointer[0] = 2;
	EdgeWeight_Pointer[1] = 1;
	EdgeWeight_Pointer[2] = 6;

	Fill_Adjacency(Graph_Pointer, &AdjacencyInformation);

	//Set adjacency list for vertex h.
	AdjacencyInformation.AdjacencyIndex = 7;

	AdjacencyInformation.Number_of_Vertices = 3;
	VertexIndex_Pointer[0] = 0;
	VertexIndex_Pointer[1] = 6;
	VertexIndex_Pointer[2] = 8;
	EdgeWeight_Pointer[0] = 8;
	EdgeWeight_Pointer[1] = 1;
	EdgeWeight_Pointer[2] = 7;

	Fill_Adjacency(Graph_Pointer, &AdjacencyInformation);

	//Set adjacency list for vertex i.
	AdjacencyInformation.AdjacencyIndex = 8;

	AdjacencyInformation.Number_of_Vertices = 3;
	VertexIndex_Pointer[0] = 2;
	VertexIndex_Pointer[1] = 6;
	VertexIndex_Pointer[2] = 7;
	EdgeWeight_Pointer[0] = 2;
	EdgeWeight_Pointer[1] = 6;
	EdgeWeight_Pointer[2] = 7;

	Fill_Adjacency(Graph_Pointer, &AdjacencyInformation);


	//Free the space of VertexIndex_Pointer and EdgeWeight_Pointer
	free(VertexIndex_Pointer);
	free(EdgeWeight_Pointer);

}
void MiniSpanTree_Make_Set(struct Vertex_Tag* ForestSetMember)
{
	//Create a tree and a node.
	struct MiniSpanTree_Node_Tag* Node_Pointer = (struct MiniSpanTree_Node_Tag*)malloc(sizeof(struct  MiniSpanTree_Node_Tag));


	//Fill the content of the node
	Node_Pointer->ForestSetMember = ForestSetMember;
	Node_Pointer->Parent = Node_Pointer;
	Node_Pointer->Rank = 0;

	//Fill the content of the member
	ForestSetMember->Node_Pointer = Node_Pointer;

}
struct Vertex_Tag* MiniSpanTree_Find_Set(struct Vertex_Tag* ForestSetMember)
{
	struct MiniSpanTree_Node_Tag* Node_Pointer = ForestSetMember->Node_Pointer;


	if (Node_Pointer != Node_Pointer->Parent)
	{
		//Execute the path-compression
		Node_Pointer->Parent = (MiniSpanTree_Find_Set(Node_Pointer->Parent->ForestSetMember))->Node_Pointer;
	}


	return Node_Pointer->Parent->ForestSetMember;

}
void MiniSpanTree_Link(struct Vertex_Tag* RootSetMember1, struct Vertex_Tag* RootSetMember2)
{
	struct MiniSpanTree_Node_Tag* Node1_Pointer = RootSetMember1->Node_Pointer;
	struct MiniSpanTree_Node_Tag* Node2_Pointer = RootSetMember2->Node_Pointer;

	if (Node1_Pointer->Rank > Node2_Pointer->Rank)
	{
		Node2_Pointer->Parent = Node1_Pointer;

	}
	else //if (Node1_Pointer->Rank <= Node2_Pointer->Rank), Node1 is appended on Node2.
	{
		Node1_Pointer->Parent = Node2_Pointer;

		if (Node1_Pointer->Rank == Node2_Pointer->Rank)
		{
			Node2_Pointer->Rank++;
		}

	}

}
//if (rank of RootSetMember1 <= rank of Node2_Pointer), Node1 is appended on Node2.
void MiniSpanTree_Union(struct Vertex_Tag* SetMember1, struct Vertex_Tag* SetMember2)
{
	MiniSpanTree_Link(MiniSpanTree_Find_Set(SetMember1), MiniSpanTree_Find_Set(SetMember2));
}
void EdgeDoublyList_Prepend(struct EdgeDoublyList_Tag* LinkedList_Pointer, struct ObjectWithWeightEdge_Tag* Insertion_Element_Address)
{
	//Store the addresses of predecessor and successor for Insertion Element
	Insertion_Element_Address->Prev = NULL;
	Insertion_Element_Address->Next = LinkedList_Pointer->head;  //NULL or The address of first element in the past time


	if (LinkedList_Pointer->head != NULL) //(1)If there is a first element before prepanding, we need to update Prev of first element (2) before cover LinkedList_Pointer->head.
	{
		LinkedList_Pointer->head->Prev = Insertion_Element_Address;
	}

	//Update the head pointer of queue.
	LinkedList_Pointer->head = Insertion_Element_Address;

	LinkedList_Pointer->Counter++;

}
void MiniSpanTree_Counting_Sort(int Array[], int* MaxMinBoundary_Pointer, struct ObjectWithWeightEdge_Tag** SortedInstantAddress_Array, size_t Instant_Size)
{
	//Space complexity : Theta( n + k )
	unsigned int Counter_Size = MaxMinBoundary_Pointer[1] - MaxMinBoundary_Pointer[0] + 1; //MaxMinBoundary[1] is max boundary, and MaxMinBoundary[0] is min boundary ; +1 means to add index=0 space. 
	struct ObjectWithWeightEdge_Tag** Output_Pointer = (struct ObjectWithWeightEdge_Tag**)malloc(Instant_Size * sizeof(struct ObjectWithWeightEdge_Tag*));
	unsigned* Counter_Pointer = (unsigned*)malloc((Counter_Size) * sizeof(unsigned));

	//Initialize the counter array to be 0.
	for (int i = 0; i < Counter_Size; i++)
	{
		Counter_Pointer[i] = 0;

	}

	//Compute the number of each value A[j]
	unsigned int Counter_Index;
	for (int j = 0; j < Instant_Size; j++)
	{
		Counter_Index = Array[j] - MaxMinBoundary_Pointer[0];
		Counter_Pointer[Counter_Index] = Counter_Pointer[Counter_Index] + 1;

	}


	//Compute the locations for fully-insersion of C[i]
	//locations of elements [ 1 : Instant_Size ]
	for (int i = 1; i < Counter_Size; i++)
	{
		Counter_Pointer[i] = Counter_Pointer[i] + Counter_Pointer[i - 1];

	}


	//Insert the values of Array
	for (int j = Instant_Size - 1; j >= 0; j--) // Initialize j = Instant_Size - 1 to make the output stable.
	{
		Counter_Index = Array[j] - MaxMinBoundary_Pointer[0];
		Output_Pointer[Counter_Pointer[Counter_Index] - 1] = SortedInstantAddress_Array[j]; //There exist conversion between location of elements [ 1 : Instant_Size ] and index [ 0 : Instant_Size - 1 ], such as -1 exist.
		Counter_Pointer[Counter_Index] = Counter_Pointer[Counter_Index] - 1;
	}

	for (int j = Instant_Size - 1; j >= 0; j--)
	{
		SortedInstantAddress_Array[j] = Output_Pointer[j];
	}

	free(Counter_Pointer);
	free(Output_Pointer);

}
unsigned int MiniSpanTree_CalculateSortedDigitNumber_Base10_INT(struct ObjectWithWeightEdge_Tag** SortedInstantAddress_Array, size_t Instant_Size)
{

	//Space complexity : Theta(n)
	char LeftPartValue_Flag = 0;

	unsigned int Number_Of_Digits = log10(INT_MAX) + 1; // We can list the form of 10^k <=INT_MAX < 10^(k+1) ; +1 means the units digit


	unsigned int UpperDigitPosition = Number_Of_Digits, LowerDigitPosition = 1; // This is the closed interval.
	//[ LowerDigitPosition , MiddleDigitPosition ] is lower region, [ MiddleDigitPosition + 1 , UpperDigitPosition ] is upper region
	unsigned int MiddleDigitPosition = (UpperDigitPosition + LowerDigitPosition) / 2; //The separation reason is that MiddleDigitPosition = ( k+(k+1) )/2 = k + 0.5 make the two separation regions, not only one.

	//Time Complexity: Theta( n * log d )
	do
	{
		LeftPartValue_Flag = 0;
		int temp;
		for (int i = 0; i < Instant_Size && LeftPartValue_Flag == 0; i++)
		{
			temp = SortedInstantAddress_Array[i]->WeightEdge_Pointer->EdgeWeight;
			LeftPartValue_Flag = LeftPartValue_Flag || (temp - temp % (int)pow(10, MiddleDigitPosition));
		}


		//Update all the digit positions
		if (LeftPartValue_Flag == 0) //LeftPartValue_Flag is 0, which means the values of all left parts are 0.
		{
			UpperDigitPosition = MiddleDigitPosition;
		}
		else
		{
			LowerDigitPosition = MiddleDigitPosition + 1;
		}
		MiddleDigitPosition = (UpperDigitPosition + LowerDigitPosition) / 2;

	} while (UpperDigitPosition != LowerDigitPosition);


	Number_Of_Digits = UpperDigitPosition;

	return Number_Of_Digits;
}
void MiniSpanTree_MSD_Radix_Sort(struct ObjectWithWeightEdge_Tag** SortedInstantAddress_Array, size_t Instant_Size, unsigned int Number_Of_Digits)
{
	unsigned int Digit_Position = Number_Of_Digits;
	//Base case , if Digit_Position=0.  
	if (Digit_Position > 0)
	{
		//Divide ( For each number, kth digit with same value are grouping )
		// n : Instant_Size
		//Space complexity : Theta(n)
		int* kth_Digit_Value = (int*)malloc(Instant_Size * sizeof(int));

		//Time complexity : Theta(n)
		//Extract kth Digit value for each number.
		for (int i = 0; i < Instant_Size; i++)
		{
			kth_Digit_Value[i] = (int)(SortedInstantAddress_Array[i]->WeightEdge_Pointer->EdgeWeight / pow(10, (Digit_Position - 1))) % 10; //Time complexity : Theta( lg(Digit_Position - 1) ) = Theta( 1 ) with maximumm digit number.
		}

		int MaxMinBoundary_Array[] = { -9,9 }; //We need to use counter for counting the number of value,and the range of value is [ -9 : 9 ].
		//Time complexity :  Theta( n ) , counter number k of Theta(n + k) is constant. k is not kth digit.
		//Sorting accorting kth Digit
		MiniSpanTree_Counting_Sort(kth_Digit_Value, MaxMinBoundary_Array, SortedInstantAddress_Array, Instant_Size);  //Here, we do not need the "stable" property , this is the difference between radix sort and most significant sort.





		// Space complexity : Theta(k) 
		unsigned int Counter_Size = MaxMinBoundary_Array[1] - MaxMinBoundary_Array[0] + 1;
		unsigned* Counter_Pointer = (unsigned*)malloc((Counter_Size) * sizeof(unsigned)); //Added index=0 space

		// Initialize the counter array to be 0. 
		// Time complexity : Theta(k) 
		for (int i = 0; i < Counter_Size; i++)
		{
			Counter_Pointer[i] = 0;

		}

		// Compute the number of each value A[j]
		// Time complexity : Theta(n) 
		unsigned int Counter_Index;
		for (int j = 0; j < Instant_Size; j++)
		{
			Counter_Index = kth_Digit_Value[j] - MaxMinBoundary_Array[0];
			Counter_Pointer[Counter_Index] = Counter_Pointer[Counter_Index] + 1;
		}


		//Conquer
		unsigned int Criteria_Number = 1; //If the number of values of the digit in a group is 1, we do not need to sort the group.
		unsigned int Next_Number_Of_Digits = Number_Of_Digits - 1;
		struct ObjectWithWeightEdge_Tag** Next_SortedInstantAddress = SortedInstantAddress_Array;
		//Time complexity : Theta( k ) 
		for (int i = 0; i < Counter_Size; i++)
		{

			if (Counter_Pointer[i] > Criteria_Number)
			{
				//Time complexity : Theta( n + k ) for each call if this is worst case ; Totally, d * Theta( n + k )
				MiniSpanTree_MSD_Radix_Sort(Next_SortedInstantAddress, Counter_Pointer[i], Next_Number_Of_Digits);
			}

			Next_SortedInstantAddress = Next_SortedInstantAddress + Counter_Pointer[i];
		}


		free(kth_Digit_Value);
		free(Counter_Pointer);

	}
}
void MiniSpanTree_Kruskal(struct Graph_Tag* Graph_Pointer)
{
	//Create space of edge list of minimum spanning tree
	Graph_Pointer->MiniSpanTree_EdgeList_Pointer = (struct EdgeDoublyList_Tag*)malloc(sizeof(struct EdgeDoublyList_Tag));
	struct EdgeDoublyList_Tag* MiniSpanTree_EdgeList_Pointer = Graph_Pointer->MiniSpanTree_EdgeList_Pointer;

	//Initialize edge list of minimum spanning tree
	MiniSpanTree_EdgeList_Pointer->head = NULL;
	MiniSpanTree_EdgeList_Pointer->Counter = 0;




	//Make each vertex be a set of forest.
	for (int i = 0; i < Graph_Pointer->Number_of_Vertex; i++)
	{
		MiniSpanTree_Make_Set(Graph_Pointer->Vertex_Pointer + i);
	}




	//Create a single list of the edges and initialize it.
	struct EdgeDoublyList_Tag* EdgeStorageList_Pointer = (struct EdgeDoublyList_Tag*)malloc(sizeof(struct EdgeDoublyList_Tag));
	EdgeStorageList_Pointer->head = NULL;
	EdgeStorageList_Pointer->Counter = 0;




	struct WeightEdge_Tag* WeightEdge_Pointer;
	struct ObjectWithWeightEdge_Tag* ObjectWithWeightEdge_Pointer;
	//Choose each adjacency
	for (int i = 0; i < Graph_Pointer->Number_of_Vertex; i++)
	{
		//Go through the whole adjacency for collecting the edges into the sorting edge list.		
		struct ObjectWithVertex_Tag* Next = Graph_Pointer->AdjacencyList_Pointer[i].head;
		while (Next != NULL)
		{
			if (Next->Vertex_Pointer->Key > i)
			{
				//Create the weight edge and fill the data. 
				//We do not create many weight edge at a time. The reason here, we free any weighted edge that is not included as a tree edge.
				WeightEdge_Pointer = (struct WeightEdge_Tag*)malloc(sizeof(struct WeightEdge_Tag)); //Space Complexity : Theta( | E | )
				WeightEdge_Pointer->VertexAddress_Pointer[0] = &Graph_Pointer->Vertex_Pointer[i];
				WeightEdge_Pointer->VertexAddress_Pointer[1] = &Graph_Pointer->Vertex_Pointer[Next->Vertex_Pointer->Key];
				WeightEdge_Pointer->EdgeWeight = Next->EdgeWeight;


				//Make the carrier to carry with Weight Edge.
				ObjectWithWeightEdge_Pointer = (struct ObjectWithWeightEdge_Tag*)malloc(sizeof(struct ObjectWithWeightEdge_Tag));
				ObjectWithWeightEdge_Pointer->WeightEdge_Pointer = WeightEdge_Pointer;


				//Insert the carrier to the list
				EdgeDoublyList_Prepend(EdgeStorageList_Pointer, ObjectWithWeightEdge_Pointer);

			}

			Next = Next->Next;
		}

	}




	//Convert the data structure of edge list into array for sorting.
	unsigned int EdgeNumber_of_Graph = EdgeStorageList_Pointer->Counter;


	struct ObjectWithWeightEdge_Tag** SortedEdgeAddress_Pointer = (struct ObjectWithWeightEdge_Tag**)malloc(EdgeNumber_of_Graph * sizeof(struct ObjectWithWeightEdge_Tag*)); //Space Complexity : Theta( | E | )

	struct ObjectWithWeightEdge_Tag* Next = EdgeStorageList_Pointer->head;
	while (Next != NULL)
	{
		//Fill the address into element of array
		static unsigned int i = 0;
		SortedEdgeAddress_Pointer[i] = Next;

		//Set the required index and pointer for next looop
		i++;
		Next = Next->Next;
	}



	//Sort the edges in the array.
	MiniSpanTree_MSD_Radix_Sort(SortedEdgeAddress_Pointer, EdgeNumber_of_Graph, MiniSpanTree_CalculateSortedDigitNumber_Base10_INT(SortedEdgeAddress_Pointer, EdgeNumber_of_Graph));



	//Take each edge from array in order.
	struct Vertex_Tag* Vertex_u_Pointer;
	struct Vertex_Tag* Vertex_v_Pointer;
	for (int i = 0; i < EdgeNumber_of_Graph; i++)
	{
		Vertex_u_Pointer = SortedEdgeAddress_Pointer[i]->WeightEdge_Pointer->VertexAddress_Pointer[0];
		Vertex_v_Pointer = SortedEdgeAddress_Pointer[i]->WeightEdge_Pointer->VertexAddress_Pointer[1];
		if (MiniSpanTree_Find_Set(Vertex_u_Pointer) != MiniSpanTree_Find_Set(Vertex_v_Pointer))
		{
			//Insert the carrier to the list
			EdgeDoublyList_Prepend(MiniSpanTree_EdgeList_Pointer, SortedEdgeAddress_Pointer[i]);

			//Merge two trees
			MiniSpanTree_Union(Vertex_u_Pointer, Vertex_v_Pointer);
		}
		else
		{
			//Remember to free ObjectWithWeightEdge and WeightEdge after take them from the list.
			free(SortedEdgeAddress_Pointer[i]->WeightEdge_Pointer);
			free(SortedEdgeAddress_Pointer[i]);
		}

	}


	//Merge the fragment memories into a contiguous memory.
	int TreeEdge_Numer = MiniSpanTree_EdgeList_Pointer->Counter;
	struct ObjectWithWeightEdge_Tag* ContiguousCarrier_Pointer = (struct ObjectWithWeightEdge_Tag*)malloc(TreeEdge_Numer * sizeof(struct ObjectWithWeightEdge_Tag));
	struct WeightEdge_Tag* ContiguousWeightEdge_Pointer = (struct WeightEdge_Tag*)malloc(TreeEdge_Numer * sizeof(struct WeightEdge_Tag));

	struct ObjectWithWeightEdge_Tag* FragEdgeCarrier_Pointer = MiniSpanTree_EdgeList_Pointer->head;
	MiniSpanTree_EdgeList_Pointer->head = NULL;
	int i = (TreeEdge_Numer - 1);
	while (FragEdgeCarrier_Pointer != NULL)
	{
		//Reserve the address of next object.
		struct ObjectWithWeightEdge_Tag* Next = FragEdgeCarrier_Pointer->Next;

		//Update the content of each edge carrier of contiguous memory.
		*(ContiguousWeightEdge_Pointer + i) = *(FragEdgeCarrier_Pointer->WeightEdge_Pointer);
		(ContiguousCarrier_Pointer + i)->WeightEdge_Pointer = ContiguousWeightEdge_Pointer + i;

		//Insert the carrier to the list
		EdgeDoublyList_Prepend(MiniSpanTree_EdgeList_Pointer, ContiguousCarrier_Pointer + i);

		//Release the fragment space.
		free(FragEdgeCarrier_Pointer->WeightEdge_Pointer);
		free(FragEdgeCarrier_Pointer);

		//Set the required index and pointer for next looop
		FragEdgeCarrier_Pointer = Next;
		i--;
	}




	struct ObjectWithWeightEdge_Tag* Temp = MiniSpanTree_EdgeList_Pointer->head;
	while (Temp != NULL)
	{
		printf("u = %d , v = %d , Weight = %d \n", Temp->WeightEdge_Pointer->VertexAddress_Pointer[0]->Key, Temp->WeightEdge_Pointer->VertexAddress_Pointer[1]->Key, Temp->WeightEdge_Pointer->EdgeWeight);
		Temp = Temp->Next;
	}



	free(EdgeStorageList_Pointer); //The edge list is not in using after convert the data structure.
	free(SortedEdgeAddress_Pointer);
}