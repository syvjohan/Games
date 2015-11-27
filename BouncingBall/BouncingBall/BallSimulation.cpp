#include "BallSimulation.h"

BallSimulation::BallSimulation() {
}

BallSimulation::~BallSimulation() {	
	if (ballPhysics) {
		delete ballPhysics;
		ballPhysics = nullptr;
	} 
	
	if (ball) {
		delete ball;
		ball = nullptr;
	}
}

SDL_Rect BallSimulation::draw(float deltaTime, SDL_Rect area, float scaleH, float scaleW) {
	ballPhysics->update(deltaTime, area);

	rectBall.x = (int)(ballPhysics->getPosition().x + 0.5f * scaleW);
	rectBall.y = (int)(ballPhysics->getPosition().y + 0.5f * scaleH);
	rectBall.h = (int)(ballPhysics->getSize().y * scaleH);
	rectBall.w = (int)(ballPhysics->getSize().x * scaleW);

	return rectBall;
}

SDL_Surface* BallSimulation::loadImage(char *cStr, SDL_Surface &surfaceScreen) {
	SDL_Surface *loadedSurface = IMG_Load(cStr);

	//The final optimized image
	SDL_Surface *optimizedSurface = NULL;
	if (loadedSurface == NULL) {
		//outputf("Unable to load image %s! SDL_image Error: %s\n", cStr, IMG_GetError());
	} else {
		//Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface(loadedSurface, surfaceScreen.format, NULL);
		if (optimizedSurface == NULL) {
			//outputf("Unable to optimize image %s! SDL Error: %s\n", cStr, SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
	return optimizedSurface;
}

//Initialize basic values.
void BallSimulation::init() {
	ball = new Ball();
	ball->setPositionX(250.0f);
	ball->setPositionY(700.0f);
	ball->setSizeW(40.0f);
	ball->setSizeH(40.0f);
	
	v2 pos;
	pos.x = ball->getPositionX();
	pos.y = ball->getPositionY();

	v2 size;
	size.x = ball->getSizeW();
	size.y = ball->getSizeH();

	v2 vel; //speed
	vel.x = 1.f;
	vel.y = 1.f;

	ballPhysics = new Physics();
	ballPhysics->setPosition(pos);
	ballPhysics->setSize(size);
	ballPhysics->setVelocity(vel);
	ballPhysics->setRestitution(0.9995f); //slowing down (0.95f).
}
