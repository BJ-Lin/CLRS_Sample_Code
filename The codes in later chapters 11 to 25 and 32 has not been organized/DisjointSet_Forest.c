#include "..\Header.h"






//Create a set(tree), and insert ForestSetMember into the object.
void Forest_Make_Set(struct ForestSetMember_Tag* ForestSetMember)
{
	//Create a tree and a node.
	struct Node_Tag* Node_Pointer = (struct Node_Tag*)malloc(sizeof(struct Node_Tag));


	//Fill the content of the node
	Node_Pointer->ForestSetMember = ForestSetMember;
	Node_Pointer->Parent = Node_Pointer;
	Node_Pointer->Rank = 0;

	//Fill the content of the member
	ForestSetMember->Node_Pointer = Node_Pointer;

}

//Find the root of the tree which is the set member, and return it. 
//During finding, execute path-compression.
struct ForestSetMember_Tag* Forest_Find_Set(struct ForestSetMember_Tag* ForestSetMember)
{
	struct Node_Tag* Node_Pointer = ForestSetMember->Node_Pointer;

	//Judge whether the node is the root of the tree. If it is not, we need to find the root and execute path-compression.
	if (Node_Pointer != Node_Pointer->Parent)
	{
		//Execute the path-compression
		Node_Pointer->Parent = (Forest_Find_Set(Node_Pointer->Parent->ForestSetMember))->Node_Pointer;
	}


	return Node_Pointer->Parent->ForestSetMember;

}




void Forest_Union(struct ForestSetMember_Tag* SetMember1, struct ForestSetMember_Tag* SetMember2)
{
	Forest_Link(Forest_Find_Set(SetMember1), Forest_Find_Set(SetMember2));
}

void Forest_Link(struct ForestSetMember_Tag* RootSetMember1, struct ForestSetMember_Tag* RootSetMember2)
{
	struct Node_Tag* Node1_Pointer = RootSetMember1->Node_Pointer;
	struct Node_Tag* Node2_Pointer = RootSetMember2->Node_Pointer;

	if (Node1_Pointer->Rank > Node2_Pointer->Rank)
	{
		Node2_Pointer->Parent = Node1_Pointer;

	}
	else //if (Node1_Pointer->Rank <= Node2_Pointer->Rank), Node1 is appended on Node2.
	{
		Node1_Pointer->Parent = Node2_Pointer;

		if (Node1_Pointer->Rank == Node2_Pointer->Rank)
		{
			Node2_Pointer->Rank++;
		}

	}

}