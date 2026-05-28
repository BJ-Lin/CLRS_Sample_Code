#include "..\Header.h"




//CLRS,4th : The contents of text and pattern are from P986.
unsigned char TextContent3[7] = { 'r','a','t','a','t','a','t' };
unsigned char PatternContent3[2] = { 'a','t' };


Text Text_Object3 = { .Length = sizeof(TextContent3),.Character_Pointer = TextContent3 };
Pattern Pattern_Object3 = { .Length = sizeof(PatternContent3),.Character_Pointer = PatternContent3 };


void SuffixArray_Counting_Sort(int Array[], int* MaxMinBoundary_Pointer, struct SubstringRank_Tag SortedInstant_Array[], size_t Instant_Size)
{
	//Space complexity : Theta( n + k )
	unsigned int Counter_Size = MaxMinBoundary_Pointer[1] - MaxMinBoundary_Pointer[0] + 1; //MaxMinBoundary[1] is max boundary, and MaxMinBoundary[0] is min boundary ; +1 means to add index=0 space.
	struct SubstringRank_Tag* Output_Pointer = (struct SubstringRank_Tag*)malloc(Instant_Size * sizeof(struct SubstringRank_Tag));
	unsigned* Counter_Pointer = (unsigned*)malloc((Counter_Size) * sizeof(unsigned));

	//Initialize the counter array to be 0.
	for (int i = 0; i < Counter_Size; i++)
	{
		Counter_Pointer[i] = 0;

	}

	//Compute the number of each value A[j]
	unsigned int Counter_Index;
	for (int j = 0; j < Instant_Size; j++)
	{
		Counter_Index = Array[j] - MaxMinBoundary_Pointer[0];
		Counter_Pointer[Counter_Index] = Counter_Pointer[Counter_Index] + 1;

	}


	//Compute the locations for fully-insersion of C[i]
	//locations of elements [ 1 : Instant_Size ]
	for (int i = 1; i < Counter_Size; i++)
	{
		Counter_Pointer[i] = Counter_Pointer[i] + Counter_Pointer[i - 1];

	}


	//Insert the values of Array
	for (int j = Instant_Size - 1; j >= 0; j--) // Initialize j = Instant_Size - 1 to make the output stable.
	{
		Counter_Index = Array[j] - MaxMinBoundary_Pointer[0];
		Output_Pointer[Counter_Pointer[Counter_Index] - 1] = SortedInstant_Array[j]; //There exist conversion between location of elements [ 1 : Instant_Size ] and index [ 0 : Instant_Size - 1 ], such as -1 exist.
		Counter_Pointer[Counter_Index] = Counter_Pointer[Counter_Index] - 1;
	}

	for (int j = Instant_Size - 1; j >= 0; j--)
	{
		SortedInstant_Array[j] = Output_Pointer[j];
	}

	free(Counter_Pointer);
	free(Output_Pointer);

}


void SuffixArray_MSD_Radix_Sort(struct SubstringRank_Tag SortedInstant_Array[], size_t Instant_Size, unsigned int Number_Of_Digits)
{

	unsigned int Digit_Position = Number_Of_Digits;
	//Base case , if Digit_Position=0.  
	if (Digit_Position > 0)
	{

		//Divide ( For each number, kth digit with same value are grouping )
		// n : Instant_Size
		//Space complexity : Theta(n)
		int* kth_Digit_Value = (int*)malloc(Instant_Size * sizeof(int));

		//Time complexity : Theta(n)
		//Extract kth Digit value for each element of SortedInstant_Array.
		//Here, we extract the Left_Rank as the 2th digit value.
		if (Digit_Position == 2)
		{
			for (int i = 0; i < Instant_Size; i++)
			{
				kth_Digit_Value[i] = (SortedInstant_Array + i)->Left_Rank;
			}

		}
		else if (Digit_Position == 1)
		{
			//Here, we extract the Right_Rank as the 1th digit value.
			for (int i = 0; i < Instant_Size; i++)
			{
				kth_Digit_Value[i] = (SortedInstant_Array + i)->Right_Rank;
			}

		}


		int MaxMinBoundary_Array[2];
		if (Instant_Size - 1 > UCHAR_MAX)
		{
			//We need to use counter for counting the number of value,and the range of value is [ -1 : Instant_Size - 1 ].  
			MaxMinBoundary_Array[0] = -1;
			MaxMinBoundary_Array[1] = Instant_Size - 1;
		}
		else
		{
			//We need to use counter for counting the number of value,and the range of value is [ -1 : UCHAR_MAX ].
			MaxMinBoundary_Array[0] = -1;
			MaxMinBoundary_Array[1] = UCHAR_MAX;
		}

		//Time complexity :  Theta( n ), counter number k of Theta(n + k) is n+1 here. k is not kth digit.
		//Sorting accorting kth Digit
		SuffixArray_Counting_Sort(kth_Digit_Value, MaxMinBoundary_Array, SortedInstant_Array, Instant_Size);  //Here, we do not need the "stable" property , this is the difference between radix sort and most significant sort.




		// Space complexity : Theta(k) 
		unsigned int Counter_Size = MaxMinBoundary_Array[1] - MaxMinBoundary_Array[0] + 1;
		unsigned* Counter_Pointer = (unsigned*)malloc((Counter_Size) * sizeof(unsigned)); //Added index=0 space

		// Initialize the counter array to be 0. 
		// Time complexity : Theta(k) 
		for (int i = 0; i < Counter_Size; i++)
		{
			Counter_Pointer[i] = 0;

		}



		// Compute the number of each value A[j]
		// Time complexity : Theta(n) 
		unsigned int Counter_Index;
		for (int j = 0; j < Instant_Size; j++)
		{
			Counter_Index = kth_Digit_Value[j] - MaxMinBoundary_Array[0];
			Counter_Pointer[Counter_Index] = Counter_Pointer[Counter_Index] + 1;
		}



		//Conquer
		unsigned int Criteria_Number = 1; //If the number of values of the digit in a group is 1, we do not need to sort the group.
		unsigned int Next_Number_Of_Digits = Number_Of_Digits - 1;
		struct SubstringRank_Tag* Next_Sorting_Instant = SortedInstant_Array;
		//Time complexity : Theta( k ) 
		for (int i = 0; i < Counter_Size; i++)
		{

			if (Counter_Pointer[i] > Criteria_Number)
			{

				//Time complexity : Theta( n + k ) for each call if this is worst case ; Totally, d * Theta( n + k )
				SuffixArray_MSD_Radix_Sort(Next_Sorting_Instant, Counter_Pointer[i], Next_Number_Of_Digits);
			}

			Next_Sorting_Instant = Next_Sorting_Instant + Counter_Pointer[i];
		}




		free(kth_Digit_Value);
		free(Counter_Pointer);

	}
}


