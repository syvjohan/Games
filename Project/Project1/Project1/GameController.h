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

			bool inMenu = true;
			bool inGame = false;

			WindowParams wParams;
			Common common;
	};

}
