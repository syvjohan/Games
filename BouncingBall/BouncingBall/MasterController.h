#pragma once

#include <SDL.h>

#include "BallSimulation.h"
#include "BallView.h"
#include "BoarderView.h"
#include "Scale.h"
#include "Defs.h"
//#include "Outputf.h"

#define SDL_SRCCOLORKEY  0x00001000

class MasterController  {
	public:
		MasterController();
		~MasterController();

		void gameLoop();
		void freeMem();

	private:
		Scale *scale;
		BallSimulation *ballSimulation;
		BallView *ballView;
		BoarderView *boarderView;
};