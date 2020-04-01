//#include <vld.h>
#include "repository.h"
#include  <assert.h>

Repository::Repository(DynamicVector<Plants>* someVector)
{
	this->dynamicVector = someVector;
	this->vectorIterator = someVector->iterator();
}

void Repository::addElement(const Plants& newElement)
{
	this->dynamicVector->addElement(newElement);	
}

Plants* Repository::getElementsRepository()
{
	return this->dynamicVector->getElements();
}


int Repository::getSizeRepository()
{
	return this->dynamicVector->getSize();
}




Plants* Repository::searchElement(string codeName)
{
	//This function searches through the repository for the element
	// Returns:
	// Pointer -> to the element || If the element exists
	// NULL || If the element doesn't exist

	Plants* currentPlants = this->dynamicVector->getElements();

	for (int i = 0; i < this->getSizeRepository(); i++)
		if (codeName == currentPlants[i].getCodedName())
			return &currentPlants[i];

	return NULL;
	//return this->dynamicVector->searchElement(codeName);
}

bool Repository::deleteElement(string codeName)
{
	Plants* elementToBeDeleted = this->searchElement(codeName);

	if (elementToBeDeleted == NULL)
		return  false;	

	Plants* listOfPlants = this->getElementsRepository();

	for(int index = 0; index < this->getSizeRepository(); index++)
		if (listOfPlants[index].getCodedName() == codeName)
		{
			this->dynamicVector->deleteElement(index);
			return true;
		}
}


const Plants* Repository::getCurrentElement()
{
	return this->vectorIterator.getCurrent();
}

const Plants* Repository::getNextElement()
{
	this->vectorIterator.next();
	return this->vectorIterator.getCurrent();
}


void testRepositoryLayer()
{
	//std::cout << "Testing repository layer..." << endl;

	searchElement_validCodeName_elementFound();
	searchElement_invalidCodeName_elementNotFound();
	deleteElement_validCodeName_elementDeleted();
	deleteElement_validCodeName_elementDeleted();
	getCurrentElement_nonEmptyRepository_elementReturned();
	getCurrentElement_EmptyRepository_nullReturned();
	getNextElement_nonEmptyRepository_nextElementReturned();
	getNextElement_lastElementInRepository_firstElementReturned();

	//std::cout << "Repository layer passed!\n\n";
}

void searchElement_validCodeName_elementFound()
{
	DynamicVector<Plants>* newVector = new DynamicVector<Plants>(10);
	Repository* newRepository = new Repository(newVector);

	Plants newPlant = Plants("I129", "Solanum tuberosum", 3, "adsfnlfkjbasdlfbl");
	newVector->addElement(newPlant);
	Plants* listOfPlants = newVector->getElements();

	Plants* isElementFound = newRepository->searchElement("I129");
	assert(isElementFound == &listOfPlants[0]);

	delete newVector;
	delete newRepository;
}

void searchElement_invalidCodeName_elementNotFound()
{
	DynamicVector<Plants>* newVector = new DynamicVector<Plants>(10);
	Repository* newRepository = new Repository(newVector);

	Plants newPlant = Plants("I129", "Solanum tuberosum", 3, "adsfnlfkjbasdlfbl");
	newVector->addElement(newPlant);

	Plants* isElementFound = newRepository->searchElement("vlad");
	assert(isElementFound == NULL);

	delete newVector;
	delete newRepository;
}


void deleteElement_validCodeName_elementDeleted()
{
	DynamicVector<Plants>* newVector = new DynamicVector<Plants>(10);
	Repository* newRepository = new Repository(newVector);

	Plants newPlant = Plants("I129", "Solanum tuberosum", 3, "adsfnlfkjbasdlfbl");
	Plants anotherPlant = Plants("abc", "def", 123, "ghi");
	newVector->addElement(newPlant);
	newVector->addElement(anotherPlant);

	bool decision = newRepository->deleteElement("I129");
	Plants* isElementFound = newRepository->searchElement("I129");

	assert(isElementFound == NULL);
	assert(decision == true);

	delete newVector;
	delete newRepository;
}

void deleteElement_invalidCodeName_elementNotDeleted()
{
	DynamicVector<Plants>* newVector = new DynamicVector<Plants>(10);
	Repository* newRepository = new Repository(newVector);

	Plants newPlant = Plants("I129", "Solanum tuberosum", 3, "adsfnlfkjbasdlfbl");
	Plants anotherPlant = Plants("abc", "def", 123, "ghi");
	newVector->addElement(newPlant);
	newVector->addElement(anotherPlant);

	bool decision = newRepository->deleteElement("vlad");
	Plants* isElementFound = newRepository->searchElement("I129");

	assert(isElementFound != NULL);
	assert(decision == false);

	delete newVector;
	delete newRepository;
}

void getCurrentElement_nonEmptyRepository_elementReturned()
{
	DynamicVector<Plants>* newVector = new DynamicVector<Plants>(10);
	Repository* newRepository = new Repository(newVector);

	Plants newPlant = Plants("I129", "Solanum tuberosum", 3, "adsfnlfkjbasdlfbl");
	Plants anotherPlant = Plants("abc", "def", 123, "ghi");
	newVector->addElement(newPlant);
	newVector->addElement(anotherPlant);

	const Plants* currentElement = newRepository->getCurrentElement();
	assert(currentElement->getCodedName() == "I129");



	delete newVector;
	delete newRepository;
}

void getCurrentElement_EmptyRepository_nullReturned()
{
	DynamicVector<Plants>* newVector = new DynamicVector<Plants>(10);
	Repository* newRepository = new Repository(newVector);	

	const Plants* currentElement = newRepository->getCurrentElement();

	assert(currentElement == NULL);

	delete newVector;
	delete newRepository;
}


void getNextElement_nonEmptyRepository_nextElementReturned()
{
	DynamicVector<Plants>* newVector = new DynamicVector<Plants>(10);
	Repository* newRepository = new Repository(newVector);

	Plants newPlant = Plants("I129", "Solanum tuberosum", 3, "adsfnlfkjbasdlfbl");
	Plants anotherPlant = Plants("abc", "def", 123, "ghi");
	newVector->addElement(newPlant);
	newVector->addElement(anotherPlant);

	const Plants* currentElement = newRepository->getNextElement();
	assert(currentElement->getCodedName() == "abc");

	delete newVector;
	delete newRepository;
}

void getNextElement_lastElementInRepository_firstElementReturned()
{
	DynamicVector<Plants>* newVector = new DynamicVector<Plants>(10);
	Repository* newRepository = new Repository(newVector);

	Plants newPlant = Plants("I129", "Solanum tuberosum", 3, "adsfnlfkjbasdlfbl");
	Plants anotherPlant = Plants("abc", "def", 123, "ghi");
	newVector->addElement(newPlant);
	newVector->addElement(anotherPlant);

	const Plants* currentElement = newRepository->getNextElement();
	currentElement = newRepository->getNextElement();

	assert(currentElement->getCodedName() == "I129");

	delete newVector;
	delete newRepository;
}





