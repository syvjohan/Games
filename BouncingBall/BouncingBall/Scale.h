#pragma once

#include "Camera.h"

class Scale {
	public:
		Scale();
		~Scale();

		void set(float sizeX, float sizeY, float sizeW, float sizeH);
		scale_t get();

	private:
		Camera *camera;
};