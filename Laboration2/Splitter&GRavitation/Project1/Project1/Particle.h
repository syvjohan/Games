#pragma once

#include <iostream>

#include <cfloat>
#include <math.h>
#include <time.h>
#include <cassert>

#include <SDL.h>

#define SIZE 5

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

	void operator+=(float s) {
		x = x + s;
		y = y + s;
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

	void operator*=(float s) {
		x = x * s;
		y = y * s;
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

struct ParticleParams {
	SDL_Surface *imgParticle;
	SDL_Surface *imgSmoke;
};

struct Particle {
	v2 position;
	v2 size;
	v2 velocity;
	v2 acceleration;
};

