#pragma once

#include <iostream>
#include <assert.h>
#include <SDL.h>
#include <SDL_image.h>

#include "Physics.h"

#define SIZE 10

class SplitterParticle {
public:
	SplitterParticle();
	~SplitterParticle();
	
	void update(float dt, SDL_Rect area);

	int x;
	int y;
	int w;
	int h;
	const Uint32 color = 0xFFFFFF;
	SDL_Surface* image;
private:
	void loadImage(char *path);

	Physics physics;
};

