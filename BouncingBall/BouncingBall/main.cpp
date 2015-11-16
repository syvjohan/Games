#include "MasterController.h"

#include "Defs.h"

int main(int, char**) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	MasterController masterController;
	masterController.gameLoop();

	return 0;
}