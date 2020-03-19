#pragma once
#include <stdlib.h>
#include <assert.h>


typedef struct {
	int serialNumber;
	char* state;
	char* specialization;
	int energyCostToRepair;
}Bot;

Bot* createBot(int serialNumber, char* state, char* specialization, int energyCostToRepair);
void destroyBot(Bot*);

void testCreateBot();

int getSerialNumber(Bot*);
int getEnergyCostToRepair(Bot*);
char* getState(Bot*);
char* getSpecialization(Bot*);
