#pragma once

#include <framework.h>

#include "Defs.h"
#include "SmokeSystem.h"
#include "SplitterSystem.h"
#include "AnimationSystem.h"
#include "Shockwave.h"
#include "BallSimulation.h"
#include "BallView.h"
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

			const float boarderMargin = 20;

			const float aimDiameter = 60;

			AudioSource *source;

			InputState inputState;
			WindowParams wParams;
			Common common;
			std::vector<View::SplitterSystem*> splitter;
			std::vector<View::SmokeSystem*> smoke;
	};

}
