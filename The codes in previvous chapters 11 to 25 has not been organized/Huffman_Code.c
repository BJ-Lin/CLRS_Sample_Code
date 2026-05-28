#include "..\Header.h"





//Ref:Data from textbook(introduction to algorithm),4th,P433
struct CharacterObject_Tag CharacterObject_Table[6] = { {.Frequency = 45,.Word = 'a'},{.Frequency = 13,.Word = 'b'},{.Frequency = 12,.Word = 'c'},{.Frequency = 16,.Word = 'd'},{.Frequency = 9,.Word = 'e'},{.Frequency = 5,.Word = 'f'} };


void Hoffman_Queue_Min_Heapify(struct CharacterObject_Tag* PointerArray[], size_t Queue_Size, unsigned Root_Index)
{
	unsigned Min_Index = 0;
	unsigned Left_Child_Index = 2 * Root_Index;
	unsigned Right_Child_Index = 2 * Root_Index + 1;

	if (Left_Child_Index <= Queue_Size && PointerArray[Left_Child_Index - 1]->Frequency < PointerArray[Root_Index - 1]->Frequency)
	{
		Min_Index = Left_Child_Index;
	}

	else
	{
		Min_Index = Root_Index;
	}

	if (Right_Child_Index <= Queue_Size && PointerArray[Right_Child_Index - 1]->Frequency < PointerArray[Min_Index - 1]->Frequency)
	{
		Min_Index = Right_Child_Index;
	}


	if (Min_Index != Root_Index)
	{
		//Exchange values of array.
		struct CharacterObject_Tag* Temp = PointerArray[Root_Index - 1];
		PointerArray[Root_Index - 1] = PointerArray[Min_Index - 1];
		PointerArray[Min_Index - 1] = Temp;

		//Update indices of PointerArray.
		(*PointerArray[Root_Index - 1]).Index = Root_Index;
		(*PointerArray[Min_Index - 1]).Index = Min_Index;


		Hoffman_Queue_Min_Heapify(PointerArray, Queue_Size, Min_Index);
	}

}

void Hoffman_Queue_Build_Min_Heap(struct CharacterObject_Tag* PointerArray[], size_t Queue_Size)
{
	for (unsigned int i = Queue_Size / 2; i >= 1; i--)
	{
		Hoffman_Queue_Min_Heapify(PointerArray, Queue_Size, i);
	}

}



signed char Hoffman_Queue_Min_Heap_Minimum(struct CharacterObject_Tag* PointerArray[], size_t Queue_Size, struct CharacterObject_Tag** MaximumAddress_Pointer)
{
	if (Queue_Size < 1)
	{
		return -1;
	}

	*MaximumAddress_Pointer = PointerArray[0];

	return 0;

}

struct CharacterObject_Tag* Hoffman_Queue_Min_Heap_Extract_Minimum(struct CharacterObject_Tag* PointerArray[], int* QueueSize_Pointer)
{
	struct CharacterObject_Tag* Temp;
	Hoffman_Queue_Min_Heap_Minimum(PointerArray, *QueueSize_Pointer, &Temp); // Reserve maximum value of heap 
	PointerArray[0] = PointerArray[*QueueSize_Pointer - 1]; //Cover the maximum by using leaf( ~ Delete maximun) 

	(*PointerArray[0]).Index = 1;



	*QueueSize_Pointer = *QueueSize_Pointer - 1;
	Hoffman_Queue_Min_Heapify(PointerArray, *QueueSize_Pointer, 1);


	return Temp;
}

