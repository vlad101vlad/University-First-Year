#pragma once

#include "service.h"
#include <string>
#include <unordered_map>

using namespace std;


class Menu
{
public:
	Service* service;

	
	typedef void(Menu::* MemberFunctionPointer)(string* listOfArguments);
	typedef unordered_map<string, MemberFunctionPointer> Dictionary;

	Menu(Service* service);

	void runMenu();

	static int getArgumentsFromInput(string inputString, string* listOfArguments);

	void addPlantUI(string* listOfArguments);
	void updatePlantUI(string* listOfArguments);
	void deletePlantUI(string* listOfArguments);
	void listPlantsUI(string* listOfArguments);
};
