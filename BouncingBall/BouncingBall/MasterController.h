#pragma once

#include <SDL.h>
#include <iostream>

#include "BallSimulation.h"
#include "BallView.h"
#include "BoarderView.h"
#include "Scale.h"
#include "Defs.h"

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