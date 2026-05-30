#ifndef HEADER_H
#define HEADER_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <float.h>
#include <limits.h>
#include <stdint.h>
#include <string.h>


#define INSERTION_SORT_MODULE 0  //If you want to test the Insertion Sort module, please set the value to 1, otherwise, set it to 0.
int InsertedArray[18];
void Insertion_Sort(int Sort_Size, int* Array); 



#define MERGE_SORT_MODULE 0	//If you want to test the Merge Sort module, please set the value to 1, otherwise, set it to 0.
void Merge_Sort(int* Array, int Sort_Size);
void Merge_Subrouting(int Left_Size, int* Left_Initial_Address, int Right_Size, int* Right_Initial_Address);






#define RECURSIVE_MATRIX_MODULE 0	//If you want to test the Recursive Matrix Multiplication module, please set the value to 1, otherwise, set it to 0.
#define Init_Matrix_Length_n  4   /**< Matrix width */
#define Init_Matrix_Length_m  4   /**< Matrix height */
#define Init_Matrix_Length_r  4   /**< Matrix depth */
float Matrix_A[Init_Matrix_Length_n][Init_Matrix_Length_m];
float Matrix_B[Init_Matrix_Length_m][Init_Matrix_Length_r];
float Matrix_C[Init_Matrix_Length_n][Init_Matrix_Length_r];
void Matrix_Multiply_Recursive(unsigned int Matrix_A_Position[2], unsigned int Matrix_B_Position[2], unsigned int Matrix_C_Position[2], unsigned int Matrix_Length_n, unsigned int Matrix_Length_m, unsigned int Matrix_Length_r); 






#define STRASSEN_MATRIX_MULTIPLY_RECURSIVE_MODULE 0	//If you want to test the Strassen Matrix Multiplication module, please set the value to 1, otherwise, set it to 0.
unsigned int  Check_SquareMatrix_Length_Power_Of_Two(unsigned int Matrix_Length_n, unsigned int* Been_Checked_Flag_Pointer); 
void Strassen_Matrix_Multiply_Recursive(float* Matrix_A_Pointer, float* Matrix_B_Pointer, float* Matrix_C_Pointer, unsigned int Matrix_Length_n, unsigned int* Been_Checked_Flag_Pointer);






#define MAX_HEAP_SORT_MODULE 0	//If you want to test the Max-Heap Sort module, please set the value to 1, otherwise, set it to 0.
float Heap_Array[27];
void Max_Heapify(float Array[], size_t Heap_Size, unsigned Root_Index); 
void Build_Max_Heap(float Array[], size_t Heap_Size); 
void MaxHeapSort(float Array[], size_t Heap_Size);





#define MIN_HEAP_SORT_MODULE 0	//If you want to test the Min-Heap Sort module, please set the value to 1, otherwise, set it to 0.
void Min_Heapify(float Array[], size_t Heap_Size, unsigned Root_Index); 
void Build_Min_Heap(float Array[], size_t Heap_Size);  
void MinHeapSort(float Array[], size_t Heap_Size);  








#define PRIORITY_QUEUE_MAX_HEAP_MODULE 0	//If you want to test the Priority Queue module, please set the value to 1, otherwise, set it to 0.
/**
 * @struct Object_of_Queue_Tag
 * @brief  Basic object structure in the max priority queue.
 */
struct Object_of_Queue_Tag
{
	float Key;
	unsigned Index;  //The range of objjects: [1 , n], which are not for array indices.
};

/**
 * @struct MaxPriority_Queue_Tag
 * @brief  Basic structure for a max priority queue.
 */
struct MaxPriority_Queue_Tag
{
	size_t Array_Size;
	size_t Queue_Size;
	struct Object_of_Queue_Tag* PointerArray[30];
};

struct Object_of_Queue_Tag Queue_Object[10];
struct MaxPriority_Queue_Tag MaxPriority_Queue;

void Queue_Max_Heapify(struct MaxPriority_Queue_Tag* MaxPriority_Queue_Pointer, unsigned Root_Index); 
signed char Queue_Max_Heap_Maximum(struct MaxPriority_Queue_Tag* MaxPriority_Queue_Pointer, struct Object_of_Queue_Tag** MaximumAddress_Pointer); 
struct Object_of_Queue_Tag* Queue_Max_Heap_Extract_Maximum(struct MaxPriority_Queue_Tag* MaxPriority_Queue_Pointer); 
signed Queue_Max_Heap_Increase_Key(struct MaxPriority_Queue_Tag* MaxPriority_Queue_Pointer, struct Object_of_Queue_Tag* Object_Pointer, float New_Key); 
signed Queue_Max_Heap_Insert(struct MaxPriority_Queue_Tag* MaxPriority_Queue_Pointer, struct Object_of_Queue_Tag* InsertedObject_Pointer);
void Max_Heap_Delete(struct MaxPriority_Queue_Tag* MaxPriority_Queue_Pointer, struct Object_of_Queue_Tag* DeletedObject_Pointer);






#define RANDOMIZED_QUICK_SORT_MODULE 0	//If you want to test the Randomized Quick Sort module, please set the value to 1, otherwise, set it to 0.
float QuickSort_Array[11];
int Randomized_QuickSort_Partition(float Array[], int Array_Size);
void Randomized_QuickSort(float Array[], int Array_Size);
void Call_Randomized_QuickSort(float Array[], int Array_Size);










#define THREE_WAY_RANDOMIZED_QUICK_SORT_MODULE 0	//If you want to test the Three-Way Randomized Quick Sort module, please set the value to 1, otherwise, set it to 0.
void ThreeWay_Randomized_QuickSort_Partition(float Array[], int Array_Size, int* Low_High_Side_Size);
void ThreeWay_Randomized_QuickSort(float Array[], int Array_Size);
void Call_ThreeWay_Randomized_QuickSort(float Array[], int Array_Size);








#define COUNTING_SORT_MODULE 0	//If you want to test the Counting Sort module, please set the value to 1, otherwise, set it to 0.
int Counting_Array[8];
void Counting_Sort(int Array[], int* MaxMinBoundary_Pointer, int SortedInstant_Array[], size_t Instant_Size); 








#define MSD_RADIX_SORT_MODULE 0	//If you want to test the MSD radix sort module, please set the value to 1, otherwise, set it to 0.
int MostSignificant_Array[12];
unsigned int CalculateSortedDigitNumber_Base10_INT(int SortedInstant_Array[], size_t Instant_Size);
void MSD_Radix_Sort(int SortedInstant_Array[], size_t Instant_Size, unsigned int Number_Of_Digits); 





#define LSD_RADIX_SORT_MODULE 0	//If you want to test the LSD radix sort module, please set the value to 1, otherwise, set it to 0.
void LSD_Radix_Sort(int SortedInstant_Array[], size_t Instant_Size, unsigned Number_Of_Digits); 






#define BUCKET_SORT_MODULE 0	//If you want to test the Bucket Sort module, please set the value to 1, otherwise, set it to 0.
float Bucket_Numbers[11]; //Value range is [0,1) for n-bucket
/**
 * @struct Carrier_In_Bucket_Tag
 * @brief  Basic structure for a carrier in a bucket.
 */
struct Carrier_In_Bucket_Tag
{
	struct Carrier_In_Bucket_Tag* Prev;
	struct Carrier_In_Bucket_Tag* Next;
	float Key;

};
/**
 * @struct Bucket_Tag
 * @brief  Basic structure for a bucket (doubly-linked list).
 */
struct Bucket_Tag //Doubly-Linked List
{
	struct Carrier_In_Bucket_Tag* head;

};
void Bucket_DoublyList_Prepend(struct Bucket_Tag* LinkedList_Pointer, struct Carrier_In_Bucket_Tag* Insertion_Element_Address);
void Bucket_Sort(float Array[], size_t Array_Size, size_t Bucket_Size);
void Bucket_DoublyList_Insert(struct Carrier_In_Bucket_Tag* Followed_Obejct_Address, struct Carrier_In_Bucket_Tag* Insertion_Element_Address);
void Bucket_DoublyList_Delete(struct Bucket_Tag* LinkedList_Pointer, struct Carrier_In_Bucket_Tag* Delete_Element_Address);
void Insertion_Sort_For_Bucket(struct Bucket_Tag* Bucket_Address);





#define SELECTION_OF_MAXIMUM_MINIMUM_MODULE 0	//If you want to test the module of selection of maximum and minimum, please set the value to 1, otherwise, set it to 0.
void Selection_Of_Maximum_Minimum(float Array[], size_t Array_Size, float* Max_Pointer, float* Min_Pointer);




#define RANDOMIZED_SELECT_MODULE 0	//If you want to test the module of randomized selection of any order, please set the value to 1, otherwise, set it to 0.
float Randomized_Select(float Array[], size_t Array_Size, unsigned Order); 
float Call_Randomized_Select(float Array[], size_t Array_Size, unsigned Order);




#define SELECTION_WORSTCASE_LINEARTIME_MODULE 0	//If you want to test the module of linear time selection of any order in worst case, please set the value to 1, otherwise, set it to 0.
void ThreeWay_Randomized_Partition_Around(float Array[], int Array_Size, float* Pivot_Address, int* Low_High_Side_Size);
float* Select(float Array[], size_t Array_Size, unsigned Order);
void Insertion_Sort_For_Select(int Group_Size, float* Array, unsigned int Group_Number);





#define STACK_MODULE 0	//If you want to test the Stack module, please set the value to 1, otherwise, set it to 0.
/**
 * @struct Object_Tag
 * @brief  Basic structure in the stack and queue.
 */
struct Object_Tag
{
	float Key;
};

/**
 * @struct Stack_Tag
 * @brief  The stack structure is constructed with array.
 */
