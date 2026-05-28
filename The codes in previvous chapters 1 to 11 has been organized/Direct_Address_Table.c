/**
 * @file    Direct_Address_Table.c
 * @brief
 * Implements direct address table data structure and its operations.
 * The pseudo codes are from Introduction to algorithm 4th, CLRS.
 *
 * @details
 * Implements direct address table operations.
 *
 *
 * @author  BJ-Lin , the email address is : <s90333125@gmail.com>
 * @date    2026-05-25
 *
 * @version 1.0
 *
 */
#include "..\Header.h"



struct Direct_Address_Object_Tag* AddressTable[10];






/**
 * @brief
 * Implements the direct address table operation which is to search an element in the table.
 * The pseudo code is from Introduction to algorithm 4th, CLRS, p274.
 *
 *
 * @param[in]		  AddressTable				  The direct address table.
 * @param[in]		  Key						  The key of the element to be searched in the table.
 *
 * @return  The element with the specified key, or NULL if not found.
 *
 * @details
 * Implements direct address table operation.
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
 * - The element with the specified key is returned, or NULL if not found.
 *
 * @note
 * - No SIMD optimization.
 * - No qualifiers, which are const, volatile, restrict, and _Atomic( Even a type specifier for a new atomic type ).
 *
 * @warning
 * - Undefined behavior if accessing out of bounds for the pointer(s).
 */
struct Direct_Address_Object_Tag* Direct_Address_Search(struct Direct_Address_Object_Tag** AddressTable, int Key)
{
	return AddressTable[Key];
}




/**
 * @brief
 * Implements the direct address table operation which is to insert an element into the table.
 * The pseudo code is from Introduction to algorithm 4th, CLRS, p274.
 *
 *
 * @param[in]		  AddressTable				  The direct address table.
 * @param[in]		  Insertion_Object_Pointer	  The element to be inserted into the table.
 *
 * @return  None.
 *
 * @details
 * Implements direct address table operation.
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
 * - Insertion_Object_Pointer is inserted into the table.
 *
 * @note
 * - No SIMD optimization.
 * - No qualifiers, which are const, volatile, restrict, and _Atomic( Even a type specifier for a new atomic type ).
 *
 * @warning
 * - None.
 */
void Direct_Address_Insert(struct Direct_Address_Object_Tag** AddressTable, struct Direct_Address_Object_Tag* Insertion_Object_Pointer)
{
	AddressTable[Insertion_Object_Pointer->Key] = Insertion_Object_Pointer;
}







/**
 * @brief
 * Implements the direct address table operation which is to delete an element in the table.
 * The pseudo code is from Introduction to algorithm 4th, CLRS, p274.
 *
 *
 * @param[in]		  AddressTable	  The direct address table.
 * @param[in]		  Deletion_Object_Pointer	  The element to be deleted from the table.
 *
 * @return  None.
 *
 * @details
 * Implements direct address table operation.
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
 * - The element to be deleted must be in the table.
 *
 *
 * @post
 * - Deletion_Object_Pointer is removed from the table.
 *
 * @note
 * - No SIMD optimization.
 * - No qualifiers, which are const, volatile, restrict, and _Atomic( Even a type specifier for a new atomic type ).
 *
 * @warning
 * - None.
 */
void Direct_Address_Delete(struct Direct_Address_Object_Tag** AddressTable, struct Direct_Address_Object_Tag* Deletion_Object_Pointer)
{
	AddressTable[Deletion_Object_Pointer->Key] = NULL;
}