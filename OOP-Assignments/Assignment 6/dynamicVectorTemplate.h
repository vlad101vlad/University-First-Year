#pragma once
#include <iostream>

template <typename T>
class DynamicVectorIterator;

template <typename T>
class DynamicVector{	
	
	friend class DynamicVectorIterator<T>;

private:
	T* elements;
	int size;
	int capacity;
public:
	//*constructor
	DynamicVector(int capacity = 10);

	// *copy function
	DynamicVector(const DynamicVector& someVector);

	//Create
	void addElement(const T& newElement);

	//Read	
	T* getElements();
	int getSize() const;

	// Delete	
	void deleteElement(int position);
	~DynamicVector();

	//operators
	T& operator[](int position);

	
	DynamicVectorIterator<T> iterator();

private:
	// Resizes the current DynamicVector, multiplying its capacity with a give factor
	void resize(double factor = 2);
};

template <typename T>
class DynamicVectorIterator
{	
	friend class DynamicVector<T>;

private:
	int currentIndex;
	DynamicVector<T>* dynamicVector;

public:
	
	DynamicVectorIterator();
	DynamicVectorIterator(DynamicVector<T>* dynamicVector);
	void next();
	const T* getCurrent();
	void operator=(DynamicVectorIterator<T> anotheIterator);

};


template <typename T>
DynamicVector<T>::DynamicVector(int capacity)
{
	this->size = 0;
	this->capacity = capacity;
	this->elements = new T[capacity];
}


template <typename T>
void DynamicVector<T>::resize(double factor)
{
	// we change the capacity with the new value
	this->capacity *= factor;

	// we create a new array with the new capacity
	T* newElements = new T[this->capacity];

	// we copy all  the elements from our vector to the new, bigger vector
	for (int i = 0; i < this->size; i++)
		newElements[i] = this->elements[i];

	//we delete the small one
	delete[] this->elements;

	//and link the bigger one
	this->elements = newElements;
}

template <typename T>
DynamicVector<T>::DynamicVector(const DynamicVector<T>& someVector)
{
	this->size = someVector.size;
	this->capacity = someVector.capacity;
	this->elements = new T[this->capacity];
	for (int i = 0; i < this->size; i++)
		this->elements[i] = someVector.elements[i];
}

template <typename T>
DynamicVector<T>::~DynamicVector()
{
	delete[] this->elements;
}

template <typename T>
T* DynamicVector<T>::getElements()
{
	return this->elements;
}

template <typename T>
int DynamicVector<T>::getSize() const
{
	return this->size;
}

template <typename T>
void DynamicVector<T>::addElement(const T& someElement)
{
	if (this->size + 1 > this->capacity)
		this->resize(2);

	this->elements[this->size] = someElement;
	this->size += 1;		
}

template <typename T>
void DynamicVector<T>::deleteElement(int position)
{
	for (int j = position; j < this->size - 1; j++)
		this->elements[j] = this->elements[j + 1];
	this->size -= 1;
}

template <typename T>
T& DynamicVector<T>::operator[](int position)
{
	return this->elements[position];
}

template <typename T>
DynamicVectorIterator<T> DynamicVector<T>::iterator()
{
	DynamicVectorIterator<T> newIterator = DynamicVectorIterator<T>(this);
	return newIterator;
}

// Iterator
template <typename T>
DynamicVectorIterator<T>::DynamicVectorIterator()
{
	this->currentIndex = -1;
	this->dynamicVector == NULL;
}


template <typename T>
DynamicVectorIterator<T>::DynamicVectorIterator(DynamicVector<T>* dynamicVector) : dynamicVector(dynamicVector)
{
	this->currentIndex = 0;
}

template <typename T>
void DynamicVectorIterator<T>::operator=(DynamicVectorIterator<T> anotheIterator)
{
	this->dynamicVector = anotheIterator.dynamicVector;
	this->currentIndex = anotheIterator.currentIndex;
}

template <typename T>
const T* DynamicVectorIterator<T>::getCurrent()
{
	//Returns:
	//-a pointer to the current elements if the vector is not empty
	//-NULL if the vector is empty
	if (this->dynamicVector->getSize() > 0)
	{
		//std::cout << this->dynamicVector->getSize();
		//std::cout << this->dynamicVector->elements[this->currentIndex]->getCodedName();
		return &this->dynamicVector->elements[this->currentIndex];
	}
	return NULL;
}

template <typename T>
void DynamicVectorIterator<T>::next()
{
	if (this->currentIndex + 1 == this->dynamicVector->getSize())
		this->currentIndex = 0;
	else
	{
		this->currentIndex += 1;
	}
}


void testDynamicVectorTemplate();
void addElement_validElement_ElementAdded();
void resize_newElementExceedsCapacity_capacityIncreased();
void getCurrent_validIterator_currentElementReturned();