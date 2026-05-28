/**
 * @file    Min_Heap_Sort.c
 * @brief
 * Implements a min heap data structure and its associated operations.
 * There are no pseudo codes on the CLRS textbook, but the algorithms are similar to operations of max heap.
 *
 * @details
 * Implements standard min heap operations.
 *
 * @author  BJ-Lin , the email address is : <s90333125@gmail.com>
 * @date    2026-05-04
 *
 * @version 1.0
 *
 */

#include "..\Header.h"




 /**
  * @brief
  * Implements heapify operation for a min heap data structure.
  * There is no pseudo code on the CLRS textbook, but the algorithm is similar to a operation of max heap.
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
  * Implements standard min heapify operation:
  *   Array[i] = heap elements
  *
  *
  * Time Complexity:  Theta(lg n)	(Worst case ; Go down the height of the tree until the leaf. )
  * 
  * 
  * Space Complexity: Theta(lg n)	(Worst case ; Recursion stack )
  *
  * @pre
  * - The pointer(s) must not be NULL.
  * - Memory must be pre-allocated.
  * - Subtrees rooted at left and right children of Root_Index must already be min heaps.
  *
  * @post
  * - The min heap property is restored for the subtree rooted at Root_Index.
  *
  * @note
  * - No SIMD optimization.
  * - No qualifiers, which are const, volatile, restrict, and _Atomic( Even a type specifier for a new atomic type ).
  *
  * @warning
  * - Undefined behavior if accessing out of bounds for pointer(s).
  */
void Min_Heapify(float Array[], size_t Heap_Size, unsigned Root_Index)
{
	//The index is from 4th, textbook p162, index = 1 ~ n for computing its parent and children conveniently in heap.
	unsigned Min_Index = Root_Index;
	unsigned Left_Child_Index = 2 * Root_Index;
	unsigned Right_Child_Index = 2 * Root_Index + 1;

	if (Left_Child_Index <= Heap_Size )
	{
		//Put the comparison condition in the inner bracket of if(Left_Child_Index <= Heap_Size) statement for avoiding the memory access violation,
		//that the Heap_Size equal array size.
		if (Array[Left_Child_Index - 1] < Array[Root_Index - 1])
		{
			Min_Index = Left_Child_Index;
		}
	}


	if (Right_Child_Index <= Heap_Size)
	{
		//Put the comparison condition in the inner bracket of if(Left_Child_Index <= Heap_Size) statement for avoiding the memory access violation,
		//that the Heap_Size equal array size.
		if (Array[Right_Child_Index - 1] < Array[Min_Index - 1])
		{
			Min_Index = Right_Child_Index;
		}
	}


	if (Min_Index != Root_Index)
	{
		//Exchange values of array.
		float Temp = Array[Root_Index - 1];
		Array[Root_Index - 1] = Array[Min_Index - 1];
		Array[Min_Index - 1] = Temp;


		Min_Heapify(Array, Heap_Size, Min_Index);
	}

}


/**
 * @brief
 * Implements build heap operation for a min heap data structure.
 * There is no pseudo code on the CLRS textbook, but the algorithm is similar to a operation of max heap.
 *
 * @param[in]      Heap_Size        The number of elements in the heap.
 * @param[in,out]  Array            Pointer to the array to be built into a min heap.
 *
 *
 *
 * @return No return value (void function).
 *
 * @details
 * Implements standard build min heap operation:
 *   Array[i] = heap elements
 *
 *
 * Time Complexity:  Theta(n)		( Worst case ; Go down the height of the tree until the leaf for each non-leaf node. )
 * Space Complexity: Theta(lg n)	( Worst case ; Recursion stack )
 *
 * @pre
 * - The pointer(s) must not be NULL.
 * - Memory must be pre-allocated.
 *
 *
 * @post
 * - The min heap property is created for the entire array, which represents a min heap.
 *
 * @note
 * - No SIMD optimization.
 * - No qualifiers, which are const, volatile, restrict, and _Atomic( Even a type specifier for a new atomic type ).
 *
 * @warning
 * - Undefined behavior if accessing out of bounds for pointer(s).
 */
void Build_Min_Heap(float Array[], size_t Heap_Size)
{
	//The index is from 4th, textbook p162, index = 1 ~ n for computing its parent and children conveniently in heap.
	// i is the index of node.
	for (unsigned int i = Heap_Size / 2; i >= 1; i--)
	{
		Min_Heapify(Array, Heap_Size, i);
	}

}



/**
 * @brief
 * Implements heap sort operation for a min heap data structure.
 * There is no pseudo code on the CLRS textbook, but the algorithm is similar to a operation of max heap.
 *
 * @param[in]	   Heap_Size        The number of elements in the heap.
 * @param[in,out]  Array			Pointer to the array to be sorted from heap.
 *
 *
 *
 * @return No return value (void function).
 *
 * @details
 * Implements standard min heap sort operation:
 *   Array[i] = sorted elements
 *
 *
 * Time Complexity:  Theta(n lg n)	( Worst case ; Go down the height of the tree until the leaf from root for each iteration. )
 * Space Complexity: Theta(lg n)	( Worst case ; Recursion stack )
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
void MinHeapSort(float Array[], size_t Heap_Size)
{

	Build_Min_Heap(Array, Heap_Size);


	size_t Heap_Size_Criteria = Heap_Size - 1;
	float temp = 0;



	//Loop invariant: 
	//the array from index 0 to New_Heap_Size - 1 is a min heap, 
	//and the array from index New_Heap_Size to Heap_Size - 1 is sorted in decreasing order.
	unsigned int New_Heap_Size = Heap_Size;
	while (New_Heap_Size >= 2)
	{
		//Exchange values.
		temp = Array[New_Heap_Size - 1];
		Array[New_Heap_Size - 1] = Array[0];
		Array[0] = temp;

		//Assign the new heap-size.
		New_Heap_Size--;
		Min_Heapify(Array, New_Heap_Size, 1);
	}

}