/**
 * @file    Merge_Sort.c
 * @brief
 * Sort the numbers in the given array using merge sort algorithm.
 * The pseudo code is from Introduction to algorithm 4th, CLRS.
 *
 * @details
 * Implements standard merge sort algorithm.
 *
 * @author  BJ-Lin , the email address is : <s90333125@gmail.com>
 * @date    2026-04-25
 *
 * @version 1.0
 *
 */

#include "..\Header.h"

void Merge_Subrouting(int Left_Size, int* Left_Initial_Address, int Right_Size, int* Right_Initial_Address)
{

	int* Left_Pointer = (int*)malloc(Left_Size * sizeof(int));
	int* Right_Pointer = (int*)malloc(Right_Size * sizeof(int));

	/*Copy the elements in the original arrays to temporary space*/
	for (int i = 0; i < Left_Size; i++)
	{
		*(Left_Pointer + i) = *(Left_Initial_Address + i);
	}

	for (int j = 0; j < Right_Size; j++)
	{
		*(Right_Pointer + j) = *(Right_Initial_Address + j);

	}


	int i = 0;
	int j = 0;
	int k = 0;
	//Loop invariant : 
	//i is the index of element which is to be copied for left copied array( Even the element with access violation ), 
	//j is the index of element which is to be copied for right copied array( Even the element with access violation ), 
	//and k is the index of empty slot for storing array.
	while (i < Left_Size && j < Right_Size)
	{

		//Choose the smaller element from two copied arrays, and copy it to the empty slot.
		if (*(Left_Pointer + i) <= *(Right_Pointer + j))
		{
			*(Left_Initial_Address + k) = *(Left_Pointer + i);
			i++;
		}
		else
		{
			*(Left_Initial_Address + k) = *(Right_Pointer + j);
			j++;
		}

		k++;

	}


	while (i < Left_Size)
	{
		*(Left_Initial_Address + k) = *(Left_Pointer + i);
		i++;
		k++;
	}


	while (j < Right_Size)
	{
		*(Left_Initial_Address + k) = *(Right_Pointer + j);
		j++;
		k++;
	}

	free(Left_Pointer);
	free(Right_Pointer);


}



 /**
  * @brief
  * Sort the numbers in the given array using merge sort algorithm.
  * The pseudo code is from Introduction to algorithm 4th, CLRS, p39, which is MERGE-SORT( A , n ).
  *
  * @param[in]      Sort_Size        The number of elements in the array to be sorted.
  * @param[in,out]  Array            Pointer to the array to be sorted.
  *
  * @return No return value (void function).
  *
  * @details
  * Implements standard merge sort algorithm:
  *   Array[i] = sorted elements
  *
  *
  * Time Complexity:  Theta(n log n)	(All cases)
  * Space Complexity: Theta(n)			(All cases ; Reserve the temporary arrays for merging.)
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
void Merge_Sort(int* Array, int Sort_Size)
{
	//Base case, already sorted.
	if (Sort_Size <= 1)
	{
		return;
	}


	//Divide the array into two groups, A[ 1 , q ] & A[ q+1 , Sort_Size ].
	int q = (1 + Sort_Size) / 2; //Calculate the index of the last element of left group.


	int Left_Size = q, Right_Size = Sort_Size - q, * Left_Initial_Address = Array, * Right_Initial_Address = Array + q;

	Merge_Sort(Left_Initial_Address, Left_Size);
	Merge_Sort(Right_Initial_Address, Right_Size);


	//Combine the two sorted groups into one sorted array.
	Merge_Subrouting(Left_Size, Left_Initial_Address, Right_Size, Right_Initial_Address);
}



