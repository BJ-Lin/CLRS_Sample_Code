/**
 * @file    Strassen_Matrix_Multiply_Recursive.c
 * @brief
 * Implements matrix multiplication using Strassen's algorithm.
 * There is no pseudo code on the CLRS textbook, but the algorithm is described in detail from Introduction to Algorithms 4th, CLRS.
 *
 * @details
 * Implements Strassen's matrix multiplication algorithm, which is an efficient algorithm for multiplying two square matrices. 
 * The algorithm reduces the number of multiplications required, resulting in a time complexity of O(n^log2(7)) ≈ O(n^2.81) for n x n matrices.
 *
 * @author  BJ-Lin , the email address is : <s90333125@gmail.com>
 * @date    2026-04-27
 *
 * @version 1.0
 *
 */
#include "..\Header.h"



 //This function is used for checking whether the length of matrix is power of 2 or not, 
 //and it will return 1 if the length of matrix is not power of 2, otherwise, it will return 0.
unsigned int  Check_SquareMatrix_Length_Power_Of_Two(unsigned int Matrix_Length_n, unsigned int* Been_Checked_Flag_Pointer)
{
	//Judge wheather the length of matrix is checked for power of 2 or not.
	*Been_Checked_Flag_Pointer = 1;

	if (Matrix_Length_n == 1)
	{
		printf("The length of matrix is 1\n");
		return 0;
	}

	else if (Matrix_Length_n < 1)
	{
		printf("The length of matrix is smaller than 1 (Incorrect).\nFunction Termination");
		return 1;
	}
	else if (Matrix_Length_n > 1)
	{
		unsigned int Compared_Target = 1;
		unsigned int Count = 0;
		unsigned int Maximum_Loop_Number = CHAR_BIT * sizeof(Matrix_Length_n); //To get the number of bits of Matrix_Length_n.  
		for (unsigned int i = 0; i < Maximum_Loop_Number; i++)
		{
			if ((Matrix_Length_n & Compared_Target) == Compared_Target)
			{
				Count++;
			}
			Compared_Target = Compared_Target << 1;

		}

		if (Count == 1)
		{
			printf("The length of matrix is power of 2.\n");
			return 0;
		}
		else
		{
			printf("The number is not power of 2 (Incorrect).\nFunction Termination");
			return 1;

		}

	}
}



 /**
  * @brief
  * Implements matrix multiplication using Strassen's algorithm.
  * There is no pseudo code on the CLRS textbook, but the algorithm is described in detail from Introduction to Algorithms 4th, CLRS, P86 to P89.
  *
  * @param[in]		Matrix_A_Pointer			Pointer to the first input matrix.
  * @param[in]		Matrix_B_Pointer			Pointer to the second input matrix.
  * @param[out]		Matrix_C_Pointer			Pointer to the output matrix.
  * @param[in]		Matrix_Length_n				The dimension of the square matrices.
  * @param[in,out]  Been_Checked_Flag_Pointer   Pointer to a flag indicating if the matrix length has been checked.
  *
  * @return No return value (void function).
  *
  * @details
  * Implements Strassen's matrix multiplication algorithm:
  * The length of the matrices must be a positive integer and a power of 2 for the algorithm to work correctly,
  *	that the reason is we need to add/substract/multiply the submatrices of A and B in each recursive function.
  * If the length is not a power of 2, the function will terminate without performing multiplication.
  *
  * Time Complexity:  Theta(n^log2(7)) ≈ O(n^2.81)  (All cases)
  * Space Complexity: Theta(n^2)					(Reserve the temporary arrays for submatrix operations.)
  *
  * @pre
  * - The pointer(s) must not be NULL.
  * - The above memories must be pre-allocated.
  *
  * @post
  * - The parameter Matrix_C_Pointer contains matrix product of Matrix_A_Pointer and Matrix_B_Pointer.
  *
  * @note
  * - No SIMD optimization.
  * - No qualifiers, which are const, volatile, restrict, and _Atomic( Even a type specifier for a new atomic type ).
  *
  * @warning
  * - Undefined behavior if accessing out of bounds for Matrix_A_Pointer, Matrix_B_Pointer, and Matrix_C_Pointer.
  * 
  */
