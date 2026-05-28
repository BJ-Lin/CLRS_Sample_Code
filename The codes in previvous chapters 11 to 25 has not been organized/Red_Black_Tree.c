#include "..\Header.h"




//The tree must be initialized.(ref: textbook 4th ,P322)
struct RedBlackTree_Tag RedBlackTree = { .RootObject_Pointer = &RedBlackTree.RedBlackTree_Sentinel,.RedBlackTree_Sentinel.Color = BLACK };
struct Object_of_RedBlackTree_Tag RedBlackTree_ObjectArray[] = { [0] .Key = 12,[1].Key = 18,[2].Key = 15,[3].Key = 19,[4].Key = 13,[5].Key = 17,[6].Key = 5,[7].Key = 2,[8].Key = 9 };


//(1)RotationNode and its right child are not sentinels for the function implementation.
//(2)Handling the link for parent of RotationNode and left child of Elder_RightChild before cover the requiring attributes of RotationNode and Elder_RightChild.
void Left_Rotate(struct RedBlackTree_Tag* RedBlackTree_Pointer, struct Object_of_RedBlackTree_Tag* RotationNode_Pointer)
{
	//Assign the right child of RotationNode into local variable.
	struct Object_of_RedBlackTree_Tag* Elder_RightChild_Pointer = RotationNode_Pointer->RightObject_Pointer;

	//Assign the sentinel into local variable.
	struct Object_of_RedBlackTree_Tag* Sentinel_Pointer = &RedBlackTree_Pointer->RedBlackTree_Sentinel;

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
		RedBlackTree_Pointer->RootObject_Pointer = Elder_RightChild_Pointer;
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



	//To modify the size 
	Elder_RightChild_Pointer->Size = RotationNode_Pointer->Size;
	RotationNode_Pointer->Size = RotationNode_Pointer->LeftObject_Pointer->Size + RotationNode_Pointer->RightObject_Pointer->Size + 1;


}

void Right_Rotate(struct RedBlackTree_Tag* RedBlackTree_Pointer, struct Object_of_RedBlackTree_Tag* RotationNode_Pointer)
{
	//Assign the left child of RotationNode into local variable.
	struct Object_of_RedBlackTree_Tag* Elder_LeftChild_Pointer = RotationNode_Pointer->LeftObject_Pointer;

	//Assign the sentinel into local variable.
	struct Object_of_RedBlackTree_Tag* Sentinel_Pointer = &RedBlackTree_Pointer->RedBlackTree_Sentinel;

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
		RedBlackTree_Pointer->RootObject_Pointer = Elder_LeftChild_Pointer;
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


	//To modify the size 
	Elder_LeftChild_Pointer->Size = RotationNode_Pointer->Size;
	RotationNode_Pointer->Size = RotationNode_Pointer->LeftObject_Pointer->Size + RotationNode_Pointer->RightObject_Pointer->Size + 1;

}

_Bool Inorder_RedBlackTree_Walk(struct RedBlackTree_Tag* RedBlackTree_Pointer, struct Object_of_RedBlackTree_Tag* Root_Pointer)
{
	//Assign the sentinel into local variable.
	struct Object_of_RedBlackTree_Tag* Sentinel_Pointer = &RedBlackTree_Pointer->RedBlackTree_Sentinel;


	if (Root_Pointer == Sentinel_Pointer)
	{
		return false; //The meaning is Empty
	}
	else
	{
		Inorder_RedBlackTree_Walk(RedBlackTree_Pointer, Root_Pointer->LeftObject_Pointer);
		printf("Key = %d Size=%u\n", Root_Pointer->Key, Root_Pointer->Size);
		Inorder_RedBlackTree_Walk(RedBlackTree_Pointer, Root_Pointer->RightObject_Pointer);

		return true;//The meaning is Non-Empty
	}

}

