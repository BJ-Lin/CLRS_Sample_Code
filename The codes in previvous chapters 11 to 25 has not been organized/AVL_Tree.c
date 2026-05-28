#include "..\Header.h"





//Ref:textbook 4th,P322
struct Object_of_AVLTree_Tag AVLTree_ObjectArray[9] =
{ [0] .Key = 12,
	[1].Key = 18,
	[2].Key = 15,
	[3].Key = 19,
	[4].Key = 13,
	[5].Key = 17,
	[6].Key = 5,
	[7].Key = 2,
	[8].Key = 9 };


//Return the height of left child and right child of node y. If the child is NULL, return 0.
void Get_ChildrenHeight(struct Object_of_AVLTree_Tag* Node_y_Pointer, int* RightHeight_Pointer, int* LeftHeight_Pointer)
{
	//Assign the height of right child of node y.
	if (Node_y_Pointer->RightObject_Pointer == NULL)
	{
		*RightHeight_Pointer = 0;
	}
	else
	{
		*RightHeight_Pointer = Node_y_Pointer->RightObject_Pointer->Height;
	}

	//Assign the height of left child of node y.
	if (Node_y_Pointer->LeftObject_Pointer == NULL)
	{
		*LeftHeight_Pointer = 0;
	}
	else
	{
		*LeftHeight_Pointer = Node_y_Pointer->LeftObject_Pointer->Height;
	}


}


//(1)RotationNode and its right child are not sentinels for the function implementation.
//(2)Handling the link for parent of RotationNode and left child of Elder_RightChild before cover the requiring attributes of RotationNode and Elder_RightChild.
void Left_Rotate_AVL(struct AVLTree_Tag* BinaryTree_Pointer, struct Object_of_AVLTree_Tag* RotationNode_Pointer)
{
	//Assign the right child of RotationNode into local variable.
	struct Object_of_AVLTree_Tag* Elder_RightChild_Pointer = RotationNode_Pointer->RightObject_Pointer;

	//Assign the sentinel into local variable.
	struct Object_of_AVLTree_Tag* Sentinel_Pointer = NULL;

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




	//Return the height of left child and right child of rotation node. If the child is NULL, return 0.
	int RightHeight;
	int LeftHeight;
	Get_ChildrenHeight(RotationNode_Pointer, &RightHeight, &LeftHeight);


	//Update the height of rotation node.
	RotationNode_Pointer->Height = 1 + (RightHeight > LeftHeight ? RightHeight : LeftHeight);

	//Return the height of left child and right child of new parent. If the child is NULL, return 0.
	Get_ChildrenHeight(Elder_RightChild_Pointer, &RightHeight, &LeftHeight);

	//Update the height of new parent.
	Elder_RightChild_Pointer->Height = 1 + (RightHeight > LeftHeight ? RightHeight : LeftHeight);

}

void Right_Rotate_AVL(struct AVLTree_Tag* BinaryTree_Pointer, struct Object_of_AVLTree_Tag* RotationNode_Pointer)
{
	//Assign the left child of RotationNode into local variable.
	struct Object_of_AVLTree_Tag* Elder_LeftChild_Pointer = RotationNode_Pointer->LeftObject_Pointer;

	//Assign the sentinel into local variable.
	struct Object_of_AVLTree_Tag* Sentinel_Pointer = NULL;

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



	//Return the height of left child and right child of rotation node. If the child is NULL, return 0.
	int RightHeight;
	int LeftHeight;
	Get_ChildrenHeight(RotationNode_Pointer, &RightHeight, &LeftHeight);


	//Update the height of rotation node.
	RotationNode_Pointer->Height = 1 + (RightHeight > LeftHeight ? RightHeight : LeftHeight);

	//Return the height of left child and right child of new parent. If the child is NULL, return 0.
	Get_ChildrenHeight(Elder_LeftChild_Pointer, &RightHeight, &LeftHeight);

	//Update the height of new parent.
	Elder_LeftChild_Pointer->Height = 1 + (RightHeight > LeftHeight ? RightHeight : LeftHeight);

}

