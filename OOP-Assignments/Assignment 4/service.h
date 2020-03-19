#pragma once

#include "repository.h"


typedef struct
{
	int currentOperation;
	int undoSize;
	int redoOperation;
	Repository** listOfPreviousStates;

}UndoMachine;


typedef struct
{
	Repository* repository;
	UndoMachine* undoMachine;
}Service;




UndoMachine* createUndoMachine();
void saveCurrentState(UndoMachine* undoMachine, Repository* currentRepository);
void undoOperation(UndoMachine* undoMachine, Repository* currentRepository);
void undoService(Service* service);

void redoOperation(UndoMachine* undoManchine, Service* service);
void redoService(Service* service);



Service* createService();
void destroyService(Service* service);


void sortBotsAscendingByState(Repository* botRepository);
int getLenghtBotsWithMaximumCostOfRepair(Service* service, int maximumEnergyCostToRepair);

int getSizeOfListBots(Service* service);
Bot** getBots(Service* service);
Bot** getBotsWithMaximumCostOfRepair(Service* service, int maximumEnergyCostToRepair);

int addBotService(Service* service, int serialNumber, char* state, char* specialization, int energyCostToRepair);
int updateBotService(Service* service, int serialNumber, char* state, char* specialization, int energyCostToRepair);
int deleteBotService(Service* service, int serialNumber);


/// Tests

void testServiceLayer();
void testUpdateBotService_validInput_botUpdated();