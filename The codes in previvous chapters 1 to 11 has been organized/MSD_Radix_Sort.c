/**
 * @file    MSD_Radix_Sort.c
 * @brief
 * Implements MSD radix sort algorithm for sorting an array of integers in ascending order.
 * There is no pseudo code on the CLRS textbook, but the algorithm is similar to the LSD radix sort.
 *
 * @details
 * Implements MSD radix sort operation.
 *
 *
 * @author  BJ-Lin , the email address is : <s90333125@gmail.com>
 * @date    2026-05-14
 *
 * @version 1.0
 *
 */
#include "..\Header.h"



int MostSignificant_Array[12] = { 329,457,657,-839,436,720,-355,842,210,111,123,-21 };

//The function is used for calculating the number of digits that we need to sort, the significant figures with base 10.
//The element values in SortedInstant_Array can be positive, negative or zero.
//The time complexity is Theta( n * log d ) , where n is the number of elements in SortedInstant_Array, and d is the number of significant digits of INT_MAX with base 10.
unsigned int CalculateSortedDigitNumber_Base10_INT(int SortedInstant_Array[], size_t Instant_Size)
{
	//We list the inequality 10^k <=INT_MAX < 10^(k+1) for INT_MAX; +1 means counting the units digit.
	unsigned int Number_Of_Digits = log10(INT_MAX) + 1; 

	//We assign the below values for [ UpperDigitPosition , LowerDigitPosition ], which is the closed interval of digit positions of significant figures with base 10.
	unsigned int UpperDigitPosition = Number_Of_Digits, LowerDigitPosition = 1;

	//We assign the below value for [ LowerDigitPosition , MiddleDigitPosition ] and [ MiddleDigitPosition + 1 , UpperDigitPosition ], which are lower region and upper region.
	//We ues the below formula for the case MiddleDigitPosition = ( k+(k+1) )/2 = k + 0.5, which are the two separation regions, not only one.
	unsigned int MiddleDigitPosition = (UpperDigitPosition + LowerDigitPosition) / 2;

	//Time Complexity: Theta( n * log d )
	do
	{
		//We check whether there is an inequality -10^(MiddleDigitPosition) < SortedInstant_Array[i] < 10^(MiddleDigitPosition), 
		//that the meaning is there exists a value in SortedInstant_Array whose digit of upper region with base 10 is zero.
		//The most significant digit of 10^(MiddleDigitPosition) is on MiddleDigitPosition+1 digit position.
		unsigned char LeftPartValue_Flag = 0;
		for (int i = 0; i < Instant_Size && LeftPartValue_Flag == 0; i++)
		{
			LeftPartValue_Flag = LeftPartValue_Flag || (SortedInstant_Array[i] - SortedInstant_Array[i] % (int)pow(10, MiddleDigitPosition));
		}


		//LeftPartValue_Flag is 0, which means the values of all left parts are 0, 
		//then we choose the lower region as the new region. 
		//Otherwise, we choose the upper region as the new region.
		if (LeftPartValue_Flag == 0) 
		{
			UpperDigitPosition = MiddleDigitPosition;
		}
		else
		{
			LowerDigitPosition = MiddleDigitPosition + 1;
		}

		//We update the value of MiddleDigitPosition for the next iteration.
		MiddleDigitPosition = (UpperDigitPosition + LowerDigitPosition) / 2;

	} while (UpperDigitPosition != LowerDigitPosition);


	Number_Of_Digits = UpperDigitPosition;


	//Return the number of digits taht we need to sort, 
	return Number_Of_Digits;
}



/**
 * @brief
 * Implements MSD radix sort algorithm for sorting an array of integers in ascending order.
 * There is no pseudo code on the CLRS textbook, but the algorithm is similar to the LSD radix sort.
 *
 * 
 * @param[in,out]  SortedInstant_Array      The elements will be sorted in SortedInstant_Array.
 * @param[in]      Instant_Size				The number of elements in SortedInstant_Array.
 * @param[in]      Number_Of_Digits         The number of digits to be sorted.
 *
 * @return None.
 *
 * @details
 * Implements MSD radix sort operation.
 * 
 *
 * Time Complexity:   O(d(n + n*k))		(Worst case ; n is the number of elements in SortedInstant_Array, k is the range of positive and negative values for base, d is the number of digits to be sorted ; The number of recursion nodes at each depth is as large as possible to make the time cost of total partitions be larger.)
 *					  O( d * n )		(Worst case ; In addition to the situation of O(d(n + n*k)), k is a constant.)
 *					  Theta(d(n + k))	(Worst case ; The number of partitions which are to be sorted is sparse.)
 *					  Theta( n )		(Best case ; There is no recursion.)
 *
 * Space Complexity: Theta( n + d*k )	(Worst case ; All kinds of recursion tree with recursion depth d.)
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
void MSD_Radix_Sort(int SortedInstant_Array[], size_t Instant_Size, unsigned int Number_Of_Digits)
{
	//The range of digit position is from position 1 to position Number_Of_Digits.
	//For instance, 75931, the digit of position 1 is 1, the digit of position 2 is 3, the digit of position 3 is 9, the digit of position 4 is 5, and the digit of position 5 is 7.
	unsigned int Digit_Position = Number_Of_Digits;

	//Base case , if Digit_Position=0.  
	if (Digit_Position > 0)
	{
		//Divide: Sorting the elements in SortedInstant_Array by referring to the digit at position Digit_Position.
		//n: Instant_Size
		//Space complexity : Theta(n)
		int* kth_Digit_Value = (int*)malloc(Instant_Size * sizeof(int));

		
		//Extract kth digit value for each number.
		//Time complexity : Theta(n)
		for (int i = 0; i < Instant_Size; i++)
		{
			kth_Digit_Value[i] = (int)(SortedInstant_Array[i] / pow(10, (Digit_Position - 1))) % 10; //Time complexity : Theta( lg(Digit_Position - 1) ) = Theta( 1 ), if the value of Digit_Position is on the interval [ 1 , the position of most significant digit of INT_MAX ].
		}


		//We need to use counter to count the numbers of the values, and the range of values is [ -9 : 9 ].
		int MaxMinBoundary_Array[] = { -9,9 }; 


		//Time complexity: Theta(n + k), the counter number k is constant.
		//Space complexity: Theta(n + k)
		//Sorting according to kth digit. k is not kth digit.
		Counting_Sort(kth_Digit_Value, MaxMinBoundary_Array, SortedInstant_Array, Instant_Size);  //Here, we do not need the "stable" property , this is a difference between MSD radix sort and LSD radix sort.


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

		free(kth_Digit_Value);





		//Conquer
		unsigned int Criteria_Number = 1; //The usage of Criteria_Number: If the number of the digit is 1, we do not need to sort it recursively.
		unsigned int Next_Number_Of_Digits = Number_Of_Digits - 1;

		//Loop invariant: Next_Sorting_Instant is the starting address of the instant that we need to sort, 
		//and the number of elements is Counter_Pointer[i].
		int* Next_Sorting_Instant = SortedInstant_Array;
		for (int i = 0; i < Counter_Size; i++) //Time complexity : Theta( k ) 
		{
			if (Counter_Pointer[i] > Criteria_Number)
			{
				MSD_Radix_Sort(Next_Sorting_Instant, Counter_Pointer[i], Next_Number_Of_Digits);
			}

			//Update the starting address for the next iteration.
			Next_Sorting_Instant = Next_Sorting_Instant + Counter_Pointer[i];
		}


		
		free(Counter_Pointer);
	}
}