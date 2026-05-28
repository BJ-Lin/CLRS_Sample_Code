#include "..\Header.h"







//data fromm text book p380
unsigned int MatrixDimensionSequence_Array[7] = { 30,35,15,5,10,20 ,25 };
unsigned int Number_of_Matrix = 6;

void Matrix_Chain_Order(unsigned int* Matrix_Dimension_Sequence_Pointer, unsigned int Number_of_Matrix)
{
	unsigned* OptimalNumber_of_ScalarMultiply_Pointer = (unsigned*)malloc(Number_of_Matrix * Number_of_Matrix * sizeof(unsigned));
	unsigned* LastLocation_of_FirstPiece_Pointer = (unsigned*)malloc(Number_of_Matrix * Number_of_Matrix * sizeof(unsigned));

	//i is the table index
	for (int i = 0; i < Number_of_Matrix; i++)
	{
		*((OptimalNumber_of_ScalarMultiply_Pointer + i) + Number_of_Matrix * i) = 0;
	}

	//j is also the table index in different direction.
	unsigned int Max_i = 0;
	unsigned int j = 0;
	unsigned int Temp_OptimalValue = 0;
	for (unsigned int Length = 2; Length <= Number_of_Matrix; Length++)
	{
		Max_i = Number_of_Matrix - (Length - 1) - 1; //It is must be carefully for Length-Index conversion.

		for (int i = 0; i <= Max_i; i++)
		{
			j = i + (Length - 1);
			*((OptimalNumber_of_ScalarMultiply_Pointer + j) + Number_of_Matrix * i) = -1;



			//k is last location index of first piece.
			for (unsigned int k = i; k <= j - 1; k++)
			{

				Temp_OptimalValue = *((OptimalNumber_of_ScalarMultiply_Pointer + k) + Number_of_Matrix * i) + *((OptimalNumber_of_ScalarMultiply_Pointer + j) + Number_of_Matrix * (k + 1)) + (Matrix_Dimension_Sequence_Pointer[i] * Matrix_Dimension_Sequence_Pointer[k + 1] * Matrix_Dimension_Sequence_Pointer[j + 1]);

				if (Temp_OptimalValue < *((OptimalNumber_of_ScalarMultiply_Pointer + j) + Number_of_Matrix * i))
				{
					*((OptimalNumber_of_ScalarMultiply_Pointer + j) + Number_of_Matrix * i) = Temp_OptimalValue;
					*((LastLocation_of_FirstPiece_Pointer + j) + Number_of_Matrix * i) = k;
				}
			}

		}

	}

	for (int i = 0; i < Number_of_Matrix; i++)
	{
		for (int j = i; j < Number_of_Matrix; j++)
		{
			printf("m[%d][%d]=%d\n", i, j, *((OptimalNumber_of_ScalarMultiply_Pointer + j) + Number_of_Matrix * i));
		}
	}

	Print_Optimal_Parenthesize(LastLocation_of_FirstPiece_Pointer, 0, Number_of_Matrix - 1);

	free(OptimalNumber_of_ScalarMultiply_Pointer);
	free(LastLocation_of_FirstPiece_Pointer);

}

void Print_Optimal_Parenthesize(unsigned int* LastLocation_of_FirstPiece_Pointer, unsigned int i, unsigned int j)
{
	if (i == j)
		printf("A%u", i);

	else
	{
		printf("(");
		Print_Optimal_Parenthesize(LastLocation_of_FirstPiece_Pointer, i, *((LastLocation_of_FirstPiece_Pointer + j) + Number_of_Matrix * i));
		Print_Optimal_Parenthesize(LastLocation_of_FirstPiece_Pointer, *((LastLocation_of_FirstPiece_Pointer + j) + Number_of_Matrix * i) + 1, j);
		printf(")");
	}


}