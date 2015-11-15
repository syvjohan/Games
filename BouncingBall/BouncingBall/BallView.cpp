#include "BallView.h"

BallView::BallView(BallSimulation *simulation) {
	camera = new Camera();
	ballSimulation = simulation;
}

BallView::~BallView() {}

float BallView::getScale() {
	return camera->getScale();
}

void BallView::setScale(float scale) {
	camera->setScale(scale);
}

SDL_Rect BallView::drawBall(float deltaTime, SDL_Rect area) {
	return ballSimulation->draw(deltaTime, area, camera->getScale());
}
