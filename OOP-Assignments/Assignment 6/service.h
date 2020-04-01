#pragma once

#include "repository.h"

class Service
{
public:
	Repository* repository;
	Repository* userData;

	Service(Repository* repository, Repository* userData);

	Plants* getListOfPlants();
	int getSizeList();

	void addElementService(string codeName, string species, int ageInMonths, string digitizedScan);
	bool updateElementService(string codeName, string species, int ageInMonths, string digitizedScan);
	bool deleteElementService(string codeName);

	// Mode B
	const Plants* getNextElementService();

	void savePlantForUprooting(string codeName);
	Plants* getPlantsToBeUprooted();
	int getSizePlantsToBeUprooted();
};

void testServiceLayer();