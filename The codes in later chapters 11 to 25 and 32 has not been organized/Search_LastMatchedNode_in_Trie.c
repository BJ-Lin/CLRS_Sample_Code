#include "..\Header.h"




//Each node need to be initialized with key value, the pointer of children table, and the length of children table.
struct Trie_Tag Trie_Object = { .RootNode.ChildrenTable.ChildrenList_Pointer = NULL,.RootNode.ChildrenTable.TableLength = 0,.RootNode.ChildrenTable.ChildrenCounter = 0 };

unsigned char StringContent[5][50] = { "abcde","acfcc","acfgh","acfgkp","acfgl" };

//Ref:CLRS,4th,P288,The family of hash functions is universal,that the probibility of h(k1)=h(k2) <= 1/m.
//The random number generator is not good enough, and I only test the expected value of object location which is very close to analytical value(+-1%), 
//so this is only for a sample of hashing.
int TrieChild_Hash_Function(struct ChildrenTable_Tag* Table, int Key)
{
	srand(Key);

	//The proof of formular from CLRS,4th,P290, I think he use some approximation to approximate collision probility 1/m + 1/(p-1).But he does not explain clearly.
	//So We must make prime number as larger as possible than slot number m for approximating the proberbility ~ 1/m.
	int PrimeNumber = 32749; //32749, which is a prime number.
	int SlotNumber = Table->TableLength; //m is the number of slots in the hash table.
	int a = 1 + (PrimeNumber - 2) * (float)rand() / RAND_MAX; //a is a random integer in the interval [1,p-1]
	int b = (PrimeNumber - 1) * (float)rand() / RAND_MAX; //b is a random integer in the interval [0,p-1]

	int HashValue = ((a * Key + b) % PrimeNumber) % SlotNumber; //Hash value in the interval [0,m-1]


	return HashValue;
}





void TrieChild_DoublyList_Prepend(struct ChildrenList_Tag* LinkedList_Pointer, struct Carrier_of_ChildNode_Tag* Insertion_Element_Address)
{
	//Store the addresses of predecessor and successor for Insertion Element
	Insertion_Element_Address->Prev = NULL;
	Insertion_Element_Address->Next = LinkedList_Pointer->head;  //NULL or The address of first element in the past time


	if (LinkedList_Pointer->head != NULL) //(1)If there is a first element before prepanding, we need to update Prev of first element (2) before cover LinkedList_Pointer->head.
	{
		LinkedList_Pointer->head->Prev = Insertion_Element_Address;
	}

	//Update the head pointer of queue.
	LinkedList_Pointer->head = Insertion_Element_Address;

	//Update the number of element in the linked list.
	LinkedList_Pointer->ObjectCounter++;
}


void TrieChild_Chained_Hash_Insert(struct ChildrenTable_Tag* Table, struct Carrier_of_ChildNode_Tag* InsertionObject_Address)
{
	int HashValue = TrieChild_Hash_Function(Table, InsertionObject_Address->TrieNode.Key);



	TrieChild_DoublyList_Prepend(Table->ChildrenList_Pointer + HashValue, InsertionObject_Address);

	//Update the number of child node in the children table.
	Table->ChildrenCounter++;
}





struct Carrier_of_ChildNode_Tag* TrieChild_DoublyList_Search(struct ChildrenList_Tag* LinkedList_Pointer, int Search_Key)
{
	struct Carrier_of_ChildNode_Tag* Target_Object_Address = LinkedList_Pointer->head;

	//AND all non-searching conditions. If one of non-searching conditions is not satisfied, it is leaving from the loop.
	while (Target_Object_Address != NULL)
	{
		if (Target_Object_Address->TrieNode.Key != Search_Key)
		{
			Target_Object_Address = Target_Object_Address->Next;
		}
		else
		{
			break;
		}

	}

	return Target_Object_Address;
}


struct Carrier_of_ChildNode_Tag* TrieChild_Chained_Hash_Search(struct ChildrenTable_Tag* Table, int Searched_Key)
{
	int HashValue = TrieChild_Hash_Function(Table, Searched_Key);
	return	TrieChild_DoublyList_Search(Table->ChildrenList_Pointer + HashValue, Searched_Key);
}






void TrieChild_DoublyList_Delete(struct ChildrenList_Tag* LinkedList_Pointer, struct Carrier_of_ChildNode_Tag* Delete_Element_Address)
{
	if (Delete_Element_Address->Prev != NULL)
	{
		Delete_Element_Address->Prev->Next = Delete_Element_Address->Next;
	}
	else
	{
		LinkedList_Pointer->head = Delete_Element_Address->Next;
	}

	if (Delete_Element_Address->Next != NULL)
	{
		Delete_Element_Address->Next->Prev = Delete_Element_Address->Prev;
	}

	//Update the number of element in the linked list.
	LinkedList_Pointer->ObjectCounter--;
}


