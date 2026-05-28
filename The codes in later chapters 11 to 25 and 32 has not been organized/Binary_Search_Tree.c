#include "..\Header.h"





//Ref:textbook 4th,P322
struct Object_of_BinaryTree_Tag BinaryTree_ObjectArray[9] =
{ [0] .Key = 12,
	[1].Key = 18,
	[2].Key = 15,
	[3].Key = 19,
	[4].Key = 13,
	[5].Key = 17,
	[6].Key = 5,
	[7].Key = 2,
	[8].Key = 9 };

void BinaryTree_Insert(struct BinaryTree_Tag* BinaryTree_Pointer, struct Object_of_BinaryTree_Tag* Insertion_Object_Pointer)
{

	//Find the empty object, and take a record for parent. 
	struct Object_of_BinaryTree_Tag* Compared_Object_Pointer = BinaryTree_Pointer->RootObject_Pointer;
	struct Object_of_BinaryTree_Tag* Parent_of_Compared_Object_Pointer = NULL;


	while (Compared_Object_Pointer != NULL)
	{
		Parent_of_Compared_Object_Pointer = Compared_Object_Pointer; //Given new parent.
		if (Insertion_Object_Pointer->Key < Compared_Object_Pointer->Key) //Given new Compared object.
		{
			Compared_Object_Pointer = Compared_Object_Pointer->LeftObject_Pointer;
		}
		else
		{
			Compared_Object_Pointer = Compared_Object_Pointer->RightObject_Pointer;
		}


	}


	//Make link between Insertion_Object_Pointer and last parent.
	Insertion_Object_Pointer->ParentObject_Pointer = Parent_of_Compared_Object_Pointer;

	if (Parent_of_Compared_Object_Pointer == NULL)
	{
		BinaryTree_Pointer->RootObject_Pointer = Insertion_Object_Pointer;
	}
	else if (Insertion_Object_Pointer->Key < Parent_of_Compared_Object_Pointer->Key)
	{
		Parent_of_Compared_Object_Pointer->LeftObject_Pointer = Insertion_Object_Pointer;
	}
	else
	{
		Parent_of_Compared_Object_Pointer->RightObject_Pointer = Insertion_Object_Pointer;
	}


}
_Bool Inorder_BinaryTree_Walk(struct Object_of_BinaryTree_Tag* Root_Pointer)
{
	if (Root_Pointer == NULL)
	{
		return false; //The meaning is Empty
	}
	else
	{
		Inorder_BinaryTree_Walk(Root_Pointer->LeftObject_Pointer);
		printf("%d ", Root_Pointer->Key);
		Inorder_BinaryTree_Walk(Root_Pointer->RightObject_Pointer);

		return true;//The meaning is Non-Empty
	}

}
struct Object_of_BinaryTree_Tag* Iterative_BinaryTree_Search(struct Object_of_BinaryTree_Tag* Root_Pointer, int Searched_Key)
{
	struct Object_of_BinaryTree_Tag* Compared_Objet_Pointer = Root_Pointer;
	while (Compared_Objet_Pointer != NULL) //Using the criteria to judge the searched key existence for all loop.
	{
		if (Compared_Objet_Pointer->Key != Searched_Key) //Using the criteria to judge the searched key have been searched for all loop.
		{
			if (Searched_Key < Compared_Objet_Pointer->Key)
			{
				Compared_Objet_Pointer = Compared_Objet_Pointer->LeftObject_Pointer;
			}

			else
			{
				Compared_Objet_Pointer = Compared_Objet_Pointer->RightObject_Pointer;
			}
		}
		else
		{
			break;
		}

	}

