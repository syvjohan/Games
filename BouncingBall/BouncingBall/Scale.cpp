#include "Scale.h"

Scale::Scale() {}

Scale::~Scale() {}

void Scale::set(float sizeW, float sizeH) {
	w = sizeW;
	h = sizeH;
}

float Scale::getW() {
	return w;
}

float Scale::getH() {
	return h;
}

