#include "repository.h"
#include <stdlib.h>
#include <string.h>




Repository* createRepository()
{
	Repository* botRepository;

	botRepository = (Repository*)malloc(sizeof(Repository));
	botRepository->size = 0;

	return botRepository;
}

Repository* copyOfCurrentRepository(Repository* currentRepository)
{
	Repository* newRepository = createRepository();
	newRepository->size = currentRepository->size;

	newRepository->data = malloc(sizeof(Bot) * newRepository->size);

	for (int i = 0; i < newRepository->size; i++)
	{
		// We get the current bot in the original repository
		Bot* currentBot = currentRepository->data[i];

		// We create a newbot with the information from the original bot
		Bot* newBot = createBot(currentBot->serialNumber, currentBot->state, 
			currentBot->specialization, currentBot->energyCostToRepair);

		// And we copy it in the copyRepository
		newRepository->data[i] = newBot;
	}

	return newRepository;
}

void destroyRepository(Repository* someRepository)
{
	for (int i = 0; i < someRepository->size; i++)
		destroyBot(someRepository->data[i]);
	if(someRepository->size != 0)
		free(someRepository->data);
	free(someRepository);

}

void addElement(Repository* botRepository, Bot* newElement)
{
	if (botRepository->size == 0)
	{
		botRepository->data = (Bot*)malloc(sizeof(Bot));
		botRepository->data[botRepository->size] = newElement;
		botRepository->size += 1;
	}
	else
	{		
		botRepository->data = realloc(botRepository->data, sizeof(Bot) * (2*botRepository->size));
		botRepository->data[botRepository->size] = newElement;
		botRepository->size += 1;
	}
}

Bot* searchBotByID(Repository* botRepository, int ID)
{
	///This functions searches for a bot by his ID
	// It returns the Bot* pointer if it finds it
	// NULL otherwise

	for (int i = 0; i < botRepository->size; i++)
		if (botRepository->data[i]->serialNumber == ID)
			return botRepository->data[i];
	return NULL;
}


int deleteElement(Repository* botRepository, int serialID)
{
	for (int i = 0; i < botRepository->size; i++)
	{
		Bot* currentBot = botRepository->data[i];
		if (currentBot->serialNumber == serialID)
		{
			destroyBot(currentBot);
			memmove(botRepository->data + i, botRepository->data + i + 1, sizeof(Bot) * botRepository->size - i);
			botRepository->size -= 1;
			botRepository->data = realloc(botRepository->data, sizeof(Bot) * (botRepository->size));
			return 1;
		}
	}
	return 0;
	
}

Bot** getListOfBots(Repository* botRepository)
{
	return botRepository->data;
}

int getSizeOfRepository(Repository* botRepository)
{
	return botRepository->size;
}


/// @@@@@@@@@@@@@@@@@@@@@@ Tests@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//
/// @@@@@@@@@@@@@@@@@@@@@@ Tests@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//
/// @@@@@@@@@@@@@@@@@@@@@@ Tests@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//


void testRepository()
{
	testAddElement_validInput_valueAdded();	
	testSearchElement_validID_elementReturned();	
	testSearchElement_invalidID_NULLpointerReturned();	
	testDeleteElement_validID_elementDeleted();
	testDeleteElement_invalidID_elementNotDeleted();
	testCopyRepository();

}

void testCopyRepository()
{
	Repository* newRepository = createRepository();
	Bot* newBot = createBot(123, "abc", "def", 456);
	Bot* anotherBot = createBot(456, "def", "def", 234);
	addElement(newRepository, newBot);
	addElement(newRepository, anotherBot);

	Repository* copyOfRepository = copyOfCurrentRepository(newRepository);
	deleteElement(newRepository, 123);

	assert(copyOfRepository->size, 2);
	assert(getSerialNumber(copyOfRepository->data[0]) == 123);
	assert(getSerialNumber(copyOfRepository->data[1]) == 456);
}


void testDeleteElement_invalidID_elementNotDeleted()
{
	Repository* newRepository = createRepository();
	Bot* newBot = createBot(123, "abc", "def", 456);
	Bot* anotherBot = createBot(456, "def", "def", 234);
	
	addElement(newRepository, newBot);
	addElement(newRepository, anotherBot);


	int succesfulDelete = deleteElement(newRepository, 125);

	assert(getSizeOfRepository(newRepository) == 2);
	assert(searchBotByID(newRepository, 123) == newBot);
	assert(searchBotByID(newRepository, 456) == anotherBot);
	assert(succesfulDelete == 0);

	//destroyBot(newBot);
	//destroyBot(anotherBot);
	destroyRepository(newRepository);

	
	
}


void testDeleteElement_validID_elementDeleted()
{
	Repository* newRepository = createRepository();
	Bot* newBot = createBot(123, "abc", "def", 456);
	Bot* anotherBot = createBot(456, "def", "def", 234);

	addElement(newRepository, newBot);
	addElement(newRepository, anotherBot);

	int succesfulDelete = deleteElement(newRepository, 123);
	assert(getSizeOfRepository(newRepository) == 1);
	assert(searchBotByID(newRepository, 123) == NULL);
	assert(succesfulDelete == 1);


	//destroyBot(newBot);
	//destroyBot(anotherBot);
	destroyRepository(newRepository);
	
}

void testSearchElement_validID_elementReturned()
{
	Repository* newRepository = createRepository();
	Bot* newBot = createBot(123, "abc", "def", 456);
	addElement(newRepository, newBot);

	Bot* foundBot = searchBotByID(newRepository, 123);
	assert(foundBot == newBot);

	//destroyBot(newBot);
	destroyRepository(newRepository);

}

void testSearchElement_invalidID_NULLpointerReturned()
{
	Repository* newRepository = createRepository();
	Bot* newBot = createBot(123, "abc", "def", 456);
	addElement(newRepository, newBot);

	Bot* foundBot = searchBotByID(newRepository, 202);
	assert(foundBot == NULL);

	//destroyBot(newBot);	
	destroyRepository(newRepository);
}

void testAddElement_validInput_valueAdded()
{
	Repository* newRepository = createRepository();
	Bot* newBot = createBot(123, "abc", "def", 456);
	Bot* anotherBot = createBot(456, "def", "def", 234);

	assert(newRepository->size == 0);

	addElement(newRepository, newBot);

	int listSize = newRepository->size;
	assert(listSize == 1);
	assert(newRepository->data[listSize - 1] == newBot);

	addElement(newRepository, anotherBot);
	listSize = newRepository->size;

	assert(listSize == 2);
	assert(newRepository->data[listSize - 1] == anotherBot);


	//destroyBot(newBot);
	//destroyBot(anotherBot);	
	destroyRepository(newRepository);
}