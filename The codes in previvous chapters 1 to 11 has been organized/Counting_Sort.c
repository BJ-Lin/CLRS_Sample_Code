/**
 * @file    Counting_Sort.c
 * @brief
 * Implements counting sort algorithm for sorting an array of integers in ascending order.
 * The pseudo code is from Introduction to algorithm 4th, CLRS.
 *
 * @details
 * Implements counting sort operation.
 * 
 *
 * @author  BJ-Lin , the email address is : <s90333125@gmail.com>
 * @date    2026-05-12
 *
 * @version 1.0
 *
 */
#include "..\Header.h"



int Counting_Array[8] = { -2,1,3,0,2,-3,0,-9 };




/**
 * @brief
 * Implements counting sort algorithm for sorting an array of integers in ascending order.
 * The pseudo code is from Introduction to algorithm 4th, CLRS, p209, which is COUNTING-SORT( A , n , k ).
 *
 * @param[in]      Array				    Each value is part/whole of element value in SortedInstant_Array for sorting the elements of SortedInstant_Array.
 * @param[in]      MaxMinBoundary_Pointer   The minimum and maximum values of elements in Array.
 * @param[in,out]  SortedInstant_Array      The elements will be sorted in SortedInstant_Array.
 * @param[in]      Instant_Size				The number of elements in SortedInstant_Array.
 *
 * @return None.
 *
 * @details
 * Implements counting sort operation.
 * The sorted elements in SortedInstant_Array are stable, 
 * which means that the relative order of elements with equal values in SortedInstant_Array is the same as in the input array.
 *
 * Time Complexity:  Theta(n + k)		(All cases ; n is the number of elements in SortedInstant_Array, k is the range of values in Array.)
 * 
 * Space Complexity: Theta(n + k)		(All cases)
 *
 * @pre
 * - The pointer(s) must not be NULL.
 * - Memory must be pre-allocated.
 *
 * @post
 * - The parameter SortedInstant_Array is sorted in ascending order.
 *
 * @note
 * - No SIMD optimization.
 * - No qualifiers, which are const, volatile, restrict, and _Atomic( Even a type specifier for a new atomic type ).
 *
 * @warning
 * - Undefined behavior if accessing out of bounds for the pointer(s).
 */
void Counting_Sort(int Array[], int* MaxMinBoundary_Pointer, int SortedInstant_Array[], size_t Instant_Size)
{
	
	//Evalute the counter size.
	//MaxMinBoundary[1] is the maximum value in Array, and MaxMinBoundary[0] is minimum value in Array; +1 means counting the starting value MaxMinBoundary[0]. 
	unsigned int Counter_Size = MaxMinBoundary_Pointer[1] - MaxMinBoundary_Pointer[0] + 1;


	//Allocate the output array that will store the sorted elements.
	int* Output_Pointer = (int*)malloc(Instant_Size * sizeof(int));


	//Allocate the counter array that will store the count of each value in Array.
	unsigned* Counter_Pointer = (unsigned*)malloc((Counter_Size) * sizeof(unsigned));


	//Initialize the counter array to be 0.
	for (int i = 0; i < Counter_Size; i++)
	{
		Counter_Pointer[i] = 0;
	}


	//Counting the number of each value in Array.
	unsigned int Counter_Index;
	for (int j = 0; j < Instant_Size; j++)
	{
		//Counter_Index is corresponding to Array[j].
		Counter_Index = Array[j] - MaxMinBoundary_Pointer[0];
		Counter_Pointer[Counter_Index] = Counter_Pointer[Counter_Index] + 1;
	}


	//Cumulative count of each value i in Array.
	//The meaning of Counter_Pointer[i] is that the elements with value i in Array from location Counter_Pointer[i - 1] + 1 to Counter_Pointer[i].
	//The range of location is [1, Instant_Size]
	for (int i = 1; i < Counter_Size; i++)
	{
		Counter_Pointer[i] = Counter_Pointer[i] + Counter_Pointer[i - 1];
	}


	//Insert the values of SortedInstant_Array.
	//Go through each index j from Instant_Size - 1 to 0 to make the output stable.
	for (int j = Instant_Size - 1; j >= 0; j--) 
	{
		Counter_Index = Array[j] - MaxMinBoundary_Pointer[0];
		Output_Pointer[Counter_Pointer[Counter_Index] - 1] = SortedInstant_Array[j]; //There exist conversion between location of elements [ 1 : Instant_Size ] and index [ 0 : Instant_Size - 1 ], such as -1 exist.
		Counter_Pointer[Counter_Index] = Counter_Pointer[Counter_Index] - 1;
	}


	//Copy the sorted elements from output array to SortedInstant_Array.
	for (int j = Instant_Size - 1; j >= 0; j--)
	{
		SortedInstant_Array[j] = Output_Pointer[j];
	}

	free(Counter_Pointer);
	free(Output_Pointer);

}