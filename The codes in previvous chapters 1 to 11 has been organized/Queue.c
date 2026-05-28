/**
 * @file    Queue.c
 * @brief
 * Implements queue data structure and its operations.
 * The pseudo codes are from Introduction to algorithm 4th, CLRS.
 *
 * @details
 * Implements queue operations.
 *
 *
 * @author  BJ-Lin , the email address is : <s90333125@gmail.com>
 * @date    2026-05-22
 *
 * @version 1.0
 *
 */
#include "..\Header.h"




struct Queue_Tag Queue = { .Head = 0, .Tail = 0, .Size = 15 };



/**
 * @brief
 * Implements the queue operation which is to insert an element into queue.
 * The pseudo code is from Introduction to algorithm 4th, CLRS, p255.
 *
 *
 * @param[in]		  Queue_Address				The address of the queue.
 * @param[in]		  Element_Address			The element to be inserted into the queue.
 *
 * @return  Return the flag which indicates whether the element was successfully inserted into the queue.
 *
 * @details
 * Implements queue operation.
 *
 *
 *
 * Time Complexity:  Theta(1)	  (All cases)
 *
 *
 *
 * Space Complexity: Theta(1)	  (All cases)
 *
 * @pre
 * - The pointer(s) must not be NULL.
 * - Memory must be pre-allocated.
 *
 *
 * @post
 * - Returns false, if the queue is full, or returns true, if the queue is not full.
 *
 * @note
 * - No SIMD optimization.
 * - No qualifiers, which are const, volatile, restrict, and _Atomic( Even a type specifier for a new atomic type ).
 *
 * @warning
 * - None.
 */
_Bool Enqueue(struct Queue_Tag* Queue_Address, struct Object_Tag* Element_Address)
{
	//Judge whether the queue is full by successively indices in two cases.
	if ((Queue_Address->Tail + 1) == Queue_Address->Head)
	{
		return false; //Overflow
	}

	else if ((Queue_Address->Tail == Queue_Address->Size - 1) && (Queue_Address->Head == 0))
	{
		return false; //Overflow
	}
	//If the queue is not full, it means there is space to insert element, so insert element and return true.
	else
	{
		//Insert the object.
		Queue_Address->Array[Queue_Address->Tail] = *Element_Address; 

		//Update the tail index in two cases.
		if (Queue_Address->Tail != Queue_Address->Size - 1)
		{
			Queue_Address->Tail++;
		}
		else
		{
			Queue_Address->Tail = 0;
		}

		return true;
	}
}



/**
 * @brief
 * Implements the queue operation which is to take an element from the queue.
 * The pseudo code is from Introduction to algorithm 4th, CLRS, p255.
 *
 *
 * @param[in]			  Queue_Address				The address of the queue.
 * @param[in,out]		  Element_Address			The address where the dequeued element will be stored.
 *
 * @return  Return the flag which indicates whether the element was successfully taken from the queue.
 *
 * @details
 * Implements queue operation.
 *
 *
 *
 * Time Complexity: Theta(1)    ¡@(All cases)
 *
 *
 *
 * Space Complexity: Theta(1)	  (All cases)
 *
 * @pre
 * - The pointer(s) must not be NULL.
 * - Memory must be pre-allocated.
 *
 *
 * @post
 * - Returns false, if the queue is empty, or returns true, if the queue is not empty.
 *
 * @note
 * - No SIMD optimization.
 * - No qualifiers, which are const, volatile, restrict, and _Atomic( Even a type specifier for a new atomic type ).
 *
 * @warning
 * - None.
 */
_Bool Dequeue(struct Queue_Tag* Queue_Address, struct Object_Tag* Element_Address)
{
	//Judge whether the queue is empty by comparing head and tail indices.
	if (Queue_Address->Head == Queue_Address->Tail)
	{
		return false; //Underflow
	}
	//If the queue is not empty, it means there is an element to dequeue, so take element and return true.
	else
	{
		//Take the object from the queue.
		*Element_Address = Queue_Address->Array[Queue_Address->Head];

		//Update the head index in two cases.
		if (Queue_Address->Head != Queue_Address->Size - 1)
		{
			Queue_Address->Head++;
		}

		else
		{
			Queue_Address->Head = 0;
		}
		return true; //Successfully take element from queue.
	}
}