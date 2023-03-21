#pragma once
# define CAPACITY 15


typedef void* Elem;
typedef void (*DestroyElemFunctionType)(void*);


typedef struct
{
	Elem* elements;
	int length;
	int capacity;
	DestroyElemFunctionType destroyElf;
}DynamicArray;



DynamicArray* createDynamicArray(int capacity, DestroyElemFunctionType destroyElf);
void destroyDynamicArray(DynamicArray* ar);

int resize(DynamicArray* ar);

void addToArray(DynamicArray* ar, Elem el);
void delete(DynamicArray* ar, int position);

int getArrayLength(DynamicArray* ar);
Elem getElemOnPos(DynamicArray* ar, int position);