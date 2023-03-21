#include "Service.h"
#include "EstateRepository.h"
#include "Operation.h"
#include <stdlib.h>
#include <string.h>




Service* createService(EstateRepo* repo)
{
	Service* service = malloc(sizeof(Service));
	if (service != NULL)
	{
		service->repo = repo;
		service->undoStack = createDynamicArray(15, &destroyOperation);
		service->redoStack = createDynamicArray(15, &destroyOperation);

		return service;
	}
}


void destroyService(Service* service)
{
	if (service != NULL)
	{
		destroyRepo(service->repo);
		destroyDynamicArray(service->undoStack);
		destroyDynamicArray(service->redoStack);
		free(service);
	}
}


EstateRepo* getRepo(Service* service)
{
	return service->repo;
}

Estate* getService(Service* service, int position)
{
	return getEstateOnPosition(service->repo, position);
}


int add(Service* service, char* type, char* address, int price, int surface)
{
	Estate* estate = createEstate(type, address, price, surface);

	int x = addEstate(service->repo, estate);
	if (x != 1)
	{
		destroyEstate(estate);
		x = 0;
	}
	else
	{
		Operation* operation = createOperation(ADD, estate);

		if (operation != NULL)
		{
			addToArray(service->undoStack, operation);
		}
	}

	return x;
}


int removeService(Service* s, char* address)
{
	Estate* estate = findEstateByAddress(s->repo, address);
	Operation* op = createOperation(DELETE, estate);

	if (op != NULL)
	{
		addToArray(s->undoStack, op);

		return removeEstate(s->repo, address);
	}
}

int prices[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int ct = 0;

int update(Service* s, char* address, int price)
{
	Estate* estate = findEstateByAddress(s->repo, address);
	Operation* op = createOperation(UPDATE, estate);

	if (op != NULL)
	{
		addToArray(s->undoStack, op);

		prices[ct++] = price;

		return updateEstate(s->repo, address, price);
	}
}


int undo(Service* s)
{
	if (s == NULL)
		return -1;

	int stackSize = getArrayLength(s->undoStack);
	if (stackSize == 0)
		return -2;

	Operation* operation = getElemOnPos(s->undoStack, stackSize - 1);
	Estate* estate = getOperationObject(operation);

	if (getOperationType(operation) == ADD)
		removeEstate(s->repo, getAddress(estate));
	else if (getOperationType(operation) == DELETE)
		addEstate(s->repo, copyEstate(estate));
	else if (getOperationType(operation) == UPDATE)
		updateEstate(s->repo, getAddress(estate), getPrice(estate));

	addToArray(s->redoStack, copyOperation(operation));

	delete(s->undoStack, stackSize - 1);

	return 0;
}


int redo(Service* s)
{
	if (s == NULL)
		return -1;

	int stackSize = getArrayLength(s->redoStack);
	if (stackSize == 0)
		return -2;

	Operation* operation = getElemOnPos(s->redoStack, stackSize - 1);
	Estate* estate = getOperationObject(operation);

	if (getOperationType(operation) == ADD)
	{
		addEstate(s->repo, copyEstate(estate));
	}
	else if (getOperationType(operation) == DELETE)
		removeEstate(s->repo, getAddress(estate));
	else if (getOperationType(operation) == UPDATE)
	{
		ct--;
		updateEstate(s->repo, getAddress(estate), prices[ct]);
		//updateEstate(s->repo, getAddress(estate), getPrice(estate));
	}

	addToArray(s->undoStack, copyOperation(operation));
	delete(s->redoStack, stackSize - 1);

	return 0;
}











/*
EstateRepo* filterType(Service* s, char type[])
{
	EstateRepo* repo = createEstateRepo();
	repo->length = 0;

	int length = getLength(s->repo);
	for (int i = 0; i < length; i++)
	{
		if (strcmp(getEstateOnPosition(s->repo, i)->type, type) == 0)
		{
			Estate* e = getEstateOnPosition(s->repo, i);
			int x = addEstate(repo, e);
		}
	}

	length = getLength(repo) - 1;

	for (int i = 0; i < length; i++)
		for (int j = i + 1; j <= length; j++)
			if (strcmp(getEstateOnPosition(repo, i)->address, getEstateOnPosition(repo, j)->address) > 0)
			{
				Estate* aux = repo->estate[i];
				repo->estate[i] = repo->estate[j];
				repo->estate[j] = aux;
			}

	return repo;
}



int undo(Service* s)
{
	if (s == NULL)
		return -1;

	int stackSize = getArrayLength(s->undoStack);
	if (stackSize == 0)
		return 1;

	Operation* operation = getElemOnPos(s->undoStack, stackSize - 1);
	if (operation == NULL)
		return -1;

	Estate* estate = getOperationObject(operation);
	if (estate == NULL)
		return -1;

	if (getOperationType(operation) == ADD)
		removeEstate(s->repo, getAddress(estate));
	else if (getOperationType(operation) == DELETE)
		addEstate(s->repo, copyEstate(estate));
	else if (getOperationType(operation) == UPDATE)
		updateEstate(s->repo, getAddress(estate), getPrice(estate));

	addToArray(s->redoStack, copyOperation(operation));

	delete(s->undoStack, stackSize - 1);

	return 0;
}


int redo(Service* s)
{
	if (s == NULL)
		return -1;

	int stackSize = getArrayLength(s->redoStack);
	if (stackSize == 0)
		return -2;

	Operation* operation = getElemOnPos(s->redoStack, stackSize - 1);
	if (operation == NULL)
		return -3;

	Estate* estate = getOperationObject(operation);
	if (estate == NULL)
		return -4;

	if (getOperationType(operation) == ADD)
	{
		addEstate(s->repo, copyEstate(estate));
	}
	else if (getOperationType(operation) == DELETE)
		removeEstate(s->repo, getAddress(estate));
	else if (getOperationType(operation) == UPDATE)
	{
		ct--;
		updateEstate(s->repo, getAddress(estate), prices[ct]);
		//updateEstate(s->repo, getAddress(estate), getPrice(estate));
	}

	addToArray(s->undoStack, copyOperation(operation));
	delete(s->redoStack, stackSize - 1);

	return 0;
}
*/