void TrieChild_Chained_Hash_Delete(struct ChildrenTable_Tag* Table, struct Carrier_of_ChildNode_Tag* DeleteObject_Address)
{
	int HashValue = TrieChild_Hash_Function(Table, DeleteObject_Address->TrieNode.Key);


	TrieChild_DoublyList_Delete(Table->ChildrenList_Pointer + HashValue, DeleteObject_Address);

	//Update the number of child node in the children table.
	Table->ChildrenCounter--;
}


//Alphabet Size / HashTable_Size = Constant for time complexity of average case.
#define Trie_Load_Factor 12.8
#define Alphabet_Size 256
#define HashTable_Size (Alphabet_Size/Trie_Load_Factor)



//Search the longest matched prefix of string in the trie. 
//If there is an last matched node in the trie, we return the pointer of the last matched node. If not, we return the pointer of root node. 
//We record the index of first unmatched character in the string if there is an unmatched character. If there is no unmatched character, we set the index of first unmatched character to be -1.
struct TrieNode_Tag* TrieNode_SearchLastMatchedNode(struct Trie_Tag* Trie_Pointer, unsigned char* String, int* Record_FirstUnmatchedCharacter_Index_Pointer)
{
	//Assign the pointer of root node to local variable.
	struct TrieNode_Tag* RootNode_Pointer = &Trie_Pointer->RootNode;

	//LastMatchedNode_Pointer is used for storing the pointer of last matched node in the trie when we are going through the trie for searching the longest matched prefix of string.
	//We initialize it with the pointer of root node, which means matching at start.
	struct TrieNode_Tag* LastMatchedNode_Pointer = &Trie_Pointer->RootNode;


	//The flag for judging if we find out the character in the last iteration of searching the longest matched prefix of string. 
	//We initialize it with 1, which means we find out the character at start.
	unsigned char FindMatchedCharacter_LastIteration_Flag = 1;

	//Go through each character in the string for searching the longest matched prefix of string in the trie.
	int i = -1;
	struct ChildrenTable_Tag* ChildrenTable_Pointer = NULL;
	while (FindMatchedCharacter_LastIteration_Flag)
	{
		//Increase the index of character in the string for current iteration, and we start with the index of first character in the string, which is 0.
		i++;

		//Assign the pointer of children table of last matched node to local variable.
		ChildrenTable_Pointer = &LastMatchedNode_Pointer->ChildrenTable;


		FindMatchedCharacter_LastIteration_Flag = 0; //We initialize the flag with 0 that we not yet find out the character at start of the current iteration.
		if (ChildrenTable_Pointer->ChildrenList_Pointer == NULL)
		{
			//If there is no child node as same as the charactee of string, we do nothing.
		}
		else
		{
			//If there is a child node with a key value as same as the character in the string, Carrier_of_ChildNode_Pointer is the pointer of carrier of child node. Otherwise the pointer is null.
			struct Carrier_of_ChildNode_Tag* Carrier_of_ChildNode_Pointer = TrieChild_Chained_Hash_Search(ChildrenTable_Pointer, String[i]);

			if (Carrier_of_ChildNode_Pointer != NULL)
			{
				//If we find out the character in the string, we update the pointer of last matched node for next iteration.
				LastMatchedNode_Pointer = &Carrier_of_ChildNode_Pointer->TrieNode;
				FindMatchedCharacter_LastIteration_Flag = 1; //We find out the character in the string, so we set the flag to be 1 for next iteration.


				if (LastMatchedNode_Pointer->Key == '\0')
				{
					//If the key value of last matched node is '\0', it means that there is already a string in the trie with same content as the string, 
					//so we take a break.
					break;
				}

			}
			else
			{
				//If there is no child node as same as the charactee of string, we do nothing.
			}

		}

	}


	if (FindMatchedCharacter_LastIteration_Flag == 0)
	{
		*Record_FirstUnmatchedCharacter_Index_Pointer = i; //Record the index of first unmatched character in the string.
	}
	else
	{
		*Record_FirstUnmatchedCharacter_Index_Pointer = -1; //If we find out the string in the trie, we set the index of first unmatched character to be -1 for indicating that there is no unmatched character.
	}

	return LastMatchedNode_Pointer;
}


