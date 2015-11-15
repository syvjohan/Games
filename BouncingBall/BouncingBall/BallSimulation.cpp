#include "BallSimulation.h"

BallSimulation::BallSimulation() {
}

BallSimulation::~BallSimulation() {
	//delete ball;
	//ball = NULL;
}

SDL_Rect BallSimulation::draw(float deltaTime, SDL_Rect area, float scale) {

	area.h *= scale;
	area.w *= scale;
	area.x *= scale;
	area.y *= scale;

	ballPhysics->update(deltaTime, area);

	rectBall.x = (int)(ballPhysics->getPosition().x + 0.5f * scale);
	rectBall.y = (int)(ballPhysics->getPosition().y + 0.5f * scale);
	rectBall.h = (int)(ballPhysics->getSize().y * scale);
	rectBall.w = (int)(ballPhysics->getSize().x * scale);

	return rectBall;
}

void BallSimulation::init() {
	ball = new Ball();
	ball->setPositionX(60.0f);
	ball->setPositionY(500.0f);
	ball->setSizeW(40.0f);
	ball->setSizeH(40.0f);
	
	v2 pos;
	pos.x = ball->getPositionX();
	pos.y = ball->getPositionY();

	v2 size;
	size.x = ball->getSizeW();
	size.y = ball->getSizeH();

	v2 vel;
	vel.x = 1;
	vel.y = 1;

	ballPhysics = new Physics();
	ballPhysics->setPosition(pos);
	ballPhysics->setSize(size);
	ballPhysics->setVelocity(vel);
	ballPhysics->setRestitution(0.9995f);
}
