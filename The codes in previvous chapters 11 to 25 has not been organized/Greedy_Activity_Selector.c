#include "..\Header.h"




//Textbook ,P418
int StartTime_Array[12] = { 0,1,3,0,5,3,5,6,7,8,2,12 };
int FinalTime_Array[12] = { 0,4,5,6,7,9,9,10,11,12,14,16 }; //The FinalTime values need to been ordered ; The index 0 in this line is only for consisting with index of Textbook ,P418 table


//From activity of index_1 to activity of index_n
void Greedy_Activity_Selector(int* StartTime_Pointer, int* FinalTime_Pointer, int Maximum_ActivityIndex)
{
	//Initialize the maximum-size subset
	int* MaximumsizeSubset_Pointer = (int*)malloc((Maximum_ActivityIndex + 1) * sizeof(int));
	for (int i = 0; i <= Maximum_ActivityIndex; i++)
	{
		MaximumsizeSubset_Pointer[i] = -1;// -1 means there is no activity index insertion.
	}


	MaximumsizeSubset_Pointer[0] = 0; //Insert activity-0
	MaximumsizeSubset_Pointer[1] = 1; //Insert activity-1
	int EmptyElement_Locator = 2;

	int SubprblemIndex = 1; //After activity-1 fnished,the other activities go on.




	for (int EarlistFinishActivity_Index = SubprblemIndex + 1; EarlistFinishActivity_Index <= Maximum_ActivityIndex; EarlistFinishActivity_Index++)
	{
		if (StartTime_Pointer[EarlistFinishActivity_Index] >= FinalTime_Pointer[SubprblemIndex])
		{
			MaximumsizeSubset_Pointer[EmptyElement_Locator] = EarlistFinishActivity_Index;
			EmptyElement_Locator++;

			SubprblemIndex = EarlistFinishActivity_Index;

		}

	}

	/*
	for (int i = 0; i <= Maximum_ActivityIndex; i++)
	{
		printf("%d ", MaximumsizeSubset_Pointer[i]);

	}*/

	free(MaximumsizeSubset_Pointer);


}