struct Stack_Tag
{
	int Top;  //The index of recently inseted element.
	unsigned int Size; //The number of elements in Array.
	struct Object_Tag Array[15];
};
struct Stack_Tag Stack;
_Bool Stack_Empty(struct Stack_Tag* Stack_Address);
_Bool Stack_Push(struct Stack_Tag* Stack_Address, struct Object_Tag Element);
_Bool Stack_Pop(struct Stack_Tag* Stack_Address, struct Object_Tag* Element_Address); 






#define QUEUE_MODULE 0	//If you want to test the Queue module, please set the value to 1, otherwise, set it to 0.
/**
 * @struct Queue_Tag
 * @brief  The queue structure is constructed with array.
 */
struct Queue_Tag
{
	int Head;
	int Tail; //The empty location for the next inserted element. The range of Head and Tail is [0, Size-1].
	unsigned int Size; //The size of array
	struct Object_Tag Array[15];
};
struct Queue_Tag Queue;
_Bool Enqueue(struct Queue_Tag* Queue_Address, struct Object_Tag* Element_Address);
_Bool Dequeue(struct Queue_Tag* Queue_Address, struct Object_Tag* Element_Address);






#define DOUBLY_LINKEDLIST_MODULE 0	//If you want to test the Doubly Linked List module, please set the value to 1, otherwise, set it to 0.
/**
 * @struct Object2_Tag
 * @brief  The structure for an element in a doubly linked list.
 */
struct Object2_Tag
{	
	struct Object2_Tag* Prev;
	struct Object2_Tag* Next;
	int Key;

};
/**
 * @struct LinkedList_Tag
 * @brief  The structure for a doubly linked list.
 */
struct LinkedList_Tag
{
	struct Object2_Tag *Head;

	unsigned int ObjectCounter;
};
struct LinkedList_Tag LinkedList;
struct Object2_Tag* DoublyList_Search(struct LinkedList_Tag* LinkedList_Pointer,int Search_Key);
void DoublyList_Prepend(struct LinkedList_Tag* LinkedList_Pointer, struct Object2_Tag *Insertion_Element_Address);
void DoublyList_Insert(struct LinkedList_Tag* LinkedList_Pointer, struct Object2_Tag* Followed_Obejct_Address, struct Object2_Tag* Insertion_Element_Address);
void DoublyList_Delete(struct LinkedList_Tag* LinkedList_Pointer, struct Object2_Tag* Delete_Element_Address);








#define CIRCULAR_DOUBLY_LINKEDLIST_MODULE 0	//If you want to test the Circular Doubly Linked List module, please set the value to 1, otherwise, set it to 0.
/**
 * @struct CircularLinkedList_Tag
 * @brief  The structure for a circular doubly linked list.
 */
struct CircularLinkedList_Tag
{
	struct Object2_Tag Senitel;
};
void Circular_DoublyList_Delete(struct Object2_Tag* Delete_Element_Address);
void Circular_DoublyList_Insert(struct Object2_Tag* Followed_Obejct_Address, struct Object2_Tag* Insertion_Element_Address);
struct Object2_Tag* Circular_DoublyList_Search(struct CircularLinkedList_Tag* LinkedList_Pointer, int Search_Key);







#define DIRECT_ADDRESS_TABLE_MODULE 0	//If you want to test the Direct Address Table module, please set the value to 1, otherwise, set it to 0.
/**
 * @struct Direct_Address_Object_Tag
 * @brief  The structure for a direct address table object.
 */
struct Direct_Address_Object_Tag 
{
	int Key;
};
struct Direct_Address_Object_Tag* AddressTable[10];
struct Direct_Address_Object_Tag* Direct_Address_Search(struct Direct_Address_Object_Tag** AddressTable, int Key);
void Direct_Address_Insert(struct Direct_Address_Object_Tag** AddressTable, struct Direct_Address_Object_Tag* Insertion_Object_Pointer);
void Direct_Address_Delete(struct Direct_Address_Object_Tag** AddressTable, struct Direct_Address_Object_Tag* Deletion_Object_Pointer);











#define HASH_TABLE_MODULE 0	//If you want to test the Hash Table module, please set the value to 1, otherwise, set it to 0.
/**
 * @struct UniversalTable_Tag
 * @brief  The structure for a universal hash table object.
 */
struct UniversalTable_Tag
{
	struct LinkedList_Tag* LinkedList;

	int TableLength; //The number of slots in the hash table.
};
struct UniversalTable_Tag UniversalTable;
int Hash_Function(struct UniversalTable_Tag* Table, struct Object2_Tag* ObjectAddress);
void Chained_Hash_Insert(struct UniversalTable_Tag* Table, struct Object2_Tag* InsertionObject_Address);
struct Object2_Tag* Chained_Hash_Search(struct UniversalTable_Tag* Table, struct Object2_Tag* SearchedObject_Address);
void Chained_Hash_Delete(struct UniversalTable_Tag* Table, struct Object2_Tag* DeleteObject_Address);







#define OPEN_ADDRESS_TABLE_MODULE 0	//If you want to test the Open Address Table module, please set the value to 1, otherwise, set it to 0.
//(1)Prime_Number_For_Slot_Number is prime value for over the whole probe sequence. (2) Auxiliary_PrimeModuleDivisor is prime value for not repeating the offset value usually with some key patterns.
#define Prime_Number_For_Slot_Number 29
#define Auxiliary_PrimeModuleDivisor 17

struct Object2_Tag* Table[Prime_Number_For_Slot_Number];
struct Object2_Tag  Object_Array[Prime_Number_For_Slot_Number];
unsigned int Auxiliary_Hashing_Function1(struct Object2_Tag* ObjectAddress);
unsigned int Double_Hashing_Function(struct Object2_Tag* ObjectAddress, unsigned int Probe_Index);
_Bool OpenAddress_Hash_Insert(struct Object2_Tag** Table, unsigned int TableSize, struct Object2_Tag* InsertionObject_Address, unsigned int* Address_of_HashValue_Record);
_Bool OpenAddress_Hash_Search(struct Object2_Tag** Table, unsigned int TableSize, struct Object2_Tag* SearchingObject_Address, unsigned int* Address_of_HashValue_Record);
unsigned int Inverse_Linear_Probing_Hashing_Function(struct Object2_Tag* ObjectAddress, unsigned int SlotPosition, unsigned int TableSize);
_Bool Linear_Probing_Hash_Delete(struct Object2_Tag** Table, unsigned int TableSize, unsigned int Delete_SlotPosition);







#define BINARY_SEARCH_TREE_MODULE 0	//If you want to test the Binary Search Tree module, please set the value to 1, otherwise, set it to 0.
struct Object_of_BinaryTree_Tag
{
	struct Object_of_BinaryTree_Tag* ParentObject_Pointer;
	struct Object_of_BinaryTree_Tag* RightObject_Pointer;
	struct Object_of_BinaryTree_Tag* LeftObject_Pointer;

	int Key;

};
struct BinaryTree_Tag
{
	struct Object_of_BinaryTree_Tag* RootObject_Pointer;

};
struct BinaryTree_Tag BinaryTree;
struct Object_of_BinaryTree_Tag BinaryTree_ObjectArray[9];
void BinaryTree_Insert(struct BinaryTree_Tag* BinaryTree_Pointer, struct Object_of_BinaryTree_Tag* Insertion_Object_Pointer);
_Bool Inorder_BinaryTree_Walk(struct Object_of_BinaryTree_Tag* Root_Pointer);
struct Object_of_BinaryTree_Tag* Iterative_BinaryTree_Search(struct Object_of_BinaryTree_Tag* Root_Pointer,int Searched_Key);
_Bool BinaryTree_Minimum(struct Object_of_BinaryTree_Tag* Root_Pointer, struct Object_of_BinaryTree_Tag** Address_of_Minimum_Object_Pointer);
_Bool BinaryTree_Maximum(struct Object_of_BinaryTree_Tag* Root_Pointer, struct Object_of_BinaryTree_Tag** Address_of_Maximum_Object_Pointer);
_Bool BinaryTree_Successor(struct Object_of_BinaryTree_Tag* Root_Pointer, struct Object_of_BinaryTree_Tag** Address_of_Successor_Object_Pointer);
void BinaryTree_Transplant(struct BinaryTree_Tag* BinaryTree_Pointer, struct Object_of_BinaryTree_Tag* Removed_Node_Pointer, struct Object_of_BinaryTree_Tag* Replacing_Node_Pointer);
void BinaryTree_Delete(struct BinaryTree_Tag* BinaryTree_Pointer, struct Object_of_BinaryTree_Tag* Removed_Node_Pointer);
void Left_Rotate_General(struct BinaryTree_Tag* BinaryTree_Pointer, struct Object_of_BinaryTree_Tag* RotationNode_Pointer);
void Right_Rotate_General(struct BinaryTree_Tag* BinaryTree_Pointer, struct Object_of_BinaryTree_Tag* RotationNode_Pointer);







#define AVL_TREE_MODULE 0	//If you want to test the AVL Tree module, please set the value to 1, otherwise, set it to 0.
struct Object_of_AVLTree_Tag
{
	struct Object_of_AVLTree_Tag* ParentObject_Pointer;
	struct Object_of_AVLTree_Tag* RightObject_Pointer;
	struct Object_of_AVLTree_Tag* LeftObject_Pointer;

	int Key;

