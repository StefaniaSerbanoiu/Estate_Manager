#pragma once

typedef struct
{
	char* type;
	char* address;
	int price;
	int surface;
}Estate;	


Estate* createEstate(char* type, char* address, int price, int surface);
void destroyEstate(Estate* estate);
Estate* copyEstate(Estate* estate);

char* getType(Estate* estate);
char* getAddress(Estate* estate);
int getPrice(Estate* estate);
int getSurface(Estate* estate);

void setType(Estate* estate, char* t);
void setAddress(Estate* estate, char* addr);
void setPrice(Estate* estate, int p);
void setSurface(Estate* estate, int s);
