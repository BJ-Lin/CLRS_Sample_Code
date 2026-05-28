/**
 * @file    Priority_Queue_Max_Heap.c
 * @brief
 * Implements a priority queue of max heap and its associated operations.
 * The pseudo codes are from Introduction to algorithm 4th, CLRS, but some algorithms are not.
 *
 * @details
 * Implements standard max priority queue operations.
 *
 * @author  BJ-Lin , the email address is : <s90333125@gmail.com>
 * @date    2026-05-04
 *
 * @version 1.0
 *
 */
#include "..\Header.h"


 //CLRS,4th : The data of array are from P165.
struct Object_of_Queue_Tag Queue_Object[10] = { {.Key = 16,.Index = 1},{.Key = 4,.Index = 2},{.Key = 10,.Index = 3},{.Key = 14,.Index = 4},{.Key = 7,.Index = 5},{.Key = 9,.Index = 6},{.Key = 3,.Index = 7},{.Key = 2,.Index = 8},{.Key = 8,.Index = 9},{.Key = 1,.Index = 10} };


 /**
  * @brief
  * Implements heapify operation for a max heap queue data structure.
  * There is no pseudo code on the CLRS textbook, but the algorithm is similar to a operation of max heap.
  *
  * @param[in,out]  MaxPriority_Queue_Pointer       Pointer to the max priority queue to be heapified.
  *
  * @param[in]      Root_Index						The index of the root element to be heapified.
  *													As same as textbook p162, the index of nodes is from 1~n for for computing its parent and children conveniently,
  *													which is different from the array index from 0~n-1.
  *
  * @return No return value (void function).
  *
  * @details
  * Implements standard max heapify operation:
  *   Array[i] = heap elements
  *
  *
  * Time Complexity:  Theta(lg n)		(Worst case ; Go down the height of the tree until the leaf.)
  * Space Complexity: Theta(lg n)		(Worst case ; Recursion stack )
  *
  * @pre
  * - The pointer(s) must not be NULL.
  * - Memory must be pre-allocated.
  * - Subtrees rooted at left and right children of Root_Index must already be max heaps.
  *
  * @post
  * - The max heap property is restored for the subtree rooted at Root_Index.
  *
  * @note
  * - No SIMD optimization.
  * - No qualifiers, which are const, volatile, restrict, and _Atomic( Even a type specifier for a new atomic type ).
  *
  * @warning
  * - Undefined behavior if accessing out of bounds for MaxPriority_Queue_Pointer.
  */
void Queue_Max_Heapify(struct MaxPriority_Queue_Tag* MaxPriority_Queue_Pointer, unsigned Root_Index)
{
	//Assine the pointer array and queue size to local variables for convenient use.
	struct Object_of_Queue_Tag** PointerArray = MaxPriority_Queue_Pointer->PointerArray;
	size_t Queue_Size = MaxPriority_Queue_Pointer->Queue_Size;

	//The index is from 4th, textbook p162, index = 1 ~ n for computing its parent and children conveniently in heap, which are not for array indices ; n is the total number of nodes of binary heap.
	unsigned Largest_Index = Root_Index;
	unsigned Left_Child_Index = 2 * Root_Index;
	unsigned Right_Child_Index = 2 * Root_Index + 1;

	if (Left_Child_Index <= Queue_Size)
	{
		//Put the comparison condition in the inner bracket of if(Left_Child_Index <= Queue_Size) statement for avoiding the memory access violation,
		//that the Queue_Size equal array size.
		if (PointerArray[Left_Child_Index - 1]->Key > PointerArray[Root_Index - 1]->Key)
		{
			Largest_Index = Left_Child_Index;
		}

	}


	if (Right_Child_Index <= Queue_Size)		
	{
		//Put the comparison condition in the inner bracket of if(Right_Child_Index <= Queue_Size) statement for avoiding the memory access violation,
		//that the Queue_Size equal array size.
		if (PointerArray[Right_Child_Index - 1]->Key > PointerArray[Largest_Index - 1]->Key)
		{
			Largest_Index = Right_Child_Index;
		}
	}


	if (Largest_Index != Root_Index)
	{
		//Exchange values of PointerArray.
		struct Object_of_Queue_Tag* Temp = PointerArray[Root_Index - 1];
		PointerArray[Root_Index - 1] = PointerArray[Largest_Index - 1];
		PointerArray[Largest_Index - 1] = Temp;

		//Update indices of PointerArray.
		PointerArray[Root_Index - 1]->Index = Root_Index;	
		PointerArray[Largest_Index - 1]->Index = Largest_Index;

		Queue_Max_Heapify(MaxPriority_Queue_Pointer, Largest_Index);

	}

}




