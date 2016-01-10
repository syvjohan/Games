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
		GAMESTATE_INMENU,
		GAMESTATE_AFTER_GAME
	};

	struct AsteroidType {
		int typ1;
		int type2;
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

			void SetAsteroidType(int lvl);
			AsteroidType GetAsteroidType();

		private:
			int screenWidth = 1280;
			int screenHeight = 720;

			WindowParams wParams;
			Common common;

			GameStates currentState;
			const float coolDownEsc = 0.5f;
			float timerEsc = coolDownEsc;

			const float timeElapseResultScreen = 3;
			float timerResultScreen = timeElapseResultScreen;

			bool isGameStarted = false;
			int currentLvl = 0;

			AsteroidType asteroidType;
	};

}
