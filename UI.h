#pragma once
#include "Service.h"


typedef struct
{
	Service* service;
}UI;


UI* createUI(Service* service);
void destroyUI(UI* ui);

void printMenu();

void printEstates(UI* ui, EstateRepo* repo);
int addEstateUI(UI* ui);
void removeEstateUI(UI* ui);
void updateEstateUI(UI* ui);

void filterUI(UI* ui);
void filterTypeUI(UI* ui);
void doubleFilterUI(UI* ui);

void undoUI(UI* ui);
void redoUI(UI* ui);

void menu(UI* ui);