	//Add the height attribute for usage of AVL tree.
	int Height;

};
struct AVLTree_Tag
{
	struct Object_of_AVLTree_Tag* RootObject_Pointer;
};
struct AVLTree_Tag AVLTree;
struct Object_of_AVLTree_Tag AVLTree_ObjectArray[9];
void Get_ChildrenHeight(struct Object_of_AVLTree_Tag* Node_y_Pointer, int* RightHeight_Pointer, int* LeftHeight_Pointer);
void Left_Rotate_AVL(struct AVLTree_Tag* BinaryTree_Pointer, struct Object_of_AVLTree_Tag* RotationNode_Pointer);
void Right_Rotate_AVL(struct AVLTree_Tag* BinaryTree_Pointer, struct Object_of_AVLTree_Tag* RotationNode_Pointer);
void Restructure(struct AVLTree_Tag* AVLTree_Pointer, struct Object_of_AVLTree_Tag* Node_x_Pointer);
void Update_HeightDifference(struct Object_of_AVLTree_Tag* Node_y_Pointer, int* Height_Difference_Of_Sibling_Pointer);
void AVLTree_Insert(struct AVLTree_Tag* BinaryTree_Pointer, struct Object_of_AVLTree_Tag* Insertion_Object_Pointer);
void AVLTree_Transplant(struct AVLTree_Tag* BinaryTree_Pointer, struct Object_of_AVLTree_Tag* Removed_Node_Pointer, struct Object_of_AVLTree_Tag* Replacing_Node_Pointer);
_Bool AVLTree_Minimum(struct Object_of_AVLTree_Tag* Root_Pointer, struct Object_of_AVLTree_Tag** Address_of_Minimum_Object_Pointer);
void AVLTree_Delete(struct AVLTree_Tag* BinaryTree_Pointer, struct Object_of_AVLTree_Tag* Removed_Node_Pointer);






#define RED_BLACK_TREE_MODULE 0	//If you want to test the Red-Black Tree module, please set the value to 1, otherwise, set it to 0.
#define RED 0
#define BLACK 1
struct Object_of_RedBlackTree_Tag
{
	struct Object_of_RedBlackTree_Tag* ParentObject_Pointer;
	struct Object_of_RedBlackTree_Tag* RightObject_Pointer;
	struct Object_of_RedBlackTree_Tag* LeftObject_Pointer;

	unsigned char Color;

	int Key;


	unsigned Size; 

};
struct RedBlackTree_Tag
{	
	//The size attribute of sentinel must be zero, that only the rotation funcion use the value to compute some result. 
	struct Object_of_RedBlackTree_Tag* RootObject_Pointer;
	struct Object_of_RedBlackTree_Tag RedBlackTree_Sentinel; 

};
struct RedBlackTree_Tag RedBlackTree ;
struct Object_of_RedBlackTree_Tag RedBlackTree_ObjectArray[9];
void Left_Rotate(struct RedBlackTree_Tag* RedBlackTree_Pointer, struct Object_of_RedBlackTree_Tag* RotationNode_Pointer);
void Right_Rotate(struct RedBlackTree_Tag* RedBlackTree_Pointer, struct Object_of_RedBlackTree_Tag* RotationNode_Pointer);
_Bool Inorder_RedBlackTree_Walk(struct RedBlackTree_Tag* RedBlackTree_Pointer, struct Object_of_RedBlackTree_Tag* Root_Pointer);
void RB_Insert(struct RedBlackTree_Tag* RedBlackTree_Pointer, struct Object_of_RedBlackTree_Tag* Insertion_Object_Pointer);
void RB_Insert_Fixup(struct RedBlackTree_Tag* RedBlackTree_Pointer, struct Object_of_RedBlackTree_Tag* Insertion_Object_Pointer);
void RB_Transplant(struct RedBlackTree_Tag* RedBlackTree_Pointer, struct Object_of_RedBlackTree_Tag* Removed_Node_Pointer, struct Object_of_RedBlackTree_Tag* Replacing_Node_Pointer);
_Bool RB_Minimum(struct RedBlackTree_Tag* RedBlackTree_Pointer, struct Object_of_RedBlackTree_Tag* Root_Pointer, struct Object_of_RedBlackTree_Tag** Address_of_Minimum_Object_Pointer);
void RB_Delete(struct RedBlackTree_Tag* RedBlackTree_Pointer, struct Object_of_RedBlackTree_Tag* Removed_Node_Pointer);
void RB_Delete_Fixup(struct RedBlackTree_Tag* RedBlackTree_Pointer, struct Object_of_RedBlackTree_Tag* Replacing_Node_Pointer);
_Bool RB_Layout(struct RedBlackTree_Tag* RedBlackTree_Pointer, struct Object_of_RedBlackTree_Tag* Root_Pointer);










#define ROD_CUTTING_MODULE 0	//If you want to test the Rod Cutting module, please set the value to 1, otherwise, set it to 0.
int Price_Table[10];
int Memoized_Cut_Rod(int* Price_Table, unsigned int MaxLength_in_Table, int CuttedRod_Length);
int Memoized_Cut_Rod_Aux(int* Price_Table, unsigned int RodLength, int* Optimal_Values_Pointer, int* Optimal_FirstPieceLength_Pointer);






#define MATRIX_CHAIN_MODULE 0	//If you want to test the Matrix Chain module, please set the value to 1, otherwise, set it to 0.
unsigned int MatrixDimensionSequence_Array[7];
unsigned int Number_of_Matrix;
void Print_Optimal_Parenthesize(unsigned int* LastLocation_of_FirstPiece_Pointer, unsigned int i, unsigned int j);
void Matrix_Chain_Order(unsigned int* Matrix_Dimension_Sequence_Pointer, unsigned int Number_of_Matrix);










#define LONGEST_COMMON_SUBSEQUENCE_MODULE 0	//If you want to test the Longest Common Subsequence module, please set the value to 1, otherwise, set it to 0.
unsigned char StringX_Array[8] ;
unsigned char StringY_Array[7] ;
struct CaseIndicator_Tag
{
	signed short* Table;
	unsigned int X_Length;
	unsigned int Y_Length;

};
struct LCS_Tag
{
	int* Table;
	unsigned int X_Length;
	unsigned int Y_Length;

};
void LCS_Length(unsigned char* StringX_Pointer, unsigned int X_Length, unsigned char* StringY_Pointer, unsigned int Y_Length);
void Start_Recursive_LCS(unsigned char* StringX_Pointer, unsigned int X_Length, unsigned char* StringY_Pointer, unsigned int Y_Length);
int Recursive_LCS_Length(unsigned char* StringX_Pointer, unsigned int i, unsigned char* StringY_Pointer, unsigned int j, struct CaseIndicator_Tag* CaseIndicator_Object_Pointer, struct LCS_Tag* LCS_Object_Pointer);
void Print_LCS(struct CaseIndicator_Tag* CaseIndicator_Object, unsigned char* StringX_Pointer, unsigned int LCSTable_Index_i, unsigned int LCSTable_Index_j);






#define OPTIMAL_BINARY_SEARCH_TREE_MODULE 0	//If you want to test the Optimal Binary Search Tree module, please set the value to 1, otherwise, set it to 0.
float ActualKey_Probability_Array[6];
float DummyKey_Probability_Array[6];
int* Optimal_BST(float* ActualKey_Probability_Poiinter, float* DummyKey_Probability_Poiinter, unsigned int Number_of_Node);
struct BinaryTree_Tag Optimal_BinaryTree ;
struct Object_of_BinaryTree_Tag Object_with_ActualKey_Array[6];
struct Object_of_BinaryTree_Tag Object_with_DummyKey_Array[6];
struct Optimal_NeededInformation_Tag
{
	float* ActualKey_Probability_Pointer;
	float* DummyKey_Probability_Pointer;
	unsigned int Number_of_Node;
}Optimal_NeededInformation;
void ActualKeyRecursive_Insert(struct BinaryTree_Tag* BinaryTree_Pointer, struct Object_of_BinaryTree_Tag* Insertion_Object_Pointer, struct LookUpRoot_Tag* LookUpRoot_Pointer);
void OptimalBinaryTree_Insert(struct BinaryTree_Tag* BinaryTree_Pointer, struct Object_of_BinaryTree_Tag* Object_with_ActualKey_Pointer, struct Object_of_BinaryTree_Tag* Object_with_DummyKey_Pointer, struct Optimal_NeededInformation_Tag *Optimal_NeededInformation_Pointer);








#define GREEDY_ACTIVITY_SELECTOR_MODULE 0	//If you want to test the Greedy Activity Selector module, please set the value to 1, otherwise, set it to 0.
struct LookUpRoot_Tag
{
	int Upper_KeyNumber;
	int Lower_KeyNumber;
	int* RootIndex_Pointer;
	unsigned int Table_Length;

}; //KeyNumber = 1 ~ n  ; Index of RootIndex_Pointer is (key Number -1) .
int StartTime_Array[12];
int FinalTime_Array[12];
void Greedy_Activity_Selector(int* StartTime_Pointer, int* FinalTime_Pointer, int Maximum_ActivityIndex);






#define HUFFMAN_CODE_MODULE 0	//If you want to test the Huffman Code module, please set the value to 1, otherwise, set it to 0.
struct CharacterObject_Tag
{
	int Frequency;  
	struct CharacterObject_Tag* ParentObject_Pointer;
	struct CharacterObject_Tag* RightObject_Pointer;
	struct CharacterObject_Tag* LeftObject_Pointer;

	int Index; //Index of element for array

	unsigned char Word; //Only leaf has the meaning of character.

};
struct CharacterObject_Tag CharacterObject_Table[6];
void Hoffman_Queue_Min_Heapify(struct CharacterObject_Tag* PointerArray[], size_t Queue_Size, unsigned Root_Index);
void Hoffman_Queue_Build_Min_Heap(struct CharacterObject_Tag* PointerArray[], size_t Queue_Size);
signed char Hoffman_Queue_Min_Heap_Minimum(struct CharacterObject_Tag* PointerArray[], size_t Queue_Size, struct CharacterObject_Tag** MaximumAddress_Pointer);
struct CharacterObject_Tag* Hoffman_Queue_Min_Heap_Extract_Minimum(struct CharacterObject_Tag* PointerArray[], int* QueueSize_Pointer);
signed Hoffman_Queue_Min_Heap_Increase_Key(struct CharacterObject_Tag* PointerArray[], struct CharacterObject_Tag* Object_Pointer, signed New_Key);
signed Hoffman_Queue_Min_Heap_Insert(struct CharacterObject_Tag* PointerArray[], int* QueueSize_Pointer, struct CharacterObject_Tag* Object_Pointer, size_t Array_Size);
void Huffman(struct CharacterObject_Tag* CharacterObject_Table, int Number_of_Character);









