/**
 * @file    Three_Way_Randomized_Quick_Sort.c
 * @brief
 * Implements 3-way randomized quick sort algorithm for sorting an array of floats in ascending order.
 * There is no pseudo code on the CLRS textbook.
 *
 * @details
 * Implements 3-way randomized quick sort operations.
 * Partition the array into three subarrays: low side, middle region, and high side.
 *
 * @author  BJ-Lin , the email address is : <s90333125@gmail.com>
 * @date    2026-05-11
 *
 * @version 1.0
 *
 */
#include "..\Header.h"





void ThreeWay_Randomized_QuickSort_Partition(float Array[], int Array_Size, int* Low_High_Side_Size)
{
	//Randomly select an pivot index from 0 to Array_Size-1.
	//0 <= rand() / (float)(RAND_MAX+1) < 1  ---> 0 <= (rand() / (float)(RAND_MAX+1)) * Array_Size < Array_Size 
	int RandomPivot_Index = (rand() / (float)(RAND_MAX + 1)) * (Array_Size);


	//Exchange the pivot element with the last element in the array.
	float temp = Array[RandomPivot_Index];
	Array[RandomPivot_Index] = Array[0];
	Array[0] = temp;



	//Assign the first element in the array as pivot.
	int Pivot_Index = 0;
	float x = Array[Pivot_Index];


	//At the beginning, the middle region boundaries are at the pivot index.
	int Middle_Region_Boundary[2] = { Pivot_Index , Pivot_Index }; 


	//Go through the array from the second element to the last element in the unknown region, and compare each element with pivot.
	for (int j = Pivot_Index + 1; j < Array_Size; j++)
	{
		//If the element is less than the pivot, move it to the low side region.
		if (Array[j] < x)
		{
			//Reserve the value of the compared element in the unknown region.
			//Now, Array[j] is empty.
			float ComparedElement = Array[j];

			
			//There are two cases, which are 
			//(1) Move the first element of high side region to the empty location Array[j] 
			//    for making the high side region with right direction displacement, which is one element length.
			//(2) If Array[Middle_Region_Boundary[1] + 1] is Array[j], no high side region, there is still empty.
			Array[j] = Array[Middle_Region_Boundary[1] + 1]; 



			//Move the first element of middle region to the empty location Array[Middle_Region_Boundary[1] + 1] 
			//for making the middle region with right direction displacement, which is one element length.
			Array[Middle_Region_Boundary[1] + 1] = Array[Middle_Region_Boundary[0]]; 


			//Fill the compared element to the empty location Array[Middle_Region_Boundary[0]].
			Array[Middle_Region_Boundary[0]] = ComparedElement;

			//Update the middle region boundaries for making the middle region with right direction displacement, which is one element length.
			Middle_Region_Boundary[0]++;
			Middle_Region_Boundary[1]++;

		}
		//If the element is equal to the pivot, move it to the middle region.
		else if (Array[j] == x)
		{
			//Reserve the value of the compared element in the unknown region.
			//Now, Array[j] is empty.
			float ComparedElement = Array[j];

			//There are two cases, which are 
			//(1) Move the first element of high side region to the empty location Array[j] 
			//    for making the high side region with right direction displacement, which is one element length.
			//(2) If Array[Middle_Region_Boundary[1] + 1] is Array[j], no high side region, there is still empty.
			Array[j] = Array[Middle_Region_Boundary[1] + 1];

			//Fill the compared element to the empty location.
			Array[Middle_Region_Boundary[1] + 1] = ComparedElement;

			Middle_Region_Boundary[1]++;
		}
		else
		{
			//If the element is greater than the pivot, it is already in the high side region, so do nothing.
		}
	}

	//Compute the size of low side and high side for the recursive calls of quick sort.
	Low_High_Side_Size[0] = Middle_Region_Boundary[0];
	Low_High_Side_Size[1] = Array_Size - (Middle_Region_Boundary[1] + 1); //+1 means counnting the index 0 in the sum of low side size and middle region size.


}


/**
 * @brief
 * Implements three way randomized quick sort algorithm for sorting an array of floats in ascending order.
 * There is no pseudo code on the CLRS textbook.
 *
 * @param[in,out]  Array			Pointer to the floats to be sorted.
 * @param[in]		Array_Size      The number of elements in the array.
 *
 *
 * @return None.
 *
 * @details
 * Implements the three way randomized quick sort operation for an array of floats.
 * The situation that all elements are same values is not a worst case anymore. 
 * The time complexity of average case is O(n log n), even the values of some elements are not distinct,
 * since the size n of T(n) compared to size n of T(n) of the unmodified algorithm is reduced.
 * 
 *
 * Time Complexity:  Theta(n log n)		(Average case ; The values of all elements are distinct.)
 *					 Theta(n^2)			(Worst case ; The values of all elements are distinct in reverse order.)
 *					 Theta(n)			(Best case ; The values of all elements are same.)
 * 
 * Space Complexity: Theta(n)			(Recursion stack ; Worst case)
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
void ThreeWay_Randomized_QuickSort(float Array[], int Array_Size)
{
	//Base case: If the array has one or zero elements, it is already sorted.
	if (1 < Array_Size)
	{
		//Partition the array into three subarrays: low side, middle region, and high side. Get the size of low side and high side.
		//The values of all elements in the low side are less than the pivot, 
		//the values of all elements in the middle region are equal to the pivot,
		//and the values of all elements in the high side are greater than the pivot.
		int Low_High_Side_Size[2] = { 0 }; //The size of low side is Low_High_Side_Size[0], and the size of high side is Low_High_Side_Size[1].
		ThreeWay_Randomized_QuickSort_Partition(Array, Array_Size, Low_High_Side_Size);


		float* HighSide_Array = &(Array[Array_Size - Low_High_Side_Size[1]]);


		//Recursively sort the low side and high side subarrays.
		ThreeWay_Randomized_QuickSort(Array, Low_High_Side_Size[0]);
		ThreeWay_Randomized_QuickSort(HighSide_Array, Low_High_Side_Size[1]);

	}

}


void Call_ThreeWay_Randomized_QuickSort(float Array[], int Array_Size)
{
	//Let the initial seed of random number generator be distributed on the interval [0, RAND_MAX] with quickly response of time variant.
	srand((time(NULL) % 10) / (float)9 * RAND_MAX);
	ThreeWay_Randomized_QuickSort(Array, Array_Size);
}
