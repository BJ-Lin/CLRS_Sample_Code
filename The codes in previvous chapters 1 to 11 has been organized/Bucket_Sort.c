/**
 * @file    Bucket_Sort.c
 * @brief
 * Implements bucket sort algorithm for sorting an array of float in ascending order.
 * The pseudo code is from Introduction to algorithm 4th, CLRS.
 *
 * @details
 * Implements bucket sort operation.
 *
 *
 * @author  BJ-Lin , the email address is : <s90333125@gmail.com>
 * @date    2026-05-16
 *
 * @version 1.0
 *
 */
#include "..\Header.h"

float Bucket_Numbers[11] = { 0.78,0.17,0.39,0.26,0.72,0.94,0.21,0.12,0.23,0.68,0.99 }; //Value range is on [0,1) for k-bucket


void Bucket_DoublyList_Prepend(struct Bucket_Tag* LinkedList_Pointer, struct Carrier_In_Bucket_Tag* Insertion_Element_Address)
{
	//Update the addresses of predecessor and successor in Insertion Element.
	Insertion_Element_Address->Prev = NULL;
	Insertion_Element_Address->Next = LinkedList_Pointer->head;  //NULL or The address of first element in the past time.


	if (LinkedList_Pointer->head != NULL) //(1)If there is a first element before prepending, we need to update Prev of the first element (2) before covering LinkedList_Pointer->head.
	{
		LinkedList_Pointer->head->Prev = Insertion_Element_Address;
	}

	//Update the head pointer of queue.
	LinkedList_Pointer->head = Insertion_Element_Address;
}


