#include <vld.h>
#include "domain.h"
#include "repository.h"
#include "service.h"
#include "menu.h"
#include <iostream>
#include <string>

using namespace std;

void testAllLayers()
{
	testDomainFunctions();
	testRepositoryLayer();
}


int main()
{
	
	testAllLayers();
	
	
	DynamicVector* plantRepository = new DynamicVector(10);	
	Service* plantService = new Service(plantRepository);
	Menu* console = new Menu(plantService);
	
	string inputInformation;
	getline(cin, inputInformation);

	if(inputInformation == "mode A")
		console->runMenu();
	

	delete plantRepository;
	delete plantService;
	delete console;

	
	return 0;
}