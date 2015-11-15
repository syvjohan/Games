#include "Ball.h"

Ball::Ball() {}

Ball::Ball(const float positionX, const float positionY, const float sizeW, const float sizeH) {
	this->sizeH = sizeH;
	this->sizeW = sizeW;

	this->positionX = positionX;
	this->positionY = positionY;
}

void Ball::setSizeW(float size) {
	this->sizeW = size;
}

void Ball::setSizeH(float size) {
	this->sizeH = size;
}

void Ball::setPositionX(float position) {
	this->positionX = position;
}

void Ball::setPositionY(float position) {
	this->positionY = position;
}

float Ball::getSizeW() {
	return this->sizeW;
}

float Ball::getSizeH() {
	return this->sizeW;
}

float Ball::getPositionX() {
	return this->positionX;
}

float Ball::getPositionY() {
	return this->positionY;
}

