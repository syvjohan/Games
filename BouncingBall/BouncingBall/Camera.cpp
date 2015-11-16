#include "Camera.h"

Camera::Camera() {
	scale.sizeH = 1;
	scale.sizeW = 1;
	scale.sizeX = 1;
	scale.sizeY = 1;
}

Camera::~Camera() {}

void Camera::set(float sizeX, float sizeY, float sizeW, float sizeH) {
	this->scale.sizeH = sizeH;
	this->scale.sizeW = sizeW;
	this->scale.sizeX = sizeX;
	this->scale.sizeY = sizeY;
}

scale_t Camera::get() {
	return scale;
}