void Strassen_Matrix_Multiply_Recursive(float* Matrix_A_Pointer, float* Matrix_B_Pointer, float* Matrix_C_Pointer, unsigned int Matrix_Length_n, unsigned int* Been_Checked_Flag_Pointer)
{
	//Judge wheather the length of matrix is power of 2,
	//and if the length of matrix is not power of 2, the function will terminate, 
	//otherwise, it will continue to execute the recursive matrix multiplication.
	if (*Been_Checked_Flag_Pointer == 0)
	{

		unsigned int Termination_Flag;
		Termination_Flag = Check_SquareMatrix_Length_Power_Of_Two(Matrix_Length_n, Been_Checked_Flag_Pointer);
		if (Termination_Flag == 1)
		{
			return;
		}

	}



	//Base case
	if (Matrix_Length_n == 1)
	{
		*Matrix_C_Pointer = (*Matrix_A_Pointer) * (*Matrix_B_Pointer);
		return;
	}

	//Divide
	//Compute the initial positions for submatrices of A,B,and C.
	unsigned int Submatrix_Length_n = Matrix_Length_n / 2;
	float* Submatrix_A11_Pointer = Matrix_A_Pointer, * Submatrix_A12_Pointer = Matrix_A_Pointer + Submatrix_Length_n, * Submatrix_A21_Pointer = Matrix_A_Pointer + Submatrix_Length_n * Matrix_Length_n, * Submatrix_A22_Pointer = Matrix_A_Pointer + Submatrix_Length_n * Matrix_Length_n + Submatrix_Length_n;
	float* Submatrix_B11_Pointer = Matrix_B_Pointer, * Submatrix_B12_Pointer = Matrix_B_Pointer + Submatrix_Length_n, * Submatrix_B21_Pointer = Matrix_B_Pointer + Submatrix_Length_n * Matrix_Length_n, * Submatrix_B22_Pointer = Matrix_B_Pointer + Submatrix_Length_n * Matrix_Length_n + Submatrix_Length_n;
	float* Submatrix_C11_Pointer = Matrix_C_Pointer, * Submatrix_C12_Pointer = Matrix_C_Pointer + Submatrix_Length_n, * Submatrix_C21_Pointer = Matrix_C_Pointer + Submatrix_Length_n * Matrix_Length_n, * Submatrix_C22_Pointer = Matrix_C_Pointer + Submatrix_Length_n * Matrix_Length_n + Submatrix_Length_n;



	//Step1.
	//Compute the product of A22 and (B21 - B11), which is the first product of Strassen's algorithm, and store the result in Product_4.
	float* Sum_4 = (float*)malloc(Submatrix_Length_n * Submatrix_Length_n * sizeof(float));
	for (int i = 0; i < Submatrix_Length_n; i++)
	{
		for (int j = 0; j < Submatrix_Length_n; j++)
		{
			*(Sum_4 + i * Submatrix_Length_n + j) = *(Submatrix_B21_Pointer + i * Matrix_Length_n + j) - *(Submatrix_B11_Pointer + i * Matrix_Length_n + j);
		}
	}

	float* Product_4 = (float*)malloc(Submatrix_Length_n * Submatrix_Length_n * sizeof(float));

	float* Submatrix_A22_Copy_Pointer = (float*)malloc(Submatrix_Length_n * Submatrix_Length_n * sizeof(float));
	for (int i = 0; i < Submatrix_Length_n; i++)
	{
		for (int j = 0; j < Submatrix_Length_n; j++)
		{
			*(Submatrix_A22_Copy_Pointer + i * Submatrix_Length_n + j) = *(Submatrix_A22_Pointer + i * Matrix_Length_n + j);
		}
	}
	Strassen_Matrix_Multiply_Recursive(Submatrix_A22_Copy_Pointer, Sum_4, Product_4, Submatrix_Length_n, Been_Checked_Flag_Pointer);


	//Step2.
	//Compute the product of A11 and (B12 - B22), which is the second product of Strassen's algorithm, and store the result in Product_1.
	float* Sum_1 = (float*)malloc(Submatrix_Length_n * Submatrix_Length_n * sizeof(float));
	for (int i = 0; i < Submatrix_Length_n; i++)
	{
		for (int j = 0; j < Submatrix_Length_n; j++)
		{
			*(Sum_1 + i * Submatrix_Length_n + j) = *(Submatrix_B12_Pointer + i * Matrix_Length_n + j) - *(Submatrix_B22_Pointer + i * Matrix_Length_n + j);
		}
	}

	float* Product_1 = (float*)malloc(Submatrix_Length_n * Submatrix_Length_n * sizeof(float));

	float* Submatrix_A11_Copy_Pointer = (float*)malloc(Submatrix_Length_n * Submatrix_Length_n * sizeof(float));
	for (int i = 0; i < Submatrix_Length_n; i++)
	{
		for (int j = 0; j < Submatrix_Length_n; j++)
		{
			*(Submatrix_A11_Copy_Pointer + i * Submatrix_Length_n + j) = *(Submatrix_A11_Pointer + i * Matrix_Length_n + j);
		}
	}
	Strassen_Matrix_Multiply_Recursive(Submatrix_A11_Copy_Pointer, Sum_1, Product_1, Submatrix_Length_n, Been_Checked_Flag_Pointer);



	//Step3.
	//Compute the product of (A11 + A22) and (B11 + B22), which is the fifth product of Strassen's algorithm, and store the result in Product_5.
	float* Sum_5 = (float*)malloc(Submatrix_Length_n * Submatrix_Length_n * sizeof(float));
	for (int i = 0; i < Submatrix_Length_n; i++)
	{
		for (int j = 0; j < Submatrix_Length_n; j++)
		{
			*(Sum_5 + i * Submatrix_Length_n + j) = *(Submatrix_A11_Pointer + i * Matrix_Length_n + j) + *(Submatrix_A22_Pointer + i * Matrix_Length_n + j);
		}
	}

	float* Sum_6 = (float*)malloc(Submatrix_Length_n * Submatrix_Length_n * sizeof(float));
	for (int i = 0; i < Submatrix_Length_n; i++)
	{
		for (int j = 0; j < Submatrix_Length_n; j++)
		{
			*(Sum_6 + i * Submatrix_Length_n + j) = *(Submatrix_B11_Pointer + i * Matrix_Length_n + j) + *(Submatrix_B22_Pointer + i * Matrix_Length_n + j);
		}
	}


	float* Product_5 = (float*)malloc(Submatrix_Length_n * Submatrix_Length_n * sizeof(float));
	Strassen_Matrix_Multiply_Recursive(Sum_5, Sum_6, Product_5, Submatrix_Length_n, Been_Checked_Flag_Pointer);


	//Step4.
	//Compute the product of (A21 + A22) and B11, which is the third product of Strassen's algorithm, and store the result in Product_3.
	float* Sum_3 = (float*)malloc(Submatrix_Length_n * Submatrix_Length_n * sizeof(float));
	for (int i = 0; i < Submatrix_Length_n; i++)
	{
		for (int j = 0; j < Submatrix_Length_n; j++)
		{
			*(Sum_3 + i * Submatrix_Length_n + j) = *(Submatrix_A21_Pointer + i * Matrix_Length_n + j) + *(Submatrix_A22_Pointer + i * Matrix_Length_n + j);
		}
	}


	float* Product_3 = (float*)malloc(Submatrix_Length_n * Submatrix_Length_n * sizeof(float));

	float* Submatrix_B11_Copy_Pointer = (float*)malloc(Submatrix_Length_n * Submatrix_Length_n * sizeof(float));
	for (int i = 0; i < Submatrix_Length_n; i++)
	{
		for (int j = 0; j < Submatrix_Length_n; j++)
		{
			*(Submatrix_B11_Copy_Pointer + i * Submatrix_Length_n + j) = *(Submatrix_B11_Pointer + i * Matrix_Length_n + j);
		}
	}
	Strassen_Matrix_Multiply_Recursive(Sum_3, Submatrix_B11_Copy_Pointer, Product_3, Submatrix_Length_n, Been_Checked_Flag_Pointer);



	//Step5.
	//Compute the product of (A11 - A21) and (B11 + B12), which is the fourth product of Strassen's algorithm, and store the result in Product_7.
	float* Sum_9 = (float*)malloc(Submatrix_Length_n * Submatrix_Length_n * sizeof(float));
	for (int i = 0; i < Submatrix_Length_n; i++)
	{
		for (int j = 0; j < Submatrix_Length_n; j++)
		{
			*(Sum_9 + i * Submatrix_Length_n + j) = *(Submatrix_A11_Pointer + i * Matrix_Length_n + j) - *(Submatrix_A21_Pointer + i * Matrix_Length_n + j);
		}
	}

	float* Sum_10 = (float*)malloc(Submatrix_Length_n * Submatrix_Length_n * sizeof(float));
	for (int i = 0; i < Submatrix_Length_n; i++)
	{
		for (int j = 0; j < Submatrix_Length_n; j++)
		{
			*(Sum_10 + i * Submatrix_Length_n + j) = *(Submatrix_B11_Pointer + i * Matrix_Length_n + j) + *(Submatrix_B12_Pointer + i * Matrix_Length_n + j);
		}
	}


	float* Product_7 = (float*)malloc(Submatrix_Length_n * Submatrix_Length_n * sizeof(float));
	Strassen_Matrix_Multiply_Recursive(Sum_9, Sum_10, Product_7, Submatrix_Length_n, Been_Checked_Flag_Pointer);

	//Step6.
	//Compute the product of (A12 - A22) and (B21 + B22), which is the sixth product of Strassen's algorithm, and store the result in Product_6.
	float* Sum_7 = (float*)malloc(Submatrix_Length_n * Submatrix_Length_n * sizeof(float));
	for (int i = 0; i < Submatrix_Length_n; i++)
	{
		for (int j = 0; j < Submatrix_Length_n; j++)
		{
			*(Sum_7 + i * Submatrix_Length_n + j) = *(Submatrix_A12_Pointer + i * Matrix_Length_n + j) - *(Submatrix_A22_Pointer + i * Matrix_Length_n + j);
		}
	}

	float* Sum_8 = (float*)malloc(Submatrix_Length_n * Submatrix_Length_n * sizeof(float));
	for (int i = 0; i < Submatrix_Length_n; i++)
	{
		for (int j = 0; j < Submatrix_Length_n; j++)
		{
			*(Sum_8 + i * Submatrix_Length_n + j) = *(Submatrix_B21_Pointer + i * Matrix_Length_n + j) + *(Submatrix_B22_Pointer + i * Matrix_Length_n + j);
		}
	}

	float* Product_6 = (float*)malloc(Submatrix_Length_n * Submatrix_Length_n * sizeof(float));
	Strassen_Matrix_Multiply_Recursive(Sum_7, Sum_8, Product_6, Submatrix_Length_n, Been_Checked_Flag_Pointer);


	//Step7
	//Compute the product of (A11 + A12) and B22, which is the seventh product of Strassen's algorithm, and store the result in Product_2.
	float* Sum_2 = (float*)malloc(Submatrix_Length_n * Submatrix_Length_n * sizeof(float));
	for (int i = 0; i < Submatrix_Length_n; i++)
	{
		for (int j = 0; j < Submatrix_Length_n; j++)
		{
			*(Sum_2 + i * Submatrix_Length_n + j) = *(Submatrix_A11_Pointer + i * Matrix_Length_n + j) + *(Submatrix_A12_Pointer + i * Matrix_Length_n + j);
		}
	}


	float* Product_2 = (float*)malloc(Submatrix_Length_n * Submatrix_Length_n * sizeof(float));

	float* Submatrix_B22_Copy_Pointer = (float*)malloc(Submatrix_Length_n * Submatrix_Length_n * sizeof(float));
	for (int i = 0; i < Submatrix_Length_n; i++)
	{
		for (int j = 0; j < Submatrix_Length_n; j++)
		{
			*(Submatrix_B22_Copy_Pointer + i * Submatrix_Length_n + j) = *(Submatrix_B22_Pointer + i * Matrix_Length_n + j);
		}
	}
	Strassen_Matrix_Multiply_Recursive(Sum_2, Submatrix_B22_Copy_Pointer, Product_2, Submatrix_Length_n, Been_Checked_Flag_Pointer);



	//Combine
	//Submatrices C11
	for (int i = 0; i < Submatrix_Length_n; i++)
	{
		for (int j = 0; j < Submatrix_Length_n; j++)
		{
			*(Submatrix_C11_Pointer + i * Matrix_Length_n + j) = *(Product_5 + i * Submatrix_Length_n + j) + *(Product_4 + i * Submatrix_Length_n + j) - *(Product_2 + i * Submatrix_Length_n + j) + *(Product_6 + i * Submatrix_Length_n + j);
		}
	}



	//Submatrices C12
	for (int i = 0; i < Submatrix_Length_n; i++)
	{
		for (int j = 0; j < Submatrix_Length_n; j++)
		{
			*(Submatrix_C12_Pointer + i * Matrix_Length_n + j) = *(Product_1 + i * Submatrix_Length_n + j) + *(Product_2 + i * Submatrix_Length_n + j);
		}
	}

	//Submatrices C21
	for (int i = 0; i < Submatrix_Length_n; i++)
	{
		for (int j = 0; j < Submatrix_Length_n; j++)
		{
			*(Submatrix_C21_Pointer + i * Matrix_Length_n + j) = *(Product_3 + i * Submatrix_Length_n + j) + *(Product_4 + i * Submatrix_Length_n + j);
		}
	}

	//Submatrices C22
	for (int i = 0; i < Submatrix_Length_n; i++)
	{
		for (int j = 0; j < Submatrix_Length_n; j++)
		{
			*(Submatrix_C22_Pointer + i * Matrix_Length_n + j) = *(Product_5 + i * Submatrix_Length_n + j) + *(Product_1 + i * Submatrix_Length_n + j) - *(Product_3 + i * Submatrix_Length_n + j) - *(Product_7 + i * Submatrix_Length_n + j);
		}
	}


	free(Sum_1);
	free(Sum_2);
	free(Sum_3);
	free(Sum_4);
	free(Sum_5);
	free(Sum_6);
	free(Sum_7);
	free(Sum_8);
	free(Sum_9);
	free(Sum_10);

	free(Product_1);
	free(Product_2);
	free(Product_3);
	free(Product_4);
	free(Product_5);
	free(Product_6);
	free(Product_7);


	free(Submatrix_A22_Copy_Pointer);
	free(Submatrix_A11_Copy_Pointer);
	free(Submatrix_B11_Copy_Pointer);
	free(Submatrix_B22_Copy_Pointer);

}