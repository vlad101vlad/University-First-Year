#include "domain.h"
#include <cstring>
#include <assert.h>
#include <iostream>


Plants::Plants(string codedName, string species, int ageInMonths, string digitizedScan)
{
	this->codeName = codedName;
	this->species = species;
	this->ageInMonths = ageInMonths;
	this->digitizedScan = digitizedScan;
}

int Plants::getAgeInMonths() const
{
	return this->ageInMonths;
}

string Plants::getCodedName() const
{
	return this->codeName;
}

string Plants::getDigitizedScan() const
{
	return this->digitizedScan;
}

string Plants::getSpecies() const
{
	return this->species;
}

Plants& Plants::operator=(const Plants& somePlant)
{
	if (this == &somePlant)
		return *this;

	this->ageInMonths = somePlant.ageInMonths;
	this->codeName = somePlant.codeName;
	this->digitizedScan = somePlant.digitizedScan;
	this->species = somePlant.species;

	return *this;
}

//Plants::~Plants()
//{
//	this->codeName.~basic_string();
//	this->digitizedScan.~basic_string();
//	this->species.~basic_string();
//}

void testDomainFunctions()
{
	//std::cout << "Testing domain layer...\n";
	PlantsConstructor_newObject_ObjectCreated();
	//std::cout << "Domain layer passed!\n";
}

void PlantsConstructor_newObject_ObjectCreated()
{
	Plants* newPlant = new Plants("I129", "Solanum tuberosum", 3, "adsfnlfkjbasdlfbl");
	
	assert(newPlant->getCodedName() == "I129");
	assert(newPlant->getAgeInMonths() == 3);
	assert(newPlant->getDigitizedScan() == "adsfnlfkjbasdlfbl");
	assert(newPlant->getSpecies() == "Solanum tuberosum");

	delete newPlant;
}