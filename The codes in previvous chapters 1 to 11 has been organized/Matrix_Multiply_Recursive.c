/**
 * @file    Matrix_Multiply_Recursive.c
 * @brief
 * Implements recursive matrix multiplication.
 * The pseudo code is from Introduction to algorithm 4th, CLRS.
 *
 * @details
 * Implements recursive matrix multiplication:
 *	Matrix_C = Matrix_A * Matrix_B
 *
 * @author  BJ-Lin , the email address is : <s90333125@gmail.com>
 * @date    2026-04-26
 *
 * @version 1.0
 *
 */

#include "..\Header.h"



float Matrix_A[Init_Matrix_Length_n][Init_Matrix_Length_m] = { {1,2,3,4},{1,2,3,4},{1,2,3,4},{1,2,3,4} };
float Matrix_B[Init_Matrix_Length_m][Init_Matrix_Length_r] = { {1,1,1,1},{2,2,2,2},{3,3,3,3},{4,4,4,4} };
float Matrix_C[Init_Matrix_Length_n][Init_Matrix_Length_r] = { 0 };


/**
 * @brief
 * Implements recursive matrix multiplication.
 * The pseudo code is from Introduction to algorithm 4th, CLRS, p83, which is MATRIX-MULTIPLY-RECURSIVE( A , B , C , n ).
 *
 * @param[in]      Matrix_A_Position        The position of the submatrix in Matrix A.
 * @param[in]      Matrix_B_Position        The position of the submatrix in Matrix B.
 * @param[in,out]  Matrix_C_Position        The position of the submatrix in Matrix C.
 * @param[in]      Matrix_Length_n          The number of rows in the submatrix of Matrix A.
 * @param[in]      Matrix_Length_m          The number of columns in the submatrix of Matrix A.
 * @param[in]      Matrix_Length_r          The number of columns in the submatrix of Matrix B.
 *
 * @return No return value (void function).
 *
 * @details
 * Implements recursive matrix multiplication:
 *   Matrix_C = Matrix_A * Matrix_B
 *
 *
 * Time Complexity:  Theta(n^3)		( if n = m = r = 2^k ; k >= 0 )
 * 
 *
 * @pre
 * - Matrix A and Matrix B must be compatible for multiplication, which means the number of columns in Matrix A must be equal to the number of rows in Matrix B.
 * 
 *
 * @post
 * - The parameter Matrix C contains the product of Matrix A and Matrix B for the specified submatrices.
 *
 * @note
 * - No SIMD optimization.
 * - No qualifiers, which are const, volatile, restrict, and _Atomic( Even a type specifier for a new atomic type ).
 *
 * @warning
 * - The length of each matrix must be positive integer.
 */
