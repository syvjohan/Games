#include "SplitterSystem.h"


SplitterSystem::SplitterSystem() {}

SplitterSystem::SplitterSystem(SDL_Surface *surfaceScreen) {
	this->surfaceScreen = surfaceScreen;
}

SplitterSystem::~SplitterSystem() {}

void SplitterSystem::drawParticles(float dt, SDL_Rect area) {
	for (int i = 0; i != 100; ++i) {
		particles[i].update(dt, area);
		fillRect(particles[i]);
	}
}

void SplitterSystem::fillRect(SplitterParticle particle) {
	SDL_Rect rect = { particle.x, particle.y, particle.w, particle.h };
	SDL_FillRect(surfaceScreen, &rect, particle.color);
}