#include "domain.h"
#include <string.h>


Bot* createBot(int serialNumber, char* state, char* specialization, int energyCostToRepair)
{
	Bot* newBot;
	newBot = (Bot*)malloc(sizeof(Bot));

	newBot->serialNumber = serialNumber;
	newBot->energyCostToRepair = energyCostToRepair;

	newBot->state = (char*)malloc(sizeof(char) * 50);
	strcpy(newBot->state, state);

	newBot->specialization = (char*)malloc(sizeof(char) * 50);
	strcpy(newBot->specialization, specialization);
	
	return newBot;
}

int getSerialNumber(Bot* someBot)
{
	return someBot->serialNumber;
}

int getEnergyCostToRepair(Bot* someBot)
{
	return someBot->energyCostToRepair;
}

char* getState(Bot* someBot)
{
	return someBot->state;
}


char* getSpecialization(Bot* someBot)
{
	return someBot->specialization;
}


void destroyBot(Bot* someBot)
{
	free(someBot->specialization);
	free(someBot->state);
	free(someBot);
}


void testCreateBot()
{
	Bot* newBot = createBot(123, "vlad", "rares", 456);
	assert(getSerialNumber(newBot) == 123);
	assert(getEnergyCostToRepair(newBot) == 456);
	assert(strcmp(getState(newBot), "vlad") == 0);
	assert(strcmp(getSpecialization(newBot),"rares") == 0);	

	destroyBot(newBot);

}