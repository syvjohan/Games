#pragma once

#include "Physics.h"
#include "Ball.h"

class BallSimulation {
	public:
		BallSimulation();
		~BallSimulation();

		SDL_Rect draw(float deltaTime, SDL_Rect area, float scale);
		void init(); //Need to be called before enter gameLoop

	private:
		Ball *ball;
		SDL_Rect rectBall;
		Physics *ballPhysics;
		
};