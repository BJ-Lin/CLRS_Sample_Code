#include "..\Header.h"



struct Graph_Tag FasterAPSP_Graph_Object;


void CreateInitialize_AdjacencyMatrix(struct Graph_Tag* Graph_Pointer)
{

	int Number_of_Vertex = Graph_Pointer->Number_of_Vertex;

	//Create the space of Adjacency Matrix.
	int MatrixSize = Number_of_Vertex * Number_of_Vertex;
	Graph_Pointer->AdjacencyMatrix_Pointer = (int*)malloc(MatrixSize * sizeof(int));


	//Initialize Adjacency Matrix.
	for (int i = 0; i < Number_of_Vertex; i++)
	{
		for (int j = 0; j < Number_of_Vertex; j++)
		{
			*(Graph_Pointer->AdjacencyMatrix_Pointer + i * Number_of_Vertex + j) = INT_MAX;
		}

		*(Graph_Pointer->AdjacencyMatrix_Pointer + i * Number_of_Vertex + i) = 0;
	}

}
//CLRS,4th,P652 ; Vertex 1 ~ Vertex 5  <---->  Array index = 0th ~ 4th
//This is adjacency matrix.
void  FasterAPSP_CreateGraph(struct Graph_Tag* Graph_Pointer)
{
	//Assigm the number of vertices.
	Graph_Pointer->Number_of_Vertex = 5;
	int Number_of_Vertex = Graph_Pointer->Number_of_Vertex;

	//Assigm the number of edges.
	Graph_Pointer->Number_of_Edge = 13;



	//Initialize the Adjacency Matrix.
	CreateInitialize_AdjacencyMatrix(Graph_Pointer);


	//Fill the elements of 0th row of Adjacency Matrix with edge weight.
	*(Graph_Pointer->AdjacencyMatrix_Pointer + 0 * Number_of_Vertex + 1) = 3;
	*(Graph_Pointer->AdjacencyMatrix_Pointer + 0 * Number_of_Vertex + 2) = 8;
	*(Graph_Pointer->AdjacencyMatrix_Pointer + 0 * Number_of_Vertex + 4) = -4;


	//Fill the elements of 1th row of Adjacency Matrix with edge weight.
	*(Graph_Pointer->AdjacencyMatrix_Pointer + 1 * Number_of_Vertex + 1) = 0;
	*(Graph_Pointer->AdjacencyMatrix_Pointer + 1 * Number_of_Vertex + 3) = 1;
	*(Graph_Pointer->AdjacencyMatrix_Pointer + 1 * Number_of_Vertex + 4) = 7;


	//Fill the elements of 2th row of Adjacency Matrix with edge weight.
	*(Graph_Pointer->AdjacencyMatrix_Pointer + 2 * Number_of_Vertex + 1) = 4;
	*(Graph_Pointer->AdjacencyMatrix_Pointer + 2 * Number_of_Vertex + 2) = 0;


	//Fill the elements of 3th row of Adjacency Matrix with edge weight.
	*(Graph_Pointer->AdjacencyMatrix_Pointer + 3 * Number_of_Vertex + 0) = 2;
	*(Graph_Pointer->AdjacencyMatrix_Pointer + 3 * Number_of_Vertex + 2) = -5;
	*(Graph_Pointer->AdjacencyMatrix_Pointer + 3 * Number_of_Vertex + 3) = 0;

	//Fill the elements of 4th row of Adjacency Matrix with edge weight.
	*(Graph_Pointer->AdjacencyMatrix_Pointer + 4 * Number_of_Vertex + 3) = 6;
	*(Graph_Pointer->AdjacencyMatrix_Pointer + 4 * Number_of_Vertex + 4) = 0;



}
unsigned Extend_Shortest_Paths(struct Graph_Tag* Graph_Pointer, int* PreviousShortestWeightMatrix1_Pointer, int* PreviousShortestWeightMatrix2_Pointer, int* PreviousPredecessorMatrix_Pointer)
{
	int Number_of_Vertex = Graph_Pointer->Number_of_Vertex;

	//These pointers are pointing to the saved results until now. 
	int* ShortestWeightMatrix_Pointer = Graph_Pointer->AllPairShortestPath_Result.ShortestWeightMatrix_Pointer;
	int* PredecessorMatrix_Pointer = Graph_Pointer->AllPairShortestPath_Result.PredecessorMatrix_Pointer;


	int* WeightResult_ij_Pointer;
	int* Weight_ik_Pointer;
	int* Weight_kj_Pointer;
	unsigned Counter = 0;
	for (int i = 0; i < Number_of_Vertex; i++)
	{
		for (int j = 0; j < Number_of_Vertex; j++)
		{

			WeightResult_ij_Pointer = ShortestWeightMatrix_Pointer + i * Number_of_Vertex + j;

			for (int k = 0; k < Number_of_Vertex; k++)
			{
				Weight_ik_Pointer = PreviousShortestWeightMatrix1_Pointer + i * Number_of_Vertex + k;
				Weight_kj_Pointer = PreviousShortestWeightMatrix2_Pointer + k * Number_of_Vertex + j;


				//Prevent overflow happenning and satisfy "infinity + any number >= number " property.
				if (*Weight_ik_Pointer != INT_MAX && *Weight_kj_Pointer != INT_MAX)
				{
					if (*Weight_ik_Pointer + *Weight_kj_Pointer < *WeightResult_ij_Pointer)
					{
						//Update the minimum weight of shortest path.
						*WeightResult_ij_Pointer = *Weight_ik_Pointer + *Weight_kj_Pointer;

						//Update the predecessor of shortest path, when the minimum weight updated.
						*(PredecessorMatrix_Pointer + i * Number_of_Vertex + j) = *(PreviousPredecessorMatrix_Pointer + k * Number_of_Vertex + j);

						Counter++;
					}

				}
			}
		}
	}

	return Counter;
}
void Faster_APSP(struct Graph_Tag* Graph_Pointer)
{
	int Number_of_Vertex = Graph_Pointer->Number_of_Vertex;


	//Allocate the space for saving the final results.
	int MatrixSize = Number_of_Vertex * Number_of_Vertex;
	Graph_Pointer->AllPairShortestPath_Result.ShortestWeightMatrix_Pointer = (int*)malloc(MatrixSize * sizeof(int));
	Graph_Pointer->AllPairShortestPath_Result.PredecessorMatrix_Pointer = (int*)malloc(MatrixSize * sizeof(int));

	int* ShortestWeightMatrix_Pointer = Graph_Pointer->AllPairShortestPath_Result.ShortestWeightMatrix_Pointer;
	int* PredecessorMatrix_Pointer = Graph_Pointer->AllPairShortestPath_Result.PredecessorMatrix_Pointer;



	//Allocate the space for previous results.
	int* PreviousShortestWeightMatrix_Pointer = (int*)malloc(MatrixSize * sizeof(int));
	int* PreviousPredecessorMatrix_Pointer = (int*)malloc(MatrixSize * sizeof(int));



	//Initialize the allocated space for input/output matrices of Extend_Shortest_Paths function.
	int* AdjacencyMatrix_Pointer = Graph_Pointer->AdjacencyMatrix_Pointer;
	for (int i = 0; i < Number_of_Vertex; i++)
	{
		for (int j = 0; j < Number_of_Vertex; j++)
		{

			*(ShortestWeightMatrix_Pointer + i * Number_of_Vertex + j) = *(AdjacencyMatrix_Pointer + i * Number_of_Vertex + j);


			if (INT_MAX == (*(PreviousShortestWeightMatrix_Pointer + i * Number_of_Vertex + j) = *(AdjacencyMatrix_Pointer + i * Number_of_Vertex + j)) || i == j)
			{
				*(PreviousPredecessorMatrix_Pointer + i * Number_of_Vertex + j) = INT_MAX;
				*(PredecessorMatrix_Pointer + i * Number_of_Vertex + j) = INT_MAX;
			}
			else
			{
				*(PreviousPredecessorMatrix_Pointer + i * Number_of_Vertex + j) = i;
				*(PredecessorMatrix_Pointer + i * Number_of_Vertex + j) = i;
			}
		}
	}


	int IterationNumber = 1;

	unsigned Counter = 1;
	while (IterationNumber < Number_of_Vertex - 1 && Counter != 0)
	{

		//Get the results of this loop for predecessor and shortest weight matrices. 
		Counter = Extend_Shortest_Paths(Graph_Pointer, PreviousShortestWeightMatrix_Pointer, PreviousShortestWeightMatrix_Pointer, PreviousPredecessorMatrix_Pointer);


		//Update the iteration number for this completed loop.
		IterationNumber = 2 * IterationNumber;


		//Prepare the required data for the next loop.
		for (int i = 0; i < Number_of_Vertex; i++)
		{
			for (int j = 0; j < Number_of_Vertex; j++)
			{

				*(PreviousShortestWeightMatrix_Pointer + i * Number_of_Vertex + j) = *(ShortestWeightMatrix_Pointer + i * Number_of_Vertex + j);
				*(PreviousPredecessorMatrix_Pointer + i * Number_of_Vertex + j) = *(PredecessorMatrix_Pointer + i * Number_of_Vertex + j);

			}

		}

	}


	free(PreviousShortestWeightMatrix_Pointer);
	free(PreviousPredecessorMatrix_Pointer);


}