//Ref: Data-structures-and-algorithms-in-C++ , 2nd, Michael T. Goodrich, Roberto Tamassia, David M. Mount, P442~P444
//Node z is unbalanced node, node y is the child of z with the greater height, node x is the child of y with the greater/equal height.
void Restructure(struct AVLTree_Tag* AVLTree_Pointer, struct Object_of_AVLTree_Tag* Node_x_Pointer)
{
	//For instance, RightLeft means the height of right child of node z is greater than the height of left child of node z, 
	//and the height of left child of node y is greater than/equal to the height of right child of node y.
	enum Structure_Tag { RightRight = 0, LeftLeft = 1, RightLeft = 2, LeftRight = 3 } Structure;



	//To get the structure type, we need to get the parent of node x and the grandparent of node x.
	struct Object_of_AVLTree_Tag* Node_y_Pointer = Node_x_Pointer->ParentObject_Pointer;
	struct Object_of_AVLTree_Tag* Node_z_Pointer = Node_y_Pointer->ParentObject_Pointer;


	//To get the structure type, we need to judge the side for node y relative to node z, and the side for node x relative to node y.
	if (Node_y_Pointer == Node_z_Pointer->LeftObject_Pointer)
	{
		if (Node_x_Pointer == Node_y_Pointer->LeftObject_Pointer)
		{
			Structure = LeftLeft;
		}
		else
		{
			Structure = LeftRight;
		}
	}
	else
	{
		if (Node_x_Pointer == Node_y_Pointer->LeftObject_Pointer)
		{
			Structure = RightLeft;
		}
		else
		{
			Structure = RightRight;
		}

	}


	//To restructure the tree, we need to rotate the tree at node z and node y according to the structure type.
	switch (Structure)
	{
	case 0:
		Left_Rotate_AVL(AVLTree_Pointer, Node_z_Pointer);
		break;

	case 1:
		Right_Rotate_AVL(AVLTree_Pointer, Node_z_Pointer);
		break;

	case 2:
		Right_Rotate_AVL(AVLTree_Pointer, Node_y_Pointer);
		Left_Rotate_AVL(AVLTree_Pointer, Node_z_Pointer);
		break;

	case 3:
		Left_Rotate_AVL(AVLTree_Pointer, Node_y_Pointer);
		Right_Rotate_AVL(AVLTree_Pointer, Node_z_Pointer);
		break;
	}


}

//*Height_Difference_Of_Sibling_Pointer = *Node_y_Pointer - *Node_y_Sibling_Pointer, 
// and the height of empty sibling node is 0.
//*Node_y_Pointer and Node_y_Pointer->ParentObject_Pointer are not empty nodes.
void Update_HeightDifference(struct Object_of_AVLTree_Tag* Node_y_Pointer, int* Height_Difference_Of_Sibling_Pointer)
{
	//To get the sibling of node y for calculating the height difference of children of node z.
	struct Object_of_AVLTree_Tag* Node_y_Sibling_Pointer;
	if (Node_y_Pointer->ParentObject_Pointer->RightObject_Pointer == Node_y_Pointer)
	{
		Node_y_Sibling_Pointer = Node_y_Pointer->ParentObject_Pointer->LeftObject_Pointer;
	}
	else
	{
		Node_y_Sibling_Pointer = Node_y_Pointer->ParentObject_Pointer->RightObject_Pointer;
	}

	//To get the height difference of children of node z.
	if (Node_y_Sibling_Pointer != NULL)
	{
		*Height_Difference_Of_Sibling_Pointer = Node_y_Pointer->Height - Node_y_Sibling_Pointer->Height;
	}
	else
	{
		*Height_Difference_Of_Sibling_Pointer = Node_y_Pointer->Height; //The height of empty sibling node is 0.
	}

}


