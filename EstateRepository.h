#pragma once
#include "Estate.h"
#include "DynamicArray.h"


typedef struct
{
	DynamicArray* estate;
	int length;
}EstateRepo;


EstateRepo* createEstateRepo();

void destroyRepo(EstateRepo* repo);

int getLength(EstateRepo* repo);

int findEstate(EstateRepo* repo, char* address);
Estate* findEstateByAddress(EstateRepo* repo, char* address);

Estate* getEstateOnPosition(EstateRepo* repo, int position);

int addEstate(EstateRepo* repo, Estate* estate);
int removeEstate(EstateRepo* repo, char* address);
int updateEstate(EstateRepo* repo, char* address, int price);

EstateRepo* filter(EstateRepo* r, char string[]);
EstateRepo* doubleFilter(EstateRepo* r, char* type, int value);




