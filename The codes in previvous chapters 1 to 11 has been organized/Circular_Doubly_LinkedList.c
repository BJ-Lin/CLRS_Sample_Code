/**
 * @file    Circular_Doubly_LinkedList.c
 * @brief
 * Implements circular doubly linked list data structure and its operations.
 * The pseudo codes are from Introduction to algorithm 4th, CLRS.
 *
 * @details
 * Implements circular doubly linked list operations.
 *
 *
 * @author  BJ-Lin , the email address is : <s90333125@gmail.com>
 * @date    2026-05-24
 *
 * @version 1.0
 *
 */
#include "..\Header.h"



 /**
  * @brief
  * Implements the circular doubly linked list operation which is to delete an element in the list.
  * The pseudo code is from Introduction to algorithm 4th, CLRS, p262.
  *
  *
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
  * - Delete_Element_Address is removed from the list.
  *
  * @note
  * - No SIMD optimization.
  * - No qualifiers, which are const, volatile, restrict, and _Atomic( Even a type specifier for a new atomic type ).
  *
  * @warning
  * - None.
  */
void Circular_DoublyList_Delete(struct Object2_Tag* Delete_Element_Address)
{
	//Update the address of predecessor for deletion element.
	Delete_Element_Address->Prev->Next = Delete_Element_Address->Next;

	//Update the address of successor for deletion element.
	Delete_Element_Address->Next->Prev = Delete_Element_Address->Prev;
}


/**
 * @brief
 * Implements the doubly linked list operation which is to insert an element in the list.
 * The pseudo code is from Introduction to algorithm 4th, CLRS, p263.
 *
 *
 * @param[in]		  Followed_Obejct_Address	  The element is followed by the new inserted element.
 * @param[in]		  Insertion_Element_Address	  The element to be inserted into the list.
 *
 * @return  None.
 *
 * @details
 * Implements circular doubly linked list operation.
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
 * - Insertion_Element_Address inserted after Followed_Obejct_Address.
 *
 * @note
 * - No SIMD optimization.
 * - No qualifiers, which are const, volatile, restrict, and _Atomic( Even a type specifier for a new atomic type ).
 *
 * @warning
 * - None.
 */
void Circular_DoublyList_Insert(struct Object2_Tag* Followed_Obejct_Address, struct Object2_Tag* Insertion_Element_Address)
{

	//Update the addresses of predecessor and successor for insertion element.
	Insertion_Element_Address->Prev = Followed_Obejct_Address;
	Insertion_Element_Address->Next = Followed_Obejct_Address->Next;  //NULL or the address of next element, in the past.

	//Update Prev of the next element of insertion element before updating Followed_Obejct_Address->Next.
	Followed_Obejct_Address->Next->Prev = Insertion_Element_Address;

	//Update the next pointer of the followed element.
	Followed_Obejct_Address->Next = Insertion_Element_Address;

}





/**
 * @brief
 * Implements the circular doubly linked list operation which is to search an element in the list.
 * The pseudo code is from Introduction to algorithm 4th, CLRS, p263.
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
struct Object2_Tag* Circular_DoublyList_Search(struct CircularLinkedList_Tag* LinkedList_Pointer, int Search_Key)
{
	//Initialize the key of sentinel
	LinkedList_Pointer->Senitel.Key = Search_Key;

	//Search the key in the list until finding out.
	struct Object2_Tag* Target_Object_Address = LinkedList_Pointer->Senitel.Next;
	while (Target_Object_Address->Key != Search_Key)
	{
		Target_Object_Address = Target_Object_Address->Next;
	}

	//If the search stop at the sentinel, the searched element is not found, and the function returns NULL. 
	//Otherwise, it returns the address of the searched element.
	if (Target_Object_Address == &LinkedList_Pointer->Senitel)
	{
		return NULL;
	}
	else
	{
		return Target_Object_Address;
	}
}