//The return value of this function is 1 if the address of maximum object is successfully assigned to the *MaximumAddress_Pointer, and 0 if the queue is empty.
signed char Queue_Max_Heap_Maximum(struct MaxPriority_Queue_Tag* MaxPriority_Queue_Pointer, struct Object_of_Queue_Tag** MaximumAddress_Pointer)
{
	//Assine the pointer array and queue size to local variables for convenient use.
	struct Object_of_Queue_Tag** PointerArray = MaxPriority_Queue_Pointer->PointerArray;
	size_t Queue_Size = MaxPriority_Queue_Pointer->Queue_Size;

	if(Queue_Size == 0)
	{
		return 0;
	}
	else
	{
		*MaximumAddress_Pointer = PointerArray[0];
		return 1;
	}
	
}




/**
 * @brief
 * Implements extract maximum operation for a max heap queue data structure.
 * The pseudo code is from Introduction to algorithm 4th, CLRS, p175, which is MAX-HEAP-EXTRACT-MAX( A ).
 *
 * @param[in,out]  MaxPriority_Queue_Pointer        Pointer to the max priority queue to be heapified.
 *
 * 
 * @return The pointer of the maximum object, which is deleted in the queue.
 *
 * @details
 * Implements maximum extraction operation for max heap queue.
 *
 *
 * Time Complexity:  Theta(lg n) ( Worst case ; Go down the height of the tree until the leaf. )
 * Space Complexity: Theta(lg n) ( Worst case ; Recursion stack )
 *
 * @pre
 * - The pointer(s) must not be NULL.
 * - Memory must be pre-allocated.
 * - MaxPriority_Queue_Pointer must be a valid max priority queue.
 * 
 *
 * @post
 * - Returns the pointer of the maximum object, which is deleted in the max heap queue. Or returns NULL if the max heap queue is empty.
 * - The max heap queue property is restored after deletion.
 * 
 * @note
 * - No SIMD optimization.
 * - No qualifiers, which are const, volatile, restrict, and _Atomic( Even a type specifier for a new atomic type ).
 *
 * @warning
 * - Undefined behavior if accessing out of bounds for MaxPriority_Queue_Pointer.
 */
struct Object_of_Queue_Tag* Queue_Max_Heap_Extract_Maximum(struct MaxPriority_Queue_Tag* MaxPriority_Queue_Pointer)
{
	struct Object_of_Queue_Tag* Temp;
	unsigned char QuerySuccess_Flag = Queue_Max_Heap_Maximum(MaxPriority_Queue_Pointer, &Temp);  //Query the maximum value of heap.

	//If the queue is empty, return NULL.
	if (QuerySuccess_Flag == 0)
	{
		return NULL;
	}


	//Assine the pointer array and queue size to local variables for convenient use.
	struct Object_of_Queue_Tag** PointerArray = MaxPriority_Queue_Pointer->PointerArray;
	size_t* QueueSize_Pointer = &(MaxPriority_Queue_Pointer->Queue_Size);


	//Cover the root with a final leaf( ~ Delete maximun).
	PointerArray[0] = PointerArray[*QueueSize_Pointer - 1]; 

	//The index is from 4th, textbook p162, index = 1 ~ n for computing its parent and children conveniently in heap, which are not for array indices; n is the total number of nodes of binary heap.
	//Update the index and queue size of new root.
	PointerArray[0]->Index = 1;	
	*QueueSize_Pointer = *QueueSize_Pointer - 1;



	//Restore the max heap property after deletion.
	Queue_Max_Heapify(MaxPriority_Queue_Pointer, 1);

	return Temp;
}




/**
 * @brief
 * Implements increase key operation for a max heap queue data structure.
 * The pseudo code is from Introduction to algorithm 4th, CLRS, p176, which is MAX-HEAP-INCREASE-KEY( A, x, k ).
 *
 * @param[in,out]  MaxPriority_Queue_Pointer        Pointer to the max priority queue for increasing object key.
 * @param[in,out]  Object_Pointer					Pointer to the object in the queue whose key is to be increased.
 * @param[in]      New_Key                          The new key value to be assigned to the object.
 *
 * @return The flag indicating whether the key was successfully increased (1) or not (0).
 *
 * @details
 * Implements key increase operation for max heap queue.
 *
 *
 * Time Complexity:  Theta(lg n) ( Worst case ; Go up the height of the tree until the root from the current node. )
 * Space Complexity: Theta(1)    (All cases)
 *
 * @pre
 * - The pointer(s) must not be NULL.
 * - Memory must be pre-allocated.
 * - MaxPriority_Queue_Pointer must be a valid max priority queue.
 * - Object_Pointer must not be NULL and must point to an object in the max priority queue.
 *
 *
 * @post
 * - Returns 1 if the key was successfully increased, or 0 if New_Key is smaller than the original key.
 * - The max heap queue property is restored after increasing the key.
 *
 * @note
 * - No SIMD optimization.
 * - No qualifiers, which are const, volatile, restrict, and _Atomic( Even a type specifier for a new atomic type ).
 *
 * @warning
 * - Undefined behavior if accessing out of bounds for MaxPriority_Queue_Pointer.
 */
