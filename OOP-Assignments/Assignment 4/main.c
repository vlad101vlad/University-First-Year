#include "domain.h"
#include "repository.h"
#include "service.h"
#include "menu.h"

#include <stdlib.h>
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC



void projectTests()
{
	testCreateBot();
	testRepository();
	testServiceLayer();
}

int main()
{
	projectTests();

	Repository* botRepository = createRepository();
	Service* botService = createService();
	Menu* console = createMenu();

	botService->repository = botRepository;
	console->service = botService;

	runMenu(console);

	destroyMenu(console);

	_CrtDumpMemoryLeaks();


	return 0;
}