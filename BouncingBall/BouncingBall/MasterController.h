#pragma once

#include <iostream>
#include <Windows.h>
#include <SDL.h>
#include <SDL_image.h>

#include "BallSimulation.h"
#include "BallView.h"
#include "BoarderView.h"

#define SDL_SRCCOLORKEY  0x00001000

class MasterController {
	public:
	MasterController();
	~MasterController();

	void gameLoop();
	void freeMem();

	private:
	SDL_Surface *loadImage(char *cStr);

	BallSimulation *ballSimulation;
	BallView *ballView;
	BoarderView *boarderView;
};