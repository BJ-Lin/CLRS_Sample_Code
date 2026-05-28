#include "..\Header.h"




unsigned char StringX_Array[8] = "ABCBDAB";
unsigned char StringY_Array[7] = "BDCABA";




void Print_LCS(struct CaseIndicator_Tag* CaseIndicator_Object, unsigned char* StringX_Pointer, unsigned int LCSTable_Index_i, unsigned int LCSTable_Index_j)
{
	if (LCSTable_Index_i == 0 || LCSTable_Index_j == 0)
	{
		return;
	}

	//Calculate table index of CaseIndicator table.
	unsigned int Table_Index_i = LCSTable_Index_i - 1;
	unsigned int Table_Index_j = LCSTable_Index_j - 1;

	if (*((CaseIndicator_Object->Table + Table_Index_j) + Table_Index_i * CaseIndicator_Object->Y_Length) == '\\')
	{
		Print_LCS(CaseIndicator_Object, StringX_Pointer, LCSTable_Index_i - 1, LCSTable_Index_j - 1);
		printf("%c ", StringX_Pointer[Table_Index_i]);
	}
	else if (*((CaseIndicator_Object->Table + Table_Index_j) + Table_Index_i * CaseIndicator_Object->Y_Length) == '|')
	{
		Print_LCS(CaseIndicator_Object, StringX_Pointer, LCSTable_Index_i - 1, LCSTable_Index_j);
	}

	else
	{
		Print_LCS(CaseIndicator_Object, StringX_Pointer, LCSTable_Index_i, LCSTable_Index_j - 1);
	}

}

void LCS_Length(unsigned char* StringX_Pointer, unsigned int X_Length, unsigned char* StringY_Pointer, unsigned int Y_Length)
{
	//Initialize the CaseIndicator object
	struct CaseIndicator_Tag CaseIndicator_Object;
	CaseIndicator_Object.X_Length = X_Length;
	CaseIndicator_Object.Y_Length = Y_Length;
	unsigned int Indicator_Table_Size = CaseIndicator_Object.X_Length * CaseIndicator_Object.Y_Length;
	CaseIndicator_Object.Table = (signed short*)malloc(Indicator_Table_Size * sizeof(signed short)); //Three case : (1)xi=yj ( Symbol:'\' )¡A(2)xi must be not a last common word( Symbol:'|' ).¡A(3)yi must be not a last common word( Symbol:'-' ).


	//Initialize the LCS object
	struct LCS_Tag LCS_Object;
	LCS_Object.X_Length = X_Length + 1;
	LCS_Object.Y_Length = Y_Length + 1;
	unsigned int LCS_Table_Size = LCS_Object.X_Length * LCS_Object.Y_Length;
	LCS_Object.Table = (int*)malloc(LCS_Table_Size * sizeof(int));


	//Compute every entry for the two table ,which are LCS_Table , CaseIndicator_Table.
	for (int i = 1; i <= X_Length; i++)
	{
		*(LCS_Object.Table + i * LCS_Object.Y_Length) = 0;
	}

	//Assign the values of base case
	for (int j = 0; j <= Y_Length; j++)
	{
		*(LCS_Object.Table + j) = 0;
	}

	//Create table index of CaseIndicator table.
	unsigned int Table_Index_i = 0;
	unsigned int Table_Index_j = 0;

	for (int i = 1; i <= X_Length; i++)
	{
		for (int j = 1; j <= Y_Length; j++)
		{
			Table_Index_i = i - 1;
			Table_Index_j = j - 1;

			if (StringX_Pointer[i - 1] == StringY_Pointer[j - 1]) //Notice : The conversion for index
			{
				*((LCS_Object.Table + j) + i * LCS_Object.Y_Length) = *((LCS_Object.Table + (j - 1)) + (i - 1) * LCS_Object.Y_Length) + 1;
				*((CaseIndicator_Object.Table + Table_Index_j) + Table_Index_i * Y_Length) = '\\'; //Notice : The conversion for index
			}

			else if (*((LCS_Object.Table + j) + (i - 1) * LCS_Object.Y_Length) >= *((LCS_Object.Table + (j - 1)) + (i)*LCS_Object.Y_Length))
			{
				*((LCS_Object.Table + j) + i * LCS_Object.Y_Length) = *((LCS_Object.Table + j) + (i - 1) * LCS_Object.Y_Length);
				*((CaseIndicator_Object.Table + Table_Index_j) + Table_Index_i * Y_Length) = '\|'; //Notice : The conversion for index
			}
			else
			{
				*((LCS_Object.Table + j) + i * LCS_Object.Y_Length) = *((LCS_Object.Table + (j - 1)) + i * LCS_Object.Y_Length);
				*((CaseIndicator_Object.Table + Table_Index_j) + Table_Index_i * Y_Length) = '\-'; //Notice : The conversion for index

			}
		}

	}

	for (int i = 0; i < LCS_Object.X_Length; i++)
	{
		for (int j = 0; j < LCS_Object.Y_Length; j++)
		{
			printf("%u ", *((LCS_Object.Table + j) + i * LCS_Object.Y_Length));
		}
		printf("\n");
	}


	Print_LCS(&CaseIndicator_Object, StringX_Pointer, X_Length, Y_Length);

	free(LCS_Object.Table);
	free(CaseIndicator_Object.Table);
}