#define DYNAMIC_ORDER_STATISTIC_MODULE 0	//If you want to test the Dynamic Order Statistic module, please set the value to 1, otherwise, set it to 0.
struct Object_of_RedBlackTree_Tag* Os_Select(struct Object_of_RedBlackTree_Tag* Root, unsigned SearchedRank);
unsigned Os_Rank(struct RedBlackTree_Tag* Tree_Pointer, struct Object_of_RedBlackTree_Tag* Node_Pointer);










#define INTERVAL_TREE_MODULE 0	//If you want to test the Interval Tree module, please set the value to 1, otherwise, set it to 0.
struct Interval_Tag
{
	int Low;
	int High;
};
struct Object_of_IntervalTree_Tag
{
	struct Object_of_IntervalTree_Tag* ParentObject_Pointer;
	struct Object_of_IntervalTree_Tag* RightObject_Pointer;
	struct Object_of_IntervalTree_Tag* LeftObject_Pointer;

	unsigned char Color; 

	struct Interval_Tag Interval;

	int MaxEndpointValue;

};
struct IntervalTree_Tag
{
	//The maximum endpoint and Interval.high value of Sentinel must be initialized to be the smallest value for deletion operation, 
	//which prevent to update the maximum endpoint value of Sentinel's parent.
	struct Object_of_IntervalTree_Tag* RootObject_Pointer;
	struct Object_of_IntervalTree_Tag IntervalTree_Sentinel; 

};
struct IntervalTree_Tag IntervalTree;
struct Object_of_IntervalTree_Tag IntervalTree_ObjectArray[10];
void IntervalTree_Insert(struct IntervalTree_Tag* IntervalTree_Pointer, struct Object_of_IntervalTree_Tag* Insertion_Object_Pointer);
void IntervalTree_Insert_Fixup(struct IntervalTree_Tag* IntervalTree_Pointer, struct Object_of_IntervalTree_Tag* Insertion_Object_Pointer);
void IntervalTree_Left_Rotate(struct IntervalTree_Tag* IntervalTree_Pointer, struct Object_of_IntervalTree_Tag* RotationNode_Pointer);
void IntervalTree_Right_Rotate(struct IntervalTree_Tag* IntervalTree_Pointer, struct Object_of_IntervalTree_Tag* RotationNode_Pointer);
_Bool IntervalTree_Layout(struct IntervalTree_Tag* IntervalTree_Pointer, struct Object_of_IntervalTree_Tag* Root_Pointer);
void IntervalTree_Transplant(struct IntervalTree_Tag* IntervalTree_Pointer, struct Object_of_IntervalTree_Tag* Removed_Node_Pointer, struct Object_of_IntervalTree_Tag* Replacing_Node_Pointer);
_Bool IntervalTree_Minimum(struct IntervalTree_Tag* IntervalTree_Pointer, struct Object_of_IntervalTree_Tag* Root_Pointer, struct Object_of_IntervalTree_Tag** Address_of_Minimum_Object_Pointer);
void IntervalTree_Delete(struct IntervalTree_Tag* IntervalTree_Pointer, struct Object_of_IntervalTree_Tag* Removed_Node_Pointer);
void IntervalTree_Delete_Fixup(struct IntervalTree_Tag* IntervalTree_Pointer, struct Object_of_IntervalTree_Tag* Replacing_Node_Pointer);
struct Interval_Tag Interval_Object;
void Interval_Search(struct IntervalTree_Tag* IntervalTree_Pointer, struct Interval_Tag* Interval_Pointer);










#define LINKEDLIST_DISJOINTSET_MODULE 0	//If you want to test the Linked List Disjoint Set module, please set the value to 1, otherwise, set it to 0.
struct SetMember_Tag
{
	int Key;
	struct SetObject_Tag* SetObject_Pointer; //Quikly find out which disjoint object belonging to (Find_Set).

};
struct DisjointObject_Tag
{
	struct SetObject_Tag* SetObject_Pointer; //Return to the set object.
	struct DisjointObject_Tag* Next;
	struct SetMember_Tag* SetMember; //Content
	
};
struct SetObject_Tag
{

	struct DisjointObject_Tag* head; //Need to be initialized with NULL for prepend function 
	struct DisjointObject_Tag* tail;

};
struct SetObject_Tag* General_CreateInit_List(void);
void DisjointObject_Prepend(struct SetObject_Tag* SetObject_Pointer, struct DisjointObject_Tag* Insertion_Element_Address);
struct SetObject_Tag* Make_Set(struct SetMember_Tag* SetMember_Pointer);
struct SetMember_Tag* Find_Set(struct SetMember_Tag* SetMember_Pointer);
struct SetObject_Tag* Union(struct SetMember_Tag* SetMember_Pointer, struct SetMember_Tag* AppendedSetMember_Pointer);








#define DISJOINTSET_FOREST_MODULE 0	//If you want to test the Disjoint Set Forest module, please set the value to 1, otherwise, set it to 0.
struct ForestSetMember_Tag
{
	int Key;
	struct Node_Tag* Node_Pointer; // The other functions use the corresponding node to trace the forest path or to modify the attributes. 
};


struct Node_Tag
{
	struct Node_Tag* Parent; //Parent has to be put into node, because only nodes have linking relations.
	int Rank;

	struct ForestSetMember_Tag* ForestSetMember;
};
void Forest_Make_Set(struct ForestSetMember_Tag* ForestSetMember);
void Forest_Link(struct ForestSetMember_Tag* RootSetMember1, struct ForestSetMember_Tag* RootSetMember2);
void Forest_Union(struct ForestSetMember_Tag* SetMember1, struct ForestSetMember_Tag* SetMember2);
struct ForestSetMember_Tag* Forest_Find_Set(struct ForestSetMember_Tag* ForestSetMember);
















struct AdjacencyInformation_Tag
{
	/*****************************************Common Attributes*****************************************/
	unsigned char Fill_EdgeValue_Flag;  // 0 : No Fill  , 1 : Fill Edge Weight , 2 : Fill Edge Capacity
	int AdjacencyIndex;
	int Number_of_Vertices;
	int* VertexIndex_Pointer; // The indices of the vertices in the adjacency.


	/***************************************************************************************************/




	/*****************************************Weight Attributes*****************************************/

	//The same index of VertexIndex_Pointer and EdgeWeight_Pointer means they are corresponding data.
	int* EdgeWeight_Pointer;  // The weight of the edges in the adjacency.

	/***************************************************************************************************/




	/*****************************************Capacity Attributes*****************************************/

	//The same index of VertexIndex_Pointer and EdgeCapacity_Pointer means they are corresponding data.
	int* EdgeCapacity_Pointer;  // The capacity of the edges in the adjacency.

	/***************************************************************************************************/

};


struct Vertex_Tag
{
	//BFS,Bellman-Ford, Dijkstra ....etc. computes the attributes for the graph
	int Distance;

	//DFS computes the attributes for the graph
	int DiscoveryTime, FinishTime;


	//Common attributes(EX: BFS,DFS,Prim's algorithm, Bellman-Ford , Dijkstra ..etc. )
	struct Vertex_Tag* Parent;


	//Record of edge object for EdmondsKarp_BFS and HopcroftKarp. 
	//The pointer store intermediate data during the algorithm execution, and it does not store the final result.
	struct ObjectWithVertex_Tag* EdgeObject_Pointer;




	//The index of this vertex and corresponding adjacency list, the minimum value is 0.
	int Key;


	//Reserve the address of the object of Order List.
	struct ObjectWithVertex_Tag* Object_in_OrderDoublyList_Pointer;


	//A set of strongly connected vertices.
	struct VertexSet_Tag* StrongConnectComponent_Pointer; //Quikly find out which disjoint object belonging (Find_Set).

	//The usage of forest set for Kruskal's algorithm
	struct MiniSpanTree_Node_Tag* Node_Pointer;  // The other functions use the corresponding node to trace the forest path or to modify the attributes.


	//The weight of edge which is from minimum spanning subtree to this vertex for usage of Prim's algorithm.
	int EdgeWeight;

	//The index of vertex in priority-queue for usage of Prim's algorithm, Dijkstra, A_Star ..etc. ; The index is from 4th, textbook p162, index = 1 ~ n
	unsigned Index;

	//The flag of vertex in priority-queue for judging the vertex if in queue, which is used in Prim's algorithm
	unsigned VertexInQueue_Flag; // 1 : i'th vertex is in the queue , 0 : i'th vertex isn't in the queue


	//Reserve the address of the object of Topologically Sort.
	struct ObjectWithVertex_Tag* Object_in_TopologicallySort_Pointer;


	//A set of left part vertices or right part vertices of bipartite graph.
	struct VertexSet_Tag* Bipartite_LeftRight_Pointer; //Quikly find out which disjoint object belonging (Find_Set).


	//Indicate the result wheather the vertex are matched to the other vertex. 
	//HopcroftKarp function save the matching vertex result only at final.    
	//NULL        : The vertex does not match to the other vertex. 
	//Other values: The vertex match to the other vertex, and the address of the other vertex are filling into the Vertex_Pointer.
	struct Vertex_Tag* MatchingVertex_Pointer;


	//Store the corresponding carrier of the vertex for bipartite of HopcroftKarp and GaleShapley. 
	struct VertexCarrier_Tag* VertexCarrier_Pointer;




