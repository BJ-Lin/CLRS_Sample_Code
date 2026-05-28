/**
 * @file    Hash_Table.c
 * @brief
 * Implements hash table data structure and its operations.
 * The pseudo codes are from Introduction to algorithm 4th, CLRS.
 *
 * @details
 * Implements hash table operations.
 *
 *
 * @author  BJ-Lin , the email address is : <s90333125@gmail.com>
 * @date    2026-05-25
 *
 * @version 1.0
 *
 */
#include "..\Header.h"



struct UniversalTable_Tag UniversalTable;



/**
 * @brief
 * Implements the hash function which is to compute the hash value for a given key.
 * There is no pseudo code on the CLRS textbook, but the theorem is on CLRS textbook, P289.
 *
 *
 * @param[in]		  Table				  The universal hash table.
 * @param[in]		  ObjectAddress		  The key of the element to be hashed.
 *
 * @return  The hash value for the given key.
 *
 * @details
 * Implements universal hash function operation.
 * The family of hash functions is universal,that the probibility of h(k1)=h(k2) <= 1/m.
 * The random number generator is not good enough, and I only test the expected value of object location which is very close to analytical value(+-1%),
 * so this is only for a sample of hashing.
 * 
 * 
 * Time Complexity:  Theta(1)	  (All cases)
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
 * - The hash value for the given key is returned.
 *
 * @note
 * - No SIMD optimization.
 * - No qualifiers, which are const, volatile, restrict, and _Atomic( Even a type specifier for a new atomic type ).
 *
 * @warning
 * - Undefined behavior if accessing out of bounds for the pointer(s).
 */
int Hash_Function(struct UniversalTable_Tag* Table, struct Object2_Tag* ObjectAddress)
{
	srand(ObjectAddress->Key);

	//The proof of formular from CLRS,4th,P290, I think he use some approximation to approximate collision probility 1/m + 1/(p-1).But he does not explain clearly.
	//So we must make prime number as larger as possible than slot number m for approximating the proberbility ~ 1/m.
	int PrimeNumber = 32749; //32749, which is a prime number.
	int SlotNumber = Table->TableLength; //m is the number of slots in the hash table.
	int a = 1 + (PrimeNumber - 2) * (float)rand() / RAND_MAX; //a is a random integer in the interval [1,p-1]
	int b = (PrimeNumber - 1) * (float)rand() / RAND_MAX; //b is a random integer in the interval [0,p-1]

	int HashValue = ((a * ObjectAddress->Key + b) % PrimeNumber) % SlotNumber; //Hash value in the interval [0,m-1]


	return HashValue;
}



/**
 * @brief
 * Implements the insertion operation which is to insert an element into the hash table.
 * The pseudo code is from Introduction to algorithm 4th, CLRS, P278.
 *
 *
 * @param[in]		  Table							  The universal hash table.
 * @param[in]		  InsertionObject_Address		  The element to be inserted into the hash table.
 *
 * @return  None.
 *
 * @details
 * Implements insertion operation in a chained hash table.
 * 
 *
 * Time Complexity:  Theta(1)	  (All cases)
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
 * - The element is inserted into the hash table.
 * - The element is counted in the linked list of the slot.
 *
 * @note
 * - No SIMD optimization.
 * - No qualifiers, which are const, volatile, restrict, and _Atomic( Even a type specifier for a new atomic type ).
 *
 * @warning
 * - Undefined behavior if accessing out of bounds for the pointer(s).
 */
void Chained_Hash_Insert(struct UniversalTable_Tag* Table, struct Object2_Tag* InsertionObject_Address)
{
	int HashValue = Hash_Function(Table, InsertionObject_Address);


	DoublyList_Prepend(Table->LinkedList + HashValue, InsertionObject_Address);

}





/**
 * @brief
 * Implements the search operation which is to find an element in the hash table.
 * The pseudo code is from Introduction to algorithm 4th, CLRS, P278.
 *
 *
 * @param[in]		  Table							  The universal hash table.
 * @param[in]		  SearchedObject_Address		  The element to be searched in the hash table.
 *
 * @return  The address of the found element.
 *
 * @details
 * Implements search operation in a chained hash table.
 *
 *
 * Time Complexity:  Theta(1)	  (Average case)
 *					 O(n)	      (Worst case)
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
 * - Return the address of the found element, or NULL if not found.
 * 
 *
 * @note
 * - No SIMD optimization.
 * - No qualifiers, which are const, volatile, restrict, and _Atomic( Even a type specifier for a new atomic type ).
 *
 * @warning
 * - Undefined behavior if accessing out of bounds for the pointer(s).
 */
struct Object2_Tag* Chained_Hash_Search(struct UniversalTable_Tag* Table, struct Object2_Tag* SearchedObject_Address)
{
	int HashValue = Hash_Function(Table, SearchedObject_Address);
	return	DoublyList_Search(Table->LinkedList + HashValue, SearchedObject_Address->Key);
}





/**
 * @brief
 * Implements the deletion operation which is to remove an element from the hash table.
 * The pseudo code is from Introduction to algorithm 4th, CLRS, P278.
 *
 *
 * @param[in]		  Table						  The universal hash table.
 * @param[in]		  DeleteObject_Address		  The element to be deleted from the hash table.
 *
 * @return  None.
 *
 * @details
 * Implements deletion operation in a chained hash table.
 *
 *
 * Time Complexity:  Theta(1)	  (All cases)
 *					
 *
 * Space Complexity: Theta(1)	  (All cases)
 *
 * @pre
 * - The pointer(s) must not be NULL.
 * - Memory must be pre-allocated.
 * - The element to be deleted must be in the hash table.
 *
 *
 * @post
 * - The element is removed from the hash table.
 *
 *
 * @note
 * - No SIMD optimization.
 * - No qualifiers, which are const, volatile, restrict, and _Atomic( Even a type specifier for a new atomic type ).
 *
 * @warning
 * - Undefined behavior if accessing out of bounds for the pointer(s).
 */
void Chained_Hash_Delete(struct UniversalTable_Tag* Table, struct Object2_Tag* DeleteObject_Address)
{
	int HashValue = Hash_Function(Table, DeleteObject_Address);

	DoublyList_Delete(Table->LinkedList + HashValue, DeleteObject_Address);
}