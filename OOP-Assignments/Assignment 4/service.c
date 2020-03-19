#include "service.h"
#include <stdlib.h>
#include <string.h>
////// UNDO//////////////////////////////////////////
UndoMachine* createUndoMachine()
{
	UndoMachine* newUndoMachine;
	newUndoMachine = malloc(sizeof(UndoMachine));

	newUndoMachine->currentOperation = 0;
	newUndoMachine->redoOperation = 0;
	newUndoMachine->undoSize = 0;
}


void saveCurrentState(UndoMachine* undoMachine, Repository* currentRepository)
{
	Repository* copyRepository = copyOfCurrentRepository(currentRepository);

	if (undoMachine->undoSize == 0)
	{
		undoMachine->listOfPreviousStates = malloc(sizeof(UndoMachine*));
		undoMachine->listOfPreviousStates[undoMachine->undoSize] = copyRepository;
		undoMachine->undoSize += 1;
	}
	else
	{
		while (undoMachine->currentOperation + 1 != undoMachine->undoSize)
		{
			//free(undoMachine->listOfPreviousStates[undoMachine->undoSize - 1]);
			undoMachine->undoSize -= 1;
			undoMachine->redoOperation -= 1;
		}

		undoMachine->listOfPreviousStates = realloc(undoMachine->listOfPreviousStates, 
			sizeof(UndoMachine*) * (undoMachine->undoSize + 1));
		undoMachine->listOfPreviousStates[undoMachine->undoSize] = copyRepository;
		undoMachine->undoSize += 1;
		undoMachine->currentOperation += 1;
		undoMachine->redoOperation += 1;
		
	}
}

void undoService(Service* service)
{
	if (service->undoMachine->currentOperation + 1 == service->undoMachine->undoSize)
	{
		saveCurrentState(service->undoMachine, service->repository);
		service->undoMachine->currentOperation -= 1;
	}
	undoOperation(service->undoMachine, service);
}

void undoOperation(UndoMachine* undoMachine, Service* service)
{
	if (undoMachine->currentOperation >= 0 && undoMachine->undoSize > 0)
	{
		service->repository = undoMachine->listOfPreviousStates[undoMachine->currentOperation];
		undoMachine->currentOperation -= 1;
		undoMachine->redoOperation -= 1;
	}
}


void redoService(Service* service)
{
	redoOperation(service->undoMachine, service);
}

void redoOperation(UndoMachine* undoManchine, Service* service)
{
	if (undoManchine->redoOperation + 1 < undoManchine->undoSize && undoManchine->undoSize > 0)
	{
		service->repository = undoManchine->listOfPreviousStates[undoManchine->redoOperation+1];
		undoManchine->redoOperation += 1;
	}
}


/////////////////////////////////////////////////////////
Service* createService()
{
	Service* newService = (Service*)malloc(sizeof(Service));
	UndoMachine* newUndoMachine = createUndoMachine();

	newService->undoMachine = newUndoMachine;

	return newService;
}


void destroyService(Service* service)
{
	destroyRepository(service->repository);
	free(service);
}

int getSizeOfListBots(Service* service)
{
	return getSizeOfRepository(service->repository);
}

Bot** getBots(Service* service)
{
	return getListOfBots(service->repository);
}


int addBotService(Service* service, int serialNumber, char* state, char* specialization, int energyCostToRepair)
{
	// This functions returns:
	// 1 - if the bot was succesfully added
	// 0 - if we found a duplicate of the Bot

	if (searchBotByID(service->repository, serialNumber) == NULL)
	{
		Bot* newBot = createBot(serialNumber, state, specialization, energyCostToRepair);

		saveCurrentState(service->undoMachine, service->repository);
		addElement(service->repository, newBot);
		return 1;
	}

	return 0;	
}

int updateBotService(Service* service, int serialNumber, char* state, char* specialization, int energyCostToRepair)
{
	Bot* botToBeUpdated = searchBotByID(service->repository, serialNumber);

	if (botToBeUpdated != NULL)
	{	
		saveCurrentState(service->undoMachine, service->repository);

		strcpy(botToBeUpdated->state, state);
		strcpy(botToBeUpdated->specialization, specialization);
		botToBeUpdated->energyCostToRepair = energyCostToRepair;
		return 1;
	}

	return 0;
}

int deleteBotService(Service* service, int serialNumber)
{
	saveCurrentState(service->undoMachine, service->repository);

	return deleteElement(service->repository, serialNumber);
}

void sortBotsAscendingByState(Repository* botRepository)
{
	for(int i = 0; i < botRepository->size-1; i++)
		for (int j = i + 1; j < botRepository->size; j++)
		{
			char* firstBotState = botRepository->data[i]->state;
			char* secondBotState = botRepository->data[j]->state;
			if (strcmp(firstBotState, secondBotState) > 0)
			{
				Bot* pivotBot = botRepository->data[i];
				botRepository->data[i] = botRepository->data[j];
				botRepository->data[j] = pivotBot;
			}
		}	
}


Bot** getBotsWithMaximumCostOfRepair(Service* service, int maximumEnergyCostToRepair)
{
	Repository* unsortedBotsRepository = createRepository();


	for (int i = 0; i < service->repository->size; i++)
	{
		Bot* currentBot = service->repository->data[i];
		if (currentBot->energyCostToRepair < maximumEnergyCostToRepair)
			addElement(unsortedBotsRepository, currentBot);
	}
	sortBotsAscendingByState(unsortedBotsRepository);
	return unsortedBotsRepository->data;
}

int getLenghtBotsWithMaximumCostOfRepair(Service* service, int maximumEnergyCostToRepair)
{
	Repository* unsortedBotsRepository = createRepository();


	for (int i = 0; i < service->repository->size; i++)
	{
		Bot* currentBot = service->repository->data[i];
		if (currentBot->energyCostToRepair < maximumEnergyCostToRepair)
			addElement(unsortedBotsRepository, currentBot);
	}
	
	return unsortedBotsRepository->size;
}

void testServiceLayer()
{
	void testUpdateBotService_validInput_botUpdated();
}

void testUpdateBotService_validInput_botUpdated()
{

	Repository* botRepository = createRepository();
	Service* botService = createService();

	botService->repository = botRepository;
	addBotService(botService, 123, "vlad", "rares", 123);

	int succesfullyUpdated = updateBotService(botService, 123, "razvan", "stefan", 456);
	Bot* updatedBot = searchBotByID(botService->repository , 123);

	assert(strcmp(updatedBot->specialization, "stefan") == 0);
	assert(strcmp(updatedBot->state, "razvan") == 0);
	assert(updatedBot->energyCostToRepair == 456);
	assert(succesfullyUpdated == 1);

	destroyBot(updatedBot);
	destroyService(botService);
	
}
