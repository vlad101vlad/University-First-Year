#include "service.h"

Service::Service(DynamicVector* repository)
{
	this->repository = repository;
}

void Service::addElementService(string codeName, string species, int ageInMonths, string digitizedScan)
{
	Plants newPlant(codeName, species, ageInMonths, digitizedScan);
	this->repository->addElement(newPlant);	
}

bool Service::updateElementService(string codeName, string species, int ageInMonths, string digitizedScan)
{
	// This function update the one element of the list. It returns:
	// True- if the element is succesfully updated
	// False- if an element with id codeName is not found	
	
	Plants thePlantToBeUpdated(codeName, species, ageInMonths, digitizedScan);
	Plants* foundElementToBeUpdated = this->repository->searchElement(codeName);

	if (foundElementToBeUpdated == NULL)
		return false;

	*foundElementToBeUpdated = thePlantToBeUpdated;
	return true;
}

bool Service::deleteElementService(string codeName)
{
	// This function deletes an element from the list
	// true -> if the element was deleted
	// false -> if the element was not deleted

	bool decision = this->repository->deleteElement(codeName);
	return decision;
}



Plants* Service::getListOfPlants()
{
	return this->repository->getElements();
}

int Service::getSizeList()
{
	return this->repository->getSizeRepository();
}