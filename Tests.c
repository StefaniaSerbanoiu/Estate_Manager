#pragma once
#include "Tests.h"
#include "EstateRepository.h"
#include "Operation.h"
#include "Service.h"
#include <stdlib.h>
#include <assert.h>



// Repository Tests

void initEstateRepoForTests(EstateRepo* repo)
{
	Estate* e = createEstate("house", "complex_a", 2000, 10099);
	addEstate(repo, e);
}

void test_createEstateRepo()
{
	EstateRepo* repo = createEstateRepo();
	assert(repo != NULL);

	destroyRepo(repo);
}

void test_getLength()
{
	EstateRepo* repo = createEstateRepo();
	assert(getLength(repo) == 0);
	initEstateRepoForTests(repo);
	assert(getLength(repo) == 1);

	destroyRepo(repo);
}

void test_findEstate()
{
	EstateRepo* repo = createEstateRepo();
	assert(findEstate(repo, "") == -1);
	initEstateRepoForTests(repo);
	assert(findEstate(repo, "complex_b") == -1);
	assert(findEstate(repo, "complex_a") == 0); // because there is just one element => placed on position 0
	assert(findEstate(repo, NULL) == -1);
	assert(findEstate(NULL, "complex_a") == -1);

	destroyRepo(repo);
}

void test_findEstateByAddress()
{
	EstateRepo* repo = createEstateRepo();
	initEstateRepoForTests(repo);
	assert(findEstateByAddress(repo, "complex_b") == NULL);
	assert(findEstateByAddress(repo, NULL) == -1);
	assert(findEstateByAddress(NULL, "complex_a") == -1);
	assert(findEstateByAddress(repo, "complex_a") == getElemOnPos(repo->estate, 0));

	destroyRepo(repo);
}

void test_getEstateOnPosition()
{
	EstateRepo* repo = createEstateRepo();
	initEstateRepoForTests(repo);

	assert(getEstateOnPosition(repo, -2) == NULL);
	assert(getEstateOnPosition(repo, 0) == getElemOnPos(repo->estate, 0));
	assert(getEstateOnPosition(NULL, 0) == NULL);

	destroyRepo(repo);
}

void testAddEstate()
{
	EstateRepo* repo = createEstateRepo();
	initEstateRepoForTests(repo);
	assert(getLength(repo) == 1);

	Estate* e = createEstate("house", "nr1986", 25, 1000);
	assert(addEstate(repo, e) == 1);
	assert(getLength(repo) == 2);

	assert(addEstate(repo, e) == 0);

	destroyRepo(repo);
}


void test_removeEstate()
{
	EstateRepo* repo = createEstateRepo();
	initEstateRepoForTests(repo);
	Estate* e = createEstate("house", "nr1986", 25, 1000);
	addEstate(repo, e);
	Estate* e2 = createEstate("house", "nr1988", 25456, 1000);
	addEstate(repo, e2);
	assert(getLength(repo) == 3);


	assert(removeEstate(repo, "nr1986") == 1);
	assert(getLength(repo) == 2);

	assert(removeEstate(repo, "nr1986") == 0);

	destroyRepo(repo);
}


void test_updateEstate()
{
	EstateRepo* repo = createEstateRepo();
	initEstateRepoForTests(repo);

	assert(getPrice(getElemOnPos(repo->estate, 0)) == 2000);
	assert(updateEstate(repo, "complex_a", 999) == 1);
	assert(getPrice(getElemOnPos(repo->estate, 0)) == 999);
	assert(updateEstate(repo, "complex_b", 999) == 0);

	destroyRepo(repo);
}

void testsEstateRepo()
{
	test_createEstateRepo();
	test_getLength();
	test_findEstate();
	test_findEstateByAddress();
	test_getEstateOnPosition();
	testAddEstate();
	test_removeEstate();
	test_updateEstate();
}

void tests_operationInvalidCases()
{
	assert(getOperationObject(NULL) == NULL);
	assert(getOperationType(NULL) == -1);
	assert(copyOperation(NULL) == NULL);
}

// Service Tests

Service* initServiceForTests()
{
	EstateRepo* repo = createEstateRepo();
	initEstateRepoForTests(repo);
	Service* service = createService(repo);
	return service;
}

