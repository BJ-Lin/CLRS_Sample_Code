#include "..\Header.h"




//The tree must be initialized.(ref: textbook 4th ,P491)
struct IntervalTree_Tag IntervalTree = { .RootObject_Pointer = &IntervalTree.IntervalTree_Sentinel,.IntervalTree_Sentinel.Color = BLACK ,.IntervalTree_Sentinel.Interval.High = -1 };
struct Object_of_IntervalTree_Tag IntervalTree_ObjectArray[10] = { [0] .Interval.Low = 16,[0].Interval.High = 21,[1].Interval.Low = 8,[1].Interval.High = 9,[2].Interval.Low = 25,[2].Interval.High = 30,[3].Interval.Low = 5,[3].Interval.High = 8,[4].Interval.Low = 15,[4].Interval.High = 23 ,[5].Interval.Low = 17,[5].Interval.High = 19,[6].Interval.Low = 26,[6].Interval.High = 26,[7].Interval.Low = 0,[7].Interval.High = 3,[8].Interval.Low = 6,[8].Interval.High = 10,[9].Interval.Low = 19,[9].Interval.High = 20 };




void IntervalTree_Insert(struct IntervalTree_Tag* IntervalTree_Pointer, struct Object_of_IntervalTree_Tag* Insertion_Object_Pointer)
{
	//Assign the sentinel into local variable.
	struct Object_of_IntervalTree_Tag* Sentinel_Pointer = &IntervalTree_Pointer->IntervalTree_Sentinel;


	//Find the empty object, and take a record for parent. 
	struct Object_of_IntervalTree_Tag* Compared_Object_Pointer = IntervalTree_Pointer->RootObject_Pointer;
	struct Object_of_IntervalTree_Tag* Parent_of_Compared_Object_Pointer = Sentinel_Pointer;

	//Assign the maximum value of insertion object.
	Insertion_Object_Pointer->MaxEndpointValue = Insertion_Object_Pointer->Interval.High;

	while (Compared_Object_Pointer != Sentinel_Pointer)
	{
		//Assign the maximum value of passed object, if the original value is smaller.
		if (Compared_Object_Pointer->MaxEndpointValue < Insertion_Object_Pointer->MaxEndpointValue)
		{
			Compared_Object_Pointer->MaxEndpointValue = Insertion_Object_Pointer->MaxEndpointValue;
		}

		Parent_of_Compared_Object_Pointer = Compared_Object_Pointer; //Given new parent.
		if (Insertion_Object_Pointer->Interval.Low < Compared_Object_Pointer->Interval.Low) //Given new Compared object.
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
		IntervalTree_Pointer->RootObject_Pointer = Insertion_Object_Pointer;


	}
	else if (Insertion_Object_Pointer->Interval.Low < Parent_of_Compared_Object_Pointer->Interval.Low)
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

	IntervalTree_Insert_Fixup(IntervalTree_Pointer, Insertion_Object_Pointer);
}

void IntervalTree_Insert_Fixup(struct IntervalTree_Tag* IntervalTree_Pointer, struct Object_of_IntervalTree_Tag* Insertion_Object_Pointer)
{
	struct Object_of_IntervalTree_Tag* Uncle_Pointer;

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
					IntervalTree_Left_Rotate(IntervalTree_Pointer, Insertion_Object_Pointer);
				}

				Insertion_Object_Pointer->ParentObject_Pointer->Color = BLACK;
				Insertion_Object_Pointer->ParentObject_Pointer->ParentObject_Pointer->Color = RED;
				IntervalTree_Right_Rotate(IntervalTree_Pointer, Insertion_Object_Pointer->ParentObject_Pointer->ParentObject_Pointer);

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
					IntervalTree_Right_Rotate(IntervalTree_Pointer, Insertion_Object_Pointer);
				}

				Insertion_Object_Pointer->ParentObject_Pointer->Color = BLACK;
				Insertion_Object_Pointer->ParentObject_Pointer->ParentObject_Pointer->Color = RED;
				IntervalTree_Left_Rotate(IntervalTree_Pointer, Insertion_Object_Pointer->ParentObject_Pointer->ParentObject_Pointer);

			}

		}

	}

	IntervalTree_Pointer->RootObject_Pointer->Color = BLACK;
}

