#pragma once

#include "domain.h"

class DynamicVector
{
private:
	int size;
	int capacity;
	Plants* elements;
public:
	//constructor
	DynamicVector(int capacity = 10);
	
	// copy function
	DynamicVector(const DynamicVector& someVector);

	//Create
	void addElement(const Plants& newElement);

	//Read
	Plants* searchElement(string codeName);
	Plants* getElements();	
	int getSize() const;
	int getSizeRepository();	
	
	// Delete
	bool deleteElement(string codeName);
	//destructor
	~DynamicVector();

	//operators
	Plants& operator[](int position);

private:
	// Resizes the current DynamicVector, multiplying its capacity with a give factor
	void resize(double factor = 2);

};

void testRepositoryLayer();
void addElementDynamicVecotor_addValidElement_elementAdded();
void searchElementDynamicVector_validID_elementFound();
void searchElementDynamicVector_invalidID_NULLReturned();
void deleteElementDynamicVector_validID_elementDeleted();
void deleteElementDynamicVector_invalidID_elementNotDeleted();