	//Store the vertex set of the vertex for forest of Hungarian. 
	struct VertexSet_Tag* ForestSet_Pointer;

	//Store the corresponding carrier of the vertex for forest of Hungarian. 
	struct VertexCarrier_Tag* VertexCarrier_in_Forest_Pointer;



	//Record the length of the path from source, the length of each edge is one.
	//The attribute is for judging the negative cycle in ShortestPathFasterAlgorithm if PathLength > Number_of_Vertex-1.
	int PathLength;

	//Reserve the address of object, that the object of the vertex in the queue list. 
	//The attribute is used in ShortestPathFasterAlgorithm.
	struct ObjectWithVertex_Tag* CorrespondObject_Pointer;

	//The coordinate of vertex for A* algorithm.
	int Coordinate[2]; //Coordinate[0] is x, and Coordinate[1] is y.

};



struct VertexCarrier_Tag
{
	struct VertexSet_Tag* VertexSet_Pointer; //Point to the set object.

	struct VertexCarrier_Tag* Next;
	struct VertexCarrier_Tag* Prev;
	struct Vertex_Tag* Vertex_Pointer; //Content

};


struct VertexSet_Tag
{
	//0 : Store the address of vertex set into Bipartite_LeftRight_Pointer of vertex ;
	//1 : Store the address of vertex set into ForestSet_Pointer of vertex ;
	unsigned int SetStoreAttribute_Flag; 

	struct VertexCarrier_Tag* head; //Need to be initialized with NULL for prepend function 
	struct VertexCarrier_Tag* tail;

	int VertexCounter;
};














struct ComponentCarrier_Tag
{
	struct ComponentCarrier_Tag* Prev;
	struct ComponentCarrier_Tag* Next;
	struct VertexSet_Tag* StronglyConnectedComponent_Pointer;

};



struct ComponentCollection_Tag
{
	struct ComponentCarrier_Tag* head;

	int ComponentCounter;

};






//We need to use object to carry vertex for different adjacency list , if not, the same vertex may be linked to different vertex.   
struct ObjectWithVertex_Tag  
{
	struct ObjectWithVertex_Tag* Prev;
	struct ObjectWithVertex_Tag* Next;
	struct Vertex_Tag* Vertex_Pointer;

	//The weight of edge for usage of Prim's algorithm, Dijkstra algorithm.
	int EdgeWeight;

	//The flow and capacity of edge for usage of Edmonds-Karp algorithm.
	int EdgeCapacity;
	int EdgeFlow;

	//Reserve the original edge address of residual edges for usage of Edmonds-Karp, HopcroftKarp algorithm.
	//The pointer store intermediate data during the algorithm execution, and it does not store the final result.
	struct ObjectWithVertex_Tag* OriginalEdge_Pointer;

	//Reserve the address of edge copy of original edge for usage of Edmonds-Karp algorithm.
	struct ObjectWithVertex_Tag* EdgeCopy_Pointer;

	//Indicate the edge direction existing for computations of Hopcroft Karp function.
	unsigned char EdgeDirection_Flag; // 1 : There is a direction from Vertex_Pointer to Edge->Vertex_Pointer ; 0 : There is no direction from Vertex_Pointer to Edge->Vertex_Pointer.

	//Record the anti-directional edge address on each edge for Hopcroft Karp function.
	struct ObjectWithVertex_Tag* AntiEdge_Pointer;

};


struct AdjacencyList_Tag
{
	struct ObjectWithVertex_Tag* head;

};


//Using linked list to construct queue for unknown number of objects.
struct QueueList_Tag
{
	struct ObjectWithVertex_Tag* head; //Must initialize to null value for prepend function.
	struct ObjectWithVertex_Tag* tail; //Must initialize to null value for dequeue function.

	int VertexCounter;
};


struct TopologicalSort_List_Tag
{
	struct ObjectWithVertex_Tag* head;

	//The initialization value of the pointer is last element of the array for making head be the whole space address. 
	//The value of the pointer is modified to the address of next empty object when the object have filled some information and inserted to a list.
	struct ObjectWithVertex_Tag* EmptyObject_Pointer;

};


struct DFS_AdditionalResult_Tag
{
	//Common attributes
	unsigned char OrderDoublyList_Flag; //0: off , 1: on 
	struct OrderDoublyList_Tag* OrderDoublyList_Pointer;

	

	/*******************Topological sort attributes*******************************************/
	unsigned char TopologicalSort_Flag; //0: off , 1: on
	struct TopologicalSort_List_Tag* TopologicalSort_List_Pointer;

	/*******************Topological sort attributes*******************************************/




	/*******************Strongly connected component attributes*******************************************/
	unsigned char StronglyConnectedComponent_Flag; //0: off , 1: on
	struct ComponentCollection_Tag* ComponentCollection_Pointer;
	unsigned char CreateComponent_Instruction; //0: off , 1: on

	//If we want to free the space of component collection, we need to free the below sub-space first.
	struct ComponentCarrier_Tag* ReleaseCompCarrierAddress;
	struct VertexSet_Tag* ReleaseCompAddress;
	struct VertexCarrier_Tag* ReleaseVertexCarrierAddress;

	/*******************Strongly connected component attributes*******************************************/

};


struct AllPairShortestPath_Result_Tag
{
	//The element of predecessor-matrix is predecessor index of vertex j with ith row(vertex) and jth column(vertex).
	int* PredecessorMatrix_Pointer;

	//Reserve the weights of shortest paths from vertex i(row) to vertex j(column) .
	int* ShortestWeightMatrix_Pointer;
};


struct EdgeSpaceAddress_Carrier_Tag
{
	struct EdgeSpaceAddress_Carrier_Tag* Prev;
	struct EdgeSpaceAddress_Carrier_Tag* Next;

	//Reserve the adddress of edge space for freeing.
	struct ObjectWithVertex_Tag* EdgeSpaceAddress;
};


struct EdgeSpaceAddress_List_Tag
{
	struct EdgeSpaceAddress_Carrier_Tag* head;
};


struct Bipartite_Tag
{
	struct VertexSet_Tag* BipartiteLeft_Unmatch_Pointer;  //The unmatch left set of bipartite graph
	struct VertexSet_Tag* BipartiteRight_Unmatch_Pointer; //The unmatch right set of bipartite graph

	struct VertexSet_Tag* BipartiteLeft_Match_Pointer;  //The match left set of bipartite graph
	struct VertexSet_Tag* BipartiteRight_Match_Pointer; //The match right set of bipartite graph


	struct VertexCarrier_Tag* ReleaseCarrierAddress;//The address of contiguous carriers for left part and right part of bipartite.


};


//The flag of graph object in DFS_AdditionalResult need to be initialized to 0. 
//The reason is we use some functions such as DFS¡BBFS...etc. that some flags are on, to make functions produce unpredictable behavior. 
struct Graph_Tag
{
	//Initialize the number of vertices and edges by Creating Graph function.
	int Number_of_Vertex;
	int Number_of_Edge;

	//The index of Vertex_Pointer and AdjacencyList_Pointer means the same vertex. The space of the locations which are pointed to, that are created by Creating Graph Function. 
	struct Vertex_Tag* Vertex_Pointer;
	struct AdjacencyList_Tag* AdjacencyList_Pointer;
	struct EdgeSpaceAddress_List_Tag EdgeSpaceAddress_List; //Record all the allocated edge space which are used in adjacency lists.


	//The element of adjacency matrix is edge weight w(i,j) with ith row(vertex) and jth column(vertex).
	int* AdjacencyMatrix_Pointer;


	//Reserve all the results of All-Pairs-Shortest-Paths
	struct AllPairShortestPath_Result_Tag AllPairShortestPath_Result;


	//Additional results such as topological sort,... etc. and turning-on buttom are all for DFS relation. The additional space of DFS_AdditionalResult which are created by specifying function. 
	struct DFS_AdditionalResult_Tag DFS_AdditionalResult;


	//The pointers are used when we call CreateStronglyConnectedComponent function or CreateReverseDirectedGraph function.
	struct Graph_Tag* TransposeGraph_Pointer;
	struct Graph_Tag* UnTransposeGraph_Pointer; //Record the previous graph pointer in the transpose graph object.


	//Edge list of minimum spanning tree for Kruskal algorithm
	struct EdgeDoublyList_Tag* MiniSpanTree_EdgeList_Pointer;


	//The pointer is used when we create bipartite.
	struct Bipartite_Tag Bipartite;


	//Each vertex own the its preference list with different representation for Gale-Shapley computation.	
	struct PreferRank_Tag* Proposer_Pointer; //The index of element is as same as vertex index.
	struct VertexRank_Tag* ProposedMember_Pointer; //The index of element plus offset equal vertex index.
	struct Vertex_Tag** Release_VertexAddress_Pointer;
	int* Release_PreferDegree_Pointer;




	//The feasible label for each vertex in Hungarian algorithm.
	struct FeasibleLabel_Tag* FeasibleLabel_Pointer;

};






#define BFS_MODULE 0	//If you want to test the BFS module, please set the value to 1, otherwise, set it to 0.
struct Graph_Tag Graph_Object;
void AdjacencyList_Prepend(struct AdjacencyList_Tag* AdjacencyList_Pointer, struct ObjectWithVertex_Tag* Insertion_Element_Address, struct Graph_Tag* Graph_Pointer);
void CreateInitialize_Vertex_and_Adjacency(struct Graph_Tag* Graph_Pointer, int Number_of_Vertices);
void AllocatedEdgeAddress_Prepend(struct EdgeSpaceAddress_List_Tag* LinkedList_Pointer, struct EdgeSpaceAddress_Carrier_Tag* Insertion_Element_Address);
struct ObjectWithVertex_Tag* Fill_Adjacency(struct Graph_Tag* Graph_Pointer, struct AdjacencyInformation_Tag* AdjacencyInformation_Pointer);
void CreateGraph(struct Graph_Tag* Graph_Pointer);
void QueueList_Prepend(struct QueueList_Tag* QueueList_Pointer, struct ObjectWithVertex_Tag* Insertion_Element_Address);
struct ObjectWithVertex_Tag* QueueList_Dequeue(struct QueueList_Tag* QueueList_Pointer);
void BFS(struct Graph_Tag* Graph_Pointer, struct Vertex_Tag* SourceVertex_Pointer);
void Print_Path(struct Vertex_Tag* SourceVertex_Pointer, struct Vertex_Tag* DestinationVertex_Pointer);






