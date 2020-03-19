#pragma once
#include "domain.h"	

typedef struct
{
	Bot** data;
	int size;

}Repository;



Repository* createRepository();
Repository* copyOfCurrentRepository(Repository* currentRepository);
void destroyRepository(Repository*);

void testRepository();
void testAddElement_validInput_valueAdded();
void testSearchElement_validID_elementReturned();
void testSearchElement_invalidID_NULLpointerReturned();
void testDeleteElement_validID_elementDeleted();
void testDeleteElement_invalidID_elementNotDeleted();
void testCopyRepository();

void addElement(Repository*, Bot* newElement);
Bot* searchBotByID(Repository* botRepository, int ID);
Bot** getListOfBots(Repository* botRepository);
int getSizeOfRepository(Repository* botRepository);
int deleteElement(Repository*, int);
