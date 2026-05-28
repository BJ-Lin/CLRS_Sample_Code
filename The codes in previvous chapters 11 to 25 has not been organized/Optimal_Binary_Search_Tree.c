#include "..\Header.h"






float ActualKey_Probability_Array[6] = { 0   ,0.15 ,0.1   ,0.05  ,0.1   , 0.2 }; //There is no Actual Key at the index [0].
float DummyKey_Probability_Array[6] = { 0.05 , 0.1 , 0.05 , 0.05 , 0.05 , 0.1 };


struct BinaryTree_Tag Optimal_BinaryTree = { .RootObject_Pointer = NULL };
struct Object_of_BinaryTree_Tag Object_with_ActualKey_Array[6] = { [1] .Key = 2,[2].Key = 4,[3].Key = 6,[4].Key = 8,[5].Key = 10 }; //There is no Actual Key at the index [0].
struct Object_of_BinaryTree_Tag Object_with_DummyKey_Array[6] = { [0] .Key = 1,[1].Key = 3,[2].Key = 5,[3].Key = 7,[4].Key = 9,[5].Key = 11 };

struct Optimal_NeededInformation_Tag Optimal_NeededInformation = { .ActualKey_Probability_Pointer = ActualKey_Probability_Array ,.DummyKey_Probability_Pointer = DummyKey_Probability_Array, .Number_of_Node = sizeof(Object_with_ActualKey_Array) / sizeof(struct Object_of_BinaryTree_Tag) - 1 };


