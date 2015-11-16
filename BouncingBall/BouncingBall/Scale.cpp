#include "Scale.h"

Scale::Scale() {
	camera = new Camera;
}
Scale::~Scale() {
	if (camera) {
		delete camera;
		camera = nullptr;
	}
}

void Scale::set(float sizeX, float sizeY, float sizeW, float sizeH) {
	camera->set(sizeX, sizeY, sizeW, sizeH);
}

scale_t Scale::get() {
	return camera->get();
}

