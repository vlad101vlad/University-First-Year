#include "menu.h"
#include <string.h>
#include <stdio.h>

#define MAX_INPUT_SIZE 256

Menu* createMenu()
{
	Menu* newMenu = (Menu*)malloc(sizeof(Menu));

	return newMenu;
}

void destroyMenu(Menu* console)
{
	destroyService(console->service);
	free(console);
}

char** convertInputIntoWords(char* inputInformation)
{
	const char* delimiter = " ,";
	char* token;

	char** listOfArguments;
	listOfArguments = malloc(sizeof(char*) * 10);
	for (int i = 0; i < 10; i++)
		listOfArguments[i] = malloc(sizeof(char) * MAX_INPUT_SIZE);
	
	
	int argumentCounter = 0;

	token = strtok(inputInformation, delimiter);
	while (token != NULL)
	{		
		strcpy(listOfArguments[argumentCounter], token);
		argumentCounter += 1;
		token = strtok(NULL, delimiter);
	}
	
	while (argumentCounter < 10)
	{
		listOfArguments[argumentCounter] = NULL;
		argumentCounter += 1;
	}
	

	return listOfArguments;
}

void freeInputInformation(char **listOfArguments)
{
	for (int i = 0; i < 10; i++)
		free(listOfArguments[i]);
	free(listOfArguments);
	
}


void listBots(Menu* console)
{
	int lenght = getSizeOfListBots(console->service);
	Bot** arrayOfBots = getBots(console->service);

	for (int i = 0; i < lenght; i++)
	{
		Bot* currentBot = arrayOfBots[i];
		printf("%d %s %s %d\n", currentBot->serialNumber, currentBot->state,
			currentBot->specialization, currentBot->energyCostToRepair);
	}

}

void listBotsBySpecialization(Menu* console,char **listOfArguments)
{
	int lenght = getSizeOfListBots(console->service);

	char* specialization = (char*)malloc(sizeof(char) * 50);
	strcpy(specialization, listOfArguments[1]);

	Bot** arrayOfBots = getBots(console->service);

	for (int i = 0; i < lenght; i++)
	{
		Bot* currentBot = arrayOfBots[i];
		if (strcmp(specialization, currentBot->specialization) == 0)
		{
			printf("%d %s %s %d\n", currentBot->serialNumber, currentBot->state,
				currentBot->specialization, currentBot->energyCostToRepair);
		}
		
	}

	free(specialization);
}

void addBotsUI(Menu* console,char **listOfArguments)
{
	int serialNumber = atoi(listOfArguments[1]);
	
	char* state = (char*)malloc(sizeof(char) * 20);
	strcpy(state, listOfArguments[2]);

	char* specialization= (char*)malloc(sizeof(char) * 20);
	strcpy(specialization, listOfArguments[3]);

	int energyCostToRepair = atoi(listOfArguments[4]);

	int succesfullyAdded = addBotService(console->service, serialNumber, state, specialization, energyCostToRepair);
	if (!succesfullyAdded)
		printf("No!\n");

	free(state);
	free(specialization);
}

void updateBotUI(Menu* console, char** listOfArguments)
{
	int serialNumber = atoi(listOfArguments[1]);
	
	char* state = (char*)malloc(sizeof(char) * 20);
	strcpy(state, listOfArguments[2]);

	char* specialization = (char*)malloc(sizeof(char) * 20);
	strcpy(specialization, listOfArguments[3]);

	int energyCostToRepair = atoi(listOfArguments[4]);

	int succesfullyUpdated = updateBotService(console->service, serialNumber, state, specialization, energyCostToRepair);
	if (!succesfullyUpdated)
		printf("No!\n");

	free(state);
	free(specialization);
}

void deleteBotUI(Menu* console, char** listOfArguments)
{
	int serialNumber = atoi(listOfArguments[1]);
	int succesfullyDeleted = deleteBotService(console->service, serialNumber);
	if (!succesfullyDeleted)
		printf("No!\n");
}

void sortByEnergyCostUI(Menu* console, char** listOfArguments)
{
	int maximumEnergyCostToRepair = atoi(listOfArguments[1]);

	Bot** arrayOfBots = getBotsWithMaximumCostOfRepair(console->service, maximumEnergyCostToRepair);
	int lenght = getLenghtBotsWithMaximumCostOfRepair(console->service, maximumEnergyCostToRepair);

	for (int i = 0; i < lenght; i++)
	{
		Bot* currentBot = arrayOfBots[i];		
		printf("%d %s %s %d\n", currentBot->serialNumber, currentBot->state,
			currentBot->specialization, currentBot->energyCostToRepair);
	
	}
	
}

void runMenu(Menu* console)
{
	while (1 == 1)
	{
		char inputInformation[MAX_INPUT_SIZE];
		gets(inputInformation);

		char** listOfArguments = convertInputIntoWords(inputInformation);

		
		if (strcmp(listOfArguments[0], "exit") == 0)
		{
			//printf("Exit branch.\n");
			freeInputInformation(listOfArguments);
			exit(0);

		}	
		
		if (strcmp(listOfArguments[0], "add") == 0)
		{
			addBotsUI(console, listOfArguments);
			//printf("Add branch.\n\n");
		}

		if (strcmp(listOfArguments[0], "update") == 0)
		{
			updateBotUI(console, listOfArguments);
			//printf("Update branch.\n\n");
		}

		if (strcmp(listOfArguments[0], "delete") == 0)
		{
			deleteBotUI(console, listOfArguments);
			//printf("Delete branch.\n\n");
		}

		if (strcmp(listOfArguments[0], "undo") == 0)
		{
			undoService(console->service);
			//printf("Undo branch\n");
		}

		if (strcmp(listOfArguments[0], "redo") == 0)
		{
			redoService(console->service);
		}

		if (strcmp(listOfArguments[0], "list") == 0 && listOfArguments[1] == NULL)
		{
			listBots(console);

			//freeInputInformation(listOfArguments);
			//printf("List branch.\n\n");
		}
		
		if (strcmp(listOfArguments[0], "list") == 0 && listOfArguments[1] != NULL && atoi(listOfArguments[1]) == 0)
		{
			listBotsBySpecialization(console, listOfArguments);
			//printf("List specialisation branch.\n");
		}

		if ( strcmp(listOfArguments[0], "list") == 0 && listOfArguments[1] != NULL && atoi(listOfArguments[1]) != 0)
		{
			sortByEnergyCostUI(console, listOfArguments);
			//printf("Energy cost to repair branch\n");
		}
	}

}