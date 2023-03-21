#pragma once
#include "Estate.h"

typedef Estate TElement;


typedef struct
{
	TElement* elements;
	int length;          // actual length of the array
	int capacity;		 // maximum length of the array
}EstateDynamicArray;

/// <summary>
/// Creates a dynamic array of generic elements, with a given capacity.
/// </summary>
/// <param name="capacity">Integer, maximum capacity for the dynamic array.</param>
/// <returns>A pointer the the created dynamic array.</returns>
EstateDynamicArray* create(int capacity);

/// <summary>
/// Destroys the dynamic array.
/// </summary>
/// <param name="arr">The dynamic array to be destoyed.</param>
/// <returns>A pointer the the created dynamic array.</returns>
void destroy(EstateDynamicArray* a);

/// <summary>
/// Adds a generic element to the dynamic array.
/// </summary>
/// <param name="arr">The dynamic array.</param>
/// <param name="p">The planet to be added.</param>
void addToEstateDA(EstateDynamicArray* a, TElement new_element);

// Tests
void testsDynamicArray();