//Here, we use '\0' as the termination character of string, and the '\0' character does not form the content of string except termination character.
//If the inserted string is already in the trie, we do nothing. Otherwise, we insert the string into the trie by inserting the non-matched part of string into the trie as a new branch from the last matched node. 
void TrieNode_Insertion(struct Trie_Tag* Trie_Pointer, unsigned char* String)
{
	int Record_FirstUnmatchedCharacter_Index;

	struct TrieNode_Tag* LastMatchedNode_Pointer = TrieNode_SearchLastMatchedNode(Trie_Pointer, String, &Record_FirstUnmatchedCharacter_Index);

	struct ChildrenTable_Tag* ChildrenTable_Pointer = &LastMatchedNode_Pointer->ChildrenTable;


	//Record_FirstUnmatchedCharacter_Index is not -1, which means that we do not find out the character in the string for the last iteration, 
	//so we need to insert the non-matched part of string into the trie as a new branch from the last matched node.
	if (Record_FirstUnmatchedCharacter_Index != -1)
	{
		Record_FirstUnmatchedCharacter_Index = Record_FirstUnmatchedCharacter_Index - 1;
		do
		{
			//Increase the index of character in the string for current iteration, and we start with the index of first non-matched character in the string.
			Record_FirstUnmatchedCharacter_Index++;

			//Create carrier of a new node for the character in the string.
			struct Carrier_of_ChildNode_Tag* InsertionObject_Address = (struct Carrier_of_ChildNode_Tag*)malloc(sizeof(struct Carrier_of_ChildNode_Tag));

			//Assign the new node to local variable for the character in the string.
			struct TrieNode_Tag* InsertionTrieNode_Pointer = &InsertionObject_Address->TrieNode;

			//Initialize the key value of new node, and the pointer of children table of new node with null pointer and 0 length.
			InsertionTrieNode_Pointer->Key = String[Record_FirstUnmatchedCharacter_Index];
			InsertionTrieNode_Pointer->ChildrenTable.ChildrenList_Pointer = NULL;
			InsertionTrieNode_Pointer->ChildrenTable.TableLength = 0;
			InsertionTrieNode_Pointer->ChildrenTable.ChildrenCounter = 0;


			//If the children table of last matched node is null pointer, we need to create and initialize the children table.
			//Time Complexity( Total Insertion for empty trie ) : Theta( HashTable_Size * (number of total nodes - number of leaves) ) ; Alphabet Size / HashTable_Size = Constant for average case of time complexity.
			if (ChildrenTable_Pointer->ChildrenList_Pointer == NULL)
			{
				ChildrenTable_Pointer->ChildrenList_Pointer = (struct ChildrenList_Tag*)malloc(sizeof(struct ChildrenList_Tag) * HashTable_Size);
				for (int i = 0; i < HashTable_Size; i++)
				{
					(ChildrenTable_Pointer->ChildrenList_Pointer + i)->head = NULL;
					(ChildrenTable_Pointer->ChildrenList_Pointer + i)->ObjectCounter = 0;
				}

				ChildrenTable_Pointer->TableLength = HashTable_Size;
			}

			TrieChild_Chained_Hash_Insert(ChildrenTable_Pointer, InsertionObject_Address);


			//Update the pointer of children table for next iteration, which is the pointer of children table of new node.
			ChildrenTable_Pointer = &InsertionTrieNode_Pointer->ChildrenTable;

		} while (String[Record_FirstUnmatchedCharacter_Index] != '\0');
	}


	//Record_FirstUnmatchedCharacter_Index is -1, which means that we find out all the characters in the string for the last iteration, and go out of the iteration,
	//Do nothing for insertion, because the string is already in the trie.

}


