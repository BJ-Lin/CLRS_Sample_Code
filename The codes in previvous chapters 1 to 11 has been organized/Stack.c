/**
 * @file    Stack.c
 * @brief
 * Implements stack data structure and its operations.
 * The pseudo codes are from Introduction to algorithm 4th, CLRS.
 *
 * @details
 * Implements stack operations.
 *
 *
 * @author  BJ-Lin , the email address is : <s90333125@gmail.com>
 * @date    2026-05-22
 *
 * @version 1.0
 *
 */
#include "..\Header.h"


struct Stack_Tag Stack = { .Top = -1, .Size = 15 };



/**
 * @brief
 * Implements the stack operation which is to judge whether the stack is empty.
 * The pseudo code is from Introduction to algorithm 4th, CLRS, p255.
 *
 *
 * @param[in]		  Stack_Address				The address of the stack.
 *
 * @return  Return the flag which indicates whether the stack is empty.
 *
 * @details
 * Implements stack operation.
 *
 *
 *
 * Time Complexity: Theta(1)    (All cases)
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
 * - Returns true, if the stack is empty, or returns false, if the stack is not empty.
 *
 * @note
 * - No SIMD optimization.
 * - No qualifiers, which are const, volatile, restrict, and _Atomic( Even a type specifier for a new atomic type ).
 *
 * @warning
 * - Undefined behavior if accessing out of bounds for the pointer(s).
 */
_Bool Stack_Empty(struct Stack_Tag* Stack_Address)
{
	//If the top index is -1, it means there is no element in stack, so it is empty, then return true.
	if (Stack_Address->Top == -1)
		return true;

	//If the top index is not -1, it is not empty, then return false.
	else
		return false;
}




/**
 * @brief
 * Implements the stack operation which is to insert an element into stack.
 * The pseudo code is from Introduction to algorithm 4th, CLRS, p255.
 *
 *
 * @param[in]		  Stack_Address				The address of the stack.
 * @param[in]		  Element					The element to be inserted into the stack.
 *
 * @return  Return the flag which indicates whether the element was successfully inserted into the stack.
 *
 * @details
 * Implements stack operation.
 *
 *
 *
 * Time Complexity: Theta(1)    (All cases)
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
 * - Returns false, if the stack is full, or returns true, if the stack is not full.
 *
 * @note
 * - No SIMD optimization.
 * - No qualifiers, which are const, volatile, restrict, and _Atomic( Even a type specifier for a new atomic type ).
 *
 * @warning
 * - Undefined behavior if accessing out of bounds for the pointer(s).
 */
_Bool Stack_Push(struct Stack_Tag* Stack_Address, struct Object_Tag Element)
{
	//If the top index is equal to the size of stack minus 1, it means there is no space to insert element, so return false for overflow.
	if (Stack_Address->Top == Stack_Address->Size - 1)
	{
		return false; //Overflow
	}

	//If the top index is less than the size of stack minus 1, it means there is space to insert element, so insert element and return true.
	else
	{
		Stack_Address->Top = Stack_Address->Top + 1;
		Stack_Address->Array[Stack_Address->Top] = Element;
		return true; //Successfully insert element into stack.
	}
}



/**
 * @brief
 * Implements the stack operation which is to take an element from the stack.
 * The pseudo code is from Introduction to algorithm 4th, CLRS, p255.
 *
 *
 * @param[in]			  Stack_Address				The address of the stack.
 * @param[in,out]		  Element_Address			The address where the popped element will be stored.
 *
 * @return  Return the flag which indicates whether the element was successfully taken from the stack.
 *
 * @details
 * Implements stack operation.
 *
 *
 *
 * Time Complexity: Theta(1)    ¡@(All cases)
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
 * - Returns false, if the stack is empty, or returns true, if the stack is not empty.
 *
 * @note
 * - No SIMD optimization.
 * - No qualifiers, which are const, volatile, restrict, and _Atomic( Even a type specifier for a new atomic type ).
 *
 * @warning
 * - Undefined behavior if accessing out of bounds for the pointer(s).
 */
_Bool Stack_Pop(struct Stack_Tag* Stack_Address, struct Object_Tag* Element_Address)
{
	//If the stack is empty, it means there is no element to pop, so return false for underflow.
	if (Stack_Empty(Stack_Address))
	{
		return false; //Underflow
	}
	//If the stack is not empty, it means there is an element to pop, so pop the element and return true.
	else
	{
		*Element_Address = Stack_Address->Array[Stack_Address->Top];
		Stack_Address->Top = Stack_Address->Top - 1;
		return true; //Successfully pop element from stack.
	}
}