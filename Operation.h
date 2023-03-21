#pragma once
#include "Estate.h"


typedef enum
{
	ADD,
	DELETE,
	UPDATE
}operationType;


typedef struct
{
	operationType type;
	Estate* estate;
}Operation;


Operation* createOperation(operationType type, Estate* estate);
void destroyOperation(Operation* operation);
Operation* copyOperation(Operation* operation);

operationType getOperationType(Operation* operation);
Estate* getOperationObject(Operation* operation);