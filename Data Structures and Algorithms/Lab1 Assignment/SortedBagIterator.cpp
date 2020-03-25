#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
	//TODO - Implementation
	
	this->currentElementIndex = 0;
}

TComp SortedBagIterator::getCurrent() {
	//TODO - Implementation
	if (this->currentElementIndex == this->bag.elementCounter)
		throw std::exception();

	return this->bag.data[this->currentElementIndex];
	
	
}

bool SortedBagIterator::valid() {
	//TODO - Implementation
	if (this->currentElementIndex < this->bag.elementCounter)
		return true;
	return false;
}

void SortedBagIterator::next() {
	//TODO - Implementation
	if (this->currentElementIndex + 1 > this->bag.elementCounter)
		throw std::exception();
	else
		this->currentElementIndex += 1;
}

void SortedBagIterator::first() {
	//TODO - Implementation
	this->currentElementIndex = 0;
}

