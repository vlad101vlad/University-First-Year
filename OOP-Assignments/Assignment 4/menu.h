#pragma once

#include "service.h"

typedef struct
{
	Service* service;

}Menu;


Menu* createMenu();
void destroyMenu(Menu* console);

void runMenu(Menu* console);
void listBots(Menu* console);
void listBotsBySpecialization(Menu* console, char** listOfArguments);
void sortByEnergyCostUI(Menu* console, char** listOfArguments);

void addBotsUI(Menu* console, char** listOfArguments);
void updateBotUI(Menu* console, char** listOfArguments);
void deleteBotUI(Menu* console, char** listOfArguments);


char** convertInputIntoWords(char* inputInformation);
void freeInputInformation(char** listOfArguments);