/**
 * @file    Randomized_Select.c
 * @brief
 * Implements selection algorithm for selecting an element of any order from an array of float.
 * The pseudo code is from Introduction to algorithm 4th, CLRS.
 *
 * @details
 * Implements selection operation.
 *
 *
 * @author  BJ-Lin , the email address is : <s90333125@gmail.com>
 * @date    2026-05-17
 *
 * @version 1.0
 *
 */
#include "..\Header.h"



 /**
¡@* @brief
¡@* Implements ramdomized selection algorithm for selecting an element of any order from an array of float.
¡@* The pseudo code is from Introduction to algorithm 4th, CLRS, p230.
¡@*
¡@*
¡@* @param[in]		Array				The floating values in Array.
¡@* @param[in]      Array_Size		    The number of elements in Array.
¡@* @param[in]      Order				The order of the element to be selected.
¡@*
¡@* @return The value of the element of the specified order in Array.
¡@*
¡@* @details
¡@* Implements selection operation.
¡@* The partition function is three way randomized partition, it is not as same as the partition function on CLRS, p230,
¡@* The situation that all elements are same values is not a worst case anymore.  
¡@* The time complexity of average case is Theta(n), even the values of some elements are not distinct, 
¡@* since the size n of T(n) compared to size n of T(n) of the unmodified algorithm is reduced.
¡@* 
¡@* 
¡@*
¡@* Time Complexity:¡@Theta( n )    (Average case ; n is the number of elements in Array ; The values of all elements are distinct.)
¡@*					¡@Theta( n^2 )  (Worst case ; The values of all elements are distinct, and we always pick the largest/smallest element as the pivot to find the smallest/largest element. The recurrence is T(n) = T(n-1) + Theta(n).)
¡@*					¡@Theta( n )    (Best case ; The values of all elements are the same, or we find out the pivot order as same as the element order to be selected at first time.)
¡@*
¡@* Space Complexity: Theta(1)	  ¡@(All cases)
¡@*
¡@* @pre
¡@* - The pointer(s) must not be NULL.
¡@* - Memory must be pre-allocated.
¡@* - 1 <= Order <= Array_Size.
¡@*
¡@* @post
¡@* - Returns the value of the element of the specified order in Array.
¡@*
¡@* @note
¡@* - No SIMD optimization.
¡@* - No qualifiers, which are const, volatile, restrict, and _Atomic( Even a type specifier for a new atomic type ).
¡@*
¡@* @warning
¡@* - Undefined behavior if accessing out of bounds for the pointer(s).
¡@*/
float Randomized_Select(float Array[], size_t Array_Size, unsigned Order)
{
	//We have the precondition 1 <= Order <= Array_Size. 
	//Base case: If the array has one element, return that element.
	if (Array_Size == 1)
		return Array[0];



	//Partition the array into three subarrays: low side, middle region, and high side. Get the size of low side and high side.
	//The values of all elements in the low side are less than the pivot, 
	//the values of all elements in the middle region are equal to the pivot,
	//and the values of all elements in the high side are greater than the pivot.
	int Low_High_Side_Size[2] = { 0 }; //The size of low side is Low_High_Side_Size[0], and the size of high side is Low_High_Side_Size[1].
	ThreeWay_Randomized_QuickSort_Partition(Array, Array_Size, Low_High_Side_Size);



	//The order of the first element in the middle region, which is also the order of the pivot element.
	int LowestPivotOrder = Low_High_Side_Size[0] + 1; 


	//The order of the last element in the middle region, which is also the order of the pivot element.
	int HighestPivotOrder = Array_Size - Low_High_Side_Size[1];

	//The order of one of the pivot elements is as same as the order of the element to be selected, 
	//so the pivot element is the answer.
	if (Order >= LowestPivotOrder && Order <= HighestPivotOrder)
		return Array[LowestPivotOrder - 1];


	//The order of the element to be selected is lower than the order of the pivot elements, 
	//so the answer is in the low side of the pivot element.
	else if (Order < LowestPivotOrder)
	{
		unsigned LowSide_Size = LowestPivotOrder - 1;
		return Randomized_Select(Array, LowSide_Size, Order);
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
		return Randomized_Select(HighSide_Array, HighSide_Size, NewOrder_In_HighSide);
	}

}


float Call_Randomized_Select(float Array[], size_t Array_Size, unsigned Order)
{
	//Let the initial seed of random number generator be distributed on the interval [0, RAND_MAX] with quickly response of time variant.
	srand((time(NULL) % 10) / (float)9 * RAND_MAX);
	return Randomized_Select(Array, Array_Size, Order);
}