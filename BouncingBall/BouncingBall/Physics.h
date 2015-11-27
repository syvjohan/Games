#pragma once

#include <SDL.h>
#include <cfloat>
#include <math.h>

//vector to use in physic object.
struct v2 {
	float x, y;

	v2 operator+(const v2& v1) {
		v2 v;
		v.x = x + v1.x;
		v.y = y + v1.y;
		return v;
	}

	v2 operator*(float s) {
		v2 v;
		v.x = x * s;
		v.y = y * s;
		return v;
	}

	void normalize() {
		float l = sqrtf(x * x + y * y);
		if (fabsf(l) > FLT_EPSILON) { //uses FLT_EPSILON because we dont wannt to compare with 0 (Difference between 1 and the least value greater than 1 that is representable).
			x /= l;
			y /= l;
		}
	}
};

class Physics {
	public:
		Physics();
		Physics(v2 position, v2 size, v2 velocity, float restitution);
		~Physics();

		v2 getPosition();
		v2 getSize();
		v2 getVelocity();
		float getRestitution();

		void setPosition(v2 position);
		void setSize(v2 size);
		void setVelocity(v2 velocity);
		void setRestitution(float restitution);

		void update(float delta, const SDL_Rect &area);

	private:
		v2 position;
		v2 size;
		v2 velocity; //speed.
		float restitution; //speed slowingdown.
};