struct RankPacket_Tag Make_Rank(struct SubstringRank_Tag SubstringRank_Pointer[], size_t Text_Length)
{
	//Assign the initial rank/order value.
	int CurrentRank = 0;
	int CurrentOrder = CurrentRank;

	//Create the rank array for storing the rank of substring.
	//The index of rank array is corresponding to the index of first character in the text. 
	//EX: T [ j : n ], j is the index of first character in the text.
	int* Rank_Array = (int*)malloc(Text_Length * sizeof(int));


	//Assign the rank value to the element of rank array, according to the sorted substring combination array.
	Rank_Array[SubstringRank_Pointer[CurrentOrder].Index] = CurrentRank;

	//Go through each index(order) of SubstringRank_Pointer.
	for (int i = 1; i < Text_Length; i++)
	{
		if ((SubstringRank_Pointer + i)->Left_Rank != (SubstringRank_Pointer + i - 1)->Left_Rank \
			|| (SubstringRank_Pointer + i)->Right_Rank != (SubstringRank_Pointer + i - 1)->Right_Rank)
		{
			CurrentRank++;
		}

		Rank_Array[SubstringRank_Pointer[i].Index] = CurrentRank;
	}

	struct RankPacket_Tag RankPacket_Object = { .Complete_RankedMission = (CurrentRank == (Text_Length - 1)),.Rank_Array = Rank_Array };

	return RankPacket_Object;
}


