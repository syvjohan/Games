#include "BallView.h"

BallView::BallView(BallSimulation *simulation) {
	ballSimulation = simulation;
}

BallView::~BallView() {}

SDL_Rect BallView::drawBall(float deltaTime, SDL_Rect area, float scaleH, float scaleW) {
	return ballSimulation->draw(deltaTime, area, scaleH, scaleW);
}
