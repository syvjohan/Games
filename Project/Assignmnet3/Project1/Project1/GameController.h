#pragma once

#include <framework.h>

#include "Defs.h"
#include "PlaneSystem.h"
#include "ShootSystem.h"
#include "Camera.h"

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

			const float boarderMargin = 10;

			AudioSource *source;

			InputState inputState;
			WindowParams wParams;
			Common common;
	};

}