void IntervalTree_Left_Rotate(struct IntervalTree_Tag* IntervalTree_Pointer, struct Object_of_IntervalTree_Tag* RotationNode_Pointer)
{
	//Assign the right child of RotationNode into local variable.
	struct Object_of_IntervalTree_Tag* Elder_RightChild_Pointer = RotationNode_Pointer->RightObject_Pointer;

	//Assign the sentinel into local variable.
	struct Object_of_IntervalTree_Tag* Sentinel_Pointer = &IntervalTree_Pointer->IntervalTree_Sentinel;

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
		IntervalTree_Pointer->RootObject_Pointer = Elder_RightChild_Pointer;
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


	//Assign the new maximum endpoint value after rotation.
	Elder_RightChild_Pointer->MaxEndpointValue = RotationNode_Pointer->MaxEndpointValue;

	RotationNode_Pointer->MaxEndpointValue = RotationNode_Pointer->Interval.High; //Assign default maximum value for successive comparisons.
	if (RotationNode_Pointer->MaxEndpointValue < RotationNode_Pointer->LeftObject_Pointer->MaxEndpointValue)
	{
		RotationNode_Pointer->MaxEndpointValue = RotationNode_Pointer->LeftObject_Pointer->MaxEndpointValue;
	}
	if (RotationNode_Pointer->MaxEndpointValue < RotationNode_Pointer->RightObject_Pointer->MaxEndpointValue)
	{
		RotationNode_Pointer->MaxEndpointValue = RotationNode_Pointer->RightObject_Pointer->MaxEndpointValue;
	}


}

void IntervalTree_Right_Rotate(struct IntervalTree_Tag* IntervalTree_Pointer, struct Object_of_IntervalTree_Tag* RotationNode_Pointer)
{
	//Assign the left child of RotationNode into local variable.
	struct Object_of_IntervalTree_Tag* Elder_LeftChild_Pointer = RotationNode_Pointer->LeftObject_Pointer;

	//Assign the sentinel into local variable.
	struct Object_of_IntervalTree_Tag* Sentinel_Pointer = &IntervalTree_Pointer->IntervalTree_Sentinel;

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
		IntervalTree_Pointer->RootObject_Pointer = Elder_LeftChild_Pointer;
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


	//Assign the new maximum endpoint value after rotation.
	Elder_LeftChild_Pointer->MaxEndpointValue = RotationNode_Pointer->MaxEndpointValue;

	RotationNode_Pointer->MaxEndpointValue = RotationNode_Pointer->Interval.High; //Assign default maximum value for successive comparisons.
	if (RotationNode_Pointer->MaxEndpointValue < RotationNode_Pointer->LeftObject_Pointer->MaxEndpointValue)
	{
		RotationNode_Pointer->MaxEndpointValue = RotationNode_Pointer->LeftObject_Pointer->MaxEndpointValue;
	}
	if (RotationNode_Pointer->MaxEndpointValue < RotationNode_Pointer->RightObject_Pointer->MaxEndpointValue)
	{
		RotationNode_Pointer->MaxEndpointValue = RotationNode_Pointer->RightObject_Pointer->MaxEndpointValue;
	}


}

_Bool IntervalTree_Layout(struct IntervalTree_Tag* IntervalTree_Pointer, struct Object_of_IntervalTree_Tag* Root_Pointer)
{
	//Assign the sentinel into local variable.
	struct Object_of_IntervalTree_Tag* Sentinel_Pointer = &IntervalTree_Pointer->IntervalTree_Sentinel;

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
		printf("Parent.Key = %d   Parent.Color = %d\n", Root_Pointer->ParentObject_Pointer->Interval.Low, Root_Pointer->ParentObject_Pointer->Color);

	}


	if (Root_Pointer->LeftObject_Pointer == Sentinel_Pointer)
	{
		printf("Empty Left_Child\n");

	}
	else
	{
		printf("Left_Child.Key = %d   Left_Child.Color = %d\n", Root_Pointer->LeftObject_Pointer->Interval.Low, Root_Pointer->LeftObject_Pointer->Color);

	}

	if (Root_Pointer->RightObject_Pointer == Sentinel_Pointer)
	{
		printf("Empty Right_Child\n");

	}
	else
	{
		printf("Right_Child.Key = %d   Right_Child.Color = %d\n", Root_Pointer->RightObject_Pointer->Interval.Low, Root_Pointer->RightObject_Pointer->Color);

	}
	return true;
}