//Abstraction : k1,k2,k3,......kn ; Both i=0~n-1 and j=1~n stand for k1~kn, we use the meaning k1~kn ,d0~dn to create a table.
int* Optimal_BST(float* ActualKey_Probability_Poiinter, float* DummyKey_Probability_Poiinter, unsigned int Number_of_Node)
{
	//Create lookup table
	unsigned int TableLength = Number_of_Node + 1;
	unsigned int ExpectedValue_Size = TableLength * TableLength;
	float* ExpectedValue_Pointer = (float*)malloc(ExpectedValue_Size * sizeof(float));
	float* ProbabilitySum_Pointer = (float*)malloc(ExpectedValue_Size * sizeof(float));

	//Create solution table
	int* RootIndex_Pointer = (int*)malloc(Number_of_Node * Number_of_Node * sizeof(int));

	//Base case ; Row Major 
	for (int i = 0; i < TableLength; i++)
	{
		*((ExpectedValue_Pointer + i) + i * TableLength) = DummyKey_Probability_Poiinter[i]; //Notice : The conversion for row index between textbook p405 and this line of source code ; Row index must be minused for 1 to be converted to our index.
		*((ProbabilitySum_Pointer + i) + i * TableLength) = DummyKey_Probability_Poiinter[i];//Notice : The conversion for row index between textbook p405 and this line of source code ; Row index must be minused for 1 to be converted to our index.
	}

	unsigned int j = 0;
	float ExpectedValue_Temp = 0;
	for (unsigned Length = 1; Length <= Number_of_Node; Length++)
	{

		//Notice : Initial j position = Number_of_Node - (Length - 1) ; Recursive case beginging ( i , i + 1 ) ---->  i + 1 = Number_of_Node - (Length - 1)  ----> i  = (Number_of_Node -1) - (Length - 1) 
		for (unsigned i = 0; i <= (Number_of_Node - 1) - (Length - 1); i++) //Notice : The conversion for row index between textbook p405 and this line of source code ; Row index must be minused for 1 to be converted to our index.
		{
			j = (i + 1) + (Length - 1); //Notice : Recursive case beginging j=i + 1 ,( i , i + 1 )
			*((ExpectedValue_Pointer + j) + i * TableLength) = FLT_MAX;

			//Pre-Calculate the lookup table for ith-node to jth-node
			*((ProbabilitySum_Pointer + j) + i * TableLength) = *((ProbabilitySum_Pointer + (j - 1)) + i * TableLength) + ActualKey_Probability_Poiinter[j] + DummyKey_Probability_Poiinter[j];



			//Notice : Recursive case beginging j=i + 1 ,( i , i + 1 )
			for (signed Root_Index = i + 1; Root_Index <= j; Root_Index++)
			{
				//Notice : Root_Index is the key index, which need to converted to (Root_Index - 1)
				ExpectedValue_Temp = *((ExpectedValue_Pointer + (Root_Index - 1)) + i * TableLength) + *((ExpectedValue_Pointer + j) + ((Root_Index - 1) + 1) * TableLength) + *((ProbabilitySum_Pointer + j) + i * TableLength);


				if (ExpectedValue_Temp < *((ExpectedValue_Pointer + j) + i * TableLength))
				{

					*((ExpectedValue_Pointer + j) + i * TableLength) = ExpectedValue_Temp;
					*((RootIndex_Pointer + (j - 1)) + i * Number_of_Node) = Root_Index; //Notice :For kj=1~n ,go into RootIndex_Pointer[  ][ 0 ~ n-1 ], (n-1)*(n-1) table , index=0 means key1 for each direction.
				}

			}

		}
	}

	/*
	for(int i=0;i< Number_of_Node;i++)
	{
		for (int j = i; j < Number_of_Node; j++)
		{
			printf("Root[%d][%d]=%d ", i, j, *((RootIndex_Pointer + j) + i * Number_of_Node));
		}

		printf("\n");
	}*/

	free(ExpectedValue_Pointer);
	free(ProbabilitySum_Pointer);


	return RootIndex_Pointer;

}
void ActualKeyRecursive_Insert(struct BinaryTree_Tag* BinaryTree_Pointer, struct Object_of_BinaryTree_Tag* Insertion_Object_Pointer, struct LookUpRoot_Tag* LookUpRoot_Pointer)
{
	//Base case 
	if (LookUpRoot_Pointer->Upper_KeyNumber - LookUpRoot_Pointer->Lower_KeyNumber < 0)
	{
		return;
	}


	//Recursive case 
	//Compute the  RootIndex
	int i = LookUpRoot_Pointer->Lower_KeyNumber - 1; //Convert the key number to index.
	int j = LookUpRoot_Pointer->Upper_KeyNumber - 1; //Convert the key number to index.
	int RootIndex = *((LookUpRoot_Pointer->RootIndex_Pointer + j) + i * LookUpRoot_Pointer->Table_Length); //RootIndex=0 means key1 

	//printf("Root[%d][%d]=%d\n", i, j,RootIndex);



	//Insert the root
	BinaryTree_Insert(BinaryTree_Pointer, &Insertion_Object_Pointer[RootIndex]);



	struct LookUpRoot_Tag Left_LookUpRoot_Object = *LookUpRoot_Pointer;
	struct LookUpRoot_Tag Right_LookUpRoot_Object = *LookUpRoot_Pointer;

	Left_LookUpRoot_Object.Upper_KeyNumber = RootIndex - 1;
	Left_LookUpRoot_Object.Lower_KeyNumber = LookUpRoot_Pointer->Lower_KeyNumber;

	Right_LookUpRoot_Object.Upper_KeyNumber = LookUpRoot_Pointer->Upper_KeyNumber;
	Right_LookUpRoot_Object.Lower_KeyNumber = RootIndex + 1;

	ActualKeyRecursive_Insert(BinaryTree_Pointer, Insertion_Object_Pointer, &Left_LookUpRoot_Object);
	ActualKeyRecursive_Insert(BinaryTree_Pointer, Insertion_Object_Pointer, &Right_LookUpRoot_Object);

}
void OptimalBinaryTree_Insert(struct BinaryTree_Tag* BinaryTree_Pointer, struct Object_of_BinaryTree_Tag* Object_with_ActualKey_Pointer, struct Object_of_BinaryTree_Tag* Object_with_DummyKey_Pointer, struct Optimal_NeededInformation_Tag* Solution_NeededInformation_Pointer)
{
	struct LookUpRoot_Tag LookUpRoot_Object;



	//Computing for the lookup table.
	LookUpRoot_Object.RootIndex_Pointer = Optimal_BST(Solution_NeededInformation_Pointer->ActualKey_Probability_Pointer, Solution_NeededInformation_Pointer->DummyKey_Probability_Pointer, Solution_NeededInformation_Pointer->Number_of_Node);

	//Initialize the interval of contiguous keys 
	LookUpRoot_Object.Upper_KeyNumber = Solution_NeededInformation_Pointer->Number_of_Node;
	LookUpRoot_Object.Lower_KeyNumber = 1;
	LookUpRoot_Object.Table_Length = Solution_NeededInformation_Pointer->Number_of_Node;


	//Insert Actual Key
	ActualKeyRecursive_Insert(BinaryTree_Pointer, Object_with_ActualKey_Pointer, &LookUpRoot_Object);


	//Insert Dummy Key
	for (int i = 0; i <= Solution_NeededInformation_Pointer->Number_of_Node; i++)
	{
		BinaryTree_Insert(BinaryTree_Pointer, Object_with_DummyKey_Pointer + i);
	}




}
