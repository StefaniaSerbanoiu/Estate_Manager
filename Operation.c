#include "Estate.h"
#include "Operation.h"
#include <stdlib.h>


Operation* createOperation(operationType type, Estate* estate)
{
	Operation* operation = malloc(sizeof(Operation));
	operation->type = type;
	Estate* copy = copyEstate(estate);
	operation->estate = copy;

	return operation;
}


void destroyOperation(Operation* operation)
{
	if (operation != NULL)
	{
		destroyEstate(operation->estate);
		free(operation);
	}
}


operationType getOperationType(Operation* operation)
{
	if (operation == NULL)
		return -1;

	return operation->type;
}


Estate* getOperationObject(Operation* operation)
{
	if (operation == NULL)
		return NULL;

	return operation->estate;
}


Operation* copyOperation(Operation* operation)
{
	if (operation == NULL)
		return NULL;

	return createOperation(operation->type, operation->estate);
}