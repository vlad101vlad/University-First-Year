#pragma once

#include "dynamicVectorTemplate.h"
#include "domain.h"
#include <assert.h>
#include <iostream>

void testDynamicVectorTemplate()
{
	//std::cout << "Testing dynamic vector..." << endl;
	addElement_validElement_ElementAdded();
	//std::cout << "Dynamic vector passed!\n";
}

void addElement_validElement_ElementAdded()
{
	Plants somePlant = Plants();
	DynamicVector<Plants>* plantVector = new DynamicVector<Plants>(10);

	plantVector->addElement(somePlant);
	assert(plantVector->getSize() == 1);

	delete plantVector;
}

void resize_newElementExceedsCapacity_capacityIncreased()
{
	DynamicVector<Plants>* plantVector = new DynamicVector<Plants>(1);
	Plants somePlant = Plants();
	Plants anotherPlant = Plants();

	plantVector->addElement(somePlant);
	plantVector->addElement(anotherPlant);

	assert(plantVector->getSize() == 2);

	delete plantVector;
}

void getCurrent_validIterator_currentElementReturned()
{
	DynamicVector<Plants>* plantVector = new DynamicVector<Plants>(10);
	Plants somePlant = Plants();
	Plants anotherPlant = Plants();

	plantVector->addElement(somePlant);
	plantVector->addElement(anotherPlant);

	DynamicVectorIterator<Plants> plantIterator = DynamicVectorIterator<Plants>(plantVector);
	
}