signed Queue_Max_Heap_Increase_Key(struct MaxPriority_Queue_Tag* MaxPriority_Queue_Pointer, struct Object_of_Queue_Tag* Object_Pointer, float New_Key)
{
	//Assine the pointer array to the local variable for convenient use.
	struct Object_of_Queue_Tag** PointerArray = MaxPriority_Queue_Pointer->PointerArray;


	// The return value of this function is 0 if New_Key is smaller than original key.
	if (New_Key < Object_Pointer->Key)
	{
		return 0;
	}


	//Update the key of Object_Pointer to New_Key.
	Object_Pointer->Key = New_Key;


	//The index is from 4th, textbook p162, index = 1 ~ n for computing its parent and children conveniently in heap,
	//which are not for array indices; n is the total number of nodes of binary heap.
	unsigned i = Object_Pointer->Index;


	//Go up the height of the tree until the root for restoring the max heap property after increasing key.
	//i = 1 is the root, which has no parent, so the loop condition is i > 1.
	while (i > 1) 
	{
		//Judge if the key of parent node is smaller than the key of current node i.
		if (PointerArray[i / 2 - 1]->Key < PointerArray[i - 1]->Key)
		{
			//Exchange pointer values of array
			struct Object_of_Queue_Tag* Temp = PointerArray[i / 2 - 1];
			PointerArray[i / 2 - 1] = PointerArray[i - 1];
			PointerArray[i - 1] = Temp;

			//Update index 
			PointerArray[i / 2 - 1]->Index = i / 2;
			PointerArray[i - 1]->Index = i;


			//Assign new i.
			i = i / 2;
		}
		else
		{
			break;
		}

	}

	return 1; //New_Key is larger than original key.
}







/**
 * @brief
 * Implements insertion operation for a max heap queue data structure.
 * The pseudo code is from Introduction to algorithm 4th, CLRS, p176, which is MAX-HEAP-INSERT( A, x, n ).
 *
 * @param[in,out]  MaxPriority_Queue_Pointer       Pointer to the max priority queue for insertion operation.
 * @param[in]	   InsertedObject_Pointer		   Pointer to the object to be inserted.
 * 
 *
 * @return The flag indicating whether the insertion was successful (1) or not (0).
 *
 * @details
 * Implements the insertion operation for max heap queue.
 *
 *
 * Time Complexity:  Theta(lg n) ( Worst case ; Go up the height of the tree until the root from the insertion node. )
 * Space Complexity: Theta(1)    (All cases )
 *
 * @pre
 * - The pointer(s) must not be NULL.
 * - Memory must be pre-allocated.
 * - MaxPriority_Queue_Pointer must be a valid max priority queue.
 * - InsertedObject_Pointer must not be NULL, and is a valid object pointer.
 *
 *
 * @post
 * - Returns 1 if the insertion is successful, or 0 if the queue is full.
 * - The max heap queue property is restored after insertion.
 *
 * @note
 * - No SIMD optimization.
 * - No qualifiers, which are const, volatile, restrict, and _Atomic( Even a type specifier for a new atomic type ).
 *
 * @warning
 * - Undefined behavior if accessing out of bounds for MaxPriority_Queue_Pointer.
 */
