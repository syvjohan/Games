#pragma once

#include <iostream>
#include <SDL.h>
#include <cfloat>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <cassert>
#include <SDL.h>
#include <SDL_image.h>

#define SIZE 10

//vector to use in physic object.
struct v2 {
	float x, y;

	v2 operator+(const v2& v1) {
		v2 v;
		v.x = x + v1.x;
		v.y = y + v1.y;
		return v;
	}

	v2 operator-(const v2& v1) {
		v2 v;
		v.x = x - v1.x;
		v.y = y - v1.y;
		return v;
	}

	v2 operator*(float s) {
		v2 v;
		v.x = x * s;
		v.y = y * s;
		return v;
	}

	v2 operator/(float s) {
		v2 v;
		v.x = x / s;
		v.y = y / s;
		return v;
	}

	void operator+=(const v2& v1) {
		x = x + v1.x;
		y = y + v1.y;
	}

	void operator-=(const v2& v1) {
		x = x - v1.x;
		y = y + v1.y;
	}

	void operator/=(const v2& v1) {
		x = x / v1.x;
		y = y / v1.y;
	}

	void operator*=(const v2& v1) {
		x = x * v1.x;
		y = y * v1.y;
	}

	void normalize() {
		float l = sqrtf(x * x + y * y); //2D. Add + z * z for 3D...
		assert(fabsf(l) > FLT_EPSILON);
		x /= l;
		y /= l;
	}
};

class SplitterParticle {
public:
	SplitterParticle();
	~SplitterParticle();
	
	void update(float dt, SDL_Rect area);

	SDL_Surface* getSurface();

	int x;
	int y;
	int w;
	int h;
	const Uint32 color = 0xFFFFFF;
private:
	float generateRandomNumber(float min, float max);

	v2 position;
	v2 size;
	v2 velocity; //speed. 
	v2 restitution; //speed slowingdown.
	v2 acceleration;

	float speedMin;
	float speedMax;
};