#define DFS_MODULE 0	//If you want to test the DFS module, please set the value to 1, otherwise, set it to 0.
struct Graph_Tag DFS_Graph_Object;
void DFS_CreateGraph(struct Graph_Tag* Graph_Pointer);
void DFS(struct Graph_Tag* Graph_Pointer, struct Vertex_Tag* SourceVertex_Pointer);
void DFS_VISIT(struct Graph_Tag* Graph_Pointer, struct Vertex_Tag* FrontierVertex_Pointer, int* Time_Pointer);







#define TOPOLOGICAL_SORT_MODULE 0	//If you want to test the Topological Sort module, please set the value to 1, otherwise, set it to 0.
void TopologicalSort_CreateGraph(struct Graph_Tag* Graph_Pointer);
void Topological_Sort_Prepend(struct TopologicalSort_List_Tag* TopologicalSort_List_Pointer, struct ObjectWithVertex_Tag* Insertion_Element_Address);
struct TopologicalSort_List_Tag* Topological_Sort(struct Graph_Tag* Graph_Pointer);






#define STRONGLY_CONNECTED_COMPONENT_MODULE 0	//If you want to test the Strongly Connected Component module, please set the value to 1, otherwise, set it to 0.
//Using linked list to construct order for unknown number of objects.
struct OrderDoublyList_Tag
{
	struct ObjectWithVertex_Tag* head; //Must initialize to null value for prepend function.

	//The value of the pointer is modified to the address of next empty object when the object have filled some information and inserted to a list.
	struct ObjectWithVertex_Tag* EmptyObject_Pointer;

	//After some evalueations, the head and EmptyObject_Pointer are not address of array, so we need to reserve it.
	struct ObjectWithVertex_Tag* ReleaseAddrress;

};
void OrderDoublyList_Prepend(struct OrderDoublyList_Tag* OrderDoublyList_Pointer, struct ObjectWithVertex_Tag* Insertion_Element_Address);
void OrderDoublyList_Delete(struct OrderDoublyList_Tag* OrderDoublyList_Pointer, struct ObjectWithVertex_Tag* Delete_Element_Address);
struct OrderDoublyList_Tag* CreateDoublyList_FinishTimeOrder_DFS(struct Graph_Tag* Graph_Pointer);
struct Graph_Tag* CreateReverseDirectedGraph(struct Graph_Tag* Graph_Pointer);
struct ObjectWithVertex_Tag* RetrieveListHead(struct OrderDoublyList_Tag* LinkedList_Pointer);
struct VertexSet_Tag* CreateInit_List(void);
void VertexCarrier_Prepend(struct VertexSet_Tag* VertexSet_Pointer, struct VertexCarrier_Tag* VertexCarrier_Pointer);
struct VertexSet_Tag* Make_VertexSet(struct Vertex_Tag* Vertex_Pointer);
struct VertexSet_Tag* Union_VertexSet(struct Vertex_Tag* Vertex_Pointer, struct Vertex_Tag* AppendedVertex_Pointer);
struct ComponentCollection_Tag* TransposeGraph_DFS(struct Graph_Tag* Graph_Pointer);
void ComponentCollection_Prepend(struct ComponentCollection_Tag* ComponentCollection_Pointer, struct ComponentCarrier_Tag* ComponentCarrier_Pointer);
void ComponentCollection_Delete(struct ComponentCollection_Tag* LinkedList_Pointer, struct ComponentCarrier_Tag* Delete_Element_Address);
struct ComponentCollection_Tag* TransferToContiguousSpace(struct Graph_Tag* Graph_Pointer);
void FreeGraph(struct Graph_Tag* Graph_Pointer);
struct ComponentCollection_Tag* CreateStronglyConnectedComponent(struct Graph_Tag* Graph_Pointer);








#define MINIMUM_SPANNING_TREE_KRUSKAL_MODULE 0	//If you want to test the Minimum Spanning Tree module, please set the value to 1, otherwise, set it to 0.
struct WeightEdge_Tag
{
	struct Vertex_Tag* VertexAddress_Pointer[2];
	int EdgeWeight;
};

struct ObjectWithWeightEdge_Tag
{
	struct ObjectWithWeightEdge_Tag* Prev;
	struct ObjectWithWeightEdge_Tag* Next;
	struct WeightEdge_Tag* WeightEdge_Pointer;
};

struct EdgeDoublyList_Tag
{
	struct ObjectWithWeightEdge_Tag* head;

	unsigned int Counter;

};
struct MiniSpanTree_Node_Tag
{
	struct MiniSpanTree_Node_Tag* Parent; //Parent has to be put into node, because only nodes have linking relations.
	int Rank;

	struct Vertex_Tag* ForestSetMember;
};
struct Graph_Tag MST_Graph_Object;
void MiniSpanTree_CreateGraph(struct Graph_Tag* Graph_Pointer);
void MiniSpanTree_Make_Set(struct Vertex_Tag* ForestSetMember);
struct Vertex_Tag* MiniSpanTree_Find_Set(struct Vertex_Tag* ForestSetMember);
void MiniSpanTree_Link(struct Vertex_Tag* RootSetMember1, struct Vertex_Tag* RootSetMember2);
void MiniSpanTree_Union(struct Vertex_Tag* SetMember1, struct Vertex_Tag* SetMember2);
void EdgeDoublyList_Prepend(struct EdgeDoublyList_Tag* LinkedList_Pointer, struct ObjectWithWeightEdge_Tag* Insertion_Element_Address);
void MiniSpanTree_Counting_Sort(int Array[], int* MaxMinBoundary_Pointer, struct ObjectWithWeightEdge_Tag** SortedInstantAddress_Array, size_t Instant_Size);
unsigned int MiniSpanTree_CalculateSortedDigitNumber_Base10_INT(struct ObjectWithWeightEdge_Tag** SortedInstantAddress_Array, size_t Instant_Size);
void MiniSpanTree_MSD_Radix_Sort(struct ObjectWithWeightEdge_Tag** SortedInstantAddress_Array, size_t Instant_Size, unsigned int Number_Of_Digits);
void MiniSpanTree_Kruskal(struct Graph_Tag* Graph_Pointer);







#define MINIMUM_SPANNING_TREE_PRIM_MODULE 0	//If you want to test the Minimum Spanning Tree module, please set the value to 1, otherwise, set it to 0.
void MiniSpanTree_QueueMinHeapify(struct Vertex_Tag* PointerArray[], size_t Queue_Size, unsigned Root_Index);
signed char MiniSpanTree_QueueMinHeap_Minimum(struct Vertex_Tag* PointerArray[], size_t Queue_Size, struct Vertex_Tag** MinnimumAddress_Pointer);
struct Vertex_Tag* QueueMinHeap_ExtractMinimum(struct Vertex_Tag* PointerArray[], size_t* QueueSize_Pointer);
signed MiniSpanTree_QueueMinHeap_DecreaseKey(struct Vertex_Tag* PointerArray[], struct Vertex_Tag* Object_Pointer, int New_EdgeWeight);
void MiniSpanTree_Prim(struct Graph_Tag* Graph_Pointer, struct Vertex_Tag* SourceVertex_Pointer);





#define BELLMAN_FORD_MODULE 0	//If you want to test the Bellman-Ford module, please set the value to 1, otherwise, set it to 0.
struct Graph_Tag BellmanFord_Graph_Object;
void BellmanFord_CreateGraph(struct Graph_Tag* Graph_Pointer);
void Initialize_Single_Source(struct Graph_Tag* Graph_Pointer, struct Vertex_Tag* SourceVertex_Pointer);
unsigned char Relax(struct Vertex_Tag* u_Pointer, struct Vertex_Tag* v_Pointer, int EdgeWeight_u_v);
unsigned char Bellman_Ford(struct Graph_Tag* Graph_Pointer, struct Vertex_Tag* SourceVertex_Pointer);





#define SHORTEST_PATH_FASTER_ALGORITHM_MODULE 0	//If you want to test the Shortest Path Faster Algorithm module, please set the value to 1, otherwise, set it to 0.
unsigned char ShortestPathFasterAlgorithm(struct Graph_Tag* Graph_Pointer, struct Vertex_Tag* SourceVertex_Pointer);



#define SINGLE_SOURCE_SHORTEST_PATH_IN_DAG_MODULE 0	//If you want to test the Single Source Shortest Path in DAG module, please set the value to 1, otherwise, set it to 0.
struct Graph_Tag DAG_ShortestPath_Graph_Object;
void DAG_ShortestPath_CreateGraph(struct Graph_Tag* Graph_Pointer);
void DAG_Shortest_Path(struct Graph_Tag* Graph_Pointer, struct Vertex_Tag* SourceVertex_Pointer);




#define DIJKSTRA_SHORTEST_PATH_MODULE 0	//If you want to test the Dijkstra module, please set the value to 1, otherwise, set it to 0.
struct Graph_Tag Dijkstra_Graph_Object;
void  Dijkstra_CreateGraph(struct Graph_Tag* Graph_Pointer);
void Dijkstra_QueueMinHeapify(struct Vertex_Tag* PointerArray[], size_t Queue_Size, unsigned Root_Index);
struct Vertex_Tag* Dijkstra_QueueMinHeap_ExtractMinimum(struct Vertex_Tag* PointerArray[], size_t* QueueSize_Pointer);
signed Dijkstra_QueueMinHeap_DecreaseKey(struct Vertex_Tag* PointerArray[], struct Vertex_Tag* Object_Pointer, int New_VertexDistance);
void Dijkstra(struct Graph_Tag* Graph_Pointer, struct Vertex_Tag* SourceVertex_Pointer);