signed Queue_Max_Heap_Insert(struct MaxPriority_Queue_Tag* MaxPriority_Queue_Pointer, struct Object_of_Queue_Tag* InsertedObject_Pointer)
{
	//Assine the pointer array and queue size to local variables for convenient use.
	struct Object_of_Queue_Tag** PointerArray = MaxPriority_Queue_Pointer->PointerArray;
	size_t* QueueSize_Pointer = &(MaxPriority_Queue_Pointer->Queue_Size);

	size_t Array_Size = MaxPriority_Queue_Pointer->Array_Size;

	//Step1. Judge if the queue is full for avoiding the memory access violation.
	if (*QueueSize_Pointer >= Array_Size)
	{

		return 0;

	}

	//Step2. Insert the new object into the queue.
	*QueueSize_Pointer = *QueueSize_Pointer + 1;
	PointerArray[*QueueSize_Pointer - 1] = InsertedObject_Pointer;

	PointerArray[*QueueSize_Pointer - 1]->Index = *QueueSize_Pointer;


	//Step3. Reserve the KEY and modify the KEY to minus infinity for using Heap_Increase_Key function.
	float K = PointerArray[*QueueSize_Pointer - 1]->Key;
	PointerArray[*QueueSize_Pointer - 1]->Key = FLT_MIN;


	//Step4. Make the max-heap property be qualified by using Heap_Increase_Key function.
	Queue_Max_Heap_Increase_Key(MaxPriority_Queue_Pointer, InsertedObject_Pointer, K);


	return 1; //Insertion successful.
}






/**
 * @brief
 * Implements deletion operation for a max heap queue data structure.
 * There is no pseudo code on the CLRS textbook.
 *
 * @param[in,out]   MaxPriority_Queue_Pointer       Pointer to the max priority queue for deletion operation.
 * @param[in]		DeletedObject_Pointer			Pointer to the object to be deleted.
 *
 *
 * @return None.
 *
 * @details
 * Implements the deletion operation for max heap queue.
 *
 *
 * Time Complexity:  Theta(lg n) ( Worst case ; Go up/down the height of the tree until the root/leaf from the deletion node. )
 * Space Complexity: Theta(lg n) ( Worst case ; Recursion stack )
 *
 * @pre
 * - The pointer(s) must not be NULL.
 * - Memory must be pre-allocated.
 * - MaxPriority_Queue_Pointer must be a valid max priority queue.
 * - DeletedObject_Pointer must not be NULL, and is a valid object pointer in the max priority queue.
 *
 *
 * @post
 * - The max heap queue property is restored after deletion.
 *
 * @note
 * - No SIMD optimization.
 * - No qualifiers, which are const, volatile, restrict, and _Atomic( Even a type specifier for a new atomic type ).
 *
 * @warning
 * - Undefined behavior if accessing out of bounds for MaxPriority_Queue_Pointer.
 */
void Max_Heap_Delete(struct MaxPriority_Queue_Tag* MaxPriority_Queue_Pointer, struct Object_of_Queue_Tag* DeletedObject_Pointer)
{
	//The index is from 4th, textbook p162, index = 1 ~ n for computing its parent and children conveniently in heap, which are not for array indices ; n is the total number of nodes of binary heap.
	unsigned int DeletedObject_Index = DeletedObject_Pointer->Index;
	unsigned int Parent_Index = DeletedObject_Index / 2;
	unsigned int Left_Child_Index = 2 * DeletedObject_Index;
	unsigned int Right_Child_Index = Left_Child_Index + 1;


	//Assine the pointer array and queue size to local variables for convenient use.
	struct Object_of_Queue_Tag** PointerArray = MaxPriority_Queue_Pointer->PointerArray;
	size_t* QueueSize_Pointer = &(MaxPriority_Queue_Pointer->Queue_Size);



	//Step1. Judge if the queue is empty after deletion or not.
	if (*QueueSize_Pointer == 1)
	{
		//Decrease the queue size.
		//The queue is empty after deletion, so there is no need to cover the deleted object by using leaf.
		*QueueSize_Pointer = *QueueSize_Pointer - 1;

		
		return;
	}
	else
	{
		//Cover the deleted object by using leaf( ~ Delete the object).
		PointerArray[DeletedObject_Index - 1] = PointerArray[*QueueSize_Pointer - 1];


		//Update the index of the moved leaf.
		PointerArray[DeletedObject_Index - 1]->Index = DeletedObject_Index;


		//Decrease the queue size.
		*QueueSize_Pointer = *QueueSize_Pointer - 1;

	}


	//Reserve the KEY and modify the KEY to minus infinity for using Heap_Increase_Key function.
	float K = PointerArray[DeletedObject_Index - 1]->Key;
	PointerArray[DeletedObject_Index - 1]->Key = FLT_MIN;


	//Restore the max-heap property by using Heap_Increase_Key function.
	Queue_Max_Heap_Increase_Key(MaxPriority_Queue_Pointer, PointerArray[DeletedObject_Index - 1], K);


	//Restore the max-heap property by using Max_Heapify function.
	Queue_Max_Heapify(MaxPriority_Queue_Pointer, DeletedObject_Index);

}