void test_getService()
{
	Service* service = initServiceForTests();
	assert(strcmp(getAddress(getService(service, 0)),"complex_a") == 0);
	destroyService(service);
}

void test_getRepo()
{
	Service* service = initServiceForTests();
	assert(getRepo(service)->length == 1);
	destroyService(service);
}

void test_service_functions()
{
	Service* service = initServiceForTests();
	assert(undo(service) == -2);
	assert(redo(service) == -2);
	add(service, "house", "test_address", 1000, 200000);
	assert(strcmp(getAddress(getService(service, 1)), "test_address") == 0);
	assert(getLength(service->repo) == 2);
	undo(service);
	assert(getLength(service->repo) == 1);
	redo(service);
	assert(getLength(service->repo) == 2);
	assert(add(service, "house", "test_address_2", 1000, 200000) == 1);
	assert(getLength(service->repo) == 3);
	assert(removeService(service, "test_address_2") == 1);
	assert(getLength(service->repo) == 2);
	undo(service);
	assert(getLength(service->repo) == 3);
	redo(service);
	assert(getLength(service->repo) == 2);
	assert(update(service, "test_address_2", 2000) == 0);
	assert(update(service, "test_address", 2000) == 1);
	assert(getPrice(getService(service, 1)) == 2000);
	undo(service);
	assert(getPrice(getService(service, 1)) == 1000);
	redo(service);
	assert(getPrice(getService(service, 1)) == 2000);
	assert(update(service, "test_address_not_existing", 1000) == 0);
	assert(removeService(service, "test_address_not_existing") == 0);
	assert(removeService(service, "test_address") == 1);
	assert(removeService(service, "test_address") == 0);
	assert(add(service, "house", "complex_a", 1000, 200000) == 0);
	assert(undo(NULL) == -1);
	assert(redo(NULL) == -1);
	destroyService(service);
}

void test_filter()
{
	Service* service = initServiceForTests();
	add(service, "house", "test_address", 1000, 200000);
	EstateRepo* r = filter(service->repo, "-");
	assert(getPrice(getEstateOnPosition(r, 0)) == 1000);
	assert(getPrice(getEstateOnPosition(r, 1)) == 2000);
	destroyRepo(r);
	EstateRepo* r2 = filter(service->repo, "complex_a");
	assert(getPrice(getEstateOnPosition(r2, 0)) == 2000);
	destroyRepo(r2);
	destroyService(service);
}

void test_doubleFilter()
{
	Service* service = initServiceForTests();
	add(service, "house", "test_address", 1000, 1000);
	add(service, "penthouse", "test_address_2", 15000, 200000);
	add(service, "house", "test_address_3", 5000, 200000);
	EstateRepo* r = doubleFilter(service->repo, "house", 1005);
	assert(strcmp(getAddress(getEstateOnPosition(r, 0)), "complex_a") == 0);
	assert(strcmp(getAddress(getEstateOnPosition(r, 1)), "test_address_3") == 0);
	destroyRepo(r);
	destroyService(service);
}

void testsService()
{
	test_getService();
	test_getRepo();
	test_service_functions();
	test_filter();
	test_doubleFilter();
}

void tests_DynamicArray()
{
	DynamicArray* ar = createDynamicArray(1, &destroyEstate);
	assert(getArrayLength(NULL) == -1);
	Estate* e = createEstate("house", "complex_a", 2000, 10099);
	addToArray(ar, e);
	assert(getArrayLength(ar) == 1);
	assert(strcmp(getAddress(getElemOnPos(ar, 0)), "complex_a") == 0);
	assert(getAddress(NULL) == NULL);
	assert(getType(NULL) == NULL);
	assert(getPrice(NULL) == -1);
	assert(getSurface(NULL) == -1);
	assert(getElemOnPos(ar, -1) == NULL);
	
	Estate* e1 = createEstate("house", "complex_a", 2000, 10099);
	addToArray(ar, e1); // tests resize function 
	assert(getArrayLength(ar) == 2);
	assert(resize(ar) == 0);
	assert(resize(NULL) == -1);
	destroyDynamicArray(ar);
}


void allTests()
{
	testsEstateRepo();
	tests_operationInvalidCases();
	testsService();
}
