#include <vld.h>
#include "repository.h"
#include <assert.h>
#include <iostream>


DynamicVector::DynamicVector(int capacity)
{
	this->size = 0;
	this->capacity = capacity;
	this->elements = new Plants[capacity];
}

DynamicVector::~DynamicVector()
{
	/*for (int i = 0; i < this->size; i++)
		delete this->elements[i];*/

	delete[] this->elements;
}

int DynamicVector::getSize() const
{
	return this->size;
}

void DynamicVector::resize(double factor)
{
	// we change the capacity with the new value
	this->capacity *= factor;

	// we create a new array with the new capacity
	Plants* newElements = new Plants[this->capacity];

	// we copy all  the elements from our vector to the new, bigger vector
	for (int i = 0; i < this->size; i++)
		newElements[i] = this->elements[i];

	//we delete the small one
	delete[] this->elements;

	//and link the bigger one
	this->elements = newElements;
}

void DynamicVector::addElement(const Plants& newElement)
{
	if (this->size + 1 > capacity)
	{
		this->resize(2);		
	}
		

	this->elements[this->size] = newElement;
	this->size += 1;
}

Plants* DynamicVector::searchElement(string codeName)
{
	// This function searches for a plant in the repository. Returns
	// pointer -> to the found object
	// NULL -> if the object is not found

	for (int i = 0; i < this->size; i++)
		if (this->elements[i].getCodedName() == codeName)
		{
			//std::cout << this->elements[i].getCodedName();
			return &(this->elements[i]);
		}
			
	return NULL;
}	

bool DynamicVector::deleteElement(string codeName)
{
	// This function searches for a plant in the repository. Returns
	// true -> if the element was deleted
	// false -> if the object is not found
	int currentSize = 0;

	Plants* newElements = new Plants[this->capacity];

	
	for(int i = 0; i < this->size; i++)
		if (this->elements[i].getCodedName() != codeName)
		{
			newElements[currentSize] = this->elements[i];
			currentSize += 1;
		}

	if (currentSize == this->getSize())
	{
		delete[] newElements;
		return false;
	}
		

	this->size = currentSize;
	delete[] this->elements;

	this->elements = newElements;
	return true;

}

Plants* DynamicVector::getElements()
{
	return this->elements;
}

int DynamicVector::getSizeRepository()
{
	return this->size;
}

Plants& DynamicVector::operator[](int position)
{
	return this->elements[position];
}

void testRepositoryLayer()
{
	addElementDynamicVecotor_addValidElement_elementAdded();
	searchElementDynamicVector_validID_elementFound();
	searchElementDynamicVector_invalidID_NULLReturned();
	deleteElementDynamicVector_validID_elementDeleted();
	deleteElementDynamicVector_invalidID_elementNotDeleted();
}



void addElementDynamicVecotor_addValidElement_elementAdded()
{
	Plants somePlant = Plants();	
	DynamicVector* newVector = new DynamicVector(10);
	
	newVector->addElement(somePlant);	
	assert(newVector->getSize() == 1);	
	
	delete newVector;
	
}

void searchElementDynamicVector_validID_elementFound()
{
	Plants newPlant = Plants("I129", "Solanum tuberosum", 3, "adsfnlfkjbasdlfbl");
	DynamicVector* newVector = new DynamicVector(10);
	newVector->addElement(newPlant);

	assert(newVector->searchElement("I129")->getDigitizedScan() == "adsfnlfkjbasdlfbl");

	
	delete newVector;
}

void searchElementDynamicVector_invalidID_NULLReturned()
{
	Plants newPlant = Plants("I129", "Solanum tuberosum", 3, "adsfnlfkjbasdlfbl");
	DynamicVector* newVector = new DynamicVector(10);
	newVector->addElement(newPlant);

	assert(newVector->searchElement("dasd") ==  NULL);

	delete newVector;
}

void deleteElementDynamicVector_validID_elementDeleted()
{
	Plants newPlant = Plants("I129", "Solanum tuberosum", 3, "adsfnlfkjbasdlfbl");
	DynamicVector* newVector = new DynamicVector(10);
	newVector->addElement(newPlant);

	auto decision = newVector->deleteElement("I129");

	assert(decision == true);
	assert(newVector->getSize() == 0);

	
	delete newVector;
}

void deleteElementDynamicVector_invalidID_elementNotDeleted()
{
	Plants newPlant = Plants("I129", "Solanum tuberosum", 3, "adsfnlfkjbasdlfbl");
	DynamicVector* newVector = new DynamicVector(10);
	newVector->addElement(newPlant);

	auto decision = newVector->deleteElement("garbage");

	assert(decision == false);
	assert(newVector->getSize() == 1);
	
	delete newVector;
}