/**
 * @brief
 * Implements bucket sort algorithm for sorting an array of float in ascending order.
 * The pseudo code is from Introduction to algorithm 4th, CLRS, p216, which is BUCKET-SORT( A , n ).
 *
 *
 * @param[in,out]  Array				The elements will be sorted in Array.
 * @param[in]      Array_Size			The number of elements in Array.
 * @param[in]      Bucket_Size          The number of buckets to be used.
 *
 *
 * @return None.
 *
 * @details
 * Implements bucket sort operation.
 *
 *
 * Time Complexity:  Theta( n + k ) + Theta( n^2 ) = Theta( n^2 + k ) = Theta( n^2 )																					  (Worst case ; n is the number of elements in Array, k is the number of buckets, and k is multiple of n, for instance, k = n , 2n, .. e.t.c ; All elements fall into a single bucket.)
 *					 Theta( n + k ) + Theta( k ) = Theta( n + k ) = Theta( n )																							  (Best case ; n is the number of elements in Array, k is the number of buckets, and k is multiple of n, for instance, k = n , 2n, .. e.t.c ; All elements fall into different buckets.)
 *					 Theta( n + k ) + k * Theta( ( n / k )^2 + ( n / k )( 1 - 1 / k ) ) = Theta( n + k ) + Theta( n^2 / k + n ) = Theta( n^2 / k + n + k ) = Theta( n )   (Average case ; n is the number of elements in Array, k is the number of buckets, and k is multiple of n, for instance, k = n , 2n, .. e.t.c ; The elements are uniformly and independently distributed into buckets. The derivation of time complexity is similar to the proof on CLRS text book p217. The time complexity is maximum expected value with maximum time cost of insertion sort, and the other time complexity of minimum expected value not showed up here is also Theta( n ).)
 * 
 * 
 * Space Complexity: Theta(n + k)	(All cases)
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
void Bucket_Sort(float Array[], size_t Array_Size, size_t Bucket_Size)
{
	//Allocate k-buckets address array.
	struct Bucket_Tag* Array_Of_Bucket = (struct Bucket_Tag*)malloc(Bucket_Size * sizeof(struct Bucket_Tag));


	//Initailize the empty bucket lists.
	for (int i = 0; i < Bucket_Size; i++)
	{
		(Array_Of_Bucket + i)->head = NULL;
	}


	//Allocate n-object
	struct Carrier_In_Bucket_Tag* Array_Of_Objects = (struct Carrier_In_Bucket_Tag*)malloc(Array_Size * sizeof(struct Carrier_In_Bucket_Tag));


	//Store A[i] into an object. Insert the object into bucket.
	for (int i = 0; i < Array_Size; i++)
	{
		(Array_Of_Objects+i)->Key = Array[i];
		Bucket_DoublyList_Prepend(Array_Of_Bucket + (unsigned)(Bucket_Size * (Array_Of_Objects + i)->Key), Array_Of_Objects + i);

	}


	//Sort each bucket and concatenate the sorted buckets into Array.
	int Stored_Location = 0;
	for (int i = 0; i < Bucket_Size; i++)
	{
		//Sort the elements in each bucket.
		Insertion_Sort_For_Bucket(Array_Of_Bucket + i);


		//Concatenate the sorted buckets into Array.
		struct Carrier_In_Bucket_Tag* Object_Address = (Array_Of_Bucket+i)->head;//Take the element out of the bucket.
		while (Object_Address != NULL)
		{
			Array[Stored_Location] = Object_Address->Key;

			//Update the address of taken element and the empty location of Array for the next iteration.
			Object_Address = Object_Address->Next;
			Stored_Location++;
		}
	}


	free(Array_Of_Bucket);
	free(Array_Of_Objects);

}

void Bucket_DoublyList_Insert(struct Carrier_In_Bucket_Tag* Followed_Obejct_Address, struct Carrier_In_Bucket_Tag* Insertion_Element_Address)
{
	//Update the addresses of predecessor and successor in Insertion Element.
	Insertion_Element_Address->Prev = Followed_Obejct_Address;
	Insertion_Element_Address->Next = Followed_Obejct_Address->Next;  //NULL or The address of element.


	if (Followed_Obejct_Address->Next != NULL) //(1)If there is a element follow the Followed_Obejct_Address before insertion, we need to update Prev of the element (2) before cover Followed_Obejct_Address->Next.
	{
		Followed_Obejct_Address->Next->Prev = Insertion_Element_Address;
	}

	//Update the head pointer of queue.
	Followed_Obejct_Address->Next = Insertion_Element_Address;

}

void Bucket_DoublyList_Delete(struct Bucket_Tag* LinkedList_Pointer, struct Carrier_In_Bucket_Tag* Delete_Element_Address)
{
	if (Delete_Element_Address->Prev != NULL)
	{
		Delete_Element_Address->Prev->Next = Delete_Element_Address->Next;
	}
	else
	{
		LinkedList_Pointer->head = Delete_Element_Address->Next;
	}

	if (Delete_Element_Address->Next != NULL)
	{
		Delete_Element_Address->Next->Prev = Delete_Element_Address->Prev;
	}

}

void Insertion_Sort_For_Bucket(struct Bucket_Tag* Bucket_Address)
{

	struct Carrier_In_Bucket_Tag* Object_Address = Bucket_Address->head;

	if (Object_Address == NULL)
	{
		//There is no element in the bucket, so there is no need to sort.
		return;
	}
	else
	{
		//Address of second object for sorting.
		Object_Address = Object_Address->Next; 
	}


	struct Carrier_In_Bucket_Tag* Compared_Object_Address = NULL;

	while (Object_Address != NULL)
	{
		float Key = Object_Address->Key;
		Compared_Object_Address = Object_Address->Prev;

		struct Carrier_In_Bucket_Tag* Next_Object_Address = Object_Address->Next;


		while (Compared_Object_Address != NULL )
		{			
			//We put the condition of Compared_Object_Address->Key > Key in the while loop for avoiding the access violation of Compared_Object_Address.
			if (Compared_Object_Address->Key > Key)
			{
				//Exchange Array[j + 1] and Array[j].
				Bucket_DoublyList_Delete(Bucket_Address, Compared_Object_Address);
				Bucket_DoublyList_Insert(Compared_Object_Address->Next, Compared_Object_Address);

				Compared_Object_Address = Compared_Object_Address->Prev->Prev;
			}
			else
			{
				break;
			}
		}

		Object_Address = Next_Object_Address;

	}

}