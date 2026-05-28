/**
 * @file    Selection_WorstCase_LinearTime.c
 * @brief
 * Implements selection algorithm for selecting an element of any order from an array of float.
 * The pseudo code is from Introduction to algorithm 4th, CLRS.
 *
 * @details
 * Implements selection operation.
 *
 *
 * @author  BJ-Lin , the email address is : <s90333125@gmail.com>
 * @date    2026-05-22
 *
 * @version 1.0
 *
 */
#include "..\Header.h"




void ThreeWay_Randomized_Partition_Around(float Array[], int Array_Size, float* Pivot_Address, int* Low_High_Side_Size)
{
	//Exchange the pivot element with the last element in the array.
	float temp = *Pivot_Address;
	*Pivot_Address = Array[0];
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
 * Implements linear time selection algorithm in worst case for selecting an element of any order from an array of float.
 * The pseudo code is from Introduction to algorithm 4th, CLRS, p237.
 *
 *
 * @param[in]		Array				The floating values in Array.
 * @param[in]       Array_Size		    The number of elements in Array.
 * @param[in]       Order				The order of the element to be selected.
 *
 * @return The value of the element of the specified order in Array.
 *
 * @details
 * Implements selection operation.
 * The partition function is three way randomized partition, it is not as same as the partition function on CLRS, p237,
 * The situation that all elements are same values is not a worst case anymore.
 * The time complexity of worst case is Theta(n), even the values of some elements are not distinct,
 * since the size n of T(n) compared to size n of T(n) of the unmodified algorithm is reduced.
 *
 *
 *
 * Time Complexity: Theta( n )  (Worst case ; The values of all elements are distinct to make the recurrence T(n) = T(|_n/5_|) + T(7n/10+constant) + Theta(n) existing. The CLRS textbook does not describe the derivation clearly. Then, use Akra-Bazzi method and the polynomial-growth condition to solve the recurrence.)
 *					
 *					
 *
 * Space Complexity: Theta(1)	(All cases)
 *
 * @pre
 * - The pointer(s) must not be NULL.
 * - Memory must be pre-allocated.
 * - 1 <= Order <= Array_Size.
 *
 * @post
 * - Returns the pointer of the element of the specified order in Array.
 *
 * @note
 * - No SIMD optimization.
 * - No qualifiers, which are const, volatile, restrict, and _Atomic( Even a type specifier for a new atomic type ).
 *
 * @warning
 * - Undefined behavior if accessing out of bounds for the pointer(s).
 */
float* Select(float Array[], size_t Array_Size, unsigned Order) 
{

	//Judge if the size of array is divisible by the number of elements in group,
	//if not, sort the first few elements and examin the order wheather it is as same as selected order,
	//to make the size of array divisible by the number of elements in group.
	unsigned Element_Number_Of_Group = 5;
	while (Array_Size % Element_Number_Of_Group != 0)
	{
		//Go through all the elements and find the minimum element in the array, 
		//to place it on the first location.
		for (unsigned j = 1; j < Array_Size; j++)
		{
			if (Array[j] < Array[0])
			{
				float temp = Array[0];
				Array[0] = Array[j];
				Array[j] = temp;
			}
		}

		//Judge if the order of the minimum element is as same as selected order.
		if (Order == 1)
		{
			return Array;
		}

		//Assign the address of next element as the address of first element, 
		//and reduce the size of array by 1, for next iteration.
		Array = Array + 1;
		Array_Size = Array_Size - 1;

		//Update the new order.
		Order = Order - 1;
	}



	//Partition the array into groups of five elements, sort each group.
	unsigned int Group_Number = Array_Size / Element_Number_Of_Group;
	for (int i = 0; i < Group_Number; i++)
	{
		Insertion_Sort_For_Select(Element_Number_Of_Group, Array + i, Group_Number);
	}



	//Recursively call Select to find the median of the group medians.
	unsigned Median_Order_In_Group_Medians = Group_Number - Group_Number / 2;
	float* Pivot_Address = Select(Array + 2 * Group_Number, Group_Number, Median_Order_In_Group_Medians);



	//Partition the array into three subarrays: low side, middle region, and high side. Get the size of low side and high side.
	//The values of all elements in the low side are less than the pivot, 
	//the values of all elements in the middle region are equal to the pivot,
	//and the values of all elements in the high side are greater than the pivot.
	int Low_High_Side_Size[2] = { 0 }; //The size of low side is Low_High_Side_Size[0], and the size of high side is Low_High_Side_Size[1].
	ThreeWay_Randomized_Partition_Around(Array, Array_Size, Pivot_Address, Low_High_Side_Size);



	//The order of the first element in the middle region, which is also the order of the pivot element.
	int LowestPivotOrder = Low_High_Side_Size[0] + 1;


	//The order of the last element in the middle region, which is also the order of the pivot element.
	int HighestPivotOrder = Array_Size - Low_High_Side_Size[1];


	//The order of one of the pivot elements is as same as the order of the element to be selected, 
	//so the pivot element is the answer.
	if (Order >= LowestPivotOrder && Order <= HighestPivotOrder)
	{
		//We can not return Pivot_Address directly, 
		//since the exact location of pivot element may have changed during partitioning.
		return Array + (LowestPivotOrder - 1);
	}

	//The order of the element to be selected is lower than the order of the pivot elements, 
	//so the answer is in the low side of the pivot element.
	else if (Order < LowestPivotOrder)
	{
		unsigned LowSide_Size = LowestPivotOrder - 1;
		return Select(Array, LowSide_Size, Order);
	}

	//The order of the element to be selected is higher than the order of the pivot element, 
	//so the answer is in the high side of the pivot element.
	else
	{
		//Smallest index of high side region = Largest index of middle side region + 1 = Number of elements for low side and middle side.
		//HighestPivotOrder = Number of elements for low side and middle side = Smallest index of high side region.
		unsigned HighSide_Size = Array_Size - HighestPivotOrder;
		float* HighSide_Array = Array + HighestPivotOrder;
		unsigned NewOrder_In_HighSide = Order - HighestPivotOrder;
		return Select(HighSide_Array, HighSide_Size, NewOrder_In_HighSide);
	}

}



void Insertion_Sort_For_Select(int Group_Size, float* Array, unsigned int Group_Number)
{
	for (int i = 1; i < Group_Size; i++)
	{
		float Key = Array[Group_Number * i];
		int j = i - 1;

		while (j >= 0)
		{
			if (Array[Group_Number * j] > Key)
			{
				Array[Group_Number * (j + 1)] = Array[Group_Number * j];
			}
			else
			{
				break;
			}
			
			j = j - 1;
		}

		Array[Group_Number * (j + 1)] = Key;
	}

}


