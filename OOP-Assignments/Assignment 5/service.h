#pragma once

#include "repository.h"

class Service
{
public:
	DynamicVector* repository;

	Service(DynamicVector* repository);

	Plants* getListOfPlants();
	int getSizeList();

	void addElementService(string codeName, string species, int ageInMonths, string digitizedScan);
	bool updateElementService(string codeName, string species, int ageInMonths, string digitizedScan);
	bool deleteElementService(string codeName);
};