#include <stdio.h>
#include "Estate.h"
#include "EstateRepository.h"
#include "Service.h"
#include "UI.h"
#include "Tests.h"
#include <string.h>
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC

int main()
{ 
	allTests();
	
	EstateRepo* repo = createEstateRepo();
	
	addEstate(repo, createEstate("house", "complex_a", 2090, 10099));
	addEstate(repo, createEstate("house", "nr1986", 250, 1000));
	addEstate(repo, createEstate("house", "nr._2567", 499, 1001));
	addEstate(repo, createEstate("penthouse", "str-A-27", 2999, 1000));
	addEstate(repo, createEstate("apartment", "complexB5", 2400, 1001));
	addEstate(repo, createEstate("house", "complex_c", 9000, 100000));
	addEstate(repo, createEstate("house", "abc", 299999, 99999));
	addEstate(repo, createEstate("house", "nr._7", 240000, 10001));
	addEstate(repo, createEstate("penthouse", "NewStreet", 99999, 10008));
	addEstate(repo, createEstate("apartment", "b", 24909, 55555));

	Service* service = createService(repo);
	UI* ui = createUI(service);

	menu(ui);

	destroyUI(ui);

	// testing for memory leaks
	_CrtDumpMemoryLeaks();

	return 0;
}



