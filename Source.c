#include "Header.h"


int main(void)
{

#if INSERTION_SORT_MODULE == 1
	size_t Array_size = sizeof(InsertedArray)/sizeof(int);


	printf("Non-Sorted Array: ");
	for (int k = 0; k < Array_size; k++)
	{
		printf("%d  ", *(InsertedArray + k));
	}
	printf("\n");


	Insertion_Sort(Array_size, InsertedArray);

	
	printf("Sorted Array:     ");
	for (int k = 0; k < Array_size; k++)
	{
		printf("%d  ", *(InsertedArray + k));
	}
	printf("\n");
#endif




#if MERGE_SORT_MODULE == 1
	int Array_size = sizeof(InsertedArray) / sizeof(int);

	printf("Non-Sorted Array: ");
	for (int k = 0; k < Array_size; k++)
	{
		printf("%d  ", *(InsertedArray + k));
	}
	printf("\n");


	Merge_Sort(InsertedArray, Array_size);


	printf("Sorted Array:     ");
	for (int k = 0; k < Array_size; k++)
	{
		printf("%d  ", *(InsertedArray + k));
	}
	printf("\n");
#endif




#if RECURSIVE_MATRIX_MODULE == 1
	//Initial positions of three matrices.
	unsigned int Matrix_A_Position[2] = { 0 };
	unsigned int Matrix_B_Position[2] = { 0 };
	unsigned int Matrix_C_Position[2] = { 0 };
	Matrix_Multiply_Recursive(Matrix_A_Position, Matrix_B_Position, Matrix_C_Position, Init_Matrix_Length_n, Init_Matrix_Length_m, Init_Matrix_Length_r);
	for (int i = 0; i < Init_Matrix_Length_n; i++)
	{
		for (int j = 0; j < Init_Matrix_Length_r; j++)
		{
			printf("C[%d][%d] = %.0f ", i, j, Matrix_C[i][j]);

		}

		printf("\n");
	}
#endif




#if STRASSEN_MATRIX_MULTIPLY_RECURSIVE_MODULE == 1
	unsigned int Been_Checked_Flag = 0; //Before every checking, we need to initialize the flag value to zero. 
	float* Init_Matrix_A_Pointer = (float*)malloc(Init_Matrix_Length_n * Init_Matrix_Length_n * sizeof(float));
	float* Init_Matrix_B_Pointer = (float*)malloc(Init_Matrix_Length_n * Init_Matrix_Length_n * sizeof(float));
	float* Init_Matrix_C_Pointer = (float*)malloc(Init_Matrix_Length_n * Init_Matrix_Length_n * sizeof(float));
	for (int i = 0; i < Init_Matrix_Length_n; i++)
	{
		for (int j = 0; j < Init_Matrix_Length_n; j++)
		{
			*(Init_Matrix_A_Pointer + i * Init_Matrix_Length_n + j) = Matrix_A[i][j];
			*(Init_Matrix_B_Pointer + i * Init_Matrix_Length_n + j) = Matrix_B[i][j];
			*(Init_Matrix_C_Pointer + i * Init_Matrix_Length_n + j) = Matrix_C[i][j];
		}
	}


	Strassen_Matrix_Multiply_Recursive(Init_Matrix_A_Pointer, Init_Matrix_B_Pointer, Init_Matrix_C_Pointer, Init_Matrix_Length_n, &Been_Checked_Flag);

	printf("\nThe computed matrix C:\n");
	for (int i = 0; i < Init_Matrix_Length_n; i++)
	{
		for (int j = 0; j < Init_Matrix_Length_n; j++)
		{
			printf("C[%d][%d] = %.0f ", i, j, *(Init_Matrix_C_Pointer + i * Init_Matrix_Length_n + j));

		}

		printf("\n");
	}

	free(Init_Matrix_A_Pointer);
	free(Init_Matrix_B_Pointer);
	free(Init_Matrix_C_Pointer);
#endif




#if MAX_HEAP_SORT_MODULE == 1
	size_t Heap_Array_Size = sizeof(Heap_Array) / sizeof(float);	

	MaxHeapSort(Heap_Array, Heap_Array_Size);

	printf("Sorted Number :");
	for(int i = 0; i < Heap_Array_Size; i++)
	{
		printf("%.0f ", Heap_Array[i]);
	}
#endif




#if MIN_HEAP_SORT_MODULE == 1
	size_t Heap_Array_Size = sizeof(Heap_Array) / sizeof(float);

	MinHeapSort(Heap_Array, Heap_Array_Size);

	printf("Sorted Number :");
	for (int i = 0; i < Heap_Array_Size; i++)
	{
		printf("%.0f ", Heap_Array[i]);
	}
#endif




#if PRIORITY_QUEUE_MAX_HEAP_MODULE == 1
	//Part1.
	MaxPriority_Queue.Queue_Size = sizeof(Queue_Object) / sizeof(struct Object_of_Queue_Tag);
	MaxPriority_Queue.Array_Size = sizeof(MaxPriority_Queue.PointerArray) / sizeof(struct Object_of_Queue_Tag*);

	for (int i = 0; i < MaxPriority_Queue.Queue_Size; i++)
	{
		MaxPriority_Queue.PointerArray[i] = Queue_Object + i;

	}

	size_t* Queue_Size_Pointer = &MaxPriority_Queue.Queue_Size;
	
	struct Object_of_Queue_Tag** PointerArray= MaxPriority_Queue.PointerArray; // Here, we declare one free place for insert function test.



	printf("Keys of Queue( After Maximum Extraction ) : \n");
	Queue_Max_Heap_Extract_Maximum(&MaxPriority_Queue);

	for (int i = 0; i < *Queue_Size_Pointer; i++)
	{
		printf("Index = %u , Key = %.0f\n", (*PointerArray[i]).Index, (*PointerArray[i]).Key);

	}
	printf("\n\n");
	






	//Part2.
	struct Object_of_Queue_Tag Object_of_Queue = { .Key = 15,.Index = 0 };

	Queue_Max_Heap_Insert(&MaxPriority_Queue, &Object_of_Queue);



	printf("Keys of Queue( After Inserting a key( 15 ) ) : \n");
	for (int i = 0; i < *Queue_Size_Pointer; i++)
	{
		printf("Index = %u , Key = %.0f\n", PointerArray[i]->Index, PointerArray[i]->Key);

	}
	printf("\n\n");






	//Part3.
	printf("Keys of Queue( After Delete two keys ( 15 , 9 ) ) : \n");
	Max_Heap_Delete(&MaxPriority_Queue, &Object_of_Queue);
	Max_Heap_Delete(&MaxPriority_Queue, PointerArray[5]);

	for (int i = 0; i < *Queue_Size_Pointer; i++)
	{
		printf("Index = %u , Key = %.0f\n", PointerArray[i]->Index, PointerArray[i]->Key);

	}
#endif




#if RANDOMIZED_QUICK_SORT_MODULE==1
	int Array_Size = sizeof(QuickSort_Array) / sizeof(float);
	
	Call_Randomized_QuickSort(QuickSort_Array, Array_Size);

	printf("Sorted Number :");
	for (int i = 0; i < Array_Size; i++)
	{
		printf("%.0f ", QuickSort_Array[i]);
	}	
#endif	




#if THREE_WAY_RANDOMIZED_QUICK_SORT_MODULE==1
	int Array_Size = sizeof(QuickSort_Array) / sizeof(float);

	Call_ThreeWay_Randomized_QuickSort(QuickSort_Array, Array_Size);

	printf("Sorted Number :");
	for (int i = 0; i < Array_Size; i++)
	{
		printf("%.0f ", QuickSort_Array[i]);
	}
#endif	




#if COUNTING_SORT_MODULE==1
	int Inverval_Boundary[2] = {-9, 9};
	Counting_Sort(Counting_Array, Inverval_Boundary, Counting_Array, sizeof(Counting_Array) / sizeof(int));

	printf("Sorted Number: %d ", Counting_Array[0]);
	for (int i = 1; i < sizeof(Counting_Array) / sizeof(int); i++)
	{
		printf(", %d ", Counting_Array[i]);
	}
	printf("\n\n");
#endif		




#if MSD_RADIX_SORT_MODULE==1	
	MSD_Radix_Sort(MostSignificant_Array, sizeof(MostSignificant_Array) / sizeof(int), CalculateSortedDigitNumber_Base10_INT(MostSignificant_Array, sizeof(MostSignificant_Array) / sizeof(int)));

	printf("Sorted Number: %d ", MostSignificant_Array[0]);
	for (int i = 1; i < sizeof(MostSignificant_Array) / sizeof(int); i++)
	{
		printf(", %d ", MostSignificant_Array[i]);
	}
	printf("\n\n");
#endif		




#if LSD_RADIX_SORT_MODULE==1	
	LSD_Radix_Sort(MostSignificant_Array, sizeof(MostSignificant_Array) / sizeof(int), CalculateSortedDigitNumber_Base10_INT(MostSignificant_Array, sizeof(MostSignificant_Array) / sizeof(int)));

	printf("Sorted Number: %d ", MostSignificant_Array[0]);
	for (int i = 1; i < sizeof(MostSignificant_Array) / sizeof(int); i++)
	{
		printf(", %d ", MostSignificant_Array[i]);
	}
	printf("\n\n");
#endif	




#if BUCKET_SORT_MODULE==1		
	Bucket_Sort(Bucket_Numbers, sizeof(Bucket_Numbers) / sizeof(float), 10);	
	printf("Sorted Number: %.2f ", Bucket_Numbers[0]);
	for (int i = 1; i < sizeof(Bucket_Numbers) / sizeof(float); i++)
	{
		printf(", %.2f ", Bucket_Numbers[i]);
	}
	printf("\n\n");
#endif	




#if SELECTION_OF_MAXIMUM_MINIMUM_MODULE==1	
	float Max = 0, Min = 0;
	Selection_Of_Maximum_Minimum(Bucket_Numbers, sizeof(Bucket_Numbers) / sizeof(float), &Max, &Min);
	printf("Maximum = %.2f, Minimum = %.2f\n", Max, Min);
#endif




#if RANDOMIZED_SELECT_MODULE==1
	for (int i = 1; i <= sizeof(Bucket_Numbers) / sizeof(float); i++)
	{
		unsigned Order = i;
		float Value = Call_Randomized_Select(Bucket_Numbers, sizeof(Bucket_Numbers) / sizeof(float), Order);
		printf("The %uth smallest element = %.2f\n", Order, Value);
	}
#endif




#if SELECTION_WORSTCASE_LINEARTIME_MODULE==1
	for (int i = 1; i <= sizeof(Bucket_Numbers) / sizeof(float); i++)
	{
		unsigned Order = i;
		unsigned Array_Size = sizeof(Bucket_Numbers) / sizeof(float);
		float* Value_Address = Select(Bucket_Numbers, Array_Size, Order);

		printf("The %uth smallest element = %.2f\n", Order, *Value_Address);

	}
#endif




#if STACK_MODULE==1
	printf("Is the Stack empty at start: \n");
	_Bool x1 = Stack_Empty(&Stack);
	if (x1 == 1)
	{
		printf("Stack is empty.\n\n");
	}
	else
	{
		printf("Stack is not empty.\n\n");	
	}

	printf("Is the Stack empty after pushing three objects: \n");
	struct Object_Tag Element[3];
	for(int i = 0; i < 3; i++)
	{
		Element[i].Key = i;
		Stack_Push(&Stack, Element[i]);
	}
	x1 = Stack_Empty(&Stack);

	if (x1 == 1)
	{
		printf("Stack is empty. \nThe number of elements is %d\n\n", Stack.Top + 1);
	}
	else
	{
		printf("Stack is not empty. \nThe number of elements is %d\n\n", Stack.Top + 1);
	}


	printf("How many elements in the stack after popping a element: \n");
	struct Object_Tag Receiver = { 0 };
	_Bool x3 = Stack_Pop(&Stack, &Receiver);
	printf("The number of the elements in the stack after popping is %d. \nThe popped element is %d\n\n", Stack.Top + 1, Receiver.Key);
#endif




#if QUEUE_MODULE==1	
	struct Object_Tag Object[20];
	for (int i = 0; i < 20; i++)
	{
		Object[i].Key = i;
		Enqueue(&Queue, Object + i);
	}
	printf("head value after enqueueing: %d\n", Queue.Head);
	printf("tail value after enqueueing: %d\n\n", Queue.Tail);



	struct Object_Tag Receiver;
	Dequeue(&Queue, &Receiver);	
	printf("head value after dequeueing: %d\n", Queue.Head);
	printf("tail value after dequeueing: %d\n", Queue.Tail);
	printf("The dequeued element is %d\n\n", Receiver.Key);
#endif




#if DOUBLY_LINKEDLIST_MODULE==1	
	struct Object2_Tag Element[15];
	struct Object2_Tag Element_Attach[2];
	


	printf("The values in the list after prepending: \n");
	for (int i = 0; i < 15; i++)
	{
		Element[i].Key = i;
		DoublyList_Prepend(&LinkedList, Element+i);
	}
	struct Object2_Tag *Next=LinkedList.Head;
	while (Next != NULL)
	{
		printf("%d ", Next->Key);
		Next = Next->Next;
	}
	printf("\n\n");



	printf("Find out the object with the key 5, and present it: ");
	struct Object2_Tag* SearchedObject_Pointer = DoublyList_Search(&LinkedList, 5);
	printf("%d ", SearchedObject_Pointer->Key);
	printf("\n\n");



	printf("Insert the objects with key 30 and key 40 after object with key 14: ");
	Element_Attach[0].Key = 30;
	Element_Attach[1].Key = 40;
	DoublyList_Insert(&LinkedList, Element+14, Element_Attach);
	DoublyList_Insert(&LinkedList, Element+14, Element_Attach+1);
	Next = LinkedList.Head;
	while (Next != NULL)
	{
		printf("%d ", Next->Key);
		Next = Next->Next;
	}
	printf("\n\n");




	printf("Delete the objects with key 14 and key 30: ");
	DoublyList_Delete(&LinkedList, Element+14);
	DoublyList_Delete(&LinkedList, Element_Attach);
	Next = LinkedList.Head;
	while (Next != NULL)
	{
		printf("%d ", Next->Key);
		Next = Next->Next;
	}
	printf("\n\n");
#endif




#if CIRCULAR_DOUBLY_LINKEDLIST_MODULE==1	
	//Initialize the circular linked list with a senitel node, and the key value of senitel node is -1 for indicating that it is a senitel node.
	struct CircularLinkedList_Tag CircularLinkedList ; 
	CircularLinkedList.Senitel.Prev = CircularLinkedList.Senitel.Next = &CircularLinkedList.Senitel;
	struct Object2_Tag Element[15];
	printf("The values in the list after inserting: \n");
	for (int i = 0; i < 15; i++)
	{
		Element[i].Key = i;
		Circular_DoublyList_Insert(&CircularLinkedList.Senitel, &Element[i]);
	}

	struct Object2_Tag* Next = CircularLinkedList.Senitel.Next;
	while (Next != &CircularLinkedList.Senitel)
	{
		printf("%d ", Next->Key);
		Next = Next->Next;
	}
	printf("\n\n");




	printf("Find out the object with the key 5, and present it: ");
	struct Object2_Tag* SearchedObject_Pointer = Circular_DoublyList_Search(&CircularLinkedList, 5);
	printf("%d ", SearchedObject_Pointer->Key);
	printf("\n\n");




	printf("Delete the objects with key 14 and key 5: ");
	Circular_DoublyList_Delete(Element + 14);
	Circular_DoublyList_Delete(Element + 5);
	Next = CircularLinkedList.Senitel.Next;
	while (Next != &CircularLinkedList.Senitel)
	{
		printf("%d ", Next->Key);
		Next = Next->Next;
	}
	printf("\n\n");
#endif




#if DIRECT_ADDRESS_TABLE_MODULE==1	
	//Initialize the direct address table with null pointer for each slot in the table.
	int Number_Of_Slot = 10;
	for (int i = 0; i < Number_Of_Slot; i++)
	{
		AddressTable[i] = NULL;
	}



	printf("Insert three elements: ");
	struct Direct_Address_Object_Tag DirectTableElement[3] = { 0 };
	for (int i = 0; i < 3; i++)
	{
		DirectTableElement[i].Key = i;
		Direct_Address_Insert(AddressTable, DirectTableElement + i);
	}
	for (int i = 0; i < Number_Of_Slot; i++)
	{
		if (AddressTable[i] != NULL)
		{
			printf("%d ", AddressTable[i]->Key);
		}
		else
		{
			printf("NULL ");
		}
		
	}
	printf("\n\n");



	printf("Delete the element with key 1: ");
	Direct_Address_Delete(AddressTable, DirectTableElement+1);
	for (int i = 0; i < Number_Of_Slot; i++)
	{
		if (AddressTable[i] != NULL)
		{
			printf("%d ", AddressTable[i]->Key);
		}
		else
		{
			printf("NULL ");
		}

	}
	printf("\n\n");



	struct Direct_Address_Object_Tag* Temp = Direct_Address_Search(AddressTable, 2);
	if (Temp != NULL)
	{
		printf("The element with key 2 is in the table, and its key value is %d\n\n", Temp->Key);
	}
	else
	{
		printf("The element with key 2 is not in the table.\n\n");
	}
#endif




#if HASH_TABLE_MODULE==1
	int TableLength = UniversalTable.TableLength = 100;
	UniversalTable.LinkedList = (struct LinkedList_Tag*)malloc(TableLength * sizeof(struct LinkedList_Tag));

	//initialize the linked list of each slot in the hash table.
	for (int i = 0; i < TableLength; i++)
	{
		UniversalTable.LinkedList[i].Head = NULL;
		UniversalTable.LinkedList[i].ObjectCounter = 0;
	}


	srand((unsigned)time(NULL));


	#define Size 10000
	int InsertionObjectSize = Size;
	struct Object2_Tag RandomKeyArray[Size];

	//Generate random keys for the objects to be inserted into the hash table.
	for (int i = 0; i < InsertionObjectSize; i++)
	{
		RandomKeyArray[i].Key = rand();

	}

	//Insert the objects into the hash table,and print the number of objects in each slot.
	for (int i = 0; i < InsertionObjectSize; i++)
	{
		Chained_Hash_Insert(&UniversalTable, &RandomKeyArray[i]);
	}
	
	float ExpectedValue = 0;
	for (int i = 0; i < TableLength; i++)
	{
		
		ExpectedValue = ExpectedValue + i * (float)(UniversalTable.LinkedList + i)->ObjectCounter / Size;

	}

	printf("Expected Value of object location = %.3f\n", ExpectedValue);

	free(UniversalTable.LinkedList);
#endif




#if OPEN_ADDRESS_TABLE_MODULE==1	
	unsigned int Hash_Value;
	for (int i = 0; i < 10; i++)
	{
		OpenAddress_Hash_Insert(Table, sizeof(Table) / sizeof(struct Object2_Tag), &Object_Array[i], &Hash_Value);
		printf("Hash_Value = %u\n", Hash_Value);
		printf("Key = %d\n\n", Table[Hash_Value]->Key);
	}
	Linear_Probing_Hash_Delete(Table, sizeof(Table) / sizeof(struct Object2_Tag),4);
#endif




#if BINARY_SEARCH_TREE_MODULE==1
	unsigned Number_Of_Objects = sizeof(BinaryTree_ObjectArray) / sizeof(struct Object_of_BinaryTree_Tag);
	
	//The constructed binary tree is as same as CLRS,4th,p322,Figure 12.3.
	for (unsigned i = 0; i < Number_Of_Objects; i++)
	{		
		BinaryTree_Insert(&BinaryTree, BinaryTree_ObjectArray+i);
	}
	
	printf("Inorder: ");
	Inorder_BinaryTree_Walk(BinaryTree.RootObject_Pointer);
	printf("\n\n");




	struct Object_of_BinaryTree_Tag* Search_Object_Pointer = Iterative_BinaryTree_Search(BinaryTree.RootObject_Pointer, 17);

	if (Search_Object_Pointer == NULL)
	{
		printf("There is not existing\n");
	}
	else 
	{ 
		printf("Key of Searched object = %d\n\n", Search_Object_Pointer->Key); 
	}
	

	struct Object_of_BinaryTree_Tag* Minimum_Object_Pointer;
	struct Object_of_BinaryTree_Tag* Maximum_Object_Pointer;

	BinaryTree_Minimum(BinaryTree.RootObject_Pointer, &Minimum_Object_Pointer);
	BinaryTree_Maximum(BinaryTree.RootObject_Pointer, &Maximum_Object_Pointer);

	printf("Minimum : %d , Maximum : %d \n", Minimum_Object_Pointer->Key, Maximum_Object_Pointer->Key);






	struct Object_of_BinaryTree_Tag* Successor_Object_Pointer;
	BinaryTree_Successor(BinaryTree_ObjectArray , &Successor_Object_Pointer);

	if (Successor_Object_Pointer == NULL)
	{
		printf("There is not existing\n");
	}
	else
	{
		printf("Successor Key : %d\n", Successor_Object_Pointer->Key);
	}
	

	BinaryTree_Delete(&BinaryTree, BinaryTree_ObjectArray);

	printf("Inorder: ");
	Inorder_BinaryTree_Walk(BinaryTree.RootObject_Pointer);
	printf("\n\n");
#endif




#if AVL_TREE_MODULE==1
	int Array_Size = sizeof(AVLTree_ObjectArray) / sizeof(struct Object_of_AVLTree_Tag);
	for (unsigned i = 0; i < Array_Size; i++)
	{
		AVLTree_Insert(&AVLTree, AVLTree_ObjectArray+i);
	}




	AVLTree_Delete(&AVLTree, AVLTree_ObjectArray+2);


	for (int i = 0; i < Array_Size; i++)
	{
		printf("Key = %d, Height = %d\n", (AVLTree_ObjectArray + i)->Key, (AVLTree_ObjectArray + i)->Height);

		int RightHeight, LeftHeight;
		Get_ChildrenHeight(AVLTree_ObjectArray + i, &RightHeight, &LeftHeight);
		printf("Children_HeightDifference =%d - %d = %d\n", LeftHeight, RightHeight, LeftHeight - RightHeight);
		if ((AVLTree_ObjectArray + i)->LeftObject_Pointer == NULL)
		{
			printf("LeftObject_Pointer is NULL\n");
		}
		else
		{
			printf("LeftObject_Pointer->Key = %d\n", (AVLTree_ObjectArray + i)->LeftObject_Pointer->Key);
		}

		if ((AVLTree_ObjectArray + i)->RightObject_Pointer == NULL)
		{
			printf("RightObject_Pointer is NULL\n\n");
		}
		else
		{
			printf("RightObject_Pointer->Key = %d\n\n", (AVLTree_ObjectArray + i)->RightObject_Pointer->Key);
		}
	}
#endif




#if RED_BLACK_TREE_MODULE==1
	unsigned Number_Of_Objects = sizeof(RedBlackTree_ObjectArray) / sizeof(struct Object_of_RedBlackTree_Tag);
	for (unsigned i = 0; i < Number_Of_Objects; i++)
	{
		RB_Insert(&RedBlackTree, RedBlackTree_ObjectArray + i);
	}
	printf("\n\n");
	Inorder_RedBlackTree_Walk(&RedBlackTree,RedBlackTree.RootObject_Pointer);
	printf("\n\n");
	RB_Delete(&RedBlackTree, RedBlackTree_ObjectArray);
	Inorder_RedBlackTree_Walk(&RedBlackTree, RedBlackTree.RootObject_Pointer);
#endif




#if ROD_CUTTING_MODULE==1	
	unsigned int MaxLength_in_Table = sizeof(Price_Table) / sizeof(int);
	int CuttedRod_Length = 0;
	Memoized_Cut_Rod(Price_Table, MaxLength_in_Table, CuttedRod_Length);
	for (int i = 0; i < MaxLength_in_Table; i++)
	{
		printf("Price_Table[%d]=%d\n", i, Price_Table[i]);
	}
#endif




#if MATRIX_CHAIN_MODULE==1	
	Matrix_Chain_Order(MatrixDimensionSequence_Array, Number_of_Matrix);
#endif





#if LONGEST_COMMON_SUBSEQUENCE_MODULE==1	
	unsigned int StringX_Length = sizeof(StringX_Array) / sizeof(char) - 1;
	unsigned int StringY_Length = sizeof(StringY_Array) / sizeof(char) - 1;
	
	LCS_Length(StringX_Array, StringX_Length, StringY_Array, StringY_Length);
	Start_Recursive_LCS(StringX_Array, StringX_Length, StringY_Array, StringY_Length);


#endif



#if OPTIMAL_BINARY_SEARCH_TREE_MODULE==1	
	unsigned int Number_of_Node = sizeof(ActualKey_Probability_Array) / sizeof(float) - 1;
	Optimal_BST(ActualKey_Probability_Array, DummyKey_Probability_Array, Number_of_Node);

	OptimalBinaryTree_Insert(&Optimal_BinaryTree, Object_with_ActualKey_Array, Object_with_DummyKey_Array, &Optimal_NeededInformation);
	printf("%d\n", Optimal_BinaryTree.RootObject_Pointer->RightObject_Pointer->LeftObject_Pointer->RightObject_Pointer->Key);
#endif




#if GREEDY_ACTIVITY_SELECTOR_MODULE==1	
	int Maximum_ActivityIndex = sizeof(StartTime_Array) / sizeof(int) - 1;
	Greedy_Activity_Selector(StartTime_Array, FinalTime_Array, Maximum_ActivityIndex);
#endif
	


#if HUFFMAN_CODE_MODULE==1	
	Huffman(CharacterObject_Table, sizeof(CharacterObject_Table) / sizeof(struct CharacterObject_Tag));
#endif
	




#if DYNAMIC_ORDER_STATISTIC_MODULE==1	
	unsigned Number_Of_Objects = sizeof(RedBlackTree_ObjectArray) / sizeof(struct Object_of_RedBlackTree_Tag);
	for (unsigned i = 0; i < Number_Of_Objects; i++)
	{
		RB_Insert(&RedBlackTree, RedBlackTree_ObjectArray + i);
	}
	RB_Delete(&RedBlackTree, RedBlackTree_ObjectArray);
	for(int i=1;i<= Number_Of_Objects-1;i++)
	{
		struct Object_of_RedBlackTree_Tag* Node_Pointer = Os_Select(RedBlackTree.RootObject_Pointer, i);
		printf("Key=%u\n", Node_Pointer->Key);
	}
	
	for (int i = 1; i < Number_Of_Objects; i++)
	{
		unsigned int Rank = Os_Rank(&RedBlackTree, RedBlackTree_ObjectArray+i);
		printf("Rank=%u\n", Rank);
	}
#endif




#if INTERVAL_TREE_MODULE==1
	int ElementNumber = sizeof(IntervalTree_ObjectArray) / sizeof(struct Object_of_IntervalTree_Tag);

	//Insert all element
	for(int i=0;i< ElementNumber;i++)
	{ 
		IntervalTree_Insert(&IntervalTree, IntervalTree_ObjectArray+i);
	}
	
	for (int i = 0; i < ElementNumber; i++)
	{
		printf("%d ", (IntervalTree_ObjectArray + i)->MaxEndpointValue);
		
	}
	printf("\n");

	Interval_Search(&IntervalTree, &Interval_Object);

	
	IntervalTree_Delete(&IntervalTree, IntervalTree_ObjectArray + 8);
	IntervalTree_Delete(&IntervalTree, IntervalTree_ObjectArray + 3);
	IntervalTree_Delete(&IntervalTree, IntervalTree_ObjectArray + 1);

	//Solution : a[0]=30¡Aa[2]=30¡Aa[4]=23¡Aa[5]=20¡Aa[6]=26¡Aa[7]=3¡Aa[9]=20
	for (int i = 0; i <= 0; i++)
	{
		//IntervalTree_Layout(&IntervalTree, IntervalTree_ObjectArray + i);
		printf("array[%d]=%d ", i, (IntervalTree_ObjectArray + i)->MaxEndpointValue);
		printf("\n");
	}

	for (int i = 2; i <= 2; i++)
	{
		//IntervalTree_Layout(&IntervalTree, IntervalTree_ObjectArray + i);
		printf("array[%d]=%d ", i, (IntervalTree_ObjectArray + i)->MaxEndpointValue);
		printf("\n");
	}


	for (int i = 4; i <= 7; i++)
	{
		//IntervalTree_Layout(&IntervalTree, IntervalTree_ObjectArray + i);
		printf("array[%d]=%d ", i, (IntervalTree_ObjectArray + i)->MaxEndpointValue);
		printf("\n");
	}

	for (int i = 9; i <= 9; i++)
	{
		//IntervalTree_Layout(&IntervalTree, IntervalTree_ObjectArray + i);
		printf("array[%d]=%d ", i, (IntervalTree_ObjectArray + i)->MaxEndpointValue);
		printf("\n");
	}




	//Test Delete function
	IntervalTree_Delete(&IntervalTree, IntervalTree_ObjectArray + 3);
	IntervalTree_Delete(&IntervalTree, IntervalTree_ObjectArray + 6);
	IntervalTree_Delete(&IntervalTree, IntervalTree_ObjectArray + 9);
	
	//Solution : a[0]=30¡Aa[1]=23¡Aa[2]=30¡Aa[4]=23¡Aa[5]=19¡Aa[7]=3¡Aa[8]=10
	for (int i = 0; i <= 2; i++)
	{
		//IntervalTree_Layout(&IntervalTree, IntervalTree_ObjectArray + i);
		printf("array[%d]=%d ", i , (IntervalTree_ObjectArray + i)->MaxEndpointValue);
		printf("\n");
	}

	for (int i = 4; i <=5; i++)
	{
		//IntervalTree_Layout(&IntervalTree, IntervalTree_ObjectArray + i);
		printf("array[%d]=%d ", i , (IntervalTree_ObjectArray + i)->MaxEndpointValue);
		printf("\n");
	}

	for (int i = 7; i <= 8; i++)
	{
		//IntervalTree_Layout(&IntervalTree, IntervalTree_ObjectArray + i);
		printf("array[%d]=%d ", i , (IntervalTree_ObjectArray + i)->MaxEndpointValue);
		printf("\n");
	}
#endif
	



#if LINKEDLIST_DISJOINTSET_MODULE==1
	struct SetMember_Tag SetMember[] = {[0].Key = 100,[1].Key = 200,[2].Key = 300,[3].Key = 400 };


	struct SetObject_Tag* SetObject_Pointer;
	int Number = sizeof(SetMember) / sizeof(struct SetMember_Tag);
	for (int i = 0; i < Number; i++)
	{
		SetObject_Pointer=Make_Set(SetMember + i);
		printf("%d   %d    %d\n", SetObject_Pointer->head->SetMember->Key, SetObject_Pointer->tail->SetMember->Key, SetObject_Pointer->tail->Next);

	}


	for (int i = 1; i < Number; i++)
	{
		SetObject_Pointer=Union(SetMember, SetMember+i);

	}


	struct SetMember_Tag* Representative_Address = Find_Set(SetMember);


	struct DisjointObject_Tag* Next = SetObject_Pointer->head;
	while (Next != NULL)
	{
		printf("%d ", Next->SetMember->Key);
		
		Next = Next->Next;
	}
	printf("\n");
#endif




#if DISJOINTSET_FOREST_MODULE==1
	struct ForestSetMember_Tag ForestSetMember_Array[] = { [0] .Key = 0,[1].Key = 1,[2].Key = 2,[3].Key = 3,[4].Key = 4,[5].Key = 5,[6].Key = 6 };
	for (int i = 0; i < sizeof(ForestSetMember_Array) / sizeof(struct ForestSetMember_Tag); i++)
	{
		Forest_Make_Set(ForestSetMember_Array + i);
	}
	for (int i = 1; i < 4; i++) //Link to ForestSetMember_Array[0]
	{
		Forest_Union(ForestSetMember_Array + i, ForestSetMember_Array);
	}
	for (int i = 5; i < 7; i++) //Link to ForestSetMember_Array[0]
	{
		Forest_Union(ForestSetMember_Array + i, ForestSetMember_Array + 4);
	
		printf("%d\n", (ForestSetMember_Array + i)->Key);
		printf("%d\n", (ForestSetMember_Array + i)->Node_Pointer->Parent->ForestSetMember->Key);
	}
#endif

	


#if BFS_MODULE==1
	CreateGraph(&Graph_Object);

	int Number_of_Vertices = 9;
	struct ObjectWithVertex_Tag* Temp_Pointer;
	for (int i = 0; i < Number_of_Vertices; i++)
	{
		Temp_Pointer = Graph_Object.AdjacencyList_Pointer[i].head;


		printf("AdjacencyList[%d] : ",i);
		while (Temp_Pointer != NULL)
		{
			printf("%d ", Temp_Pointer->Vertex_Pointer->Key);

			Temp_Pointer = Temp_Pointer->Next;
		}
		printf("\n");
	}

	BFS(&Graph_Object, Graph_Object.Vertex_Pointer);

	for (int i = 0; i < Number_of_Vertices; i++)
	{
		printf("Distance of Vertex[%d]=%d\n", Graph_Object.Vertex_Pointer[i].Key, Graph_Object.Vertex_Pointer[i].Distance);
	}

	printf("Path from vertex[%d] to vertex[%d]: ", Graph_Object.Vertex_Pointer->Key, (Graph_Object.Vertex_Pointer+4)->Key);
	Print_Path(Graph_Object.Vertex_Pointer, Graph_Object.Vertex_Pointer+4);
#endif




#if DFS_MODULE==1
	DFS_CreateGraph(&DFS_Graph_Object);

	int Number_of_Vertices = 6;
	struct ObjectWithVertex_Tag* Temp_Pointer;
	for (int i = 0; i < Number_of_Vertices; i++)
	{
		Temp_Pointer = DFS_Graph_Object.AdjacencyList_Pointer[i].head;


		printf("AdjacencyList[%d] : ", i);
		while (Temp_Pointer != NULL)
		{
			printf("%d ", Temp_Pointer->Vertex_Pointer->Key);

			Temp_Pointer = Temp_Pointer->Next;
		}
		printf("\n");
	}

	DFS(&DFS_Graph_Object, DFS_Graph_Object.Vertex_Pointer);
	for (int i = 0; i < Number_of_Vertices; i++)
	{
		printf("Vertex[%d]=%d(Discovery Time)  %d(Finish Time)\n", DFS_Graph_Object.Vertex_Pointer[i].Key, DFS_Graph_Object.Vertex_Pointer[i].DiscoveryTime, DFS_Graph_Object.Vertex_Pointer[i].FinishTime);
	}
#endif
	



#if TOPOLOGICAL_SORT_MODULE==1
	TopologicalSort_CreateGraph(&DFS_Graph_Object);

	int Number_of_Vertices = 5;
	struct ObjectWithVertex_Tag* Temp_Pointer;
	for (int i = 0; i < Number_of_Vertices; i++)
	{
		Temp_Pointer = DFS_Graph_Object.AdjacencyList_Pointer[i].head;


		printf("AdjacencyList[%d] : ", i);
		while (Temp_Pointer != NULL)
		{
			printf("%d ", Temp_Pointer->Vertex_Pointer->Key);

			Temp_Pointer = Temp_Pointer->Next;
		}
		printf("\n");
	}


	struct ObjectWithVertex_Tag* DFS_ObjectWithVertex_Pointer= Topological_Sort(&DFS_Graph_Object)->head;
	
	printf("Topology Sort Order: ");
	while (DFS_ObjectWithVertex_Pointer != NULL)
	{
		printf("%d ", DFS_ObjectWithVertex_Pointer->Vertex_Pointer->Key);
		DFS_ObjectWithVertex_Pointer = DFS_ObjectWithVertex_Pointer->Next;
	}
#endif




#if STRONGLY_CONNECTED_COMPONENT_MODULE==1
	DFS_CreateGraph(&DFS_Graph_Object);
	int Number_of_Vertices = 6;
	struct ObjectWithVertex_Tag* Temp_Pointer;
	for (int i = 0; i < Number_of_Vertices; i++)
	{
		Temp_Pointer = DFS_Graph_Object.AdjacencyList_Pointer[i].head;


		printf("AdjacencyList[%d] : ", i);
		while (Temp_Pointer != NULL)
		{
			printf("%d ", Temp_Pointer->Vertex_Pointer->Key);

			Temp_Pointer = Temp_Pointer->Next;
		}
		printf("\n");
	}

	printf("\n");


	struct ComponentCollection_Tag* ComponentCollection_Pointer = CreateStronglyConnectedComponent(&DFS_Graph_Object);

	struct ComponentCarrier_Tag* ComponentCarrier_pointer = ComponentCollection_Pointer->head;
	int i = 0;
	printf("There are %d components\n", ComponentCollection_Pointer->ComponentCounter);
	while (ComponentCarrier_pointer != NULL)
	{
		printf("ComponentID[%d], the number of vertex is %d: ", i, ComponentCarrier_pointer->StronglyConnectedComponent_Pointer->VertexCounter);
		i++;
		struct VertexCarrier_Tag* VertexCarrier_Pointer = ComponentCarrier_pointer->StronglyConnectedComponent_Pointer->head;
		while (VertexCarrier_Pointer != NULL)
		{
			printf("%d ", VertexCarrier_Pointer->Vertex_Pointer->Key);

			VertexCarrier_Pointer = VertexCarrier_Pointer->Next;
		}
		printf("\n");

		ComponentCarrier_pointer = ComponentCarrier_pointer->Next;
	}
#endif




#if MINIMUM_SPANNING_TREE_KRUSKAL_MODULE==1
	MiniSpanTree_CreateGraph(&MST_Graph_Object);

	for (int i = 0; i < MST_Graph_Object.Number_of_Vertex; i++)
	{
		printf("Adjacency[%d]:\n",i);
		
		struct ObjectWithVertex_Tag* Next = (MST_Graph_Object.AdjacencyList_Pointer + i)->head;
		while (Next!=NULL)
		{
			printf("Weight of Vertex[%d]=%d\n", Next->Vertex_Pointer->Key, Next->EdgeWeight);

			Next = Next->Next;
		}

		printf("\n");
	}
	
	MiniSpanTree_Kruskal(&MST_Graph_Object);
#endif




#if MINIMUM_SPANNING_TREE_PRIM_MODULE==1
	MiniSpanTree_CreateGraph(&MST_Graph_Object);

	MiniSpanTree_Prim(&MST_Graph_Object, MST_Graph_Object.Vertex_Pointer);

	for (int i = 1; i < MST_Graph_Object.Number_of_Vertex; i++)
	{
		printf("Parent of Vertex[%d]=%d\n", MST_Graph_Object.Vertex_Pointer[i].Key, MST_Graph_Object.Vertex_Pointer[i].Parent->Key);
		printf("Weight of Vertex[%d]=%d\n", MST_Graph_Object.Vertex_Pointer[i].Key, MST_Graph_Object.Vertex_Pointer[i].EdgeWeight);

		printf("\n");
	}
#endif




#if BELLMAN_FORD_MODULE==1
	BellmanFord_CreateGraph(&BellmanFord_Graph_Object);

	for (int i = 0; i < BellmanFord_Graph_Object.Number_of_Vertex; i++)
	{
		printf("Adjacency[%d]:\n", i);

		struct ObjectWithVertex_Tag* Next = (BellmanFord_Graph_Object.AdjacencyList_Pointer + i)->head;
		while (Next != NULL)
		{
			printf("Weight of Vertex[%d]=%d\n", Next->Vertex_Pointer->Key, Next->EdgeWeight);

			Next = Next->Next;
		}

		printf("\n");
	}

	int Non_Negative_Cycle_Flag=Bellman_Ford(&BellmanFord_Graph_Object, BellmanFord_Graph_Object.Vertex_Pointer + 4);


	for (int i = 0; i < BellmanFord_Graph_Object.Number_of_Vertex; i++)
	{
		printf("Distance of Vertex[%d]=%d\n", i, (BellmanFord_Graph_Object.Vertex_Pointer+i)->Distance);

		if ((BellmanFord_Graph_Object.Vertex_Pointer + i)->Parent != NULL)
		{
			printf("Parent of Vertex[%d]=%d\n\n", i, (BellmanFord_Graph_Object.Vertex_Pointer + i)->Parent->Key);
		}		
	}

	printf("\nNon_Negative_Cycle_Flag=%d\n", Non_Negative_Cycle_Flag);
#endif




#if SHORTEST_PATH_FASTER_ALGORITHM_MODULE==1
	BellmanFord_CreateGraph(&BellmanFord_Graph_Object);

	for (int i = 0; i < BellmanFord_Graph_Object.Number_of_Vertex; i++)
	{
		printf("Adjacency[%d]:\n", i);

		struct ObjectWithVertex_Tag* Next = (BellmanFord_Graph_Object.AdjacencyList_Pointer + i)->head;
		while (Next != NULL)
		{
			printf("Weight of Vertex[%d]=%d\n", Next->Vertex_Pointer->Key, Next->EdgeWeight);

			Next = Next->Next;
		}

		printf("\n");
	}

	int Non_Negative_Cycle_Flag = ShortestPathFasterAlgorithm(&BellmanFord_Graph_Object, BellmanFord_Graph_Object.Vertex_Pointer + 4);


	for (int i = 0; i < BellmanFord_Graph_Object.Number_of_Vertex; i++)
	{
		printf("Distance of Vertex[%d]=%d\n", i, (BellmanFord_Graph_Object.Vertex_Pointer + i)->Distance);

		if ((BellmanFord_Graph_Object.Vertex_Pointer + i)->Parent != NULL)
		{
			printf("Parent of Vertex[%d]=%d\n\n", i, (BellmanFord_Graph_Object.Vertex_Pointer + i)->Parent->Key);
		}
	}

	printf("\nNon_Negative_Cycle_Flag=%d\n", Non_Negative_Cycle_Flag);
#endif




#if SINGLE_SOURCE_SHORTEST_PATH_IN_DAG_MODULE==1
	DAG_ShortestPath_CreateGraph(&DAG_ShortestPath_Graph_Object);

	for (int i = 0; i < DAG_ShortestPath_Graph_Object.Number_of_Vertex; i++)
	{
		printf("AdjacencyList[%d]:\n", i);

		struct ObjectWithVertex_Tag* Next = (DAG_ShortestPath_Graph_Object.AdjacencyList_Pointer + i)->head;
		while (Next != NULL)
		{
			printf("Weight of Vertex[%d]=%d\n", Next->Vertex_Pointer->Key, Next->EdgeWeight);

			Next = Next->Next;
		}
		printf("\n");
	}

	DAG_Shortest_Path(&DAG_ShortestPath_Graph_Object, DAG_ShortestPath_Graph_Object.Vertex_Pointer+1);

	for (int i = 0; i < DAG_ShortestPath_Graph_Object.Number_of_Vertex; i++)
	{
		if ((DAG_ShortestPath_Graph_Object.Vertex_Pointer + i)->Distance < INT_MAX)
		{
			printf("Distance of Vertex[%d]=%d\n", i, (DAG_ShortestPath_Graph_Object.Vertex_Pointer + i)->Distance);
		}
		else
		{
			printf("Can't reach Vertex[%d]\n", i);
		}

		if ((DAG_ShortestPath_Graph_Object.Vertex_Pointer + i)->Parent != NULL)
		{
			printf("Parent of Vertex[%d]=%d\n", i, (DAG_ShortestPath_Graph_Object.Vertex_Pointer + i)->Parent->Key);
		}
		else
		{
			printf("Vertex[%d] has no parent\n", i);
		}

		printf("\n");
	}
#endif




#if DIJKSTRA_SHORTEST_PATH_MODULE==1
	Dijkstra_CreateGraph(&Dijkstra_Graph_Object);


	for (int i = 0; i < Dijkstra_Graph_Object.Number_of_Vertex; i++)
	{
		printf("AdjacencyList[%d]:\n", i);

		struct ObjectWithVertex_Tag* Next = (Dijkstra_Graph_Object.AdjacencyList_Pointer + i)->head;
		while (Next != NULL)
		{
			printf("Weight of Vertex[%d]=%d\n", Next->Vertex_Pointer->Key, Next->EdgeWeight);

			Next = Next->Next;
		}

		printf("\n");
	}



	Dijkstra(&Dijkstra_Graph_Object, Dijkstra_Graph_Object.Vertex_Pointer+4);


	for (int i = 0; i < Dijkstra_Graph_Object.Number_of_Vertex; i++)
	{
		printf("Distance of Vertex[%d]=%d\n", i, (Dijkstra_Graph_Object.Vertex_Pointer + i)->Distance);

		if ((Dijkstra_Graph_Object.Vertex_Pointer + i)->Parent != NULL)
		{
			printf("Parent of Vertex[%d]=%d\n\n", i, (Dijkstra_Graph_Object.Vertex_Pointer + i)->Parent->Key);
		}
		else 
		{
			printf("Vertex[%d] has no parent\n", i);
		}
	}
#endif




#if A_STAR_SHORTEST_PATH_MODULE==1
	A_Star_CreateGraph(&A_Star_Graph_Object);

	for (int i = 0; i < A_Star_Graph_Object.Number_of_Vertex; i++)
	{
		printf("AdjacencyList[%d]:\n", i);

		struct ObjectWithVertex_Tag* Next = (A_Star_Graph_Object.AdjacencyList_Pointer + i)->head;
		while (Next != NULL)
		{
			printf("Weight of Vertex[%d]=%d\n", Next->Vertex_Pointer->Key, Next->EdgeWeight);

			Next = Next->Next;
		}

		printf("\n");
	}


	A_Star(&A_Star_Graph_Object, A_Star_Graph_Object.Vertex_Pointer + 4, A_Star_Graph_Object.Vertex_Pointer + 0);


	int i = 0;
	printf("Distance of Vertex[%d]=%d\n", i, (A_Star_Graph_Object.Vertex_Pointer + i)->Distance);

	if ((A_Star_Graph_Object.Vertex_Pointer + i)->Parent != NULL)
	{
		printf("Parent of Vertex[%d]=%d\n\n", i, (A_Star_Graph_Object.Vertex_Pointer + i)->Parent->Key);
	}
#endif




#if FASTER_ALL_PAIRS_SHORTEST_PATHS_MODULE==1
	FasterAPSP_CreateGraph(&FasterAPSP_Graph_Object);
	

	printf("Adjacency Matrix :\n");
	for (int i = 0; i < FasterAPSP_Graph_Object.Number_of_Vertex; i++)
	{
		for (int j = 0; j < FasterAPSP_Graph_Object.Number_of_Vertex; j++)
		{
			
			if (*(FasterAPSP_Graph_Object.AdjacencyMatrix_Pointer + i * FasterAPSP_Graph_Object.Number_of_Vertex + j) != INT_MAX)
			{
				printf("%d     ", *(FasterAPSP_Graph_Object.AdjacencyMatrix_Pointer + i * FasterAPSP_Graph_Object.Number_of_Vertex + j));

			}
			else
			{
				printf("Inf   ");

			}

		}

		printf("\n");
	}

	Faster_APSP(&FasterAPSP_Graph_Object);

	printf("\n\n");


	printf("Weights of all pairs shortest paths :\n");
	for (int i = 0; i < FasterAPSP_Graph_Object.Number_of_Vertex; i++)
	{
		for (int j = 0; j < FasterAPSP_Graph_Object.Number_of_Vertex; j++)
		{

			if (*(FasterAPSP_Graph_Object.AllPairShortestPath_Result.ShortestWeightMatrix_Pointer + i * FasterAPSP_Graph_Object.Number_of_Vertex + j) != INT_MAX)
			{
				printf("%d     ", *(FasterAPSP_Graph_Object.AllPairShortestPath_Result.ShortestWeightMatrix_Pointer + i * FasterAPSP_Graph_Object.Number_of_Vertex + j));
			}
			else
			{
				printf("Inf   ");

			}


		}

		printf("\n");
	}

	printf("\n");



	printf("Predecessor Matrix :\n(0)   (1)   (2)   (3)   (4)     <------Destination Vertex Index\n");
	for (int i = 0; i < FasterAPSP_Graph_Object.Number_of_Vertex; i++)
	{
		for (int j = 0; j < FasterAPSP_Graph_Object.Number_of_Vertex; j++)
		{


			if (*(FasterAPSP_Graph_Object.AllPairShortestPath_Result.PredecessorMatrix_Pointer + i * FasterAPSP_Graph_Object.Number_of_Vertex + j) != INT_MAX)
			{
				printf("%d     ", *(FasterAPSP_Graph_Object.AllPairShortestPath_Result.PredecessorMatrix_Pointer + i * FasterAPSP_Graph_Object.Number_of_Vertex + j));
			}
			else
			{
				printf("Inf   ");

			}


		}

		printf("\n");
	}
#endif




#if FLOYD_WARSHALL_ALL_PAIRS_SHORTEST_PATHS_MODULE==1
	FasterAPSP_CreateGraph(&FasterAPSP_Graph_Object);


	printf("Adjacency Matrix :\n");
	for (int i = 0; i < FasterAPSP_Graph_Object.Number_of_Vertex; i++)
	{
		for (int j = 0; j < FasterAPSP_Graph_Object.Number_of_Vertex; j++)
		{

			if (*(FasterAPSP_Graph_Object.AdjacencyMatrix_Pointer + i * FasterAPSP_Graph_Object.Number_of_Vertex + j) != INT_MAX)
			{
				printf("%d     ", *(FasterAPSP_Graph_Object.AdjacencyMatrix_Pointer + i * FasterAPSP_Graph_Object.Number_of_Vertex + j));
	
			}
			else
			{
				printf("Inf   ");

			}

		}

		printf("\n");
	}

	Floyd_Warshall(&FasterAPSP_Graph_Object);

	printf("\n\n");
	

	printf("Weights of all pairs shortest paths :\n");
	for (int i = 0; i < FasterAPSP_Graph_Object.Number_of_Vertex; i++)
	{
		for (int j = 0; j < FasterAPSP_Graph_Object.Number_of_Vertex; j++)
		{

			if (*(FasterAPSP_Graph_Object.AllPairShortestPath_Result.ShortestWeightMatrix_Pointer + i * FasterAPSP_Graph_Object.Number_of_Vertex + j) != INT_MAX)
			{
				printf("%d     ", *(FasterAPSP_Graph_Object.AllPairShortestPath_Result.ShortestWeightMatrix_Pointer + i * FasterAPSP_Graph_Object.Number_of_Vertex + j));
			}
			else
			{
				printf("Inf   ");

			}


		}

		printf("\n");
	}

	printf("\n");



	printf("Predecessor Matrix :\n(0)   (1)   (2)   (3)   (4)     <------Destination Vertex Index\n");
	for (int i = 0; i < FasterAPSP_Graph_Object.Number_of_Vertex; i++)
	{
		for (int j = 0; j < FasterAPSP_Graph_Object.Number_of_Vertex; j++)
		{


			if (*(FasterAPSP_Graph_Object.AllPairShortestPath_Result.PredecessorMatrix_Pointer + i * FasterAPSP_Graph_Object.Number_of_Vertex + j) != INT_MAX)
			{
				printf("%d     ", *(FasterAPSP_Graph_Object.AllPairShortestPath_Result.PredecessorMatrix_Pointer + i * FasterAPSP_Graph_Object.Number_of_Vertex + j));
			}
			else
			{
				printf("Inf   ");

			}


		}

		printf("\n");
	}
#endif




#if JOHNSON_ALL_PAIRS_SHORTEST_PATHS_MODULE==1
	Johnson_CreateGraph(&Johnson_Graph_Object);
	
	for (int i = 0; i < Johnson_Graph_Object.Number_of_Vertex; i++)
	{
		printf("Adjacency[%d]:\n", i);

		struct ObjectWithVertex_Tag* Next = (Johnson_Graph_Object.AdjacencyList_Pointer + i)->head;
		while (Next != NULL)
		{
			printf("Weight of Vertex[%d]=%d\n", Next->Vertex_Pointer->Key, Next->EdgeWeight);

			Next = Next->Next;
		}

		printf("\n");
	}
	

	Johnson(&Johnson_Graph_Object);



	printf("\n");
	printf("Weights of all pairs shortest paths :\n");
	for (int i = 0; i < Johnson_Graph_Object.Number_of_Vertex; i++)
	{
		for (int j = 0; j < Johnson_Graph_Object.Number_of_Vertex; j++)
		{

			if (*(Johnson_Graph_Object.AllPairShortestPath_Result.ShortestWeightMatrix_Pointer + i * Johnson_Graph_Object.Number_of_Vertex + j) != INT_MAX)
			{
				printf("%d     ", *(Johnson_Graph_Object.AllPairShortestPath_Result.ShortestWeightMatrix_Pointer + i * Johnson_Graph_Object.Number_of_Vertex + j));
			}
			else
			{
				printf("Inf   ");

			}


		}

		printf("\n");
	}

	printf("\n");



	printf("Predecessor Matrix :\n(0)   (1)   (2)   (3)   (4)     <------Destination Vertex Index\n");
	for (int i = 0; i < Johnson_Graph_Object.Number_of_Vertex; i++)
	{
		for (int j = 0; j < Johnson_Graph_Object.Number_of_Vertex; j++)
		{


			if (*(Johnson_Graph_Object.AllPairShortestPath_Result.PredecessorMatrix_Pointer + i * Johnson_Graph_Object.Number_of_Vertex + j) != INT_MAX)
			{
				printf("%d     ", *(Johnson_Graph_Object.AllPairShortestPath_Result.PredecessorMatrix_Pointer + i * Johnson_Graph_Object.Number_of_Vertex + j));
			}
			else
			{
				printf("Inf   ");

			}


		}

		printf("\n");
	}

	

	printf("\n\nRecovere the edge weight of graph :\n");
	for (int i = 0; i < Johnson_Graph_Object.Number_of_Vertex; i++)
	{
		printf("Adjacency[%d]:\n", i);

		struct ObjectWithVertex_Tag* Next = (Johnson_Graph_Object.AdjacencyList_Pointer + i)->head;
		while (Next != NULL)
		{
			printf("Weight of Vertex[%d]=%d\n", Next->Vertex_Pointer->Key, Next->EdgeWeight);

			Next = Next->Next;
		}

		printf("\n");
	}
#endif




#if EDMONDS_KARP_MAXIMUM_FLOW_MODULE==1
	EdmondsKarp_CreateGraph(&EdmondsKarp_Graph_Object);

	printf("\n\n");
	for (int i = 0; i < EdmondsKarp_Graph_Object.Number_of_Vertex; i++)
	{
		printf("Adjacency[%d]:\n", i);

		struct ObjectWithVertex_Tag* Next = (EdmondsKarp_Graph_Object.AdjacencyList_Pointer + i)->head;
		while (Next != NULL)
		{
			printf("Capacity of Vertex[%d]=%d\n", Next->Vertex_Pointer->Key, Next->EdgeCapacity);

			Next = Next->Next;
		}

		printf("\n");
	}


	EdmondsKarp(&EdmondsKarp_Graph_Object, EdmondsKarp_Graph_Object.Vertex_Pointer, EdmondsKarp_Graph_Object.Vertex_Pointer+5);

	for (int i = 0; i < EdmondsKarp_Graph_Object.Number_of_Vertex; i++)
	{
		struct ObjectWithVertex_Tag* Edge_Pointer = EdmondsKarp_Graph_Object.AdjacencyList_Pointer[i].head;
		while(Edge_Pointer!=NULL)
		{
			printf("Flow(u[%d],v[%d] ) = %d\n", i, Edge_Pointer->Vertex_Pointer->Key, Edge_Pointer->EdgeFlow);
			Edge_Pointer = Edge_Pointer->Next;
		}
	}
#endif




#if HOPCROFT_KARP_MAXIMUM_BIPARTITE_MODULE==1
	HopcroftKarp_CreateGraph(&HopcroftKarp_Graph_Object);


	for (int i = 0; i < HopcroftKarp_Graph_Object.Number_of_Vertex; i++)
	{
		printf("AdjacencyList[%d]: ", i);

		struct ObjectWithVertex_Tag* Next = (HopcroftKarp_Graph_Object.AdjacencyList_Pointer + i)->head;
		while (Next != NULL)
		{
			printf("%d( AntiID=%d )  ", Next->Vertex_Pointer->Key, Next->AntiEdge_Pointer->Vertex_Pointer->Key);

			Next = Next->Next;
		}

		printf("\n");
	}


	printf("/*******************LeftBipartite**************************\n");
	
	struct VertexCarrier_Tag* Next = HopcroftKarp_Graph_Object.Bipartite.BipartiteLeft_Unmatch_Pointer->head;
	while (Next != NULL)
	{
		struct ObjectWithVertex_Tag* Next2 = (HopcroftKarp_Graph_Object.AdjacencyList_Pointer + Next->Vertex_Pointer->Key)->head;
		printf("Vertex[%d]: ", Next->Vertex_Pointer->Key);
		while (Next2 != NULL)
		{
			printf("Edge[%d] ", Next2->Vertex_Pointer->Key);

			Next2 = Next2->Next;
		}

		printf("\n");

		Next = Next->Next;
	}
	printf("\n");
	


	printf("/*******************RightBipartite**************************\n");
	Next = HopcroftKarp_Graph_Object.Bipartite.BipartiteRight_Unmatch_Pointer->head;
	while (Next != NULL)
	{
		printf("Vertex[%d]: ", Next->Vertex_Pointer->Key);
		struct ObjectWithVertex_Tag* Next2 = (HopcroftKarp_Graph_Object.AdjacencyList_Pointer + Next->Vertex_Pointer->Key)->head;
		while (Next2 != NULL)
		{
			printf("Edge[%d] ", Next2->Vertex_Pointer->Key);

			Next2 = Next2->Next;
		}

		printf("\n");

		Next = Next->Next;
	}
	printf("\n");



	HopcroftKarp(&HopcroftKarp_Graph_Object);
	
	struct VertexCarrier_Tag* VertexCarrierRight = HopcroftKarp_Graph_Object.Bipartite.BipartiteRight_Match_Pointer->head;
	while (VertexCarrierRight != NULL)
	{
		printf("Matching Result:( %d , %d )\n", VertexCarrierRight->Vertex_Pointer->MatchingVertex_Pointer->Key, VertexCarrierRight->Vertex_Pointer->Key);
		VertexCarrierRight = VertexCarrierRight->Next;
	}
#endif




#if GALE_SHAPLEY_STABLE_MATCHING_MODULE==1	
	GaleShapley_CreateGraph(&GaleShapley_Graph_Object);
	GaleShapley(&GaleShapley_Graph_Object);

	struct VertexCarrier_Tag* Next = GaleShapley_Graph_Object.Bipartite.BipartiteLeft_Match_Pointer->head;

	while (Next != NULL)
	{
		printf("( %d ", Next->Vertex_Pointer->Key);
		if (Next->Vertex_Pointer->MatchingVertex_Pointer != NULL)
		{
			printf(", %d )", Next->Vertex_Pointer->MatchingVertex_Pointer->Key);
		}
		else
		{
			printf(" )");
		}

		Next = Next->Next;
	}

	printf("\n\n");
	Next = GaleShapley_Graph_Object.Bipartite.BipartiteRight_Match_Pointer->head;

	while (Next != NULL)
	{
		printf("( %d ", Next->Vertex_Pointer->Key);
		if (Next->Vertex_Pointer->MatchingVertex_Pointer != NULL)
		{
			printf(", %d )", Next->Vertex_Pointer->MatchingVertex_Pointer->Key);
		}
		else
		{
			printf(" )");
		}

		Next = Next->Next;
	}

	printf("\n\n");
	Next = GaleShapley_Graph_Object.Bipartite.BipartiteLeft_Unmatch_Pointer->head;

	while (Next != NULL)
	{
		printf("( %d ", Next->Vertex_Pointer->Key);
		if (Next->Vertex_Pointer->MatchingVertex_Pointer != NULL)
		{
			printf(", %d )", Next->Vertex_Pointer->MatchingVertex_Pointer->Key);
		}
		else
		{
			printf(" )");
		}

		Next = Next->Next;
	}


	printf("\n\n");
	Next = GaleShapley_Graph_Object.Bipartite.BipartiteRight_Unmatch_Pointer->head;

	while (Next != NULL)
	{
		printf("( %d ", Next->Vertex_Pointer->Key);
		if (Next->Vertex_Pointer->MatchingVertex_Pointer != NULL)
		{
			printf(", %d )", Next->Vertex_Pointer->MatchingVertex_Pointer->Key);
		}
		else
		{
			printf(" )");
		}

		Next = Next->Next;
	}
	printf("\n\n\n\n");


	//Free all allocated memory
	Release_Bipartite(&GaleShapley_Graph_Object.Bipartite);

	FreeGraphRepresent(&GaleShapley_Graph_Object);

	Release_PreferenceLists(&GaleShapley_Graph_Object);
#endif




#if HUNGARIAN_MAXIMUM_WEIGHT_MODULE==1
	Hungarian_CreateGraph(&Hungarian_Graph_Object);


	//Assign the number of vertex in left/right part of bipartite graph.
	int Number_of_Vertex = Hungarian_Graph_Object.Number_of_Vertex / 2;



	//Print Adjacency Matrix.
	printf("Weight Matrix: \n");
	for (int i = 0; i < Number_of_Vertex; i++)
	{
		for (int j = 0; j < Number_of_Vertex; j++)
		{
			printf("%d ", *(Hungarian_Graph_Object.AdjacencyMatrix_Pointer + i * Number_of_Vertex + j));

		}
		printf("\n");
	}

	printf("\n\n");


	Hungarian(&Hungarian_Graph_Object);

	printf("\n\n");
	struct VertexCarrier_Tag* Next = Hungarian_Graph_Object.Bipartite.BipartiteRight_Match_Pointer->head;
	printf("BipartiteRight_Match_Pointer( LeftVertexKey , RightVertexIndexKey ) :\n");
	int SumWeight = 0;
	while (Next != NULL)
	{
		printf("( %d , %d )\n", Next->Vertex_Pointer->MatchingVertex_Pointer->Key, Next->Vertex_Pointer->Key);

		int i = Next->Vertex_Pointer->MatchingVertex_Pointer->Key;
		int j = Next->Vertex_Pointer->Key - Number_of_Vertex;
		SumWeight = SumWeight + (*(Hungarian_Graph_Object.AdjacencyMatrix_Pointer + i * Number_of_Vertex + j));
		Next = Next->Next;
	}
	printf("\n\n");
	printf("Matching Sum : %d\n", SumWeight);


	Release_Bipartite(&Hungarian_Graph_Object.Bipartite);

	FreeGraphMatrixRepresent(&GaleShapley_Graph_Object);
#endif




#if ROBIN_KARP_STRING_MATCHING_MODULE==1
	Rabin_Karp_Matcher(&Text_Object, &Pattern_Object);
#endif




#if FINITE_AUTOMA_STRING_MATCHING_MODULE==1
	Finite_Automaton_Matcher(&Text_Object2, &Pattern_Object2, &Alphabet_Object);
#endif




#if KMP_STRING_MATCHING_MODULE==1
	KMP_Matcher(&Text_Object, &Pattern_Object);
#endif




#if LONGEST_COMMON_PREFIX_WITH_SUFFIX_ARRAY_MODULE==1
	int* Suffix_Array = Compute_Suffix_Array(&Text_Object3);

	for (int i = 0; i < Text_Object3.Length; i++)
	{
		printf("SA[%d]=%d\n", i, Suffix_Array[i]); //go through each element of suffix array.
	}


	int* LCP_Array = Compute_LCP_Array(&Text_Object3, Suffix_Array);


	for (int i = 0; i < Text_Object3.Length; i++)
	{
		printf("LCP_Array[%d]=%d\n", i, LCP_Array[i]);

	}

	free(LCP_Array);
	free(Suffix_Array);
#endif




#if TEXT_PATTERN_MATCHING_WITH_DC3_SKEWALGORITHM_MODULE==1
	int* Suffix_Array = (int*)malloc(Text_Object4.Length * sizeof(int));
	DC3_Suffix_Array(&Text_Object4, Suffix_Array, 256);
	
	for (int i = 0; i < Text_Object4.Length; i++)
	{
		printf("Suffix_Array[%d]=%d\n", i, Suffix_Array[i]);
	}

	printf("\n");

	DC3_Suffix_Array_Matcher(&Text_Object4, Suffix_Array, &Pattern_Object4);

	free(Suffix_Array);
#endif




#if SEARCH_LASTMATCHEDNODE_IN_TRIE_MODULE==1
	//Insert the strings into Trie.
	int Number_of_String = sizeof(StringContent) / sizeof(StringContent[0]);
	for (int i = 0; i < Number_of_String; i++)
	{
		TrieNode_Insertion(&Trie_Object, StringContent[i]);
	}


	//Check the first unmatched character index of strings in Trie.
	printf("Trie Layout :\n");

	int Record_FirstUnmatchedCharacter_Index;
	for (int i = 0; i < Number_of_String; i++)
	{
		struct TrieNode_Tag* LastMatchedNode_Pointer = TrieNode_SearchLastMatchedNode(&Trie_Object, StringContent[i], &Record_FirstUnmatchedCharacter_Index);
		printf("Unmatch character index in the String( -1 means the whole string is matched ) : %d\n", Record_FirstUnmatchedCharacter_Index); //-1 means the whole string is matched, otherwise it means the index of first unmatched character in the string.
	}


	//Delete the string in the trie, and show the result.
	int Flag = TrieNode_Delete(&Trie_Object, "abc");
	 Flag = TrieNode_Delete(&Trie_Object, StringContent[1]);


	printf("\nTrie Layout( Deletion ) :\n");
	for (int i = 0; i < Number_of_String; i++)
	{
		struct TrieNode_Tag* LastMatchedNode_Pointer = TrieNode_SearchLastMatchedNode(&Trie_Object, StringContent[i], &Record_FirstUnmatchedCharacter_Index);
		printf("Unmatch character index in the String( -1 means the whole string is matched ) : %d\n", Record_FirstUnmatchedCharacter_Index); //-1 means the whole string is matched, otherwise it means the index of first unmatched character in the string.
	}
#endif

}