/**
 * @file    Insertion_Sort.c
 * @brief    
 * Sort the numbers in the given array using insertion sort algorithm.
 * The pseudo code is from Introduction to algorithm 4th, CLRS.
 * 
 * @details
 * Implements standard insertion sort algorithm.
 *
 * @author  BJ-Lin , the email address is : <s90333125@gmail.com>
 * @date    2026-04-24
 *
 * @version 1.0
 *
 */

#include "..\Header.h"



int InsertedArray[18] = { 1,3,2,4,8,6,5,10,11,9,7,13,15,12,14,17,16,18 };

/**
 * @brief
 * Sort the numbers in the given array using insertion sort algorithm.
 * The pseudo code is from Introduction to algorithm 4th, CLRS, p19, which is INSERTION-SORT( A , n ).
 *
 * @param[in]      Sort_Size        The number of elements in the array to be sorted.
 * @param[in,out]  Array            Pointer to the array to be sorted.
 *
 * @return No return value (void function).
 *
 * @details
 * Implements standard insertion sort algorithm:
 *   Array[i] = sorted elements
 *
 *
 * Time Complexity:  Theta(n)	( Best case ; Already sorted )
 * 					 Theta(n^2) ( Worst case ; Reverse sorted)
 * 
 * 
 * Space Complexity: Theta(1)	(All cases)
 *
 * @pre
 * - The pointer(s) must not be NULL.
 * - Memory must be pre-allocated.
 *
 * @post
 * - The parameter Array contains the sorted elements.
 *
 * @note
 * - No SIMD optimization.
 * - No qualifiers, which are const, volatile, restrict, and _Atomic( Even a type specifier for a new atomic type ). 
 *
 * @warning
 * - Undefined behavior if accessing out of bounds for pointer(s).
 */

void Insertion_Sort(int Sort_Size, int* Array)
{
	int j;
	int Key;

	//Choose the index of inserted element fromm small to large.
	for (int i = 1; i < Sort_Size; i++)
	{
		Key = Array[i];
		j = i - 1;

		//Loop invariant : j is the index of compared element( Even the element with access violation ), and j+1 is the index of empty slot.
		while (j >= 0)
		{
			if (Array[j] > Key)
			{
				Array[j + 1] = Array[j];
				j = j - 1;
			}
			else
			{
				break;
			}
		}

		//Assign the key to the empty slot.
		Array[j + 1] = Key;
	}
}