//Compute the suffix array of the given text in lexicographically sorted rank.
//The suffix array store the index of first character of suffix in the text.
//The index of suffix array is corresponding to the rank of substring.
int* Compute_Suffix_Array(Text* Text_Pointer)
{
	//Assign the text length to local variable.
	int Text_Length = Text_Pointer->Length;

	//Create the substring combination array for storing the rank of left substring, rank of right substring, and index of first character of left substring in the text.
	struct SubstringRank_Tag* SubstringRank_Pointer = (struct SubstringRank_Tag*)malloc(Text_Length * sizeof(struct SubstringRank_Tag));



	//Create the suffix array for storing the index of first character of suffix in the text.
	//The index of suffix array is corresponding to the rank of substring.
	int* Suffix_Array = (int*)malloc(Text_Length * sizeof(int));

	//Go through each character in the text and initialize the elements of SubstringRank_Pointer.
	//The index i of SubstringRank_Pointer is corresponding to the index of Character_Pointer in the text.
	unsigned char* Character_Pointer = Text_Pointer->Character_Pointer;
	for (int i = 0; i < Text_Length; i++)
	{
		//Initialize the rank of left substring with the ASCII code of character.
		(SubstringRank_Pointer + i)->Left_Rank = Character_Pointer[i];


		//Initialize the rank of right substring.
		if (i < Text_Length - 1)//Prevent the access of Character_Pointer[i + 1] over the bound.
		{
			(SubstringRank_Pointer + i)->Right_Rank = Character_Pointer[i + 1];
		}
		else
		{
			(SubstringRank_Pointer + i)->Right_Rank = -1; //The rank of right substring is -1 when the right substring is empty.
		}

		(SubstringRank_Pointer + i)->Index = i; //The index of first character for left substring in the text.

	}

	//Sort the substring combination array based on the rank of left substring and right substring.
	//The index of SubstringRank_Pointer after sorting is corresponding to the order of combination substring.
	//Here, I use the word "order" instead of "rank", 
	//because the value of order is always different between different element of SubstringRank_Pointer. 
	unsigned int Number_Of_Digits = 2; //We have two digits to sort : left rank and right rank.
	SuffixArray_MSD_Radix_Sort(SubstringRank_Pointer, Text_Length, Number_Of_Digits);


	//Initialize upper bound of the length of substring combination.
	int UpperBound_Length = 2;

	while (UpperBound_Length < Text_Length)
	{
		//Make the rank array for each substring.
		struct RankPacket_Tag RankPacket_Object = Make_Rank(SubstringRank_Pointer, Text_Length);
		int* Rank_Array = RankPacket_Object.Rank_Array;



		//If all substrings have been assigned different rank values, we can stop the process early.
		if (RankPacket_Object.Complete_RankedMission)
		{
			free(Rank_Array);
			break; //All substrings have been assigned different rank values.
		}



		//Go through each character in the text and update the elements of SubstringRank_Pointer.
		for (int i = 0; i < Text_Length; i++)
		{
			//Update the rank of left substring.
			(SubstringRank_Pointer + i)->Left_Rank = Rank_Array[i];

			//Update the rank of right substring.
			if (i + UpperBound_Length < Text_Length) //Prevent the access of Rank_Array[i + UpperBound_Length] over the bound.
			{
				(SubstringRank_Pointer + i)->Right_Rank = Rank_Array[i + UpperBound_Length];
			}
			else
			{
				(SubstringRank_Pointer + i)->Right_Rank = -1; //The rank of right substring is -1 when the right substring is empty.
			}

			(SubstringRank_Pointer + i)->Index = i; //The index of first character for left substring in the text.

		}

		//Sort the substring combination array based on the rank of left substring and right substring.
		SuffixArray_MSD_Radix_Sort(SubstringRank_Pointer, Text_Length, Number_Of_Digits);

		//Double the upper bound of the length of substring combination currently.
		UpperBound_Length = 2 * UpperBound_Length;

		free(Rank_Array);
	}


	//Go through each order of SubstringRank_Pointer 
	//and assign the index of first character in the text to the suffix array.
	for (int i = 0; i < Text_Length; i++)
	{
		Suffix_Array[i] = SubstringRank_Pointer[i].Index;
	}

	return Suffix_Array;
}


//Compute the longest common prefix array of the given text based on the suffix array.
int* Compute_LCP_Array(Text* Text_Pointer, int Suffix_Array[])
{
	//Assign the text length to local variable.
	int Text_Length = Text_Pointer->Length;


	//Create the rank array for storing the rank of suffix.
	//The index of rank array is corresponding to the index of first character in the text. 
	int* Rank_Array = (int*)malloc(Text_Length * sizeof(int));


	//Create the LCP array for storing the longest common prefix length between adjacent suffixes T[ Suffix_Array[i] : ] and T[ Suffix_Array[i-1] : ].
	int* LCP_Array = (int*)malloc(Text_Length * sizeof(int));

	//Go through each index(rank) of Suffix_Array and assign the rank value to the element of rank array.
	for (int i = 0; i < Text_Length; i++)
	{
		Rank_Array[Suffix_Array[i]] = i;
	}



	//Rank i-1 = -1 is not exist, when i=0. 
	//So, we initialize LCP_Array[0] = 0 by definition.
	LCP_Array[0] = 0;


	//Go through each index i of character in the text.
	unsigned char* Character_Pointer = Text_Pointer->Character_Pointer; //Assign the character pointer in the text to local variable.
	int DisplacementStep = 0;
	for (int i = 0; i < Text_Length; i++)
	{
		//Rank 0 has been initialized, so we skip the rank 0.
		if (Rank_Array[i] > 0)
		{
			int j = Suffix_Array[Rank_Array[i] - 1]; //The index j of first character in the text for suffix with Rank_Array[i]-1.

			//Choose the maximum location of character for avooiding over bound in the text.
			int MaximmumLocation = i > j ? i : j;

			while (MaximmumLocation + DisplacementStep < Text_Length)
			{
				if (Character_Pointer[i + DisplacementStep] == Character_Pointer[j + DisplacementStep]) //Place the if-statement in while loop for avoiding over bound.
				{
					DisplacementStep++;
				}
				else
				{
					break;
				}
			}

			//Assign the longest common prefix length between adjacent suffixes T[ i : ] and T[ j : ] to the LCP array.
			//The longest common prefix length = DisplacementStep - 1(back to the matching position) + 1(starting position)=DisplacementStep.
			LCP_Array[Rank_Array[i]] = DisplacementStep;


			if (DisplacementStep > 0)
			{
				DisplacementStep--; //According to the property of Lemma 32.8, we decrease DisplacementStep by 1 for next index i+1.
			}

		}

	}

	free(Rank_Array);
	return LCP_Array;
}
