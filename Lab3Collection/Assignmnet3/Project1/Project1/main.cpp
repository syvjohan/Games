#include "GameController.h"

#undef main
int main(int, char**) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	srand(time(NULL));
	
	Controller::GameController gameController;
	gameController.gameLoop();
	return 0;
}