//If node z is unbalanced node, the node y is the child of z with the greater height, node x is the child of y with the greater height.
//We use node y to update the height of parent of node y iteratively until the unbalanced node z is found.
void AVLTree_Insert(struct AVLTree_Tag* BinaryTree_Pointer, struct Object_of_AVLTree_Tag* Insertion_Object_Pointer)
{

	//Find the empty object, and take a record for parent. 
	struct Object_of_AVLTree_Tag* Compared_Object_Pointer = BinaryTree_Pointer->RootObject_Pointer;
	struct Object_of_AVLTree_Tag* Parent_of_Compared_Object_Pointer = NULL;


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






	//The height of new internal node is updated to 1.
	struct Object_of_AVLTree_Tag* Node_y_Pointer = Insertion_Object_Pointer;
	Node_y_Pointer->Height = 1;


	//If the parent of node y is null, the height of tree is 1, and the tree is balanced, so we can return directly.
	if (Node_y_Pointer->ParentObject_Pointer == NULL)
	{
		return;
	}


	//To get the height difference of children of node z.
	int Height_Difference_Of_Sibling;
	Update_HeightDifference(Node_y_Pointer, &Height_Difference_Of_Sibling);



	//Update the height of some ancestors of Insertion_Object_Pointer 
	//until the unbalanced node with | height differnece of children | = 2 or balanced node with | height differnece of children | = 0 for the updated result is found.
	//Time Complexity: O(log n).
	while (Height_Difference_Of_Sibling == 1)
	{
		//The height of parent node is updated.
		Node_y_Pointer->ParentObject_Pointer->Height = Node_y_Pointer->ParentObject_Pointer->Height + 1;


		//Update the node y for the next loop.
		Node_y_Pointer = Node_y_Pointer->ParentObject_Pointer;


		//If the parent of node y for the next loop is null, the height updation is completed, and the tree is balanced, so we can return directly.
		if (Node_y_Pointer->ParentObject_Pointer == NULL)
		{
			return;
		}

		//To get the height difference of children of node z.
		Update_HeightDifference(Node_y_Pointer, &Height_Difference_Of_Sibling);
	}


	//Time Complexity: O(1).
	if (Height_Difference_Of_Sibling == 2)
	{
		struct Object_of_AVLTree_Tag* Node_x_Pointer;

		//The height of node z is updated to the height of node y + 1, which is the height of node y before updating + 2.
		Node_y_Pointer->ParentObject_Pointer->Height++;


		//Return the height of left child and right child of node y. If the child is NULL, return 0.
		int RightHeight;
		int LeftHeight;
		Get_ChildrenHeight(Node_y_Pointer, &RightHeight, &LeftHeight);


		//To get the child node x with greater height.
		if (RightHeight > LeftHeight)
		{
			Node_x_Pointer = Node_y_Pointer->RightObject_Pointer;
		}
		else
		{
			Node_x_Pointer = Node_y_Pointer->LeftObject_Pointer;
		}


		Restructure(BinaryTree_Pointer, Node_x_Pointer);
	}

}



void AVLTree_Transplant(struct AVLTree_Tag* BinaryTree_Pointer, struct Object_of_AVLTree_Tag* Removed_Node_Pointer, struct Object_of_AVLTree_Tag* Replacing_Node_Pointer)
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

_Bool AVLTree_Minimum(struct Object_of_AVLTree_Tag* Root_Pointer, struct Object_of_AVLTree_Tag** Address_of_Minimum_Object_Pointer)
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


