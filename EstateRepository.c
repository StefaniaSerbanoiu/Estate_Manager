#pragma once
#include "EstateRepository.h"
#include "Operation.h"
#include "Estate.h"
#include "DynamicArray.h"
#include <stdlib.h>
#include <string.h>


EstateRepo* createEstateRepo()
{
	EstateRepo* repo = malloc(sizeof(EstateRepo));
	if (repo != NULL)
	{
		repo->estate = createDynamicArray(15, &destroyEstate);
		repo->length = 0;
		return repo;
	}
}


void destroyRepo(EstateRepo* repo)
{
	if (repo != NULL)
	{
		destroyDynamicArray(repo->estate);
		free(repo);
	}
}


int getLength(EstateRepo* repo)
{
	return repo->length;
}


int findEstate(EstateRepo* repo, char* address)
{
	if (repo == NULL || address == NULL)
		return -1;
	
	for (int i = 0; i < repo->length; i++)
	{
		Estate* estate = getElemOnPos(repo->estate, i);
		char* addr = getAddress(estate);
		if (strcmp(addr, address) == 0)
		{
			return i;
		}
	}
	return -1;
}


Estate* findEstateByAddress(EstateRepo* repo, char* address)
{
	if (repo == NULL || address == NULL)
		return -1;

	for (int i = 0; i < repo->length; i++)
	{
		Estate* estate = getElemOnPos(repo->estate, i);
		if (strcmp(estate->address, address) == 0)
		{
			return estate;
		}
	}
	return NULL;
}

Estate* getEstateOnPosition(EstateRepo* repo, int position)
{
	if (repo == NULL)
		return NULL;
	if (position < 0 || position >= repo->length)
		return NULL;
	return getElemOnPos(repo->estate, position);
}

int addEstate(EstateRepo* repo, Estate* estate)
{
	if (findEstate(repo, estate->address) == -1)
	{
		addToArray(repo->estate, estate);
		repo->length++;
		return 1;
	}
	return 0;
}

int removeEstate(EstateRepo* repo, char* address)
{
	int position = findEstate(repo, address);
	if (position != -1)
	{
		Estate* estate = getElemOnPos(repo->estate, position);
		delete(repo->estate, position);
		repo->length--;

		return 1;
	}
	return 0;
}

int updateEstate(EstateRepo* repo, char* address, int price)
{
	int position = findEstate(repo, address);

	if (position != -1)
	{
		Estate* estate = getElemOnPos(repo->estate, position);
		estate->price = price;
		return 1;
	}
	return 0;
}

EstateRepo* filter(EstateRepo* r, char string[])
{
	EstateRepo* repo = createEstateRepo();
	repo->length = 0;

	if (string[0] == '-')
	{
		int len = getLength(r);
		for (int i = 0; i < len; i++)
		{
				Estate* e = getEstateOnPosition(r, i);
				int x = addEstate(repo, copyEstate(e));
		}
	}

	else
	{
		int len = getLength(r);
		for (int i = 0; i < len; i++)
		{
			if (strstr(getEstateOnPosition(r, i)->address, string) != NULL)
			{
				Estate* e = getEstateOnPosition(r, i);
				int x = addEstate(repo, copyEstate(e));
			}
		}
	}

	int length_j = getLength(repo);
	int length_i = length_j - 1;

	for (int i = 0; i < length_i; i++)
	{

		for (int j = i + 1; j < length_j; j++)
		{
			int price_j = getPrice(getEstateOnPosition(repo, j));
			if (getPrice(getEstateOnPosition(repo, i)) > price_j)
			{
				Estate* ei = getEstateOnPosition(repo, i);
				Estate* ej = getEstateOnPosition(repo, j);

				char* type_aux = getType(ei);
				char* address_aux = getAddress(ei);
				int surface_aux = getSurface(ei);
				int price_aux = getPrice(ei);

				setType(ei, getType(ej));
				setAddress(ei, getAddress(ej));
				setSurface(ei, getSurface(ej));
				setPrice(ei, price_j);

				setType(ej, type_aux);
				setAddress(ej, address_aux);
				setSurface(ej, surface_aux);
				setPrice(ej, price_aux);
			}
		}
	}
	return repo;

	
}

EstateRepo* doubleFilter(EstateRepo* r , char* type, int value)
{
	EstateRepo* repo = createEstateRepo();
	repo->length = 0;

	int length = getLength(r);
	for (int i = 0; i < length; i++)
	{
		Estate* estate = getEstateOnPosition(r, i);
		if (strcmp(estate->type, type) == 0 && estate->surface > value)
		{
			int x = addEstate(repo, copyEstate(estate));
		}
	}
	return repo;
}