#include "..\Header.h"




struct SetObject_Tag* General_CreateInit_List(void)
{
	struct SetObject_Tag* SetObject_Pointer = (struct SetObject_Tag*)malloc(sizeof(struct SetObject_Tag));
	SetObject_Pointer->head = NULL;
	SetObject_Pointer->tail = NULL;

	return SetObject_Pointer;
}


void DisjointObject_Prepend(struct SetObject_Tag* SetObject_Pointer, struct DisjointObject_Tag* Insertion_Element_Address)
{
	//Update the tail pointer of list.
	if (SetObject_Pointer->head == NULL)
	{
		SetObject_Pointer->tail = Insertion_Element_Address;
	}


	//Store the addresses of SetObject and successor for Insertion Element
	Insertion_Element_Address->SetObject_Pointer = SetObject_Pointer;
	Insertion_Element_Address->Next = SetObject_Pointer->head;  //NULL or The address of first element in the past time


	//Update the head pointer of list.
	SetObject_Pointer->head = Insertion_Element_Address;


	//Update the pointer to the set object in the set member 
	Insertion_Element_Address->SetMember->SetObject_Pointer = SetObject_Pointer;

}

//Create a set(Linked list), and insert the only object with a set member.  
struct SetObject_Tag* Make_Set(struct SetMember_Tag* SetMember_Pointer)
{
	//Create a linked list and initialize it.
	struct SetObject_Tag* SetObject_Pointer = General_CreateInit_List();


	//Create a disjoint object.
	struct DisjointObject_Tag* DisjointObject_Pointer = (struct DisjointObject_Tag*)malloc(sizeof(struct DisjointObject_Tag));

	//Fill the content into disjoint object.
	DisjointObject_Pointer->SetMember = SetMember_Pointer;

	//Insert the disjoint object.
	DisjointObject_Prepend(SetObject_Pointer, DisjointObject_Pointer);


	return SetObject_Pointer;

}

//Find the set(Linked list) which containing the set member.
struct SetMember_Tag* Find_Set(struct SetMember_Tag* SetMember_Pointer)
{
	//Step1. Back to the set SetObject_Pointer ; Step2. Go to the first object ,and return SetMember
	return SetMember_Pointer->SetObject_Pointer->head->SetMember;

}


struct SetObject_Tag* Union(struct SetMember_Tag* SetMember_Pointer, struct SetMember_Tag* AppendedSetMember_Pointer)
{
	//Assign the set object in the appended list to the local variable;
	struct SetObject_Tag* AppendedSetObject = AppendedSetMember_Pointer->SetObject_Pointer;

	//Assign both the tail object and set object to the local variables;
	struct SetObject_Tag* FollowedSetObject = SetMember_Pointer->SetObject_Pointer;
	struct DisjointObject_Tag* FollowedTail = FollowedSetObject->tail;

	//Union the two sets.
	FollowedTail->Next = AppendedSetObject->head;


	//Update the attributes for each object in the appended linked list.
	struct DisjointObject_Tag* Next = FollowedTail->Next;
	while (Next != NULL)
	{
		//Update the pointers to set for each object.
		Next->SetObject_Pointer = FollowedSetObject;
		Next->SetMember->SetObject_Pointer = FollowedSetObject;

		//Update tail for each loop.
		FollowedSetObject->tail = Next;


		//Update the new checked object.
		Next = Next->Next;

	}

	//Destroy the appended set for disjoint sets property.
	free(AppendedSetObject);

	return FollowedSetObject;
}
