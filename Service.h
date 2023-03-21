#pragma once
#include "EstateRepository.h"
#include "DynamicArray.h"


typedef struct
{
	EstateRepo* repo;
	DynamicArray* undoStack;
	DynamicArray* redoStack;
}Service;


Service* createService(EstateRepo* repo);
void destroyService(Service* service);

EstateRepo* getRepo(Service* service);

Estate* getService(Service* service, int position);


int add(Service* service, char* type, char* address, int price, int surface);
int removeService(Service* s, char* address);
int update(Service* s, char* address, int price);

int undo(Service* s);
int redo(Service* s);