//(1)This function comfirm the new insertion node to be red and link to sentinel. 
void RB_Insert(struct RedBlackTree_Tag* RedBlackTree_Pointer, struct Object_of_RedBlackTree_Tag* Insertion_Object_Pointer)
{
	//Assign the sentinel into local variable.
	struct Object_of_RedBlackTree_Tag* Sentinel_Pointer = &RedBlackTree_Pointer->RedBlackTree_Sentinel;


	//Find the empty object, and take a record for parent. 
	struct Object_of_RedBlackTree_Tag* Compared_Object_Pointer = RedBlackTree_Pointer->RootObject_Pointer;
	struct Object_of_RedBlackTree_Tag* Parent_of_Compared_Object_Pointer = Sentinel_Pointer;


	Insertion_Object_Pointer->Size = 1;

	while (Compared_Object_Pointer != Sentinel_Pointer)
	{
		Compared_Object_Pointer->Size++;

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

	if (Parent_of_Compared_Object_Pointer == Sentinel_Pointer)
	{
		RedBlackTree_Pointer->RootObject_Pointer = Insertion_Object_Pointer;


	}
	else if (Insertion_Object_Pointer->Key < Parent_of_Compared_Object_Pointer->Key)
	{
		Parent_of_Compared_Object_Pointer->LeftObject_Pointer = Insertion_Object_Pointer;
	}
	else
	{
		Parent_of_Compared_Object_Pointer->RightObject_Pointer = Insertion_Object_Pointer;
	}

	//Additionally compared to binary search tree, it is necessary to link the sentinel.
	Insertion_Object_Pointer->LeftObject_Pointer = Sentinel_Pointer;
	Insertion_Object_Pointer->RightObject_Pointer = Sentinel_Pointer;

	//Make the new insertion node to be red.
	Insertion_Object_Pointer->Color = RED;

	RB_Insert_Fixup(RedBlackTree_Pointer, Insertion_Object_Pointer);
}

void RB_Insert_Fixup(struct RedBlackTree_Tag* RedBlackTree_Pointer, struct Object_of_RedBlackTree_Tag* Insertion_Object_Pointer)
{
	struct Object_of_RedBlackTree_Tag* Uncle_Pointer;

	while (Insertion_Object_Pointer->ParentObject_Pointer->Color == RED)
	{
		if (Insertion_Object_Pointer->ParentObject_Pointer == Insertion_Object_Pointer->ParentObject_Pointer->ParentObject_Pointer->LeftObject_Pointer)
		{
			Uncle_Pointer = Insertion_Object_Pointer->ParentObject_Pointer->ParentObject_Pointer->RightObject_Pointer;

			//Red grandparent exchange color with black parent and black uncle.
			if (Uncle_Pointer->Color == RED)
			{
				Insertion_Object_Pointer->ParentObject_Pointer->Color = BLACK;
				Uncle_Pointer->Color = BLACK;
				Insertion_Object_Pointer->ParentObject_Pointer->ParentObject_Pointer->Color = RED;

				Insertion_Object_Pointer = Insertion_Object_Pointer->ParentObject_Pointer->ParentObject_Pointer;
			}

			else
			{
				if (Insertion_Object_Pointer == Insertion_Object_Pointer->ParentObject_Pointer->RightObject_Pointer)
				{
					Insertion_Object_Pointer = Insertion_Object_Pointer->ParentObject_Pointer;
					Left_Rotate(RedBlackTree_Pointer, Insertion_Object_Pointer);
				}

				Insertion_Object_Pointer->ParentObject_Pointer->Color = BLACK;
				Insertion_Object_Pointer->ParentObject_Pointer->ParentObject_Pointer->Color = RED;
				Right_Rotate(RedBlackTree_Pointer, Insertion_Object_Pointer->ParentObject_Pointer->ParentObject_Pointer);

			}
		}

		else
		{
			Uncle_Pointer = Insertion_Object_Pointer->ParentObject_Pointer->ParentObject_Pointer->LeftObject_Pointer;

			//Red grandparent exchange color with black parent and black uncle.
			if (Uncle_Pointer->Color == RED)
			{
				Insertion_Object_Pointer->ParentObject_Pointer->Color = BLACK;
				Uncle_Pointer->Color = BLACK;
				Insertion_Object_Pointer->ParentObject_Pointer->ParentObject_Pointer->Color = RED;

				//Assign new insertion object for new property-4 violation
				Insertion_Object_Pointer = Insertion_Object_Pointer->ParentObject_Pointer->ParentObject_Pointer;
			}

			else
			{
				if (Insertion_Object_Pointer == Insertion_Object_Pointer->ParentObject_Pointer->LeftObject_Pointer)
				{
					Insertion_Object_Pointer = Insertion_Object_Pointer->ParentObject_Pointer;
					Right_Rotate(RedBlackTree_Pointer, Insertion_Object_Pointer);
				}

				Insertion_Object_Pointer->ParentObject_Pointer->Color = BLACK;
				Insertion_Object_Pointer->ParentObject_Pointer->ParentObject_Pointer->Color = RED;
				Left_Rotate(RedBlackTree_Pointer, Insertion_Object_Pointer->ParentObject_Pointer->ParentObject_Pointer);

			}

		}

	}

	RedBlackTree_Pointer->RootObject_Pointer->Color = BLACK;
}

void RB_Transplant(struct RedBlackTree_Tag* RedBlackTree_Pointer, struct Object_of_RedBlackTree_Tag* Removed_Node_Pointer, struct Object_of_RedBlackTree_Tag* Replacing_Node_Pointer)
{
	struct Object_of_RedBlackTree_Tag* Sentinel_Pointer = &RedBlackTree_Pointer->RedBlackTree_Sentinel;

	if (Removed_Node_Pointer->ParentObject_Pointer == Sentinel_Pointer)
	{
		RedBlackTree_Pointer->RootObject_Pointer = Replacing_Node_Pointer;
	}
	else if (Removed_Node_Pointer == Removed_Node_Pointer->ParentObject_Pointer->LeftObject_Pointer)
	{
		Removed_Node_Pointer->ParentObject_Pointer->LeftObject_Pointer = Replacing_Node_Pointer;
	}
	else
	{
		Removed_Node_Pointer->ParentObject_Pointer->RightObject_Pointer = Replacing_Node_Pointer;
	}

	Replacing_Node_Pointer->ParentObject_Pointer = Removed_Node_Pointer->ParentObject_Pointer;

}

_Bool RB_Minimum(struct RedBlackTree_Tag* RedBlackTree_Pointer, struct Object_of_RedBlackTree_Tag* Root_Pointer, struct Object_of_RedBlackTree_Tag** Address_of_Minimum_Object_Pointer)
{

	//Assign the sentinel into local variable.
	struct Object_of_RedBlackTree_Tag* Sentinel_Pointer = &RedBlackTree_Pointer->RedBlackTree_Sentinel;

	*Address_of_Minimum_Object_Pointer = Root_Pointer;

	if (*Address_of_Minimum_Object_Pointer == Sentinel_Pointer)
	{
		return false; //Empty Tree
	}

	while ((*Address_of_Minimum_Object_Pointer)->LeftObject_Pointer != Sentinel_Pointer) //Test for End Node
	{
		*Address_of_Minimum_Object_Pointer = (*Address_of_Minimum_Object_Pointer)->LeftObject_Pointer;

	}



	return true; //Non-Empty Tree

}

void RB_Delete(struct RedBlackTree_Tag* RedBlackTree_Pointer, struct Object_of_RedBlackTree_Tag* Removed_Node_Pointer)
{

	//Assign the sentinel into local variable.
	struct Object_of_RedBlackTree_Tag* Sentinel_Pointer = &RedBlackTree_Pointer->RedBlackTree_Sentinel;

	//Property : Color of RemovedNode_Pointer is removed from the tree.
	struct Object_of_RedBlackTree_Tag* RemovedNode_Pointer = Removed_Node_Pointer;
	unsigned char Color_Original = RemovedNode_Pointer->Color;

	struct Object_of_RedBlackTree_Tag* Replacing_Node_Pointer;



	struct Object_of_RedBlackTree_Tag* y;
	if (Removed_Node_Pointer->LeftObject_Pointer == Sentinel_Pointer)
	{
		Replacing_Node_Pointer = Removed_Node_Pointer->RightObject_Pointer;
		RB_Transplant(RedBlackTree_Pointer, RemovedNode_Pointer, Replacing_Node_Pointer);


		//Increase the size of each node from original node to root.
		y = Replacing_Node_Pointer->ParentObject_Pointer;
		while (y != Sentinel_Pointer)
		{
			y->Size--;

			//Assign new y
			y = y->ParentObject_Pointer;

		}
	}

	else if (Removed_Node_Pointer->RightObject_Pointer == Sentinel_Pointer)
	{
		Replacing_Node_Pointer = Removed_Node_Pointer->LeftObject_Pointer;
		RB_Transplant(RedBlackTree_Pointer, RemovedNode_Pointer, Replacing_Node_Pointer);


		//Increase the size of each node from original node to root.
		y = Replacing_Node_Pointer->ParentObject_Pointer;
		while (y != Sentinel_Pointer)
		{
			y->Size--;

			//Assign new x and y
			y = y->ParentObject_Pointer;

		}

	}

	else
	{
		//Find the successor of *Removed_Node_Pointer
		RB_Minimum(RedBlackTree_Pointer, Removed_Node_Pointer->RightObject_Pointer, &RemovedNode_Pointer);
		Color_Original = RemovedNode_Pointer->Color;
		Replacing_Node_Pointer = RemovedNode_Pointer->RightObject_Pointer;


		//If the successor is not on the right side of *Removed_Node_Pointer immediately, we need to connect the two interfaces additionally.
		if (RemovedNode_Pointer != Removed_Node_Pointer->RightObject_Pointer)
		{
			RB_Transplant(RedBlackTree_Pointer, RemovedNode_Pointer, RemovedNode_Pointer->RightObject_Pointer);

			//Double direction for linking ; Link the succesor and the right side subtree of removed node.
			RemovedNode_Pointer->RightObject_Pointer = Removed_Node_Pointer->RightObject_Pointer;
			RemovedNode_Pointer->RightObject_Pointer->ParentObject_Pointer = RemovedNode_Pointer;

		}
		else
		{
			Replacing_Node_Pointer->ParentObject_Pointer = RemovedNode_Pointer;
		}

		//Link the succesor and the parent of removed node
		RB_Transplant(RedBlackTree_Pointer, Removed_Node_Pointer, RemovedNode_Pointer);

		//Double direction for linking ; Link the succesor and the left side subtree of removed node.
		RemovedNode_Pointer->LeftObject_Pointer = Removed_Node_Pointer->LeftObject_Pointer;
		RemovedNode_Pointer->LeftObject_Pointer->ParentObject_Pointer = RemovedNode_Pointer;

		//Convert the color of RemovedNode_Pointer to color of Removed_Node_Pointer.
		RemovedNode_Pointer->Color = Removed_Node_Pointer->Color;

		//Inherit the size  
		RemovedNode_Pointer->Size = Removed_Node_Pointer->Size;

		//Increase the size of each node from original node to root.
		y = Replacing_Node_Pointer->ParentObject_Pointer;
		while (y != Sentinel_Pointer)
		{
			y->Size--;

			//Assign new y
			y = y->ParentObject_Pointer;

		}

	}

	if (Color_Original == BLACK)
	{
		RB_Delete_Fixup(RedBlackTree_Pointer, Replacing_Node_Pointer);
	}

}

void RB_Delete_Fixup(struct RedBlackTree_Tag* RedBlackTree_Pointer, struct Object_of_RedBlackTree_Tag* Replacing_Node_Pointer)
{
	struct Object_of_RedBlackTree_Tag* Sibling_of_ReplacingNode_Pointer;

	while (Replacing_Node_Pointer != RedBlackTree_Pointer->RootObject_Pointer && Replacing_Node_Pointer->Color == BLACK)
	{
		if (Replacing_Node_Pointer == Replacing_Node_Pointer->ParentObject_Pointer->LeftObject_Pointer)
		{
			//Assign the sibling of ReplacingNode
			Sibling_of_ReplacingNode_Pointer = Replacing_Node_Pointer->ParentObject_Pointer->RightObject_Pointer;

			if (Sibling_of_ReplacingNode_Pointer == RED)
			{
				Sibling_of_ReplacingNode_Pointer->Color = BLACK;
				Replacing_Node_Pointer->ParentObject_Pointer->Color = RED;
				Left_Rotate(RedBlackTree_Pointer, Replacing_Node_Pointer->ParentObject_Pointer);

				Sibling_of_ReplacingNode_Pointer = Replacing_Node_Pointer->ParentObject_Pointer->RightObject_Pointer;
			}

			if (Sibling_of_ReplacingNode_Pointer->LeftObject_Pointer->Color == BLACK && Sibling_of_ReplacingNode_Pointer->RightObject_Pointer->Color == BLACK)
			{
				//Movde black color up from two nodes for assigning new Replacing_Node_Pointer
				Sibling_of_ReplacingNode_Pointer->Color = RED;
				Replacing_Node_Pointer = Replacing_Node_Pointer->ParentObject_Pointer;

			}
			else
			{
				if (Sibling_of_ReplacingNode_Pointer->RightObject_Pointer->Color == BLACK)
				{
					Sibling_of_ReplacingNode_Pointer->LeftObject_Pointer->Color = BLACK;
					Sibling_of_ReplacingNode_Pointer->Color = RED;
					Right_Rotate(RedBlackTree_Pointer, Sibling_of_ReplacingNode_Pointer);
					Sibling_of_ReplacingNode_Pointer = Replacing_Node_Pointer->ParentObject_Pointer->RightObject_Pointer;
				}

				Sibling_of_ReplacingNode_Pointer->Color = Replacing_Node_Pointer->ParentObject_Pointer->Color;
				Replacing_Node_Pointer->ParentObject_Pointer->Color = BLACK;
				Sibling_of_ReplacingNode_Pointer->RightObject_Pointer->Color = BLACK;

				Left_Rotate(RedBlackTree_Pointer, Replacing_Node_Pointer->ParentObject_Pointer);
				Replacing_Node_Pointer = RedBlackTree_Pointer->RootObject_Pointer;

			}

		}
		else
		{
			//Assign the sibling of ReplacingNode
			Sibling_of_ReplacingNode_Pointer = Replacing_Node_Pointer->ParentObject_Pointer->LeftObject_Pointer;

			if (Sibling_of_ReplacingNode_Pointer->Color == RED)
			{
				Sibling_of_ReplacingNode_Pointer->Color = BLACK;
				Replacing_Node_Pointer->ParentObject_Pointer->Color = RED;
				Right_Rotate(RedBlackTree_Pointer, Replacing_Node_Pointer->ParentObject_Pointer);

				Sibling_of_ReplacingNode_Pointer = Replacing_Node_Pointer->ParentObject_Pointer->LeftObject_Pointer;
			}

			if (Sibling_of_ReplacingNode_Pointer->LeftObject_Pointer->Color == BLACK && Sibling_of_ReplacingNode_Pointer->RightObject_Pointer->Color == BLACK)
			{
				//Movde black color up from two nodes for assigning new Replacing_Node_Pointer
				Sibling_of_ReplacingNode_Pointer->Color = RED;
				Replacing_Node_Pointer = Replacing_Node_Pointer->ParentObject_Pointer;

			}
			else
			{
				if (Sibling_of_ReplacingNode_Pointer->LeftObject_Pointer->Color == BLACK)
				{
					Sibling_of_ReplacingNode_Pointer->RightObject_Pointer->Color = BLACK;
					Sibling_of_ReplacingNode_Pointer->Color = RED;
					Left_Rotate(RedBlackTree_Pointer, Sibling_of_ReplacingNode_Pointer);
					Sibling_of_ReplacingNode_Pointer = Replacing_Node_Pointer->ParentObject_Pointer->LeftObject_Pointer;
				}

				Sibling_of_ReplacingNode_Pointer->Color = Replacing_Node_Pointer->ParentObject_Pointer->Color;
				Replacing_Node_Pointer->ParentObject_Pointer->Color = BLACK;
				Sibling_of_ReplacingNode_Pointer->LeftObject_Pointer->Color = BLACK;

				Right_Rotate(RedBlackTree_Pointer, Replacing_Node_Pointer->ParentObject_Pointer);
				Replacing_Node_Pointer = RedBlackTree_Pointer->RootObject_Pointer;

			}

		}

	}

	Replacing_Node_Pointer->Color = BLACK;
}

_Bool RB_Layout(struct RedBlackTree_Tag* RedBlackTree_Pointer, struct Object_of_RedBlackTree_Tag* Root_Pointer)
{
	//Assign the sentinel into local variable.
	struct Object_of_RedBlackTree_Tag* Sentinel_Pointer = &RedBlackTree_Pointer->RedBlackTree_Sentinel;

	if (Root_Pointer == Sentinel_Pointer)
	{
		printf("Empty Tree\n");
		return false; //The meaning is Empty
	}

	if (Root_Pointer->ParentObject_Pointer == Sentinel_Pointer)
	{
		printf("Empty Parent\n");

	}
	else
	{
		printf("Parent.Key = %d   Parent.Color = %d\n", Root_Pointer->ParentObject_Pointer->Key, Root_Pointer->ParentObject_Pointer->Color);

	}


	if (Root_Pointer->LeftObject_Pointer == Sentinel_Pointer)
	{
		printf("Empty Left_Child\n");

	}
	else
	{
		printf("Left_Child.Key = %d   Left_Child.Color = %d\n", Root_Pointer->LeftObject_Pointer->Key, Root_Pointer->LeftObject_Pointer->Color);

	}

	if (Root_Pointer->RightObject_Pointer == Sentinel_Pointer)
	{
		printf("Empty Right_Child\n");

	}
	else
	{
		printf("Right_Child.Key = %d   Right_Child.Color = %d\n", Root_Pointer->RightObject_Pointer->Key, Root_Pointer->RightObject_Pointer->Color);

	}

	return true;

}




