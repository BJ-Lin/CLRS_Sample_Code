/**
 * @file    Doubly_LinkedList.c
 * @brief
 * Implements doubly linked list data structure and its operations.
 * The pseudo codes are from Introduction to algorithm 4th, CLRS.
 *
 * @details
 * Implements doubly linked list operations.
 *
 *
 * @author  BJ-Lin , the email address is : <s90333125@gmail.com>
 * @date    2026-05-24
 *
 * @version 1.0
 *
 */
#include "..\Header.h"

struct LinkedList_Tag LinkedList = { .Head = NULL,.ObjectCounter = 0 };


/**
 * @brief
 * Implements the doubly linked list operation which is to search an element in the list.
 * The pseudo code is from Introduction to algorithm 4th, CLRS, p260.
 *
 *
 * @param[in]		  LinkedList_Pointer		The address of the linked list.
 * @param[in]		  Search_Key				The key of the element to be searched in the list.
 *
 * @return  Return the address of the searched element.
 *
 * @details
 * Implements doubly linked list operation.
 *
 *
 *
 * Time Complexity:  Theta(n)	  (Worst case)
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
 * - Returns the address of the searched element if found, otherwise returns NULL.
 *
 * @note
 * - No SIMD optimization.
 * - No qualifiers, which are const, volatile, restrict, and _Atomic( Even a type specifier for a new atomic type ).
 *
 * @warning
 * - None.
 */
struct Object2_Tag* DoublyList_Search(struct LinkedList_Tag* LinkedList_Pointer, int Search_Key)
{
	struct Object2_Tag* Target_Object_Address = LinkedList_Pointer->Head;

	//Traverse the list until the searched element is found or the end of the list is reached.
	while (Target_Object_Address != NULL)
	{
		if (Target_Object_Address->Key != Search_Key)
		{
			Target_Object_Address = Target_Object_Address->Next;
		}
		else
		{
			break;
		}

	}

	return Target_Object_Address;
}



/**
 * @brief
 * Implements the doubly linked list operation which is to prepend an element in the list.
 * The pseudo code is from Introduction to algorithm 4th, CLRS, p260.
 *
 *
 * @param[in]		  LinkedList_Pointer		  The address of the linked list.
 * @param[in]		  Insertion_Element_Address	  The element to be inserted into the list.
 *
 * @return  None.
 *
 * @details
 * Implements doubly linked list operation.
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
 * - The linked list with Insertion_Element_Address as the new head, and the number of elements in the list is increased by 1.
 *
 * @note
 * - No SIMD optimization.
 * - No qualifiers, which are const, volatile, restrict, and _Atomic( Even a type specifier for a new atomic type ).
 *
 * @warning
 * - None.
 */
void DoublyList_Prepend(struct LinkedList_Tag* LinkedList_Pointer, struct Object2_Tag* Insertion_Element_Address)
{
	//Update the addresses of predecessor and successor for insertion element.
	Insertion_Element_Address->Prev = NULL;
	Insertion_Element_Address->Next = LinkedList_Pointer->Head;  //NULL or the address of first element, in the past.

	//If there is a first element before prepanding, we need to update Prev of first element before updating LinkedList_Pointer->Head.
	if (LinkedList_Pointer->Head != NULL) 
	{
		LinkedList_Pointer->Head->Prev = Insertion_Element_Address;
	}

	//Update the head pointer in the doubly linked list.
	LinkedList_Pointer->Head = Insertion_Element_Address;

	//Update the number of elements in the doubly linked list.
	LinkedList_Pointer->ObjectCounter++;
}




/**
 * @brief
 * Implements the doubly linked list operation which is to insert an element in the list.
 * The pseudo code is from Introduction to algorithm 4th, CLRS, p261.
 *
 *
 * @param[in]		  LinkedList_Pointer		  The address of the linked list.
 * @param[in]		  Followed_Obejct_Address	  The element is followed by the new inserted element.
 * @param[in]		  Insertion_Element_Address	  The element to be inserted into the list.
 *
 * @return  None.
 *
 * @details
 * Implements doubly linked list operation.
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
 * - The element to be followed must be in the list.
 *
 *
 * @post
 * - Insertion_Element_Address inserted after Followed_Obejct_Address, and the number of elements in the list is increased by 1.
 *
 * @note
 * - No SIMD optimization.
 * - No qualifiers, which are const, volatile, restrict, and _Atomic( Even a type specifier for a new atomic type ).
 *
 * @warning
 * - None.
 */
void DoublyList_Insert(struct LinkedList_Tag* LinkedList_Pointer, struct Object2_Tag* Followed_Obejct_Address, struct Object2_Tag* Insertion_Element_Address)
{
	//Update the addresses of predecessor and successor for insertion element.
	Insertion_Element_Address->Prev = Followed_Obejct_Address;
	Insertion_Element_Address->Next = Followed_Obejct_Address->Next;  //NULL or the address of next element, in the past.


	//If there is a element before insertion, we need to update Prev of the element before updating Followed_Obejct_Address->Next.
	if (Followed_Obejct_Address->Next != NULL) 
	{
		Followed_Obejct_Address->Next->Prev = Insertion_Element_Address;
	}

	//Update the next pointer of the followed element.
	Followed_Obejct_Address->Next = Insertion_Element_Address;

	//Update the number of elements in the linked list.
	LinkedList_Pointer->ObjectCounter++;
}




/**
 * @brief
 * Implements the doubly linked list operation which is to delete an element in the list.
 * The pseudo code is from Introduction to algorithm 4th, CLRS, p261.
 *
 *
 * @param[in]		  LinkedList_Pointer		  The address of the linked list.
 * @param[in]		  Delete_Element_Address	  The element to be deleted from the list.
 *
 * @return  None.
 *
 * @details
 * Implements doubly linked list operation.
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
 * - The element to be deleted must be in the list.
 *
 *
 * @post
 * - Delete_Element_Address is removed from the list, and the number of elements in the list is decreased by 1.
 *
 * @note
 * - No SIMD optimization.
 * - No qualifiers, which are const, volatile, restrict, and _Atomic( Even a type specifier for a new atomic type ).
 *
 * @warning
 * - None.
 */
void DoublyList_Delete(struct LinkedList_Tag* LinkedList_Pointer, struct Object2_Tag* Delete_Element_Address)
{
	//Update the attribute of predecessor of deletion element.
	if (Delete_Element_Address->Prev != NULL)
	{
		Delete_Element_Address->Prev->Next = Delete_Element_Address->Next;
	}
	else
	{
		LinkedList_Pointer->Head = Delete_Element_Address->Next;
	}

	//Update the attribute of successor of deletion element.
	if (Delete_Element_Address->Next != NULL)
	{
		Delete_Element_Address->Next->Prev = Delete_Element_Address->Prev;
	}

	//Update the number of elements in the linked list.
	LinkedList_Pointer->ObjectCounter--;

}