#pragma once
#include "DynamicArray.h"
#include <stdlib.h>


DynamicArray* createDynamicArray(int capacity, DestroyElemFunctionType destroyElf)
{
	DynamicArray* ar = (DynamicArray*)malloc(sizeof(DynamicArray));

	if (ar != NULL)
	{
		ar->capacity = capacity;
		ar->length = 0;

		ar->elements = (Elem*)malloc(capacity * sizeof(Elem));
		if (ar->elements != NULL)
		{
			ar->destroyElf = destroyElf;
			return ar;
		}
	}
}


void destroyDynamicArray(DynamicArray* ar)
{
	if (ar != NULL)
	{
		for (int i = 0; i < ar->length; i++)
			ar->destroyElf(ar->elements[i]);

		free(ar->elements);
		ar->elements = NULL;

		free(ar);

		ar = NULL;
	}
}

int resize(DynamicArray* ar)
{
	if (ar == NULL)
		return -1;

	ar->capacity *= 2;


	Elem* auxiliary = (Elem*)malloc(ar->capacity * sizeof(Elem));

	if (auxiliary != NULL)
	{
		for (int i = 0; i < ar->length; i++)
			auxiliary[i] = ar->elements[i];
		ar->elements = auxiliary;

		ar->elements = auxiliary;

		return 0;
	}
}


void addToArray(DynamicArray* ar, Elem el)
{
	if (ar != NULL && ar->elements != NULL)
	{
		if (ar->length == ar->capacity)
		{
			resize(ar);
		}

		int x = ar->length;
		ar->elements[x] = el;
		ar->length++;
	}
}


void delete(DynamicArray* ar, int position)
{
	if (ar != NULL && position >= 0 && position < ar->length)
	{
		ar->destroyElf(ar->elements[position]);

		if (position != ar->length - 1)
			ar->elements[position] = ar->elements[ar->length - 1];

		ar->length--;
	}
}


int getArrayLength(DynamicArray* ar)
{
	if (ar == NULL)
		return -1;

	return ar->length;
}


Elem getElemOnPos(DynamicArray* ar, int position)
{
	if (ar == NULL || position < 0 || position >= ar->length)
		return NULL;

	return ar->elements[position];
}