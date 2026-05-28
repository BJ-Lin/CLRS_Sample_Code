/**
 * @file    Max_Heap_Sort.c
 * @brief
 * Implements a max heap data structure and its associated operations.
 * The pseudo codes are from Introduction to algorithm 4th, CLRS.
 *
 * @details
 * Implements standard max heap operations.
 *
 * @author  BJ-Lin , the email address is : <s90333125@gmail.com>
 * @date    2026-05-04
 *
 * @version 1.0
 *
 */
#include "..\Header.h"


float Heap_Array[27] = { 1,16,20,26,13,21,27,12,9,9,9,19,7,24,14,8,2,18,15,22,10,23,17,4,11,6,5 };

 /**
  * @brief
  * Implements heapify operation for a max heap data structure.
  * The pseudo code is from Introduction to algorithm 4th, CLRS, p165, which is MAX-HEAPIFY( A , i ).
  *
  * @param[in]      Heap_Size        The number of elements in the heap.
  * @param[in,out]  Array            Pointer to the array to be heapified.
  * 
  * @param[in]      Root_Index       The index of the root element to be heapified. 
  *								     As same as textbook p162, the index of nodes is from 1~n for for computing its parent and children conveniently,
  *								     which is different from the array index from 0~n-1.
  * 
  * @return No return value (void function).
  *
  * @details
  * Implements standard max heapify operation:
  *   Array[i] = heap elements
  *
  *
  * Time Complexity:  Theta(lg n)	(Worst case ; Go down the height of the tree until the leaf.)
  * Space Complexity: Theta(lg n)	(Worst case ; Recursion stack)
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
  * - Undefined behavior if accessing out of bounds for pointer(s).
  */
void Max_Heapify(float Array[], size_t Heap_Size, unsigned Root_Index)
{
	//The index is from 4th, textbook p162, index = 1 ~ n for computing its parent and children conveniently in heap.
	unsigned Largest_Index = Root_Index;
	unsigned Left_Child_Index = 2 * Root_Index;
	unsigned Right_Child_Index = 2 * Root_Index + 1;


	
	if (Left_Child_Index <= Heap_Size)
	{
		//Put the comparison condition in the inner bracket of if(Left_Child_Index <= Heap_Size) statement for avoiding the memory access violation,
		//that the Heap_Size equal array size.
		if (Array[Left_Child_Index - 1] > Array[Root_Index - 1])
		{
			Largest_Index = Left_Child_Index;
		}
	}


	if (Right_Child_Index <= Heap_Size )
	{
		//Put the comparison condition in the inner bracket of if(Left_Child_Index <= Heap_Size) statement for avoiding the memory access violation,
		//that the Heap_Size equal array size.
		if (Array[Right_Child_Index - 1] > Array[Largest_Index - 1])
		{
			Largest_Index = Right_Child_Index;
		}	
	}



	if (Largest_Index != Root_Index)
	{
		//Exchange values of array.
		float Temp = Array[Root_Index - 1];
		Array[Root_Index - 1] = Array[Largest_Index - 1];
		Array[Largest_Index - 1] = Temp;


		Max_Heapify(Array, Heap_Size, Largest_Index);
	}

}



/**
 * @brief
 * Implements build heap operation for a max heap data structure.
 * The pseudo code is from Introduction to algorithm 4th, CLRS, p167, which is BUILD-MAX-HEAP( A , n ).
 *
 * @param[in]      Heap_Size        The number of elements in the heap.
 * @param[in,out]  Array            Pointer to the array to be built into a max heap.
 *
 * 					
 *
 * @return No return value (void function).
 *
 * @details
 * Implements standard build max heap operation:
 *   Array[i] = heap elements
 *
 *
 * Time Complexity:  Theta(n)		(Worst case ; Go down the height of the tree until the leaf for each non-leaf node.)
 * Space Complexity: Theta(lg n)	(Worst case ; Recursion stack )
 *
 * @pre
 * - The pointer(s) must not be NULL.
 * - Memory must be pre-allocated.
 * 
 *
 * @post
 * - The max heap property is created for Array, which represents a max heap.
 *
 * @note
 * - No SIMD optimization.
 * - No qualifiers, which are const, volatile, restrict, and _Atomic( Even a type specifier for a new atomic type ).
 *
 * @warning
 * - Undefined behavior if accessing out of bounds for pointer(s).
 */
void Build_Max_Heap(float Array[], size_t Heap_Size)
{
	//The index is from 4th, textbook p162, index = 1 ~ n for computing its parent and children conveniently in heap.
	// i is the index of node.
	for (unsigned int i = Heap_Size / 2; i >= 1; i--)
	{
		Max_Heapify(Array, Heap_Size, i);
	}

}



/**
 * @brief
 * Implements heap sort operation for a max heap data structure.
 * The pseudo code is from Introduction to algorithm 4th, CLRS, p170, which is HEAP-SORT( A , n ).
 *
 * @param[in]      Heap_Size        The number of elements in the heap.
 * @param[in,out]  Array			Pointer to the array to be sorted from heap.
 *
 *
 *
 * @return No return value (void function).
 *
 * @details
 * Implements standard max heap sort operation:
 *   Array[i] = sorted elements
 *
 *
 * Time Complexity:  Theta(n lg n)	(Worst case ; Go down the height of the tree until the leaf from root for each iteration.)
 * Space Complexity: Theta(lg n)	(Worst case ; Recursion stack)
 *
 * @pre
 * - The pointer(s) must not be NULL.
 * - Memory must be pre-allocated.
 *
 *
 * @post
 * - The parameter Array is sorted in decreasing order.
 *
 * @note
 * - No SIMD optimization.
 * - No qualifiers, which are const, volatile, restrict, and _Atomic( Even a type specifier for a new atomic type ).
 *
 * @warning
 * - Undefined behavior if accessing out of bounds for pointer(s).
 */
void MaxHeapSort(float Array[], size_t Heap_Size) //The heap functions Max_Heapify, Build_Max_Heap, and MaxHeapSort, only heap size of MaxHeapSort is changed.
{

	Build_Max_Heap(Array, Heap_Size);


	//Loop invariant: 
	//the array from index 0 to New_Heap_Size - 1 is a max heap, 
	//and the array from index New_Heap_Size to Heap_Size - 1 is sorted in increasing order.
	unsigned int New_Heap_Size = Heap_Size;
	while (New_Heap_Size >= 2)
	{
		//Exchange values.
		float temp = Array[New_Heap_Size - 1];
		Array[New_Heap_Size - 1] = Array[0];
		Array[0] = temp;

		//Assign the new heap-size.
		New_Heap_Size--;
		Max_Heapify(Array, New_Heap_Size, 1); 
	}

}