#pragma once

#include <framework.h>

#include "Defs.h"

#include "ManagerModel.h"
#include "ManagerView.h"

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

			const float borderW = 10;
			const float borderH = 10;

			AudioSource *source;

			InputState inputState;
			WindowParams wParams;
			Common common;
	};

}
