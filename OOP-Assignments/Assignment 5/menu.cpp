#include "menu.h"
#include <string>
#include <string.h>
#include <iostream>

using namespace std;

Menu::Menu(Service* service)
{
	this->service = service;
}

int Menu::getArgumentsFromInput(string inputString, string* listOfArguments)
{
	int numberOfArguments = 0;
	int currentPosition = 0, previousPosition = 0;

	//Keyword search
	currentPosition = inputString.find_first_of(" ");
	listOfArguments[numberOfArguments] = inputString.substr(previousPosition, currentPosition - previousPosition);
	numberOfArguments += 1;
	previousPosition = currentPosition + 1;
	///@@@@@///

	const string delimiters = ",";
	currentPosition = inputString.find_first_of(delimiters);

	// Here we split the arguments by the comma
	while (currentPosition != string::npos)
	{
		listOfArguments[numberOfArguments] = inputString.substr(previousPosition, currentPosition - previousPosition);
		numberOfArguments += 1;

		previousPosition = currentPosition + 1;
		currentPosition = inputString.find_first_of(delimiters, previousPosition);
	}
	listOfArguments[numberOfArguments] = inputString.substr(previousPosition, size(inputString));
	
	
	return numberOfArguments;
}

void Menu::runMenu()
{
	while (true)
	{
		string inputInformation;
		getline(cin, inputInformation);

		string* listOfArguments = new string[20];
		int numberOfArguments = Menu::getArgumentsFromInput(inputInformation, listOfArguments);

		string keyWord = listOfArguments[0];
		
		if (keyWord == "exit")
			break;
		
		Dictionary commands;
		commands.emplace("add", &Menu::addPlantUI);
		commands.emplace("update", &Menu::updatePlantUI);
		commands.emplace("delete", &Menu::deletePlantUI);
		commands.emplace("list", &Menu::listPlantsUI);

		
		MemberFunctionPointer functionPointer = commands[keyWord];
		(this->*functionPointer)(listOfArguments);
		 

	}
}

void Menu::addPlantUI(string* listOfArguments)
{
	//cout << "Add branch\n";
	string codeName = listOfArguments[1];
	string species = listOfArguments[2];
	int ageInMonths = stoi(listOfArguments[3]);
	string digitizedScan = listOfArguments[4];

	this->service->addElementService(codeName, species, ageInMonths, digitizedScan);
}

void Menu::updatePlantUI(string* listOfArguments)
{
	//cout << "Update branch\n";
	string codeName = listOfArguments[1];
	string newSpecies = listOfArguments[2];
	int newAgeInMonths = stoi(listOfArguments[3]);
	string newDigitizedScan = listOfArguments[4];
	
	this->service->updateElementService(codeName, newSpecies, newAgeInMonths, newDigitizedScan);
}

void Menu::deletePlantUI(string* listOfArguments)
{
	//cout << "Delete branch\n";
	string codeName = listOfArguments[1];

	this->service->deleteElementService(codeName);
}

void Menu::listPlantsUI(string* listOfArguments)
{
	//cout << "List branch\n";
	const int plantListSize = this->service->getSizeList();
	Plants* listOfPlants = this->service->getListOfPlants();

	for (int i = 0; i < plantListSize; i++)
	{
		Plants currentPlant = listOfPlants[i];
		cout << currentPlant.getCodedName() << " " << currentPlant.getSpecies() << " "
			<< currentPlant.getAgeInMonths() << " " << currentPlant.getDigitizedScan() << endl;
	}
}