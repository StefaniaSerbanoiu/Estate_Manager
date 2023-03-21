#include "EstateDynamicArray.h"
#include <stdlib.h>

EstateDynamicArray* create(int capacity)
{
	EstateDynamicArray* arr = malloc(sizeof(EstateDynamicArray));
	// checking if the space was actually allocated in memory
	if (arr == NULL)
	{
		return NULL;
	}

	// if the allocation was successful
	arr->elements = malloc(capacity * sizeof(TElement));
	// checking if the elements's space was allocated in memory successfully
	if (arr->elements == NULL)
	{
		return NULL;
	}

	return arr;
}

void destroy(EstateDynamicArray* a)
{
	// checking if the array a actually exists and it's valid
	if (a != NULL)
	{
		// free the allocated space for the estates
		free(a->elements);
		a->elements = NULL;

		// free the space allocated for the dynamic array
		free(a);
	}
}


// resizes the array, allocating more space for it
void resizeEstateDA(EstateDynamicArray* arr)
{
	// checking if the array actually exists
	if (arr != NULL)
	{
		arr->capacity *= 2;
		TElement* e = realloc(arr->elements, arr->capacity * sizeof(TElement));
		// check if the realloc operation was executed successfully
		if (e)
		{
			arr->elements = e;
		}
	}
}


void addToEstateDA(EstateDynamicArray* a, TElement new_element)
{
	// check if the array and its elements are valid
	if (a && a->elements)
	{
		// if the new length is bigger than the capacity of the array, the array needs to be resized
		if (a->length == a->capacity)
		{
			resizeEstateDA(a);
		}
		// adding a new element at the end of the dynamic array, then updating the length
		a->elements[a->length] = new_element;
		a->length++;
	}
}

/*
void testsdynamicarray()
{
	dynamicarray* da = createdynamicarray(2);
	if (da == null)
		assert(0);

	assert(da->capacity == 2);
	assert(da->length == 0);

	planet p1 = createplanet("wolf 1061 c", "terrestrial", 13.8);
	add(da, p1);
	assert(da->length == 1);

	planet p2 = createplanet("hat-p-26b", "neptune-like", 450);
	add(da, p2);
	assert(da->length == 2);

	// capacity must double
	planet p3 = createplanet("proxima centauri b", "terrestrial", 4.2);
	add(da, p3);
	assert(da->length == 3);
	assert(da->capacity == 4);

	destroy(da);
}
*/