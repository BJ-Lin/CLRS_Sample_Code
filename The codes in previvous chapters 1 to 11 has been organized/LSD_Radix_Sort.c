/**
 * @file    LSD_Radix_Sort.c
 * @brief
 * Implements LSD radix sort algorithm for sorting an array of integers in ascending order.
 * The pseudo code is from Introduction to algorithm 4th, CLRS.
 *
 * @details
 * Implements LSD radix sort operation.
 *
 *
 * @author  BJ-Lin , the email address is : <s90333125@gmail.com>
 * @date    2026-05-14
 *
 * @version 1.0
 *
 */
#include "..\Header.h"





 /**
  * @brief
  * Implements LSD radix sort algorithm for sorting an array of integers in ascending order.
  * The pseudo code is from Introduction to algorithm 4th, CLRS, p213, which is RADIX-SORT( A , n , d ).
  *
  *
  * @param[in,out]  SortedInstant_Array       The elements will be sorted in SortedInstant_Array.
  * @param[in]      Instant_Size			  The number of elements in SortedInstant_Array.
  * @param[in]      Number_Of_Digits          The number of digits to be sorted.
  *
  * 
  * @return None.
  *
  * @details
  * Implements LSD radix sort operation.
  *
  *
  * Time Complexity:  Theta(d(n + k))		 (All cases ; n is the number of elements in SortedInstant_Array, k is the range of positive and negative values for base, d is the number of digits to be sorted.)
  *					  
  *					  
  * Space Complexity: Theta(n + k)			 (All cases)
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
void LSD_Radix_Sort(int SortedInstant_Array[], size_t Instant_Size, unsigned Number_Of_Digits)
{
	//We need to use counter to count the numbers of the values, and the range of values is [ -9 : 9 ].
	int MaxMinBoundary_Array[] = { -9,9 }; 

	//Space complexity : Theta(n)
	int* kth_Digit_Value = (int*)malloc(Instant_Size * sizeof(int));

	//Sorting accorting kth Digit
	//Time complexity : Theta(d)
	for (unsigned int Digit_Position = 1; Digit_Position <= Number_Of_Digits; Digit_Position++)
	{
		//Time complexity : Theta(n)
		//Extract kth digit value for each number.
		for (int j = 0; j < Instant_Size; j++)
		{
			kth_Digit_Value[j] = (int)(SortedInstant_Array[j] / pow(10, (Digit_Position - 1))) % 10;
		}


		//Time complexity : Theta(n + k)
		Counting_Sort(kth_Digit_Value, MaxMinBoundary_Array, SortedInstant_Array, Instant_Size);
	}

	free(kth_Digit_Value);

}