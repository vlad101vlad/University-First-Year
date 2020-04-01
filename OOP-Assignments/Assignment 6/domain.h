#pragma once

#include <string>

using namespace std;

class Plants
{
private:
	string codeName;	
	string species;
	int ageInMonths;
	string digitizedScan;
public:
	// default constructor
	Plants(string codedName = "", string species = "", int ageInMonths = 0, string digitizedScan = "");

	// deconstructor
	//~Plants();

	// getters
	string getCodedName() const;
	string getSpecies() const;
	int getAgeInMonths() const;
	string getDigitizedScan() const;

	Plants& operator=(const Plants& somePlant);

};

void testDomainFunctions();
void PlantsConstructor_newObject_ObjectCreated();