#define A_STAR_SHORTEST_PATH_MODULE 0	//If you want to test the A* module, please set the value to 1, otherwise, set it to 0.
struct Graph_Tag A_Star_Graph_Object;
void  A_Star_CreateGraph(struct Graph_Tag* Graph_Pointer);
signed A_Star_QueueMinHeap_DecreaseKey(struct Vertex_Tag* PointerArray[], struct Vertex_Tag* Object_Pointer, float New_f_n, float* f_n_Pointer);
void A_Star_QueueMinHeapify(struct Vertex_Tag* PointerArray[], size_t Queue_Size, unsigned Root_Index, float* f_n_Pointer);
struct Vertex_Tag* A_Star_QueueMinHeap_ExtractMinimum(struct Vertex_Tag* PointerArray[], size_t* QueueSize_Pointer, float* f_n_Pointer);
struct Vertex_Tag* A_Star(struct Graph_Tag* Graph_Pointer, struct Vertex_Tag* SourceVertex_Pointer, struct Vertex_Tag* DestinationVertex_Pointer);




#define FASTER_ALL_PAIRS_SHORTEST_PATHS_MODULE 0	//If you want to test the Faster All Pairs Shortest Paths module, please set the value to 1, otherwise, set it to 0.
struct Graph_Tag FasterAPSP_Graph_Object;
void CreateInitialize_AdjacencyMatrix(struct Graph_Tag* Graph_Pointer);
void  FasterAPSP_CreateGraph(struct Graph_Tag* Graph_Pointer);
unsigned Extend_Shortest_Paths(struct Graph_Tag* Graph_Pointer, int* PreviousShortestWeightMatrix1_Pointer, int* PreviousShortestWeightMatrix2_Pointer, int* PreviousPredecessorMatrix_Pointer);
void Faster_APSP(struct Graph_Tag* Graph_Pointer);





#define FLOYD_WARSHALL_ALL_PAIRS_SHORTEST_PATHS_MODULE 0	//If you want to test the Floyd-Warshall module, please set the value to 1, otherwise, set it to 0.
void Floyd_Warshall(struct Graph_Tag* Graph_Pointer);




#define JOHNSON_ALL_PAIRS_SHORTEST_PATHS_MODULE 0	//If you want to test the Johnson's algorithm module, please set the value to 1, otherwise, set it to 0.
struct Graph_Tag Johnson_Graph_Object;
void  Johnson_CreateGraph(struct Graph_Tag* Graph_Pointer);
void  Johnson_ReserveRecoverGraph(struct Graph_Tag* Graph_Pointer, unsigned char Reserve_Recover_Flag); // 0 : Reserve , the others : Recover
_Bool Johnson(struct Graph_Tag* Graph_Pointer);







#define EDMONDS_KARP_MAXIMUM_FLOW_MODULE 0	//If you want to test the Edmonds-Karp module, please set the value to 1, otherwise, set it to 0.
struct Graph_Tag EdmondsKarp_Graph_Object;
void EdmondsKarp_CreateGraph(struct Graph_Tag* Graph_Pointer);
struct Graph_Tag* Create_ResidualGraph(struct Graph_Tag* Graph_Pointer);
void FreeGraphRepresent(struct Graph_Tag* Graph_Pointer);
unsigned char EdmondsKarp_BFS(struct Graph_Tag* Graph_Pointer, struct Graph_Tag* ResidualGraph_Pointer, struct Vertex_Tag* Residual_SourceVertex_Pointer, struct Vertex_Tag* Residual_DestinationVertex_Pointer);
void EdmondsKarp(struct Graph_Tag* Graph_Pointer, struct Vertex_Tag* SourceVertex_Pointer, struct Vertex_Tag* DestinationVertex_Pointer);
struct SplitedEdge_Tag
{
	struct SplitedEdge_Tag* Prev;
	struct SplitedEdge_Tag* Next;

	//The edge (u,v) is going to be splited into two edges (u,x) and (x,v) with a new vertex x.
	struct ObjectWithVertex_Tag* Edge_Pointer; //The edge direction is from u to v or from v to u.
	struct Vertex_Tag* Vertex_u_Pointer; //The smaller key value is vertex u.
	struct Vertex_Tag* Vertex_v_Pointer; //The larger key value is vertex v.

	//Record the number of antiparallel edges between vertex u and vertex v.
	//The value need to be initialized to 1 when creating a new splited edge object.
	int EdgeCounter;
};

struct SplitedEdgeList_Tag
{
	struct SplitedEdge_Tag* head;
};

struct CandidateSplitedEdge_Table_Tag
{
	struct SplitedEdgeList_Tag* SplitedEdge_List_Pointer;

	int SquareTable_Length; //The number of slots in the hash table.

};
int AntiParallelEdge_HashFunction(struct CandidateSplitedEdge_Table_Tag* Table, int Key);
void SplitedEdgeList_Prepend(struct SplitedEdgeList_Tag* LinkedList_Pointer, struct SplitedEdge_Tag* Insertion_Element_Address);
void AntiParallelEdge_Insert(struct CandidateSplitedEdge_Table_Tag* Table, struct SplitedEdge_Tag* InsertionObject_Address);
struct SplitedEdge_Tag* SplitedEdgeList_Search(struct SplitedEdgeList_Tag* LinkedList_Pointer, struct SplitedEdge_Tag* ComparedObject_Address);
struct SplitedEdge_Tag* AntiParallelEdge_Search(struct CandidateSplitedEdge_Table_Tag* Table, struct SplitedEdge_Tag* ComparedObject_Address);
void SplitedEdgeList_Delete(struct SplitedEdgeList_Tag* LinkedList_Pointer, struct SplitedEdge_Tag* Delete_Element_Address);
void  EdmondsKarp_ReserveRecoverGraph(struct Graph_Tag* Graph_Pointer, unsigned char Reserve_Recover_Flag);
struct ObjectWithVertex_Tag* Comform_EdmondsKarpGraph(struct Graph_Tag* Graph_Pointer, struct Vertex_Tag** SourceVertexAddress_Pointer, struct Vertex_Tag** DestinationVertexAddress_Pointer);









#define HOPCROFT_KARP_MAXIMUM_BIPARTITE_MODULE 0	//If you want to test the Hopcroft-Karp module, please set the value to 1, otherwise, set it to 0.
struct Graph_Tag HopcroftKarp_Graph_Object;
struct M_AugmentPath_Tag
{
	struct Vertex_Tag** EndChildVertexAddress_Pointer;
	int  EmptyElement_Location;
};
struct VertexSet_Tag* CreateInit_HopcroftKarp_List(void);
void HopcroftKarp_VertexCarrier_Prepend(struct VertexSet_Tag* VertexSet_Pointer, struct VertexCarrier_Tag* VertexCarrier_Pointer);
void HopcroftKarp_VertexCarrier_Delete(struct VertexSet_Tag* LinkedList_Pointer, struct VertexCarrier_Tag* Delete_Element_Address);
struct VertexSet_Tag* HopcroftKarp_Make_VertexSet(struct Vertex_Tag* Vertex_Pointer, struct VertexCarrier_Tag* VertexCarrier_Pointer);
struct VertexSet_Tag* HopcroftKarp_Union_VertexSet(struct Vertex_Tag* Vertex_Pointer, struct Vertex_Tag* AppendedVertex_Pointer);
struct VertexCarrier_Tag* HopcroftKarp_Bipartite(struct Graph_Tag* Graph_Pointer, int RightPart_Offset);
struct ObjectWithVertex_Tag* Fill_BidirectionalAdjacency(struct Graph_Tag* Graph_Pointer, struct AdjacencyInformation_Tag* AdjacencyInformation_Pointer);
void HopcroftKarp_CreateGraph(struct Graph_Tag* Graph_Pointer);
struct Graph_Tag* Create_BFS_BipartiteGraph(struct Graph_Tag* Graph_Pointer);
struct Graph_Tag* Create_BFSGraph(struct Graph_Tag* Graph_Pointer);
struct M_AugmentPath_Tag* DFS_AugmPath(struct Graph_Tag* Graph_Pointer);
struct Vertex_Tag* DFS_AugmPath_VISIT(struct Graph_Tag* Graph_Pointer, struct Vertex_Tag* FrontierVertex_Pointer, int* Time_Pointer);
void Release_AugmentPath(struct M_AugmentPath_Tag* M_AugmentPath_Pointer);
void Release_Bipartite(struct Bipartite_Tag* Bipartite_Pointer);
void BipartiteInitialization(struct Graph_Tag* Graph_Pointer, int Initial_Flag);
void HopcroftKarp(struct Graph_Tag* Graph_Pointer);









#define GALE_SHAPLEY_STABLE_MATCHING_MODULE 0	//If you want to test the Gale-Shapley stable matching module, please set the value to 1, otherwise, set it to 0.
struct Graph_Tag GaleShapley_Graph_Object;
struct PreferRank_Tag
{
	struct Vertex_Tag** VertexAddress_Pointer; //From highest preference( smallest index 0 ) to lowest preference( largest index ), each vertex address is stored in the order.
};

struct VertexRank_Tag
{
	int* PreferDegree_Pointer; //The index of PreferDegree_Pointer is vertex index, the preference of vertex is stored in the order.
};
void GaleShapley_CreateGraph(struct Graph_Tag* Graph_Pointer);
void GaleShapley(struct Graph_Tag* Graph_Pointer);
void Release_PreferenceLists(struct Graph_Tag* Graph_Pointer);