//If node z is unbalanced node, the node y is the child of z with the greater height, node x is the child of y with the greater/equal height.
//We use sibling of node y to update the height of parent of node y iteratively until the unbalanced node z is found.
void AVLTree_Delete(struct AVLTree_Tag* BinaryTree_Pointer, struct Object_of_AVLTree_Tag* Removed_Node_Pointer)
{
	//Sibling_of_Node_y_Pointer may be a null pointer, so we create the local variable Parent_of_Node_y_Pointer to record its parent.
	struct Object_of_AVLTree_Tag* Sibling_of_Node_y_Pointer;
	struct Object_of_AVLTree_Tag* Parent_of_Node_y_Pointer;


	if (Removed_Node_Pointer->LeftObject_Pointer == NULL)
	{
		AVLTree_Transplant(BinaryTree_Pointer, Removed_Node_Pointer, Removed_Node_Pointer->RightObject_Pointer);

		//Record the substitute node for the height difference calculation.
		//Sibling_of_Node_y_Pointer may be a null pointer, which means the height of subtree is 0.
		Sibling_of_Node_y_Pointer = Removed_Node_Pointer->RightObject_Pointer;
		Parent_of_Node_y_Pointer = Removed_Node_Pointer->ParentObject_Pointer;
	}

	else if (Removed_Node_Pointer->RightObject_Pointer == NULL)
	{
		AVLTree_Transplant(BinaryTree_Pointer, Removed_Node_Pointer, Removed_Node_Pointer->LeftObject_Pointer);

		//Record the substitute node for the height difference calculation.
		//Sibling_of_Node_y_Pointer is not a null pointer
		Sibling_of_Node_y_Pointer = Removed_Node_Pointer->LeftObject_Pointer;
		Parent_of_Node_y_Pointer = Removed_Node_Pointer->ParentObject_Pointer;
	}

	else
	{
		//Find the successor of *Removed_Node_Pointer
		//Minimum_Object_Pointer is not a null pointer
		struct Object_of_AVLTree_Tag* Minimum_Object_Pointer;
		AVLTree_Minimum(Removed_Node_Pointer->RightObject_Pointer, &Minimum_Object_Pointer);



		//If the successor is not on the right side of *Removed_Node_Pointer immediately, we need to connect the two interfaces additionally.
		if (Minimum_Object_Pointer != Removed_Node_Pointer->RightObject_Pointer)
		{
			//Record the substitute node for the height difference calculation.
			//Sibling_of_Node_y_Pointer may be a null pointer.
			//Parent_of_Node_y_Pointer is not a null pointer
			Sibling_of_Node_y_Pointer = (Minimum_Object_Pointer)->RightObject_Pointer;
			Parent_of_Node_y_Pointer = Minimum_Object_Pointer->ParentObject_Pointer;


			AVLTree_Transplant(BinaryTree_Pointer, Minimum_Object_Pointer, (Minimum_Object_Pointer)->RightObject_Pointer);


			//Double direction for linking ; Link the succesor and the right side subtree of removed node.
			(Minimum_Object_Pointer)->RightObject_Pointer = Removed_Node_Pointer->RightObject_Pointer;
			(Minimum_Object_Pointer)->RightObject_Pointer->ParentObject_Pointer = (Minimum_Object_Pointer);

		}
		else
		{
			//Record the substitute node for the height difference calculation.
			//Sibling_of_Node_y_Pointer may be a null pointer.
			//Parent_of_Node_y_Pointer is not a null pointer.
			Sibling_of_Node_y_Pointer = Minimum_Object_Pointer->RightObject_Pointer;
			Parent_of_Node_y_Pointer = Minimum_Object_Pointer;
		}


		//Link the succesor and the parent of removed node
		AVLTree_Transplant(BinaryTree_Pointer, Removed_Node_Pointer, Minimum_Object_Pointer);

		//Double direction for linking ; Link the succesor and the left side subtree of removed node.
		(Minimum_Object_Pointer)->LeftObject_Pointer = Removed_Node_Pointer->LeftObject_Pointer;
		(Minimum_Object_Pointer)->LeftObject_Pointer->ParentObject_Pointer = (Minimum_Object_Pointer);


		Minimum_Object_Pointer->Height = Removed_Node_Pointer->Height; //The height of moved up node is the same as the height of removed node before deletion.

	}





	//(1)If the parent of node y is null, the root/parent of location is null, we can return directly.
	//(2)We can not use BinaryTree_Pointer->RootObject_Pointer to judge whether the parent of node y is null, 
	//because the root node may be removed, and the new root node may be the substitute node which is node y, 
	//so we need to use Parent_of_Node_y_Pointer to judge whether the parent of node y is null.
	int Height_Difference_Of_Sibling;
	if (Parent_of_Node_y_Pointer == NULL)
	{
		return;
	}
	else//Parent_of_Node_y_Pointer is not null.
	{
		//Return the height of node y and its sibling. If the child is NULL, return 0.
		int RightHeight;
		int LeftHeight;
		Get_ChildrenHeight(Parent_of_Node_y_Pointer, &RightHeight, &LeftHeight);

		if (RightHeight - LeftHeight < 0)
		{
			Height_Difference_Of_Sibling = RightHeight - LeftHeight;
		}
		else
		{
			Height_Difference_Of_Sibling = LeftHeight - RightHeight;
		}
	}

	if (Height_Difference_Of_Sibling == 0)
	{
		//The height of parent node is updated.
		Parent_of_Node_y_Pointer->Height = Parent_of_Node_y_Pointer->Height - 1;



		//From this line in this bracket, we can get the parent of node y from Sibling_of_Node_y_Pointer. Because Sibling_of_Node_y_Pointer would not be a null pointer.
		//If the parent of sibling of node y for the next loop is null, the height updation is completed, and the tree is balanced, so we can return directly.
		Sibling_of_Node_y_Pointer = Parent_of_Node_y_Pointer;//Update the sibling of node y for the next loop.
		if (Sibling_of_Node_y_Pointer->ParentObject_Pointer == NULL)
		{
			return;
		}

		//To get the height difference of children of node z.
		Update_HeightDifference(Sibling_of_Node_y_Pointer, &Height_Difference_Of_Sibling);

	}
	else if (Height_Difference_Of_Sibling == -2)
	{
		struct Object_of_AVLTree_Tag* Node_y_Pointer;
		struct Object_of_AVLTree_Tag* Node_x_Pointer;

		//The height of node y >= 2.
		if (Parent_of_Node_y_Pointer->RightObject_Pointer == Sibling_of_Node_y_Pointer)
		{
			Node_y_Pointer = Parent_of_Node_y_Pointer->LeftObject_Pointer;
		}
		else
		{
			Node_y_Pointer = Parent_of_Node_y_Pointer->RightObject_Pointer;
		}


		//Return the height of left child and right child of node y. If the child is NULL, return 0.
		int RightHeight;
		int LeftHeight;
		Get_ChildrenHeight(Node_y_Pointer, &RightHeight, &LeftHeight);



		//To get the child node x with greater/equal height.
		if (RightHeight > LeftHeight)
		{
			Node_x_Pointer = Node_y_Pointer->RightObject_Pointer;
		}
		else if (RightHeight < LeftHeight)
		{
			Node_x_Pointer = Node_y_Pointer->LeftObject_Pointer;
		}

		//If the height of left child and right child of node y are equal, we can choose any child as node x for the function implementation, and the result is the same.
		//Here we choose the child on the same side as node y relative to node z as node x for the function implementation. The number of rotations for the function implementation is 1, which is the minimum number.
		else
		{
			if (Node_y_Pointer->ParentObject_Pointer->RightObject_Pointer == Node_y_Pointer)
			{
				Node_x_Pointer = Node_y_Pointer->RightObject_Pointer;
			}
			else
			{
				Node_x_Pointer = Node_y_Pointer->LeftObject_Pointer;
			}
		}

		Restructure(BinaryTree_Pointer, Node_x_Pointer);




		//Update the sibling of node y for the next loop.
		if (Node_y_Pointer->ParentObject_Pointer == Node_x_Pointer)
		{
			//The node x is moved up to replace the root z of subtree, so the height difference for the next loop is based on the moved up node x.
			//Update the sibling of node y for the next loop.
			Sibling_of_Node_y_Pointer = Node_x_Pointer;
		}
		else
		{
			//The node y is moved up to replace the root z of subtree, so the height difference for the next loop is based on the moved up node y.
			Sibling_of_Node_y_Pointer = Node_y_Pointer;
		}


		//If the parent of the sibling of node y for the next loop is null, the height updation is completed, and the tree is balanced, so we can return directly.
		if (Sibling_of_Node_y_Pointer->ParentObject_Pointer == NULL)
		{
			return;
		}

		//To get the height difference of children of node z.
		Update_HeightDifference(Sibling_of_Node_y_Pointer, &Height_Difference_Of_Sibling);

	}




	//Update the height of some ancestors of Removed_Node_Pointer 
	//until the balanced node with | height differnece of children | = 1 for the updated result is found.
	//Time Complexity: O(log n).
	while (1)
	{
		if (Height_Difference_Of_Sibling == 0)
		{
			//The height of the parent node is updated.
			Sibling_of_Node_y_Pointer->ParentObject_Pointer->Height = Sibling_of_Node_y_Pointer->ParentObject_Pointer->Height - 1;


			//Update the sibling of node y for the next loop.
			Sibling_of_Node_y_Pointer = Sibling_of_Node_y_Pointer->ParentObject_Pointer;


			//If the parent of sibling of node y for the next loop is null, the height updation is completed, and the tree is balanced, so we can return directly.
			if (Sibling_of_Node_y_Pointer->ParentObject_Pointer == NULL)
			{
				return;
			}

			//To get the height difference of children of node z.
			Update_HeightDifference(Sibling_of_Node_y_Pointer, &Height_Difference_Of_Sibling);
		}
		else if (Height_Difference_Of_Sibling == -2)
		{
			struct Object_of_AVLTree_Tag* Node_y_Pointer;
			struct Object_of_AVLTree_Tag* Node_x_Pointer;


			//The height of node y >= 2.
			if (Sibling_of_Node_y_Pointer->ParentObject_Pointer->RightObject_Pointer == Sibling_of_Node_y_Pointer)
			{
				Node_y_Pointer = Sibling_of_Node_y_Pointer->ParentObject_Pointer->LeftObject_Pointer;
			}
			else
			{
				Node_y_Pointer = Sibling_of_Node_y_Pointer->ParentObject_Pointer->RightObject_Pointer;
			}



			//Return the height of left child and right child of node y. If the child is NULL, return 0.
			int RightHeight;
			int LeftHeight;
			Get_ChildrenHeight(Node_y_Pointer, &RightHeight, &LeftHeight);


			//To get the child node x with greater/equal height.
			if (RightHeight > LeftHeight)
			{
				Node_x_Pointer = Node_y_Pointer->RightObject_Pointer;
			}
			else if (RightHeight < LeftHeight)
			{
				Node_x_Pointer = Node_y_Pointer->LeftObject_Pointer;
			}
			//If the height of left child and right child of node y are equal, we can choose any child as node x for the function implementation, and the result is the same.
			//Here we choose the child on the same side as node y relative to node z as node x for the function implementation. The number of rotations for the function implementation is 1, which is the minimum number.
			else
			{
				if (Node_y_Pointer->ParentObject_Pointer->RightObject_Pointer == Node_y_Pointer)
				{
					Node_x_Pointer = Node_y_Pointer->RightObject_Pointer;
				}
				else
				{
					Node_x_Pointer = Node_y_Pointer->LeftObject_Pointer;
				}
			}

			Restructure(BinaryTree_Pointer, Node_x_Pointer);




			//Update the sibling of node y for the next loop.
			if (Node_y_Pointer->ParentObject_Pointer == Node_x_Pointer)
			{
				//The node x is moved up to replace the root z of subtree, so the height difference for the next loop is based on the moved up node x.
				//Update the sibling of node y for the next loop.
				Sibling_of_Node_y_Pointer = Node_x_Pointer;
			}
			else
			{
				//The node y is moved up to replace the root z of subtree, so the height difference for the next loop is based on the moved up node y.
				Sibling_of_Node_y_Pointer = Node_y_Pointer;
			}


			//If the parent of the sibling of node y for the next loop is null, the height updation is completed, and the tree is balanced, so we can return directly.
			if (Sibling_of_Node_y_Pointer->ParentObject_Pointer == NULL)
			{
				return;
			}

			//To get the height difference of children of node z.
			Update_HeightDifference(Sibling_of_Node_y_Pointer, &Height_Difference_Of_Sibling);
		}
		else//Height_Difference_Of_Sibling == -1
		{
			break;
		}
	}

}