void Matrix_Multiply_Recursive(unsigned int Matrix_A_Position[2], unsigned int Matrix_B_Position[2], unsigned int Matrix_C_Position[2], unsigned int Matrix_Length_n, unsigned int Matrix_Length_m, unsigned int Matrix_Length_r)
{
	/*Base case*/
	if (Matrix_Length_n <= 1 && Matrix_Length_m <= 1 && Matrix_Length_r <= 1)
	{
		Matrix_C[Matrix_C_Position[0]][Matrix_C_Position[1]] = Matrix_C[Matrix_C_Position[0]][Matrix_C_Position[1]] + Matrix_A[Matrix_A_Position[0]][Matrix_A_Position[1]] * Matrix_B[Matrix_B_Position[0]][Matrix_B_Position[1]];
		return;
	}



	/*Divide*/
	/* Compute the first half length of matrix A & B & C */
	unsigned int First_Half_Amount_n = 0, First_Half_Amount_m = 0, First_Half_Amount_r = 0;
	unsigned char Half_Flag_n = 0, Half_Flag_m = 0, Half_Flag_r = 0;

	if (Matrix_Length_n > 1)
	{
		First_Half_Amount_n = (1 + Matrix_Length_n) / 2;
		Half_Flag_n = 1;  //Judge if we divide the matrix into two halves in n-direction.
	}


	if (Matrix_Length_m > 1)
	{
		First_Half_Amount_m = (1 + Matrix_Length_m) / 2;
		Half_Flag_m = 1;  //Judge if we divide the matrix into two halves in m-direction.
	}

	if (Matrix_Length_r > 1)
	{
		First_Half_Amount_r = (1 + Matrix_Length_r) / 2;
		Half_Flag_r = 1;  //Judge if we divide the matrix into two halves in r-direction.
	}



	/*Compute the position && length of submatrix of Matrix A*/
	unsigned int Length_A11_n = 0, Length_A11_m = 0, Length_A12_n = 0, Length_A12_m = 0, Length_A21_n = 0, Length_A21_m = 0, Length_A22_n = 0, Length_A22_m = 0;
	unsigned int Submatrix_A11_Position[2] = { 0 }, Submatrix_A12_Position[2] = { 0 }, Submatrix_A21_Position[2] = { 0 }, Submatrix_A22_Position[2] = { 0 };

	if (Half_Flag_n == 0 && Half_Flag_m == 0)
	{
		//Given position of submatrix .
		Submatrix_A11_Position[0] = Matrix_A_Position[0];
		Submatrix_A11_Position[1] = Matrix_A_Position[1];

		//Given Length A11.
		Length_A11_n = Matrix_Length_n;
		Length_A11_m = Matrix_Length_m;

	}


	if (Half_Flag_n == 0 && Half_Flag_m == 1)
	{
		//Given position of submatrix. 
		Submatrix_A11_Position[0] = Matrix_A_Position[0];
		Submatrix_A11_Position[1] = Matrix_A_Position[1];

		Submatrix_A12_Position[0] = Matrix_A_Position[0];
		Submatrix_A12_Position[1] = Matrix_A_Position[1] + First_Half_Amount_m;

		//Given Length A11.
		Length_A11_n = Matrix_Length_n;
		Length_A11_m = First_Half_Amount_m;

		//Given Length A12.
		Length_A12_n = Matrix_Length_n;
		Length_A12_m = (Matrix_Length_m - First_Half_Amount_m);

	}

	if (Half_Flag_n == 1 && Half_Flag_m == 0)
	{
		//Given position of submatrix.
		Submatrix_A11_Position[0] = Matrix_A_Position[0];
		Submatrix_A11_Position[1] = Matrix_A_Position[1];

		Submatrix_A21_Position[0] = Matrix_A_Position[0] + First_Half_Amount_n;
		Submatrix_A21_Position[1] = Matrix_A_Position[1];


		//Given Length A11.
		Length_A11_n = First_Half_Amount_n;
		Length_A11_m = Matrix_Length_m;

		//Given Length A21.
		Length_A21_n = (Matrix_Length_n - First_Half_Amount_n);
		Length_A21_m = Matrix_Length_m;

	}


	if (Half_Flag_n == 1 && Half_Flag_m == 1)
	{
		//Given position of submatrix.
		Submatrix_A11_Position[0] = Matrix_A_Position[0];
		Submatrix_A11_Position[1] = Matrix_A_Position[1];

		Submatrix_A12_Position[0] = Matrix_A_Position[0];
		Submatrix_A12_Position[1] = Matrix_A_Position[1] + First_Half_Amount_m;

		Submatrix_A21_Position[0] = Matrix_A_Position[0] + First_Half_Amount_n;
		Submatrix_A21_Position[1] = Matrix_A_Position[1];

		Submatrix_A22_Position[0] = Matrix_A_Position[0] + First_Half_Amount_n;
		Submatrix_A22_Position[1] = Matrix_A_Position[1] + First_Half_Amount_m;


		//Given Length A11.
		Length_A11_n = First_Half_Amount_n;
		Length_A11_m = First_Half_Amount_m;

		//Given Length A12.
		Length_A12_n = First_Half_Amount_n;
		Length_A12_m = (Matrix_Length_m - First_Half_Amount_m);

		//Given Length A21.
		Length_A21_n = (Matrix_Length_n - First_Half_Amount_n);
		Length_A21_m = First_Half_Amount_m;

		//Given Length A22.
		Length_A22_n = (Matrix_Length_n - First_Half_Amount_n);
		Length_A22_m = (Matrix_Length_m - First_Half_Amount_m);

	}



	/* Compute the position && length of submatrix of Matrix B */
	unsigned int Length_B11_r = 0, Length_B12_r = 0, Length_B21_r = 0, Length_B22_r = 0;
	unsigned int Submatrix_B11_Position[2] = { 0 }, Submatrix_B12_Position[2] = { 0 }, Submatrix_B21_Position[2] = { 0 }, Submatrix_B22_Position[2] = { 0 };

	if (Half_Flag_m == 0 && Half_Flag_r == 0)
	{
		//Given position of submatrix. 
		Submatrix_B11_Position[0] = Matrix_B_Position[0];
		Submatrix_B11_Position[1] = Matrix_B_Position[1];

		//Given Length B11.
		Length_B11_r = Matrix_Length_r;

	}


	if (Half_Flag_m == 0 && Half_Flag_r == 1)
	{
		//Given position of submatrix .
		Submatrix_B11_Position[0] = Matrix_B_Position[0];
		Submatrix_B11_Position[1] = Matrix_B_Position[1];

		Submatrix_B12_Position[0] = Matrix_B_Position[0];
		Submatrix_B12_Position[1] = Matrix_B_Position[1] + First_Half_Amount_r;

		//Given Length B11.
		Length_B11_r = First_Half_Amount_r;

		//Given Length B12.
		Length_B12_r = (Matrix_Length_r - First_Half_Amount_r);

	}

	if (Half_Flag_m == 1 && Half_Flag_r == 0)
	{
		//Given position of submatrix. 
		Submatrix_B11_Position[0] = Matrix_B_Position[0];
		Submatrix_B11_Position[1] = Matrix_B_Position[1];

		Submatrix_B21_Position[0] = Matrix_B_Position[0] + First_Half_Amount_m;
		Submatrix_B21_Position[1] = Matrix_B_Position[1];


		//Given Length B11.
		Length_B11_r = Matrix_Length_r;

		//Given Length B21.
		Length_B21_r = Matrix_Length_r;

	}


	if (Half_Flag_m == 1 && Half_Flag_r == 1)
	{
		//Given position of submatrix.
		Submatrix_B11_Position[0] = Matrix_B_Position[0];
		Submatrix_B11_Position[1] = Matrix_B_Position[1];

		Submatrix_B12_Position[0] = Matrix_B_Position[0];
		Submatrix_B12_Position[1] = Matrix_B_Position[1] + First_Half_Amount_r;

		Submatrix_B21_Position[0] = Matrix_B_Position[0] + First_Half_Amount_m;
		Submatrix_B21_Position[1] = Matrix_B_Position[1];

		Submatrix_B22_Position[0] = Matrix_B_Position[0] + First_Half_Amount_m;
		Submatrix_B22_Position[1] = Matrix_B_Position[1] + First_Half_Amount_r;


		//Given Length B11.
		Length_B11_r = First_Half_Amount_r;

		//Given Length B12.
		Length_B12_r = (Matrix_Length_r - First_Half_Amount_r);

		//Given Length B21.
		Length_B21_r = First_Half_Amount_r;

		//Given Length B22.
		Length_B22_r = (Matrix_Length_r - First_Half_Amount_r);

	}





	/*Compute the position && length of submatrix of Matrix C */
	unsigned int Submatrix_C11_Position[2] = { 0 }, Submatrix_C12_Position[2] = { 0 }, Submatrix_C21_Position[2] = { 0 }, Submatrix_C22_Position[2] = { 0 };

	if (Half_Flag_n == 0 && Half_Flag_r == 0)
	{
		//Given position of submatrix. 
		Submatrix_C11_Position[0] = Matrix_C_Position[0];
		Submatrix_C11_Position[1] = Matrix_C_Position[1];

	}


	if (Half_Flag_n == 0 && Half_Flag_r == 1)
	{
		//Given position of submatrix. 
		Submatrix_C11_Position[0] = Matrix_C_Position[0];
		Submatrix_C11_Position[1] = Matrix_C_Position[1];

		Submatrix_C12_Position[0] = Matrix_C_Position[0];
		Submatrix_C12_Position[1] = Matrix_C_Position[1] + First_Half_Amount_r;

	}

	if (Half_Flag_n == 1 && Half_Flag_r == 0)
	{
		//Given position of submatrix. 
		Submatrix_C11_Position[0] = Matrix_C_Position[0];
		Submatrix_C11_Position[1] = Matrix_C_Position[1];

		Submatrix_C21_Position[0] = Matrix_C_Position[0] + First_Half_Amount_n;
		Submatrix_C21_Position[1] = Matrix_C_Position[1];

	}


	if (Half_Flag_n == 1 && Half_Flag_r == 1)
	{
		//Given position of submatrix. 
		Submatrix_C11_Position[0] = Matrix_C_Position[0];
		Submatrix_C11_Position[1] = Matrix_C_Position[1];

		Submatrix_C12_Position[0] = Matrix_C_Position[0];
		Submatrix_C12_Position[1] = Matrix_C_Position[1] + First_Half_Amount_r;

		Submatrix_C21_Position[0] = Matrix_C_Position[0] + First_Half_Amount_n;
		Submatrix_C21_Position[1] = Matrix_C_Position[1];

		Submatrix_C22_Position[0] = Matrix_C_Position[0] + First_Half_Amount_n;
		Submatrix_C22_Position[1] = Matrix_C_Position[1] + First_Half_Amount_r;


	}




	//Conquer the prtoblem. 
	//Matrix C's 1st row * 1st column.
	Matrix_Multiply_Recursive(Submatrix_A11_Position, Submatrix_B11_Position, Submatrix_C11_Position, Length_A11_n, Length_A11_m, Length_B11_r);

	if (Half_Flag_m == 1)  //For the result C11, if we divide the matrix into two halves in m-direction, there exists two submatrix A12 and B21.
		Matrix_Multiply_Recursive(Submatrix_A12_Position, Submatrix_B21_Position, Submatrix_C11_Position, Length_A12_n, Length_A12_m, Length_B21_r);



	//Matrix C's 1st row  * 2st column.
	if (Half_Flag_r == 1)  //For the result C12, if we divide the matrix into two halves in r-direction, there exists two submatrix A11 and B12.
		Matrix_Multiply_Recursive(Submatrix_A11_Position, Submatrix_B12_Position, Submatrix_C12_Position, Length_A11_n, Length_A11_m, Length_B12_r);

	if (Half_Flag_m == 1 && Half_Flag_r == 1)  //For the result C12, if we divide the matrix into two halves in m-direction and r-direction, there exists two submatrix A12 and B22.
		Matrix_Multiply_Recursive(Submatrix_A12_Position, Submatrix_B22_Position, Submatrix_C12_Position, Length_A12_n, Length_A12_m, Length_B22_r);



	//Matrix C's 2st row * 1st column.
	if (Half_Flag_n == 1) //For the result C21, if we divide the matrix into two halves in n-direction, there exists two submatrix A21 and B11.
		Matrix_Multiply_Recursive(Submatrix_A21_Position, Submatrix_B11_Position, Submatrix_C21_Position, Length_A21_n, Length_A21_m, Length_B11_r);

	if (Half_Flag_n == 1 && Half_Flag_m == 1)  //For the result C21, if we divide the matrix into two halves in n-direction and m-direction, there exists two submatrix A22 and B21.
		Matrix_Multiply_Recursive(Submatrix_A22_Position, Submatrix_B21_Position, Submatrix_C21_Position, Length_A22_n, Length_A22_m, Length_B21_r);



	//Matrix C's 2st row * 2st column.
	if (Half_Flag_n == 1 && Half_Flag_r == 1) //For the result C22, if we divide the matrix into two halves in n-direction and r-direction, there exists two submatrix A21 and B12.
		Matrix_Multiply_Recursive(Submatrix_A21_Position, Submatrix_B12_Position, Submatrix_C22_Position, Length_A21_n, Length_A21_m, Length_B12_r);

	if (Half_Flag_n == 1 && Half_Flag_m == 1 && Half_Flag_r == 1) //For the result C22, if we divide the matrix into two halves in n-direction and m-direction and r-direction, there exists two submatrix A22 and B22.
		Matrix_Multiply_Recursive(Submatrix_A22_Position, Submatrix_B22_Position, Submatrix_C22_Position, Length_A22_n, Length_A22_m, Length_B22_r);



}