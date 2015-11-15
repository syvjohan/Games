#pragma once

#include "Camera.h"
#include "BallSimulation.h"

class BallView {
	public:
		BallView(BallSimulation *ballSimulation);
		~BallView();

		SDL_Rect drawBall(float deltaTime, SDL_Rect area);

		void setScale(float scale);
		float getScale();


	private:
		Camera *camera;
		BallSimulation *ballSimulation;
};

