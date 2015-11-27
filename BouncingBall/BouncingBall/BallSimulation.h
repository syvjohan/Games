#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include "Physics.h"
#include "Ball.h"

class BallSimulation {
	public:
		BallSimulation();
		~BallSimulation();

		SDL_Rect draw(float deltaTime, SDL_Rect area, float scaleH, float scaleW);
		void init(); //Need to be called before enter gameLoop

		SDL_Surface *loadImage(char *cStr, SDL_Surface &surfaceScreen);

	private:
		Ball *ball;
		SDL_Rect rectBall;
		Physics *ballPhysics;
		
};