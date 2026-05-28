#include "..\Header.h"





//Ref to p364,Fig 14.1 ; length 1 with price 1 and so on.
int Price_Table[10] = { 1,5,8,9,10,17,17,20,24,30 };

//There is a main differece between text book and the below function, we calculate all optimal values for all length (difference), and then choose the length of cutted rod.
int Memoized_Cut_Rod(int* Price_Table, unsigned int MaxLength_in_Table, int CuttedRod_Length)
{
	if (CuttedRod_Length > MaxLength_in_Table || CuttedRod_Length < 0)
	{
		return -1; //This function can not compute the optimal solution, it is beyond the table scope.
	}

	int Optimal_Value_Size = MaxLength_in_Table + 1; // +1 means including length 0 into the length set.
	int* Optimal_Values_Pointer = (int*)malloc(Optimal_Value_Size * sizeof(int)); //The index is the length of a rod.
	int* Optimal_FirstPieceLength_Pointer = (int*)malloc(Optimal_Value_Size * sizeof(int)); //The index is the length of a rod.

	for (int i = 0; i < Optimal_Value_Size; i++)
	{
		Optimal_Values_Pointer[i] = -32767;
	}


	Memoized_Cut_Rod_Aux(Price_Table, MaxLength_in_Table, Optimal_Values_Pointer, Optimal_FirstPieceLength_Pointer);


	/*
	for (int Length = 0; Length <= 10; Length++)
	{
		printf("Optimal_Values_Pointer[%d] = %d\n", Length, Optimal_Values_Pointer[Length]);
		printf("Optimal_FirstPieceLength_Pointer[%d] = %d\n", Length, Optimal_FirstPieceLength_Pointer[Length]);
	}*/


	free(Optimal_Values_Pointer);
	free(Optimal_FirstPieceLength_Pointer);

	return Optimal_Values_Pointer[CuttedRod_Length];
}

int Memoized_Cut_Rod_Aux(int* Price_Table, unsigned int RodLength, int* Optimal_Values_Pointer, int* Optimal_FirstPieceLength_Pointer)
{
	//Find the Optimal Values from Optimal Value Table
	if (Optimal_Values_Pointer[RodLength] >= 0)
	{
		return Optimal_Values_Pointer[RodLength];
	}



	if (RodLength == 0)
	{
		Optimal_Values_Pointer[RodLength] = 0; //Record the optimal value.
		Optimal_FirstPieceLength_Pointer[RodLength] = 0;
	}
	else
	{
		int Table_Index = 0;
		for (int FirstPiece_Length = 1; FirstPiece_Length <= RodLength; FirstPiece_Length++)
		{
			Table_Index = FirstPiece_Length - 1;
			int Price_Temp = Price_Table[Table_Index] + Memoized_Cut_Rod_Aux(Price_Table, RodLength - FirstPiece_Length, Optimal_Values_Pointer, Optimal_FirstPieceLength_Pointer);
			if (Optimal_Values_Pointer[RodLength] < Price_Temp)
			{
				Optimal_Values_Pointer[RodLength] = Price_Temp;//Record the optimal value.
				Optimal_FirstPieceLength_Pointer[RodLength] = FirstPiece_Length; //Record the optimal length.
			}

		}
	}



	return Optimal_Values_Pointer[RodLength];
}