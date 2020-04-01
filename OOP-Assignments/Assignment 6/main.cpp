#pragma once

#include <vld.h>

#include "domain.h"
//#include "dynamicVector.h"
#include "dynamicVectorTemplate.h"
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
	testDynamicVectorTemplate();
}


int main(){
	
	testAllLayers();	
	
	DynamicVector<Plants>* plantVector = new DynamicVector<Plants>(10);	
	DynamicVector<Plants>* userPlantVector = new DynamicVector<Plants>(10);

	Repository* userRepository = new Repository(userPlantVector);
	Repository* plantRepository = new Repository(plantVector);
	Service* plantService = new Service(plantRepository, userRepository);
	Menu* console = new Menu(plantService);

	console->runMenu();
	
	delete userPlantVector;
	delete plantVector;

	delete plantRepository;
	delete userRepository;

	delete plantService;
	delete console;

	
	return 0;
}