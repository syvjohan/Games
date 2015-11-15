#include "Camera.h"

Camera::Camera() {}

Camera::~Camera() {}

void Camera::setScale(float s) {
	this->scale = s;
}

float Camera::getScale() {
	return this->scale;
}