#define HUNGARIAN_MAXIMUM_WEIGHT_MODULE 0	//If you want to test the Hungarian Maximum Weight module, please set the value to 1, otherwise, set it to 0.
struct Graph_Tag Hungarian_Graph_Object;
struct FeasibleLabel_Tag
{
	int* Left_h_Pointer;
	int* Right_h_Pointer;

};
struct BFS_Forest_Tag
{
	struct VertexSet_Tag Left_VertexSet_in_Forest;
	struct VertexSet_Tag Right_VertexSet_in_Forest;

	struct VertexSet_Tag Left_VertexSet_in_NonForest;
	struct VertexSet_Tag Right_VertexSet_in_NonForest;
};
void FreeGraphMatrixRepresent(struct Graph_Tag* Graph_Pointer);
void CreateInitialize_AdjacencyMatrix_Bipartite(struct Graph_Tag* Graph_Pointer, int* WeightMatrix_Pointer);
void Hungarian_CreateGraph(struct Graph_Tag* Graph_Pointer);
void CreateInitialize_DefaultLabel(struct Graph_Tag* Graph_Pointer);
void Initialize_Slack(struct Graph_Tag* Graph_Pointer, struct BFS_Forest_Tag* BFS_Forest_Pointer, int* MinSlackValue_Pointer);
void GreedyBipartiteMatching(struct Graph_Tag* Graph_Pointer);
void FindAugPath_and_SymmetricDifference(struct Graph_Tag* Graph_Pointer);
void Free_FeasibleLabel(struct Graph_Tag* Graph_Pointer);
void Hungarian(struct Graph_Tag* Graph_Pointer);














#define ROBIN_KARP_STRING_MATCHING_MODULE 0	//If you want to test the Robin Karp String Matching module, please set the value to 1, otherwise, set it to 0.
struct Text_Tag
{
	uint32_t Length; //The length of string not including the terminating null character.
	unsigned char* Character_Pointer; //The pointer point to the first character of string.
};
typedef struct Text_Tag Text;
typedef struct Text_Tag Pattern;
unsigned char TextContent[19];
unsigned char PatternContent[5];
Text Text_Object;
Pattern Pattern_Object;
uint32_t TwoEqualLengthString_Compare(unsigned char* String1_Pointer, unsigned char* String2_Pointer, uint32_t Length);
uint32_t Modular_FastExponentiation(uint32_t Base, uint32_t Power, uint32_t Modulus);
void Rabin_Karp_Matcher(Text* Text_Pointer, Pattern* Pattern_Pointer);





#define FINITE_AUTOMA_STRING_MATCHING_MODULE 0	//If you want to test the Finite Automa String Matching module, please set the value to 1, otherwise, set it to 0.
unsigned char TextContent2[11];
unsigned char PatternContent2[7];
Text Text_Object2;
Pattern Pattern_Object2;
struct Alphabet_Tag
{
	int Size; //The number of characters in alphabet.
	unsigned char* Character_Pointer; //The pointer point to the first character of alphabet.
};
typedef struct Alphabet_Tag Alphabet;
unsigned char AlphabetContent[3];
Alphabet Alphabet_Object;
struct TransitionPacket_Tag
{
	//The transition table for size (Pattern_Length + 1) states ¡Ñ | £U |
	//The allcated space is 2D table, and the meaning of the row is state, the meaning of the column is character in alphabet.
	int* Transition_Table;

	//The direct address table for alphabet.
	//The index is corresponding to ASCII code of character,the code value = [ 0 : UCHAR_MAX ].
	//The value is corresponding to the index of character in alphabet, the index = [ 0 : Amount_Max ], and the Amount_Max <= UCHAR_MAX.
	unsigned char* DirectAddress_Table;
};
struct TransitionPacket_Tag* Compute_Transition_Function(Pattern* Pattern_Pointer, Alphabet* Alphabet_Pointer);
void Finite_Automaton_Matcher(Text* Text_Pointer, Pattern* Pattern_Pointer, Alphabet* Alphabet_Pointer);






#define KMP_STRING_MATCHING_MODULE 0	//If you want to test the KMP String Matching module, please set the value to 1, otherwise, set it to 0.
int* Compute_Prefix_Function(Pattern* Pattern_Pointer);
void KMP_Matcher(Text* Text_Pointer, Pattern* Pattern_Pointer);








#define LONGEST_COMMON_PREFIX_WITH_SUFFIX_ARRAY_MODULE 0	//If you want to test the Longest Common Prefix With Suffix Array module, please set the value to 1, otherwise, set it to 0.
//The ranks of left substring and right substring for a string combination of them.
struct SubstringRank_Tag
{
	int Left_Rank;  //The rank of left substring in text.
	int Right_Rank;  //The rank of right substring in text.
	int Index; //The starting character index of left substring in text.
};

struct RankPacket_Tag
{
	int* Rank_Array;
	unsigned char  Complete_RankedMission;
};
unsigned char TextContent3[7];
unsigned char PatternContent3[2];
Text Text_Object3;
Pattern Pattern_Object3;
void SuffixArray_Counting_Sort(int Array[], int* MaxMinBoundary_Pointer, struct SubstringRank_Tag SortedInstant_Array[], size_t Instant_Size);
void SuffixArray_MSD_Radix_Sort(struct SubstringRank_Tag SortedInstant_Array[], size_t Instant_Size, unsigned int Number_Of_Digits);
struct RankPacket_Tag Make_Rank(struct SubstringRank_Tag SubstringRank_Pointer[], size_t Text_Length);
int* Compute_Suffix_Array(Text* Text_Pointer);
int* Compute_LCP_Array(Text* Text_Pointer, int Suffix_Array[]);









#define TEXT_PATTERN_MATCHING_WITH_DC3_SKEWALGORITHM_MODULE 0	//If you want to test the Text Pattern Matching With DC3 Skew Algorithm module, please set the value to 1, otherwise, set it to 0.
struct DC3_Text_Tag
{

	int Length; //The length of string not including the terminating null character.

	
	//The type of Character_Pointer is int*,
	//because we need to store the rank of each character in the string for calling DC3_Suffix_Array recursively, and the rank is O(n), where n is the length of string. 
	int* Character_Pointer; //The pointer point to the first character of the string s.
};
typedef struct DC3_Text_Tag  DC3_Text;
int TextContent4[];
DC3_Text Text_Object4;
unsigned char PatternContent4[2];
Pattern Pattern_Object4;
bool Compare_Two_Substring(int FirstCharacter_of_StringA, int SuffixRank_of_SecondCharacter_of_StringA, int FirstCharacter_of_StringB, int SuffixRank_of_SecondCharacter_of_StringB);
void RadixPass(int* StartIndex_Pointer, int* Sorted_StartIndex_Pointer, int* TextAddress_with_Offset, int Number_of_StartIndex, int Maximum_CounterIndex);
void DC3_Suffix_Array(DC3_Text* Text_Pointer, int* Suffix_Array, int Maximum_CounterIndex);
void DC3_Suffix_Array_Matcher(DC3_Text* Text_Pointer, int* Suffix_Array, Pattern* Pattern_Pointer);











#define SEARCH_LASTMATCHEDNODE_IN_TRIE_MODULE 0	//If you want to test the Search Last Matched Node In Trie module, please set the value to 1, otherwise, set it to 0.
struct ChildrenTable_Tag
{
	struct ChildrenList_Tag* ChildrenList_Pointer;

	int TableLength; //The number of slots in the children table.
	int ChildrenCounter; //The number of child nodes in the children table.
};
struct TrieNode_Tag
{
	unsigned char Key;

	struct ChildrenTable_Tag ChildrenTable; //Hash table for children nodes.

};
struct Carrier_of_ChildNode_Tag
{

	struct Carrier_of_ChildNode_Tag* Prev;
	struct Carrier_of_ChildNode_Tag* Next;

	struct TrieNode_Tag TrieNode; //The content of the carrier is the child node.
};
//Doubly linked list for array version.
struct ChildrenList_Tag
{
	struct Carrier_of_ChildNode_Tag* head;

	unsigned int ObjectCounter;
};
struct Trie_Tag
{
	struct TrieNode_Tag RootNode;
};
struct Trie_Tag Trie_Object;
unsigned char StringContent[5][50];
int TrieChild_Hash_Function(struct ChildrenTable_Tag* Table, int Key);
void TrieChild_DoublyList_Prepend(struct ChildrenList_Tag* LinkedList_Pointer, struct Carrier_of_ChildNode_Tag* Insertion_Element_Address);
void TrieChild_Chained_Hash_Insert(struct ChildrenTable_Tag* Table, struct Carrier_of_ChildNode_Tag* InsertionObject_Address);
struct Carrier_of_ChildNode_Tag* TrieChild_DoublyList_Search(struct ChildrenList_Tag* LinkedList_Pointer, int Search_Key);
struct Carrier_of_ChildNode_Tag* TrieChild_Chained_Hash_Search(struct ChildrenTable_Tag* Table, int Searched_Key);
void TrieChild_DoublyList_Delete(struct ChildrenList_Tag* LinkedList_Pointer, struct Carrier_of_ChildNode_Tag* Delete_Element_Address);
void TrieChild_Chained_Hash_Delete(struct ChildrenTable_Tag* Table, struct Carrier_of_ChildNode_Tag* DeleteObject_Address);
struct TrieNode_Tag* TrieNode_SearchLastMatchedNode(struct Trie_Tag* Trie_Pointer, unsigned char* String, int* Record_FirstUnmatchedCharacter_Index_Pointer);
void TrieNode_Insertion(struct Trie_Tag* Trie_Pointer, unsigned char* String);
_Bool TrieNode_Delete(struct Trie_Tag* Trie_Pointer, unsigned char* String);




#endif