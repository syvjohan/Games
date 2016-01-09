#pragma once

#include <framework.h>

#include "Defs.h"

#include "ManagerModel.h"
#include "ManagerView.h"
#include "MenuModel.h"
#include "MenuView.h"


#include <vector>
#include <cstdlib>
#include <ctime>

namespace Controller {
	enum GameStates {
		GAMESTATE_INGAME = 0,
		GAMESTATE_INMENU
	};

	static bool gRunning = true;

	class EventManager : public IEventProcessor {
		public:
		void onWindowClose() { gRunning = false; }
	};

	class GameController {
		public:
			GameController();
			~GameController();

			void gameLoop();

		private:
			int screenWidth = 1280;
			int screenHeight = 720;

			WindowParams wParams;
			Common common;

			GameStates currentState;
			const float coolDownEsc = 0.5f;
			float timerEsc = coolDownEsc;

			bool isGameStarted = false;
	};

}
