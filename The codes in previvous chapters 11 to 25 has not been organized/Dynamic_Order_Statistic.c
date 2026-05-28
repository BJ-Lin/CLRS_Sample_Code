#include "..\Header.h"


struct Object_of_RedBlackTree_Tag* Os_Select(struct Object_of_RedBlackTree_Tag* Root, unsigned SearchedRank)
{
	unsigned RootRank = Root->LeftObject_Pointer->Size + 1;

	if (SearchedRank == RootRank)
	{
		return Root;
	}

	else if (SearchedRank < RootRank)
	{
		return Os_Select(Root->LeftObject_Pointer, SearchedRank);
	}

	else
	{
		return Os_Select(Root->RightObject_Pointer, SearchedRank - RootRank);
	}

}

unsigned Os_Rank(struct RedBlackTree_Tag* Tree_Pointer, struct Object_of_RedBlackTree_Tag* Node_Pointer)
{
	unsigned NodeRank = Node_Pointer->LeftObject_Pointer->Size + 1;
	struct Object_of_RedBlackTree_Tag* CheckedNode_Pointer = Node_Pointer;

	while (CheckedNode_Pointer != Tree_Pointer->RootObject_Pointer)
	{
		if (CheckedNode_Pointer == CheckedNode_Pointer->ParentObject_Pointer->RightObject_Pointer)
		{
			NodeRank = NodeRank + CheckedNode_Pointer->ParentObject_Pointer->LeftObject_Pointer->Size + 1;
		}

		CheckedNode_Pointer = CheckedNode_Pointer->ParentObject_Pointer;
	}

	return NodeRank;
}