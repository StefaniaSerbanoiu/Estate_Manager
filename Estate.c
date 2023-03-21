#include "Estate.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

Estate* createEstate(char* type, char* address, int price, int surface)
{
	Estate* estate = malloc(sizeof(Estate));
	if (estate != NULL)
	{
		estate->type = malloc(sizeof(char) * (strlen(type) + 1));
		if (estate->type != NULL)
			strcpy(estate->type, type);

		estate->address = malloc(sizeof(char) * (strlen(address) + 1));
		if (estate->address != NULL)
			strcpy(estate->address, address);

		estate->price = price;

		estate->surface = surface;

		return estate;
	}
}


void destroyEstate(Estate* estate)
{
	if (estate == NULL)
		return;

	
	free(estate->type);
	free(estate->address);

	free(estate);
}

char* getType(Estate* estate)
{
	if (estate == NULL)
		return NULL;
	return estate->type;
}

char* getAddress(Estate* estate)
{
	if (estate == NULL)
		return NULL;
	return estate->address;
}

int getSurface(Estate* estate)
{
	if (estate == NULL)
		return -1;
	return estate->surface;
}

int getPrice(Estate* estate)
{
	if (estate == NULL)
		return -1;
	return estate->price;
}

Estate* copyEstate(Estate* estate)
{
	if (estate == NULL)
		return NULL;

	return createEstate(estate->type, estate->address, estate->price, estate->surface);
}

void setType(Estate* estate, char* t)
{
	estate->type = t;
}

void setAddress(Estate* estate, char* addr)
{
	estate->address = addr;
}

void setPrice(Estate* estate, int p)
{
	estate->price = p;
}

void setSurface(Estate* estate, int s)
{
	estate->surface = s;
}
