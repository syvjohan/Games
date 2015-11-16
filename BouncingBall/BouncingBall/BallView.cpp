#include "BallView.h"

BallView::BallView(BallSimulation *simulation) {
	ballSimulation = simulation;
}

BallView::~BallView() {}

SDL_Rect BallView::drawBall(float deltaTime, SDL_Rect area, float scaleX, float scaleY, float scaleH, float scaleW) {
	return ballSimulation->draw(deltaTime, area, scaleX, scaleY, scaleH, scaleW);
}
