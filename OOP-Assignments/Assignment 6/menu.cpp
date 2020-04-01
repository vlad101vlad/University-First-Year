#include "menu.h"
#include <string>
#include <string.h>
#include <iostream>

using namespace std;

Menu::Menu(Service* service)
{
	this->currentMode = -1;
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

		if (inputInformation == "exit")
		{
			//If we face exit , we stop the application				
			break;			
		}
		
		// We create a string to extract the arguments from the input
		string* listOfArguments = new string[20];
		int numberOfArguments = Menu::getArgumentsFromInput(inputInformation, listOfArguments);

		// We specify which is the keyword
		string keyWord = listOfArguments[0];	

		if (keyWord == "mode")
		{	
			// Here we state in which mode we are in
			string modeArgument = listOfArguments[1];
			if (modeArgument == "A" or modeArgument == "B")
				this->currentMode = (int)(modeArgument[0] - 'A');

			delete[] listOfArguments;			
		}
		else
		{
			// If the keyword is not mode, we check for other keywords, each of being specific for their mode
			if (this->currentMode == 0)
			{
				// Mode administrator
				
				Dictionary commands;
				commands.emplace("add", &Menu::addPlantUI);
				commands.emplace("update", &Menu::updatePlantUI);
				commands.emplace("delete", &Menu::deletePlantUI);
				commands.emplace("list", &Menu::listPlantsUI);

				try
				{
					if (commands.find(keyWord) == commands.end())
					{
						string errorMessage("Invalid keyword");
						//throw errorMessage;
					}
					else
					{
						MemberFunctionPointer functionPointer = commands[keyWord];
						(this->*functionPointer)(listOfArguments);
						delete[] listOfArguments;
					}

				}
				catch (string errorMessage)
				{
					cout << "UI Error: Invalid keyword " << errorMessage << endl;
				}
			}
			else
			{
				if (this->currentMode == 1)
				{
					//Mode user
					//cout << "Mode user branch\n";

					Dictionary commands;
					commands.emplace("next", &Menu::printCurrentPlant);
					commands.emplace("save", &Menu::savePlantForUprooting);
					commands.emplace("list", &Menu::listSpeciesWithAge);
					commands.emplace("mylist", &Menu::listUprootedPlants);

					try
					{
						if (commands.find(keyWord) == commands.end())
						{
							string errorMessage("Invalid keyword");
							//throw errorMessage;
						}
						else
						{
							MemberFunctionPointer functionPointer = commands[keyWord];
							(this->*functionPointer)(listOfArguments);
							delete[] listOfArguments;
						}

					}
					catch (string errorMessage)
					{
						cout << "UI Error: Invalid keyword " << errorMessage << endl;
					}
				}
				else
				{
					// Here we arrive when mode is different from A or B
					delete[] listOfArguments;
					break;
				}				
			}			
		}		
	}	
}

// Mode B

void Menu::listUprootedPlants(string* listOfArguments)
{
	//cout << "mylist branch\n";
	Plants* listOfPlants = this->service->getPlantsToBeUprooted();
	int sizeListOfPlants = this->service->getSizePlantsToBeUprooted();

	for (int i = 0; i < sizeListOfPlants; i++)
	{
		Plants currentPlant = listOfPlants[i];
		cout << currentPlant.getCodedName() << " " << currentPlant.getSpecies() << " " << currentPlant.getAgeInMonths() 
			<< " " << currentPlant.getDigitizedScan() << endl;
	
	}
}

void Menu::listSpeciesWithAge(string* listOfArguments)
{
	//cout << "List species with age branch\n";
	string species = " " + listOfArguments[1];
	int age = stoi(listOfArguments[2]);

	Plants* listOfPlants = this->service->getListOfPlants();
	const int plantListSize = this->service->getSizeList();

	for (int i = 0; i < plantListSize; i++)
	{
		Plants currentPlant = listOfPlants[i];
		if(currentPlant.getSpecies() == species && currentPlant.getAgeInMonths() < age)
			cout << currentPlant.getCodedName() << " " << currentPlant.getSpecies() << " "
				<< currentPlant.getAgeInMonths() << " " << currentPlant.getDigitizedScan() << endl;
	}

}

void Menu::savePlantForUprooting(string* listOfArguments)
{
	//cout << "Save branch\n";
	string codedName = listOfArguments[1];
	this->service->savePlantForUprooting(codedName);	
}

void Menu::printCurrentPlant(string* listOfArguments)
{
	//cout << "Next branch\n";
	const Plants* nextPlant = this->service->getNextElementService();

	if (nextPlant != NULL)
		cout << nextPlant->getCodedName() << " " << nextPlant->getSpecies() << " "
		<< nextPlant->getAgeInMonths() << " " << nextPlant->getDigitizedScan() << endl;
}


// Mode A

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