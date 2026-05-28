/**
 * @file    Randomized_Quick_Sort.c
 * @brief
 * Implements randomized quick sort algorithm for sorting an array of floats in ascending order.
 * The pseudo code is from Introduction to algorithm 4th, CLRS.
 *
 * @details
 * Implements standard randomized quick sort operations.
 *
 * @author  BJ-Lin , the email address is : <s90333125@gmail.com>
 * @date    2026-05-10
 *
 * @version 1.0
 *
 */
#include "..\Header.h"


float QuickSort_Array[] = {10,7,8,5,1,3,2,4,6,9,8};

int Randomized_QuickSort_Partition(float Array[], int Array_Size)
{
	//Randomly select an pivot index from 0 to Array_Size-1.
	//0 <= rand() / (float)(RAND_MAX+1) < 1  ---> 0 <= (rand() / (float)(RAND_MAX+1)) * Array_Size < Array_Size 
	int RandomPivot_Index = (rand() / (float)(RAND_MAX + 1)) * (Array_Size);


	//Exchange the pivot element with the last element in the array.
	float temp = Array[RandomPivot_Index];
	Array[RandomPivot_Index] = Array[Array_Size - 1];
	Array[Array_Size - 1] = temp;


	//Choose the last element as pivot.
	int Pivot_Index = Array_Size - 1;
	float x = Array[Pivot_Index];


	//Loop invariant: i is the index of the last element of the low side, 
	//and j is the index of the first element being compared with pivot in the unknown region. 
	//Initially, the low side is empty, and the unknown region is the whole array except the pivot.
	int i = -1;
	for (int j = 0; j < Pivot_Index; j++)
	{
		//If the j-th element is smaller than or equal to pivot, 
		//then it should be in the low side, and we need to exchange it with the i+1-th element.
		if (Array[j] <= x)
		{
			//Exchange i+1-th element and jth element.
			i++;
			float temp = Array[i];
			Array[i] = Array[j];
			Array[j] = temp;
		}
	}



	//Insert the pivot element to position between the low side and high side.
	int Middle_Index = i + 1;
	Array[Pivot_Index] = Array[Middle_Index];
	Array[Middle_Index] = x;



	int LowSide_Size = Middle_Index;
	return LowSide_Size;
}



/**
 * @brief
 * Implements randomized quick sort algorithm for sorting an array of floats in ascending order.
 * The pseudo code is from Introduction to algorithm 4th, CLRS, p192, which is RANDOMIZED-QUICKSORT( A , p , r ).
 *
 * @param[in,out]   Array			Pointer to the array of floats to be sorted.
 * @param[in]		Array_Size      The number of elements in the array.
 *
 *
 * @return None.
 *
 * @details
 * Implements the randomized quick sort operation for an array of floats.
 *
 *
 * Time Complexity:  Theta(n log n)		(Average case ; The values of all elements are distinct.)
 *					 Theta(n^2)			(Worst case ; The values of all elements are the same or sorted with distinct values in reverse order.) 
 *					 Theta(n lg n)		(Best case ; The values of all elements are distinct and the pivot divides the array into two equal halves.)
 * 
 * 
 * Space Complexity: Theta(n) (Recursion stack ; Worst case)
 *
 * @pre
 * - The pointer(s) must not be NULL.
 * - Memory must be pre-allocated.
 *
 * @post
 * - The parameter Array is sorted in ascending order.
 *
 * @note
 * - No SIMD optimization.
 * - No qualifiers, which are const, volatile, restrict, and _Atomic( Even a type specifier for a new atomic type ).
 *
 * @warning
 * - Undefined behavior if accessing out of bounds for the pointer(s).
 */
void Randomized_QuickSort(float Array[], int Array_Size)
{
	//Base case: If the array has one or zero elements, it is already sorted.
	if (1 < Array_Size)
	{
	
		//Partition the array into two subarrays: low side and high side, and get the size of low side.
		//The values of all elements in the low side are less than or equal to the pivot, 
		//and the values of all elements in the high side are greater than the pivot.
		int LowSide_Size = Randomized_QuickSort_Partition(Array, Array_Size);


		//Recursively sort the low side and high side subarrays.
		int HighSide_Size = Array_Size - (LowSide_Size + 1);//+1 is number of the pivot element.
		float* HighSide_Array = &Array[LowSide_Size + 1];
		Randomized_QuickSort(Array, LowSide_Size);
		Randomized_QuickSort(HighSide_Array, HighSide_Size);
	}
}




void Call_Randomized_QuickSort(float Array[], int Array_Size)
{
	//Let the initial seed of random number generator be distributed on the interval [0, RAND_MAX] with quickly response of time variant.
	srand((time(NULL) % 10)/(float)9 * RAND_MAX);
	Randomized_QuickSort(Array, Array_Size);
}
