/**
 * @file    Selection_Of_Maximum_Minimum.c
 * @brief
 * Implements selection algorithm for selecting maximum and minimum elements from an array of float.
 * There is no pseudo code on the CLRS textbook, but the algorithm is described in detail from Introduction to Algorithms 4th, CLRS.
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
  * @brief
  * Implements selection algorithm for selecting maximum and minimum elements from an array of float.
  * There is no pseudo code on the CLRS textbook, but the algorithm is from Introduction to algorithm 4th, CLRS, p228, which is described in details.
  *
  *
  * @param[in]		 Array				 The floating values in Array.
  * @param[in]       Array_Size		¡@¡@ The number of elements in Array.
  * @param[out]      Max_Pointer       ¡@The maximum element value of Array.
  * @param[out]      Min_Pointer       ¡@The minimum element value of Array.
  *
  * @return None.
  *
  * @details
  * Implements selection operation.
  *
  *
  * Time Complexity:  Theta( n )	(All cases ; n is the number of elements in Array ; The maximum number of comparison is 3 * floor(n/2). )
  *					  
  *
  *
  * Space Complexity: Theta(1)		(All cases)
  *
  * @pre
  * - The pointer(s) must not be NULL.
  * - Memory must be pre-allocated.
  *
  * @post
  * - Max_Pointer and Min_Pointer get the maximum and minimum element values of Array.
  *
  * @note
  * - No SIMD optimization.
  * - No qualifiers, which are const, volatile, restrict, and _Atomic( Even a type specifier for a new atomic type ).
  *
  * @warning
  * - Undefined behavior if accessing out of bounds for the pointer(s).
  */
void Selection_Of_Maximum_Minimum(float Array[], size_t Array_Size, float* Max_Pointer, float* Min_Pointer)
{
	
	//Total comparison times. If Array_Size is even, counting the compaison for initialization.
	unsigned Number_Of_Comparison = Array_Size / 2; 


	if ((Array_Size % 2) == 0)  //Even number.
	{
		//Initialize the maximum and minimum.
		if (Array[0] > Array[1])
		{
			*Max_Pointer = Array[0];
			*Min_Pointer = Array[1];
		}
		else
		{
			*Max_Pointer = Array[1];
			*Min_Pointer = Array[0];
		}

			
		for (int i = 1; i < Number_Of_Comparison; i++)  
		{
			//Judge the higher and lower element in each pair.
			//Number of comparisons, the comparison for initialization is counted: |_n/2_|
			if (Array[2 * i] > Array[2 * i + 1])
			{
				//Judge the maximum value currently.
				//Number of comparisons in the brackets of both Array[2 * i] > Array[2 * i + 1]) and Array[2 * i] <= Array[2 * i + 1]): (|_n/2_| - 1 )
				if (Array[2 * i] > *Max_Pointer)
				{
					*Max_Pointer = Array[2 * i];
				}

				//Judge the minimum value currently.
				//Number of comparisons in the brackets of both Array[2 * i] > Array[2 * i + 1]) and Array[2 * i] <= Array[2 * i + 1]): (|_n/2_| - 1 )
				if (Array[2 * i + 1] < *Min_Pointer)
				{
					*Min_Pointer = Array[2 * i + 1];
				}

			}
			else
			{
				if (Array[2 * i + 1] > *Max_Pointer)
				{
					*Max_Pointer = Array[2 * i + 1];
				}

				if (Array[2 * i] < *Min_Pointer)
				{
					*Min_Pointer = Array[2 * i];
				}
			}
		}
	}
	else //odd number.
	{
		//Initialize the maximum and minimum.
		*Max_Pointer = Array[0];
		*Min_Pointer = Array[0];


		for (int i = 0; i < Number_Of_Comparison; i++)
		{
			//Judge the higher and lower element in each pair.
			//Number of comparisons, the comparison for initialization is counted: |_n/2_|
			if (Array[2 * i + 1] > Array[2 * i + 2])
			{
				//Judge the maximum value currently.
				//Number of comparisons in the brackets of both Array[2 * i + 1] > Array[2 * i + 2] and Array[2 * i + 1] <= Array[2 * i + 2]: |_n/2_|
				if (Array[2 * i + 1] > *Max_Pointer)
				{
					*Max_Pointer = Array[2 * i + 1];
				}

				//Judge the minimum value currently.
				//Number of comparisons in the brackets of both Array[2 * i + 1] > Array[2 * i + 2] and Array[2 * i + 1] <= Array[2 * i + 2]: |_n/2_|
				if (Array[2 * i + 2] < *Min_Pointer)
				{
					*Min_Pointer = Array[2 * i + 2];
				}
			}
			else
			{
				if (Array[2 * i + 2] > *Max_Pointer)
				{
					*Max_Pointer = Array[2 * i + 2];
				}

				if (Array[2 * i + 1] < *Min_Pointer)
				{
					*Min_Pointer = Array[2 * i + 1];
				}
			}
		}

	}

}



