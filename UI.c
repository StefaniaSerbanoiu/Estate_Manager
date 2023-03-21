#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "UI.h"
#include "Estate.h"


UI* createUI(Service* service)
{
	UI* ui = malloc(sizeof(UI));

	if (ui == NULL)
		return NULL;

	ui->service = service;

	return ui;
}


void destroyUI(UI* ui)
{
	if (ui == NULL)
		return;

	destroyService(ui->service);
	free(ui);
}


void printMenu()
{
	printf("~~~~~~~~~~~~~~MENU~~~~~~~~~~~~~\n1. To see all estates, press 1.\n2. To add a new estate, press 2.\n3. To remove an estate, press 3.\n");
	printf("4. To update an existing estate, press 4.\n5. To sort, press 5.\n");
	printf("6. To undo last operation, press 6.\n7. To redo last operation, press 7.\n");
	printf("8. To see all estates of a given type, having the surface greater than a user provided value, press 8.\n10. To exit, press 0.\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}


void printEstates(UI* ui, EstateRepo* repo)
{
	if (ui == NULL)
		return;

	if (repo == NULL)
		return;

	int len = getLength(repo);
	for (int i = 0; i < len; i++)
	{
		Estate* estate = getService(ui->service, i);
		printf("The %s at the address %s has the price %d and surface %d.\n", getType(estate), getAddress(estate), getPrice(estate), getSurface(estate));

	}
	printf("\n\n");
}

void printEstatesList(EstateRepo* repo)
{
	if (repo == NULL)
		return;

	int len = getLength(repo);
	for (int i = 0; i < len; i++)
	{
		Estate* estate = getEstateOnPosition(repo, i);
		printf("The %s at the address %s has the price %d and surface %d.\n", getType(estate), getAddress(estate), getPrice(estate), getSurface(estate));

	}
	printf("\n\n");
}



int addEstateUI(UI* ui)
{
	char type[15], address[50];
	int price, surface;

	printf("Introduce the type: ");
	scanf("%s", type);
	while (strcmp(type, "house") != 0 && strcmp(type, "apartament") != 0 && strcmp(type, "penthouse") != 0)
	{
		printf("Error!!! The type is not correct!!! Try again!!!\n");
		printf("Introduce the type: ");
		scanf("%s", type);
		
	}
	printf("Introduce the address: ");
	scanf("%s", address);
	printf("Introduce the price: ");
	scanf(" %d", &price);
	while (price < 50)
	{
		printf("Error!!! The price is too low!!! Try again!!!\n");
		printf("Introduce the price: ");
		scanf(" %d", &price);

	}
	printf("Introduce the surface: ");
	scanf(" %d", &surface);
	while (price < 5)
	{
		printf("Error!!! The surface is too small!!! Try again!!!\n");
		printf("Introduce the surface: ");
		scanf(" %d", &surface);
	}
	return add(ui->service, type, address, price, surface);
}


void removeEstateUI(UI* ui)
{
	char address[50];
	printf("Introduce the address: ");
	scanf("%s", address);
	int result = removeService(ui->service, address);
	while (!result)
	{
		printf("The estate at address %s doesn't exist.\n", address);
		printf("Introduce the address: ");
		scanf("%s", address);
		result = removeService(ui->service, address);
	}
	printf("The estate at address %s was deleted.\n", address);
}

void updateEstateUI(UI* ui)
{
	char address[50];
	int price;

	printf("Introduce the address: ");
	scanf("%s", address);
	printf("Introduce the new price: ");
	scanf(" %d", &price);
	while (price < 50)
	{
		printf("Error!!! The price is too low!!! Try again!!!\n");
		printf("Introduce the price: ");
		scanf(" %d", &price);

	}

	int result = update(ui->service, address, price);
	while (!result)
	{
		printf("The estate at address %s doesn't exist.\n", address);
		printf("Introduce the address: ");
		scanf("%s", address);
		result = update(ui->service, address, price);
	}
	printf("The estate at address %s was updated.\n", address);
}


void filterUI(UI* ui)
{
	char string[20];
	printf("Introduce the string to be found or '-' to apply to all:");
	scanf("%s", string);
	
	EstateRepo* repo = filter(getRepo(ui->service), string);
	printEstatesList(repo);

	destroyRepo(repo);
}

void doubleFilterUI(UI* ui)
{
	char type[15];
	printf("Introduce the type: ");
	scanf("%s", type);
	while (strcmp(type, "house") != 0 && strcmp(type, "apartament") != 0 && strcmp(type, "penthouse") != 0)
	{
		printf("Error!!! The type is not correct!!! Try again!!!\n");
		printf("Introduce the type: ");
		scanf("%s", type);

	}

	int value;
	printf("Introduce the value: ");
	scanf("%d", &value);

	EstateRepo* repo =  doubleFilter(getRepo(ui->service), type, value);
	printEstatesList(repo);

	destroyRepo(repo);
}


void undoUI(UI* ui)
{
	undo(ui->service);
	printf("Done\n");
}


void redoUI(UI* ui)
{
	redo(ui->service);
	printf("Done\n");
}


void menu(UI* ui)
{
	printMenu();
	int option;
	int done = 0;
	while (!done)
	{
		scanf("%d", &option);
		if (option == 1)
			printEstates(ui, getRepo(ui->service));
		else if (option == 2)
			addEstateUI(ui);
		else if (option == 3)
			removeEstateUI(ui);
		else if (option == 4)
			updateEstateUI(ui);
		else if (option == 5)
			filterUI(ui);
		else if (option == 6)
			undoUI(ui);
		else if (option == 7)
			redoUI(ui);
		else if (option == 8)
			doubleFilterUI(ui);
		else if (option == 0)
			done = 1;
		else
			printf("That option doesn't exist!!! Try again!!!\n");
	}
}

/*
void filterTypeUI(UI* ui)
{
	char type[15];
	printf("Introduce the type:");
	scanf("%s", type);

	//EstateRepo* repo = filterType(ui->service, type);
	//printEstates(ui, repo);
}
*/