void Start_Recursive_LCS(unsigned char* StringX_Pointer, unsigned int X_Length, unsigned char* StringY_Pointer, unsigned int Y_Length)
{
	//Initialize the CaseIndicator object
	struct CaseIndicator_Tag CaseIndicator_Object;
	CaseIndicator_Object.X_Length = X_Length;
	CaseIndicator_Object.Y_Length = Y_Length;
	unsigned int Indicator_Table_Size = CaseIndicator_Object.X_Length * CaseIndicator_Object.Y_Length;
	CaseIndicator_Object.Table = (signed short*)malloc(Indicator_Table_Size * sizeof(signed short)); //Three case : (1)xi=yj ( Symbol:'\' )¡A(2)xi must be not a last common word( Symbol:'|' ).¡A(3)yi must be not a last common word( Symbol:'-' ).

	for (int i = 0; i < CaseIndicator_Object.X_Length; i++)
	{
		for (int j = 0; j < CaseIndicator_Object.Y_Length; j++)
		{

			*((CaseIndicator_Object.Table + j) + i * Y_Length) = -1;

		}
	}


	//Initialize the LCS object
	struct LCS_Tag LCS_Object;
	LCS_Object.X_Length = X_Length + 1;
	LCS_Object.Y_Length = Y_Length + 1;
	unsigned int LCS_Table_Size = LCS_Object.X_Length * LCS_Object.Y_Length;
	LCS_Object.Table = (int*)malloc(LCS_Table_Size * sizeof(int));

	for (int i = 0; i < LCS_Object.X_Length; i++)
	{
		for (int j = 0; j < LCS_Object.Y_Length; j++)
		{

			*((LCS_Object.Table + j) + i * Y_Length) = -1;

		}
	}

	Recursive_LCS_Length(StringX_Pointer, X_Length, StringY_Pointer, Y_Length, &CaseIndicator_Object, &LCS_Object);

	Print_LCS(&CaseIndicator_Object, StringX_Pointer, X_Length, Y_Length);

	free(LCS_Object.Table);
	free(CaseIndicator_Object.Table);

}

int Recursive_LCS_Length(unsigned char* StringX_Pointer, unsigned int i, unsigned char* StringY_Pointer, unsigned int j, struct CaseIndicator_Tag* CaseIndicator_Object_Pointer, struct LCS_Tag* LCS_Object_Pointer)
{


	//Check the table entry exist or not.
	if (*((LCS_Object_Pointer->Table + j) + i * LCS_Object_Pointer->Y_Length) >= 0)
	{


		return *((LCS_Object_Pointer->Table + j) + i * LCS_Object_Pointer->Y_Length);
	}

	//Base case
	if (i == 0 || j == 0)
	{

		*((LCS_Object_Pointer->Table + j) + i * LCS_Object_Pointer->Y_Length) = 0;
		return *((LCS_Object_Pointer->Table + j) + i * LCS_Object_Pointer->Y_Length);
	}

	//Recursivve case
	if (StringX_Pointer[i - 1] == StringY_Pointer[j - 1]) //Notice : The conversion for index
	{

		*((LCS_Object_Pointer->Table + j) + i * LCS_Object_Pointer->Y_Length) = Recursive_LCS_Length(StringX_Pointer, i - 1, StringY_Pointer, j - 1, CaseIndicator_Object_Pointer, LCS_Object_Pointer) + 1;


		*((CaseIndicator_Object_Pointer->Table + (j - 1)) + (i - 1) * CaseIndicator_Object_Pointer->Y_Length) = '\\';//Notice : The conversion for index


		return *((LCS_Object_Pointer->Table + j) + i * LCS_Object_Pointer->Y_Length);
	}

	else if (Recursive_LCS_Length(StringX_Pointer, i - 1, StringY_Pointer, j, CaseIndicator_Object_Pointer, LCS_Object_Pointer) >= Recursive_LCS_Length(StringX_Pointer, i, StringY_Pointer, j - 1, CaseIndicator_Object_Pointer, LCS_Object_Pointer)) //Notice : The conversion for index
	{
		*((LCS_Object_Pointer->Table + j) + i * LCS_Object_Pointer->Y_Length) = *((LCS_Object_Pointer->Table + j) + (i - 1) * LCS_Object_Pointer->Y_Length);
		*((CaseIndicator_Object_Pointer->Table + (j - 1)) + (i - 1) * CaseIndicator_Object_Pointer->Y_Length) = '\|';//Notice : The conversion for index
		return *((LCS_Object_Pointer->Table + j) + i * LCS_Object_Pointer->Y_Length);
	}
	else
	{
		*((LCS_Object_Pointer->Table + j) + i * LCS_Object_Pointer->Y_Length) = *((LCS_Object_Pointer->Table + (j - 1)) + i * LCS_Object_Pointer->Y_Length);
		*((CaseIndicator_Object_Pointer->Table + (j - 1)) + (i - 1) * CaseIndicator_Object_Pointer->Y_Length) = '\-';//Notice : The conversion for index

		return *((LCS_Object_Pointer->Table + j) + i * LCS_Object_Pointer->Y_Length);
	}


}