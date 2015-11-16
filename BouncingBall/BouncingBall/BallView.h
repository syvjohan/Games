#pragma once

#include "BallSimulation.h"

class BallView {
	public:
		BallView(BallSimulation *ballSimulation);
		~BallView();

		SDL_Rect drawBall(float deltaTime, SDL_Rect area, float scaleX, float scaleY, float scaleH, float scaleW);

	private:
		BallSimulation *ballSimulation;
};

