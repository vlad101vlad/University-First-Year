#pragma once

#include "domain.h"
#include "dynamicVectorTemplate.h"



class Repository
{
public:	
	DynamicVector<Plants>* dynamicVector;
	DynamicVectorIterator<Plants> vectorIterator;

	Repository(DynamicVector<Plants>* someVector);


	// Constructor
	

	void addElement(const Plants& newElement);
	Plants* searchElement(string codeName);
	bool deleteElement(string codeName);

	Plants* getElementsRepository();	
	int getSizeRepository();
	
	// Modifies the iterator
	const Plants* getCurrentElement();
	const Plants* getNextElement();

};

void testRepositoryLayer();
void searchElement_validCodeName_elementFound();
void searchElement_invalidCodeName_elementNotFound();
void deleteElement_validCodeName_elementDeleted();
void deleteElement_invalidCodeName_elementNotDeleted();
void getCurrentElement_nonEmptyRepository_elementReturned();
void getCurrentElement_EmptyRepository_nullReturned();
void getNextElement_nonEmptyRepository_nextElementReturned();
void getNextElement_lastElementInRepository_firstElementReturned();




