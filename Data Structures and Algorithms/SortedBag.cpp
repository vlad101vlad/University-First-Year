#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <iostream>

using namespace std;

SortedBag::SortedBag(Relation r) {
	//TODO - Implementation
	this->elementCounter = 0;
	this->bagSize = 5;
	this->data = new TComp[this->bagSize];
	this->relation = r;
}

void SortedBag::add(TComp e) {
	//TODO - Implementation
	if (this->elementCounter + 1 > this->bagSize) {
		// We make a resize
		this->bagSize *= 2;

		//We create a bigger array
		TComp* newData = new TComp[this->bagSize];

		//We copy all the new elements into the newly created array
		for (int i = 0; i < this->elementCounter; i++)
			newData[i] = this->data[i];

		// We delete the old array
		delete[] this->data;

		//We link the new array to the current object
		this->data = newData;
	}

	if (this->elementCounter == 0)
	{
		this->data[0] = e;
		this->elementCounter += 1;
	}
	else
	{
		bool found = false;
		for (int i = this->elementCounter - 1; i >= 0; i--)
		{
			if (this->relation(this->data[i], e))
			{
				found = true;
				this->elementCounter += 1;
				for (int j = this->elementCounter - 1; j > i + 1; j--)
					this->data[j] = this->data[j - 1];
				this->data[i + 1] = e;
				break;
			}			
		}
		
		if (!found)
		{
			for (int i = this->elementCounter; i > 0; i--)
				this->data[i] = this->data[i - 1];
			this->data[0] = e;
			this->elementCounter += 1;
		}
		
		
	}
	
	/*for (int i = 0; i < this->elementCounter; i++)
		cout << this->data[i] << " ";
	cout << endl;*/
}


bool SortedBag::remove(TComp e) {
	//TODO - Implementation
	for (int i = 0; i < this->elementCounter; i++)
	{
		if (this->data[i] == e)
		{
			for (int j = i; j < elementCounter - 1; j++)
				this->data[j] = this->data[j + 1];
			this->elementCounter -= 1;
			return true;
		}
			
	}

	return false;
}


bool SortedBag::search(TComp elem) const {
	for (int i = 0; i < this->elementCounter; i++)
		if (this->data[i] == elem)
			return true;

	return false;
}


int SortedBag::nrOccurrences(TComp elem) const {
	//TODO - Implementation
	int counter = 0;
	for (int i = 0; i < this->elementCounter; i++)
		if (this->data[i] == elem)
			counter += 1;

	return counter;
}



int SortedBag::size() const {
	//TODO - Implementation
	return this->elementCounter;
}


bool SortedBag::isEmpty() const {
	//TODO - Implementation	
	if (this->elementCounter == 0)
		return true;
	return false;
}


SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}


SortedBag::~SortedBag() {
	//TODO - Implementation
	delete[] this->data;
}

int SortedBag::removeAll()
{
	int deletedElements = 0;
	for (int i = 0; i < this->elementCounter - 1; i++)
	{	
		int currentElement = this->data[i]; // We save the current element
		int hasMoreOccurences = 0;
		int startIndex = i;
		int endIndex = i;
		
		if (this->data[i + 1] == currentElement) // We find more occurences
		{
			hasMoreOccurences = 1;
			for (int j = i + 1; this->data[j] == currentElement; j++)
				endIndex = j;
		}

		if (hasMoreOccurences)
		{
			int absoluteValue = endIndex+1 - startIndex; // We compute the absolute value between indicies
			this->elementCounter -= absoluteValue; // We substract the number of deleted elements
			
			/*cout << startIndex << " " << endIndex << endl;
			cout << absoluteValue << endl;*/

			for (int k = startIndex; k < this->elementCounter; k++)
				this->data[k] = this->data[k + absoluteValue]; // We modify the bag
		}
			
	}

	/*for (int i = 0; i < this->elementCounter; i++)
		cout << this->data[i] << " ";*/
	//cout << deletedElements;
	return deletedElements;
}
