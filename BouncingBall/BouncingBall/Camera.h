#pragma once

typedef struct scale_s {
	float sizeX;
	float sizeY;
	float sizeW;
	float sizeH;
}scale_t;

class Camera {
	public:
		Camera();
		~Camera();

		void set(float sizeX, float sizeY, float sizeW, float sizeH);
		scale_t get();
	private: 
		scale_t scale;
};