signed Hoffman_Queue_Min_Heap_Increase_Key(struct CharacterObject_Tag* PointerArray[], struct CharacterObject_Tag* Object_Pointer, signed New_Key)
{
	if (New_Key < (*Object_Pointer).Frequency)
	{
		return 0;

	}

	(*Object_Pointer).Frequency = New_Key;


	size_t i = (*Object_Pointer).Index;

	while (i > 1 && (*PointerArray[i / 2 - 1]).Frequency > (*PointerArray[i - 1]).Frequency)
	{

		//Exchange pointer values of array
		struct CharacterObject_Tag* Temp = PointerArray[i / 2 - 1];
		PointerArray[i / 2 - 1] = PointerArray[i - 1];
		PointerArray[i - 1] = Temp;

		//Update index 
		(*PointerArray[i / 2 - 1]).Index = i / 2;
		(*PointerArray[i - 1]).Index = i;


		//Assign new i
		i = i / 2;


	}

	return 1;

}


signed Hoffman_Queue_Min_Heap_Insert(struct CharacterObject_Tag* PointerArray[], int* QueueSize_Pointer, struct CharacterObject_Tag* Object_Pointer, size_t Array_Size)
{
	//Step1. Judge the error cases
	if (*QueueSize_Pointer >= Array_Size)
	{

		return 0;

	}

	//Step2. Plug the new object in the queue
	*QueueSize_Pointer = *QueueSize_Pointer + 1;
	PointerArray[*QueueSize_Pointer - 1] = Object_Pointer;

	(*PointerArray[*QueueSize_Pointer - 1]).Index = *QueueSize_Pointer;


	//Step3. Reserve the KEY and modify the KEY to minus infinity for using Heap_Increase_Key function
	int K = (*PointerArray[*QueueSize_Pointer - 1]).Frequency;
	(*PointerArray[*QueueSize_Pointer - 1]).Frequency = -1;



	//Step4. Plug the new object in the queue
	Hoffman_Queue_Min_Heap_Increase_Key(PointerArray, Object_Pointer, K);

	return 1;

}


void Huffman(struct CharacterObject_Tag* CharacterObject_Table, int Number_of_Character)
{
	//Initialize the min-heap 
	int Queue_Size = Number_of_Character;
	struct CharacterObject_Tag** MinHeapArray = (struct CharacterObject_Tag**)malloc(Queue_Size * sizeof(struct CharacterObject_Tag*));
	for (int i = 0; i < Queue_Size; i++)
	{
		MinHeapArray[i] = &CharacterObject_Table[i];
	}

	Hoffman_Queue_Build_Min_Heap(MinHeapArray, Queue_Size);


	int Number_of_InternalNode = Number_of_Character - 1;
	struct CharacterObject_Tag* InternalNode_Pointer = (struct CharacterObject_Tag*)malloc(Number_of_InternalNode * sizeof(struct CharacterObject_Tag));
	struct CharacterObject_Tag* x, * y;

	for (int i = 0; i < Number_of_InternalNode; i++)
	{


		x = Hoffman_Queue_Min_Heap_Extract_Minimum(MinHeapArray, &Queue_Size);



		y = Hoffman_Queue_Min_Heap_Extract_Minimum(MinHeapArray, &Queue_Size);



		//Doubly link
		InternalNode_Pointer[i].LeftObject_Pointer = x;
		x->ParentObject_Pointer = &InternalNode_Pointer[i];

		//Doubly link
		InternalNode_Pointer[i].RightObject_Pointer = y;
		y->ParentObject_Pointer = &InternalNode_Pointer[i];

		//Link to parent
		InternalNode_Pointer[i].ParentObject_Pointer = NULL;
		InternalNode_Pointer[i].Frequency = x->Frequency + y->Frequency;


		Hoffman_Queue_Min_Heap_Insert(MinHeapArray, &Queue_Size, &InternalNode_Pointer[i], Number_of_Character);



	}

	//Fill the children pointer for character objects.
	for (int i = 0; i < Number_of_Character; i++)
	{
		CharacterObject_Table[i].LeftObject_Pointer = NULL;
		CharacterObject_Table[i].RightObject_Pointer = NULL;
	}


	struct CharacterObject_Tag* Root_of_HoffmanTree = Hoffman_Queue_Min_Heap_Extract_Minimum(MinHeapArray, &Queue_Size);




	free(MinHeapArray);
}