//If there is a string in the trie, we delete it and return 1. Otherwise, we do nothing in the trie and return 0.
_Bool TrieNode_Delete(struct Trie_Tag* Trie_Pointer, unsigned char* String)
{

	//The number of parent node in trie for the string, and we need to add 1 for the root node which is parent node.
	int Number_of_ParentNode = strlen(String) + 1;

	//We use an dynamic array to store the address of table of parent node for each character in the string.
	struct ChildrenTable_Tag** ParentTableAddress_Array = (struct ChildrenTable_Tag**)malloc(sizeof(struct ChildrenTable_Tag*) * Number_of_ParentNode);


	//Assign the pointer of root node to local variable.
	struct TrieNode_Tag* RootNode_Pointer = &Trie_Pointer->RootNode;


	//LastMatchedNode_Pointer is used for storing the pointer of last matched node in the trie when we are going through the trie for searching the longest matched prefix of string.
	//We initialize it with the pointer of root node, which means matching at start.
	struct TrieNode_Tag* LastMatchedNode_Pointer = &Trie_Pointer->RootNode;


	//The flag for judging if we find out the character in the last iteration of searching the longest matched prefix of string. 
	//We initialize it with 1, which means we find out the character at start.
	unsigned char FindMatchedCharacter_LastIteration_Flag = 1;

	//Go through each character in the string for searching the longest matched prefix of string in the trie.
	int i = -1;
	struct ChildrenTable_Tag* ChildrenTable_Pointer = NULL;
	while (FindMatchedCharacter_LastIteration_Flag)
	{

		//Increase the index of character in the string for current iteration, and we start with the index of first character in the string, which is 0.
		i++;


		//Store the address of table of parent node for current character in the string into the array for later use of deletion.
		ParentTableAddress_Array[i] = &LastMatchedNode_Pointer->ChildrenTable;


		//Assign the pointer of children table of last matched node to local variable.
		ChildrenTable_Pointer = &LastMatchedNode_Pointer->ChildrenTable;


		FindMatchedCharacter_LastIteration_Flag = 0; //We initialize the flag with 0 that we not yet find out the character at start of the current iteration.
		if (ChildrenTable_Pointer->ChildrenList_Pointer == NULL)
		{
			//If there is no child node as same as the charactee of string, we do nothing.
		}
		else
		{
			//If there is a child node with a key value as same as the character in the string, Carrier_of_ChildNode_Pointer is the pointer of carrier of child node. Otherwise the pointer is null.
			struct Carrier_of_ChildNode_Tag* Carrier_of_ChildNode_Pointer = TrieChild_Chained_Hash_Search(ChildrenTable_Pointer, String[i]);

			if (Carrier_of_ChildNode_Pointer != NULL)
			{
				//If we find out the character in the string, we update the pointer of last matched node for next iteration.
				LastMatchedNode_Pointer = &Carrier_of_ChildNode_Pointer->TrieNode;
				FindMatchedCharacter_LastIteration_Flag = 1; //We find out the character in the string, so we set the flag to be 1 for next iteration.


				if (LastMatchedNode_Pointer->Key == '\0')
				{
					//If the key value of last matched node is '\0', it means that there is already a string in the trie with same content as the string, 
					//so we take a break.
					break;
				}

			}
			else
			{
				//If there is no child node as same as the charactee of string, we do nothing.
			}

		}

	}


	if (FindMatchedCharacter_LastIteration_Flag == 0)
	{
		//We do not find out the string in the trie, so we free the allocated space and return 0 for indicating that we do not delete any character in the string.
		free(ParentTableAddress_Array);
		return 0;
	}


	//i is the index of parent node.
	i = Number_of_ParentNode - 1;
	while (i >= 0)
	{
		//The character value String[j] is as same as key of child node of parent node, which is included with '\0'.
		int j = i;

		//Search the child node of parent node with key value as same as character value String[j] for deletion
		struct Carrier_of_ChildNode_Tag* Carrier_of_ChildNode_Pointer = TrieChild_Chained_Hash_Search(ParentTableAddress_Array[i], String[j]);


		//Delete the child node of parent node with key value as same as character value String[j].
		TrieChild_Chained_Hash_Delete(ParentTableAddress_Array[i], Carrier_of_ChildNode_Pointer);


		//Free the memory of child node for deletion.
		free(Carrier_of_ChildNode_Pointer);

		if (ParentTableAddress_Array[i]->ChildrenCounter == 0)
		{
			//If there is no child node in the children table of parent node after deletion, we free the memory of children table for deletion.
			free(ParentTableAddress_Array[i]->ChildrenList_Pointer);

			//Update the pointer of children table of parent node to be null pointer for indicating that there is no child node in the children table of parent node.
			ParentTableAddress_Array[i]->ChildrenList_Pointer = NULL;

			//Update the length of children table of parent node to be 0 for indicating that there is no child node in the children table of parent node.
			ParentTableAddress_Array[i]->TableLength = 0;
		}


		//If there is still child node in the children table of parent node after deletion, we take a break for leaving from the loop, 
		//because we only need to delete the non-common part of string in the trie.
		if (ParentTableAddress_Array[i]->ChildrenCounter != 0)
		{
			break;
		}


		//Decrease the index of parent node for next iteration of deletion.
		i--;

	};


	//Free the allocated space for storing the address of table of parent node.
	free(ParentTableAddress_Array);

	//We delete the string from the trie and return 1.
	return 1;

}