	return Compared_Objet_Pointer;

}
_Bool BinaryTree_Minimum(struct Object_of_BinaryTree_Tag* Root_Pointer, struct Object_of_BinaryTree_Tag** Address_of_Minimum_Object_Pointer)
{
	*Address_of_Minimum_Object_Pointer = Root_Pointer;

	if (*Address_of_Minimum_Object_Pointer == NULL)
	{
		return false; //Empty Tree
	}

	while ((*Address_of_Minimum_Object_Pointer)->LeftObject_Pointer != NULL) //Test for End Node
	{
		*Address_of_Minimum_Object_Pointer = (*Address_of_Minimum_Object_Pointer)->LeftObject_Pointer;

	}


	return true; //Non-Empty Tree

}
_Bool BinaryTree_Maximum(struct Object_of_BinaryTree_Tag* Root_Pointer, struct Object_of_BinaryTree_Tag** Address_of_Maximum_Object_Pointer)
{
	*Address_of_Maximum_Object_Pointer = Root_Pointer;

	if (*Address_of_Maximum_Object_Pointer == NULL)
	{
		return false; //Empty Tree
	}

	while ((*Address_of_Maximum_Object_Pointer)->RightObject_Pointer != NULL) //Test for End Node
	{
		*Address_of_Maximum_Object_Pointer = (*Address_of_Maximum_Object_Pointer)->RightObject_Pointer;

	}


	return true; //Non-Empty Tree


}
_Bool BinaryTree_Successor(struct Object_of_BinaryTree_Tag* Root_Pointer, struct Object_of_BinaryTree_Tag** Address_of_Successor_Object_Pointer)
{
	if (Root_Pointer == NULL)
	{
		return false;//Empty Tree
	}

	if (Root_Pointer->RightObject_Pointer != NULL)
	{
		BinaryTree_Minimum(Root_Pointer->RightObject_Pointer, Address_of_Successor_Object_Pointer);
		return true; //Non-Empty Tree
	}
	else
	{

		struct Object_of_BinaryTree_Tag* Compared_Parent_Pointer = Root_Pointer->ParentObject_Pointer;
		struct Object_of_BinaryTree_Tag* Compared_Object_Pointer = Root_Pointer;


		while (Compared_Parent_Pointer != NULL) //If Compared_Parent_Pointer is null(Empty), all of objects have been searched, the successor does not exist. 
		{
			if (Compared_Parent_Pointer->RightObject_Pointer == Compared_Object_Pointer)
			{
				Compared_Object_Pointer = Compared_Parent_Pointer;
				Compared_Parent_Pointer = Compared_Object_Pointer->ParentObject_Pointer;
			}
			else
			{
				break;
			}

		}

		*Address_of_Successor_Object_Pointer = Compared_Parent_Pointer;
		return true; //Non-Empty Tree
	}




}
void BinaryTree_Transplant(struct BinaryTree_Tag* BinaryTree_Pointer, struct Object_of_BinaryTree_Tag* Removed_Node_Pointer, struct Object_of_BinaryTree_Tag* Replacing_Node_Pointer)
{
	if (Removed_Node_Pointer->ParentObject_Pointer == NULL)
	{
		BinaryTree_Pointer->RootObject_Pointer = Replacing_Node_Pointer;
	}
	else if (Removed_Node_Pointer->ParentObject_Pointer->LeftObject_Pointer == Removed_Node_Pointer)
	{
		Removed_Node_Pointer->ParentObject_Pointer->LeftObject_Pointer = Replacing_Node_Pointer;
	}
	else
	{
		Removed_Node_Pointer->ParentObject_Pointer->RightObject_Pointer = Replacing_Node_Pointer;
	}

	if (Replacing_Node_Pointer != NULL)
	{
		Replacing_Node_Pointer->ParentObject_Pointer = Removed_Node_Pointer->ParentObject_Pointer;
	}
}
void BinaryTree_Delete(struct BinaryTree_Tag* BinaryTree_Pointer, struct Object_of_BinaryTree_Tag* Removed_Node_Pointer)
{
	if (Removed_Node_Pointer->LeftObject_Pointer == NULL)
	{
		BinaryTree_Transplant(BinaryTree_Pointer, Removed_Node_Pointer, Removed_Node_Pointer->RightObject_Pointer);
	}

	else if (Removed_Node_Pointer->RightObject_Pointer == NULL)
	{
		BinaryTree_Transplant(BinaryTree_Pointer, Removed_Node_Pointer, Removed_Node_Pointer->LeftObject_Pointer);
	}

	else
	{
		//Find the successor of *Removed_Node_Pointer
		struct Object_of_BinaryTree_Tag* Minimum_Object_Pointer;
		BinaryTree_Minimum(Removed_Node_Pointer->RightObject_Pointer, &Minimum_Object_Pointer);

		//If the successor is not on the right side of *Removed_Node_Pointer immediately, we need to connect the two interfaces additionally.
		if (Minimum_Object_Pointer != Removed_Node_Pointer->RightObject_Pointer)
		{
			BinaryTree_Transplant(BinaryTree_Pointer, Minimum_Object_Pointer, (Minimum_Object_Pointer)->RightObject_Pointer);

			//Double direction for linking ; Link the succesor and the right side subtree of removed node.
			(Minimum_Object_Pointer)->RightObject_Pointer = Removed_Node_Pointer->RightObject_Pointer;
			(Minimum_Object_Pointer)->RightObject_Pointer->ParentObject_Pointer = (Minimum_Object_Pointer);
		}

		//Link the succesor and the parent of removed node
		BinaryTree_Transplant(BinaryTree_Pointer, Removed_Node_Pointer, Minimum_Object_Pointer);

		//Double direction for linking ; Link the succesor and the left side subtree of removed node.
		(Minimum_Object_Pointer)->LeftObject_Pointer = Removed_Node_Pointer->LeftObject_Pointer;
		(Minimum_Object_Pointer)->LeftObject_Pointer->ParentObject_Pointer = (Minimum_Object_Pointer);

	}

}
//(1)RotationNode and its right child are not sentinels for the function implementation.
//(2)Handling the link for parent of RotationNode and left child of Elder_RightChild before cover the requiring attributes of RotationNode and Elder_RightChild.
void Left_Rotate_General(struct BinaryTree_Tag* BinaryTree_Pointer, struct Object_of_BinaryTree_Tag* RotationNode_Pointer)
{
	//Assign the right child of RotationNode into local variable.
	struct Object_of_BinaryTree_Tag* Elder_RightChild_Pointer = RotationNode_Pointer->RightObject_Pointer;

	//Assign the sentinel into local variable.
	struct Object_of_BinaryTree_Tag* Sentinel_Pointer = NULL;

	//Doubly link between  RotationNode and new right child.
	RotationNode_Pointer->RightObject_Pointer = Elder_RightChild_Pointer->LeftObject_Pointer;
	if (RotationNode_Pointer->RightObject_Pointer != Sentinel_Pointer)
	{
		RotationNode_Pointer->RightObject_Pointer->ParentObject_Pointer = RotationNode_Pointer;
	}

	//Doubly link between Elder_RightChild_Pointer and new parent.
	Elder_RightChild_Pointer->ParentObject_Pointer = RotationNode_Pointer->ParentObject_Pointer;
	if (RotationNode_Pointer->ParentObject_Pointer == Sentinel_Pointer)
	{
		BinaryTree_Pointer->RootObject_Pointer = Elder_RightChild_Pointer;
	}
	else if (RotationNode_Pointer == RotationNode_Pointer->ParentObject_Pointer->LeftObject_Pointer)
	{
		RotationNode_Pointer->ParentObject_Pointer->LeftObject_Pointer = Elder_RightChild_Pointer;
	}
	else
	{
		RotationNode_Pointer->ParentObject_Pointer->RightObject_Pointer = Elder_RightChild_Pointer;
	}


	//Doubly link between Elder_RightChild_Pointer and RotationNode_Pointer.
	Elder_RightChild_Pointer->LeftObject_Pointer = RotationNode_Pointer;
	RotationNode_Pointer->ParentObject_Pointer = Elder_RightChild_Pointer;

}
void Right_Rotate_General(struct BinaryTree_Tag* BinaryTree_Pointer, struct Object_of_BinaryTree_Tag* RotationNode_Pointer)
{
	//Assign the left child of RotationNode into local variable.
	struct Object_of_BinaryTree_Tag* Elder_LeftChild_Pointer = RotationNode_Pointer->LeftObject_Pointer;

	//Assign the sentinel into local variable.
	struct Object_of_BinaryTree_Tag* Sentinel_Pointer = NULL;

	//Doubly link between  RotationNode and new left child.
	RotationNode_Pointer->LeftObject_Pointer = Elder_LeftChild_Pointer->RightObject_Pointer;
	if (RotationNode_Pointer->LeftObject_Pointer != Sentinel_Pointer)
	{
		RotationNode_Pointer->LeftObject_Pointer->ParentObject_Pointer = RotationNode_Pointer;
	}

	//Doubly link between Elder_LeftChild_Pointer and new parent.
	Elder_LeftChild_Pointer->ParentObject_Pointer = RotationNode_Pointer->ParentObject_Pointer;
	if (RotationNode_Pointer->ParentObject_Pointer == Sentinel_Pointer)
	{
		BinaryTree_Pointer->RootObject_Pointer = Elder_LeftChild_Pointer;
	}
	else if (RotationNode_Pointer == RotationNode_Pointer->ParentObject_Pointer->LeftObject_Pointer)
	{
		RotationNode_Pointer->ParentObject_Pointer->LeftObject_Pointer = Elder_LeftChild_Pointer;
	}
	else
	{
		RotationNode_Pointer->ParentObject_Pointer->RightObject_Pointer = Elder_LeftChild_Pointer;
	}


	//Doubly link between Elder_LeftChild_Pointer and RotationNode_Pointer.
	Elder_LeftChild_Pointer->RightObject_Pointer = RotationNode_Pointer;
	RotationNode_Pointer->ParentObject_Pointer = Elder_LeftChild_Pointer;

}