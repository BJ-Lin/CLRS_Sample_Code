#include "..\Header.h"


//CLRS,4th : The contents of text and pattern are from P964.
unsigned char TextContent[19] = { 2,3,5,9,0,2,3,1,4,1,5,2,6,7,3,9,9,2,1 };
unsigned char PatternContent[5] = { 3,1,4,1,5 };



Text Text_Object = { .Length = sizeof(TextContent),.Character_Pointer = TextContent };
Pattern Pattern_Object = { .Length = sizeof(PatternContent),.Character_Pointer = PatternContent };



int* Compute_Prefix_Function(Pattern* Pattern_Pointer)
{
	//Create the prefix table.
	int Pattern_Length = Pattern_Pointer->Length;
	int* Prefix_Table = (int*)malloc(Pattern_Length * sizeof(int));

	//Initialize the first element Prefix_Table[ q - 1 ] with q=1.
	//k and index of Prefix_Table are the locations of the character in the pattern from 0 to (Pattern_Length - 1), so that the index value -1 means the element is not exist.
	Prefix_Table[0] = -1;
	int k = -1;

	//Compute the prefix table for pattern.
	for (int q = 1; q < Pattern_Length; q++)
	{
		//First,if k = -1, it means there is no prefix P[ 0 : k = -1 ],
		//and we only need to compare the next character P[ k + 1 : k + 1 ] with the truncated Pattern_Pointer->Character_Pointer[q],that it is going to execute the "if (Pattern_Pointer->Cha....)" command.
		//Second, judge if prefix P[ 1 : k ] + P[ k + 1 ] is a suffix of P[ 0 : q ].
		//If not, we need to shorten the prefix P[ 0 : k ] to P[ 0 : Prefix_Table[k] ] and then compare P[ Prefix_Table[k] + 1 ] with P[ q ] again.
		//If it is true, we can add 1 to k by the "if command".
		while (k > -1 && Pattern_Pointer->Character_Pointer[k + 1] != Pattern_Pointer->Character_Pointer[q])
		{
			k = Prefix_Table[k];
		}

		//Compare the truncated character to validate if P[ 0 : k +1 ] is a suffix of P[ 0 : q ].
		if (Pattern_Pointer->Character_Pointer[k + 1] == Pattern_Pointer->Character_Pointer[q])
		{
			k++;
		}
		Prefix_Table[q] = k;
	}
	return Prefix_Table;
}

void KMP_Matcher(Text* Text_Pointer, Pattern* Pattern_Pointer)
{
	//Compute the prefix table for KMP matcher.
	int* Prefix_Table = Compute_Prefix_Function(Pattern_Pointer);

	//Assign the text length and pattern length to local variables.
	int Text_Length = Text_Pointer->Length;
	int Pattern_Length = Pattern_Pointer->Length;
	int Pattern_EndIndex = Pattern_Length - 1;

	//Assign the character pointer of text and pattern to local variables.
	unsigned char* TextCharacter_Pointer = Text_Pointer->Character_Pointer;
	unsigned char* PatternCharacter_Pointer = Pattern_Pointer->Character_Pointer;

	int q = -1; //The index of character matched.
	for (int i = 0; i < Text_Length; i++)
	{
		while (q > -1 && PatternCharacter_Pointer[q + 1] != TextCharacter_Pointer[i])
		{
			q = Prefix_Table[q];
		}
		if (PatternCharacter_Pointer[q + 1] == TextCharacter_Pointer[i])
		{
			q++;
		}
		if (q == Pattern_EndIndex)
		{
			printf("Pattern occurs with shift = %d\n", i - Pattern_EndIndex);
			q = Prefix_Table[q];
		}
	}
	free(Prefix_Table);
}