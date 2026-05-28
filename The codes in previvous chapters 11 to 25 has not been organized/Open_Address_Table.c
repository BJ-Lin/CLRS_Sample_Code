#include "..\Header.h"




struct Object2_Tag  Object_Array[Prime_Number_For_Slot_Number] = { [0] .Key = 0,[1].Key = 1,[2].Key = 2,[3].Key = 21,[4].Key = 4,[5].Key = 33,[6].Key = 62,[7].Key = 7,[8].Key = 8,[9].Key = 9,
																  [10].Key = 10,[11].Key = 11,[12].Key = 12,[13].Key = 13,[14].Key = 14,[15].Key = 15,[16].Key = 16,[17].Key = 17,[18].Key = 18,[19].Key = 19,
																	[20].Key = 20,[21].Key = 32,[22].Key = 22,[23].Key = 23,[24].Key = 24,[25].Key = 25,[26].Key = 26,[27].Key = 27,[28].Key = 28 };

//Open-address table
unsigned int Auxiliary_Hashing_Function1(struct Object2_Tag* ObjectAddress)
{
	return ObjectAddress->Key % Prime_Number_For_Slot_Number;
}
unsigned int Double_Hashing_Function(struct Object2_Tag* ObjectAddress, unsigned int Probe_Index)
{
	unsigned int Auxiliary_Value1 = 0;
	unsigned int Auxiliary_Value2 = 0;
	Auxiliary_Value1 = Auxiliary_Hashing_Function1(ObjectAddress);
	Auxiliary_Value2 = 1;  //For not using the delete flag to delete the slot, we need to using linear probing function.
	//Auxiliary_Value2 = 1 + (ObjectAddress->Key % Auxiliary_PrimeModuleDivisor);

	return (Auxiliary_Value1 + Probe_Index * Auxiliary_Value2) % Prime_Number_For_Slot_Number;

}
_Bool OpenAddress_Hash_Insert(struct Object2_Tag** Table, unsigned int TableSize, struct Object2_Tag* InsertionObject_Address, unsigned int* Address_of_HashValue_Record)
{
	unsigned int Probe_Index = 0; //0~m-1

	while (Probe_Index < TableSize)
	{
		*Address_of_HashValue_Record = Double_Hashing_Function(InsertionObject_Address, Probe_Index);
		if (Table[*Address_of_HashValue_Record] == NULL)
		{
			Table[*Address_of_HashValue_Record] = InsertionObject_Address;

			return 1;
		}

		else
		{
			Probe_Index++;
		}

	}

	return 0;

}
_Bool OpenAddress_Hash_Search(struct Object2_Tag** Table, unsigned int TableSize, struct Object2_Tag* SearchingObject_Address, unsigned int* Address_of_HashValue_Record)
{
	unsigned int Probe_Index = 0; //0~m-1
	*Address_of_HashValue_Record = Double_Hashing_Function(SearchingObject_Address, Probe_Index);

	while (Table[*Address_of_HashValue_Record] != NULL && Probe_Index < TableSize)
	{

		if (Table[*Address_of_HashValue_Record]->Key == SearchingObject_Address->Key)
		{
			return 1;
		}

		else
		{
			Probe_Index++;
			*Address_of_HashValue_Record = Double_Hashing_Function(SearchingObject_Address, Probe_Index);
		}


	}

	return 0;

}
unsigned int Inverse_Linear_Probing_Hashing_Function(struct Object2_Tag* ObjectAddress, unsigned int SlotPosition, unsigned int TableSize)
{
	return (SlotPosition - (ObjectAddress->Key % TableSize)) % TableSize;

}
_Bool Linear_Probing_Hash_Delete(struct Object2_Tag** Table, unsigned int TableSize, unsigned int Delete_SlotPosition)
{

	struct Object2_Tag* New_Object_Address;
	while (true)
	{
		Table[Delete_SlotPosition] = NULL;
		unsigned int New_Delete_Slot_Position = Delete_SlotPosition;

		do
		{
			New_Delete_Slot_Position = (New_Delete_Slot_Position + 1) % TableSize;
			New_Object_Address = Table[New_Delete_Slot_Position];

			if (New_Object_Address == NULL)
			{
				return 1;
			}

		} while (Inverse_Linear_Probing_Hashing_Function(Table[New_Delete_Slot_Position], Delete_SlotPosition, TableSize) >= Inverse_Linear_Probing_Hashing_Function(Table[New_Delete_Slot_Position], New_Delete_Slot_Position, TableSize));

		Table[Delete_SlotPosition] = New_Object_Address;



		//Update the new deleting slot for the next run.
		Delete_SlotPosition = New_Delete_Slot_Position;


	}

}