void IntervalTree_Transplant(struct IntervalTree_Tag* IntervalTree_Pointer, struct Object_of_IntervalTree_Tag* Removed_Node_Pointer, struct Object_of_IntervalTree_Tag* Replacing_Node_Pointer)
{
	struct Object_of_IntervalTree_Tag* Sentinel_Pointer = &IntervalTree_Pointer->IntervalTree_Sentinel;

	if (Removed_Node_Pointer->ParentObject_Pointer == Sentinel_Pointer)
	{
		IntervalTree_Pointer->RootObject_Pointer = Replacing_Node_Pointer;
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

_Bool IntervalTree_Minimum(struct IntervalTree_Tag* IntervalTree_Pointer, struct Object_of_IntervalTree_Tag* Root_Pointer, struct Object_of_IntervalTree_Tag** Address_of_Minimum_Object_Pointer)
{

	//Assign the sentinel into local variable.
	struct Object_of_IntervalTree_Tag* Sentinel_Pointer = &IntervalTree_Pointer->IntervalTree_Sentinel;

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

void IntervalTree_Delete(struct IntervalTree_Tag* IntervalTree_Pointer, struct Object_of_IntervalTree_Tag* Removed_Node_Pointer)
{

	//Assign the sentinel into local variable.
	struct Object_of_IntervalTree_Tag* Sentinel_Pointer = &IntervalTree_Pointer->IntervalTree_Sentinel;

	//Property : Color of RemovedNode_Pointer is removed from the tree.
	struct Object_of_IntervalTree_Tag* RemovedNode_Pointer = Removed_Node_Pointer;
	unsigned char Color_Original = RemovedNode_Pointer->Color;

	struct Object_of_IntervalTree_Tag* Replacing_Node_Pointer;


	struct Object_of_IntervalTree_Tag* x;
	struct Object_of_IntervalTree_Tag* y;
	if (Removed_Node_Pointer->LeftObject_Pointer == Sentinel_Pointer)
	{
		Replacing_Node_Pointer = Removed_Node_Pointer->RightObject_Pointer;
		IntervalTree_Transplant(IntervalTree_Pointer, RemovedNode_Pointer, Replacing_Node_Pointer);


		//Update the maximum endpoint value from initial position to the root.
		y = Replacing_Node_Pointer->ParentObject_Pointer;

		int Original_Value;
		while (y != Sentinel_Pointer)
		{
			Original_Value = y->MaxEndpointValue;
			//Compute the new maximum endpoint value.
			y->MaxEndpointValue = y->Interval.High; //Assign default maximum value for successive comparisons.
			if (y->MaxEndpointValue < y->LeftObject_Pointer->MaxEndpointValue)
			{
				y->MaxEndpointValue = y->LeftObject_Pointer->MaxEndpointValue;
			}
			if (y->MaxEndpointValue < y->RightObject_Pointer->MaxEndpointValue)
			{
				y->MaxEndpointValue = y->RightObject_Pointer->MaxEndpointValue;
			}

			if (y->MaxEndpointValue == Original_Value)
			{
				break;
			}


			//Assign new y
			y = y->ParentObject_Pointer;
		}

	}

	else if (Removed_Node_Pointer->RightObject_Pointer == Sentinel_Pointer)
	{
		Replacing_Node_Pointer = Removed_Node_Pointer->LeftObject_Pointer;
		IntervalTree_Transplant(IntervalTree_Pointer, RemovedNode_Pointer, Replacing_Node_Pointer);


		//Update the maximum endpoint value from initial position to the root.
		y = Replacing_Node_Pointer->ParentObject_Pointer;



		int Original_Value;
		while (y != Sentinel_Pointer)
		{
			Original_Value = y->MaxEndpointValue;
			//Compute the new maximum endpoint value.
			y->MaxEndpointValue = y->Interval.High; //Assign default maximum value for successive comparisons.
			if (y->MaxEndpointValue < y->LeftObject_Pointer->MaxEndpointValue)
			{
				y->MaxEndpointValue = y->LeftObject_Pointer->MaxEndpointValue;
			}
			if (y->MaxEndpointValue < y->RightObject_Pointer->MaxEndpointValue)
			{
				y->MaxEndpointValue = y->RightObject_Pointer->MaxEndpointValue;
			}

			if (y->MaxEndpointValue == Original_Value)
			{
				break;
			}

			//Assign new y
			y = y->ParentObject_Pointer;
		}



	}

	else
	{
		//Find the successor of *Removed_Node_Pointer.
		IntervalTree_Minimum(IntervalTree_Pointer, Removed_Node_Pointer->RightObject_Pointer, &RemovedNode_Pointer);
		Color_Original = RemovedNode_Pointer->Color;
		Replacing_Node_Pointer = RemovedNode_Pointer->RightObject_Pointer;


		//If the successor is not on the right side of *Removed_Node_Pointer immediately, we need to connect the two interfaces additionally.
		if (RemovedNode_Pointer != Removed_Node_Pointer->RightObject_Pointer)
		{
			IntervalTree_Transplant(IntervalTree_Pointer, RemovedNode_Pointer, RemovedNode_Pointer->RightObject_Pointer);

			//Double direction for linking ; Link the succesor and the right side subtree of removed node.
			RemovedNode_Pointer->RightObject_Pointer = Removed_Node_Pointer->RightObject_Pointer;
			RemovedNode_Pointer->RightObject_Pointer->ParentObject_Pointer = RemovedNode_Pointer;

		}
		else
		{
			Replacing_Node_Pointer->ParentObject_Pointer = RemovedNode_Pointer;
		}

		//Link the succesor and the parent of removed node.
		IntervalTree_Transplant(IntervalTree_Pointer, Removed_Node_Pointer, RemovedNode_Pointer);

		//Double direction for linking ; Link the succesor and the left side subtree of removed node.
		RemovedNode_Pointer->LeftObject_Pointer = Removed_Node_Pointer->LeftObject_Pointer;
		RemovedNode_Pointer->LeftObject_Pointer->ParentObject_Pointer = RemovedNode_Pointer;

		//Convert the color of RemovedNode_Pointer to color of Removed_Node_Pointer.
		RemovedNode_Pointer->Color = Removed_Node_Pointer->Color;

		//Update the maximum endpoint value from initial position to the root.
		y = Replacing_Node_Pointer->ParentObject_Pointer;

		//Preserve the maximum endpoint value of removed node pointer for that if the computation of the maximum endpoint value keep going.
		RemovedNode_Pointer->MaxEndpointValue = Removed_Node_Pointer->MaxEndpointValue;


		int Original_Value;
		int Counter = 0;
		while (y != Sentinel_Pointer)
		{
			Original_Value = y->MaxEndpointValue;

			//Compute the new maximum endpoint value.
			y->MaxEndpointValue = y->Interval.High; //Assign default maximum value for successive comparisons.
			if (y->MaxEndpointValue < y->LeftObject_Pointer->MaxEndpointValue)
			{
				y->MaxEndpointValue = y->LeftObject_Pointer->MaxEndpointValue;
			}
			if (y->MaxEndpointValue < y->RightObject_Pointer->MaxEndpointValue)
			{
				y->MaxEndpointValue = y->RightObject_Pointer->MaxEndpointValue;
			}

			//Assign new y and preserve old y to x
			x = y;
			y = y->ParentObject_Pointer;
			if (x->MaxEndpointValue == Original_Value && Counter == 0)
			{
				Counter++;
				y = RemovedNode_Pointer;
			}
			else if (x->MaxEndpointValue == Original_Value && Counter == 1)
			{
				Counter++;
				break;

			}


		}

	}

	if (Color_Original == BLACK)
	{
		IntervalTree_Delete_Fixup(IntervalTree_Pointer, Replacing_Node_Pointer);
	}

}

void IntervalTree_Delete_Fixup(struct IntervalTree_Tag* IntervalTree_Pointer, struct Object_of_IntervalTree_Tag* Replacing_Node_Pointer)
{
	struct Object_of_IntervalTree_Tag* Sibling_of_ReplacingNode_Pointer;

	while (Replacing_Node_Pointer != IntervalTree_Pointer->RootObject_Pointer && Replacing_Node_Pointer->Color == BLACK)
	{
		if (Replacing_Node_Pointer == Replacing_Node_Pointer->ParentObject_Pointer->LeftObject_Pointer)
		{
			//Assign the sibling of ReplacingNode
			Sibling_of_ReplacingNode_Pointer = Replacing_Node_Pointer->ParentObject_Pointer->RightObject_Pointer;

			if (Sibling_of_ReplacingNode_Pointer == RED)
			{
				Sibling_of_ReplacingNode_Pointer->Color = BLACK;
				Replacing_Node_Pointer->ParentObject_Pointer->Color = RED;
				IntervalTree_Left_Rotate(IntervalTree_Pointer, Replacing_Node_Pointer->ParentObject_Pointer);

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
					IntervalTree_Right_Rotate(IntervalTree_Pointer, Sibling_of_ReplacingNode_Pointer);
					Sibling_of_ReplacingNode_Pointer = Replacing_Node_Pointer->ParentObject_Pointer->RightObject_Pointer;
				}

				Sibling_of_ReplacingNode_Pointer->Color = Replacing_Node_Pointer->ParentObject_Pointer->Color;
				Replacing_Node_Pointer->ParentObject_Pointer->Color = BLACK;
				Sibling_of_ReplacingNode_Pointer->RightObject_Pointer->Color = BLACK;

				IntervalTree_Left_Rotate(IntervalTree_Pointer, Replacing_Node_Pointer->ParentObject_Pointer);
				Replacing_Node_Pointer = IntervalTree_Pointer->RootObject_Pointer;

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
				IntervalTree_Right_Rotate(IntervalTree_Pointer, Replacing_Node_Pointer->ParentObject_Pointer);

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
					IntervalTree_Left_Rotate(IntervalTree_Pointer, Sibling_of_ReplacingNode_Pointer);
					Sibling_of_ReplacingNode_Pointer = Replacing_Node_Pointer->ParentObject_Pointer->LeftObject_Pointer;
				}

				Sibling_of_ReplacingNode_Pointer->Color = Replacing_Node_Pointer->ParentObject_Pointer->Color;
				Replacing_Node_Pointer->ParentObject_Pointer->Color = BLACK;
				Sibling_of_ReplacingNode_Pointer->LeftObject_Pointer->Color = BLACK;

				IntervalTree_Right_Rotate(IntervalTree_Pointer, Replacing_Node_Pointer->ParentObject_Pointer);
				Replacing_Node_Pointer = IntervalTree_Pointer->RootObject_Pointer;

			}

		}

	}

	Replacing_Node_Pointer->Color = BLACK;
}




struct Interval_Tag Interval_Object = { 2,5 };

void Interval_Search(struct IntervalTree_Tag* IntervalTree_Pointer, struct Interval_Tag* Interval_Pointer)
{
	struct Object_of_IntervalTree_Tag* Sentinel = &IntervalTree_Pointer->IntervalTree_Sentinel;
	struct Object_of_IntervalTree_Tag* ComparedObject_Pointer = IntervalTree_Pointer->RootObject_Pointer;
	int Criteria1;
	int Criteria2;

	while (ComparedObject_Pointer != Sentinel && ((Interval_Pointer->High < ComparedObject_Pointer->Interval.Low) || (Interval_Pointer->Low > ComparedObject_Pointer->Interval.High)))
	{
		Criteria1 = ComparedObject_Pointer->LeftObject_Pointer != Sentinel;
		Criteria2 = ComparedObject_Pointer->LeftObject_Pointer->MaxEndpointValue >= Interval_Pointer->Low;
		if (Criteria1 && Criteria2)
		{
			ComparedObject_Pointer = ComparedObject_Pointer->LeftObject_Pointer;
		}
		else
		{
			ComparedObject_Pointer = ComparedObject_Pointer->RightObject_Pointer;
		}

	}

	if (ComparedObject_Pointer != Sentinel)
	{
		printf("Low= %d , High= %d \n", ComparedObject_Pointer->Interval.Low, ComparedObject_Pointer->Interval.High);
	}
	else
	{
		printf("No overlap for this tree");
	}


}