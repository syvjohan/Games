#include "SplitterSystem.h"


SplitterSystem::SplitterSystem() {}

SplitterSystem::SplitterSystem(SDL_Surface *surfaceScreen) {
	this->surfaceScreen = surfaceScreen;
}

SplitterSystem::~SplitterSystem() {}

void SplitterSystem::drawParticles(float dt, SDL_Rect area) {
	loadImage("spark.png");

	for (int i = 0; i != sizeof(particles) / sizeof(particles[0]); ++i) {
		particles[i].update(dt, area);
		fillRect(particles[i], surfaceImg);
	}
}

void SplitterSystem::loadImage(char *path) {
	surfaceImg = IMG_Load(path);
	assert(surfaceImg != NULL && "Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
}

void SplitterSystem::fillRect(SplitterParticle particle, SDL_Surface *surfaceImg) {

	SDL_Rect rect = { particle.x, particle.y, particle.w, particle.h };

	Uint32 color = SDL_MapRGB(surfaceImg->format, 0, 0, 0);
	SDL_SetColorKey(surfaceImg, 0x00001000, color);

	SDL_BlitScaled(surfaceImg, NULL, surfaceScreen, &rect);
}