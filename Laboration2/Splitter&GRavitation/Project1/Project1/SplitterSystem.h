#pragma once

#include "SplitterParticle.h"

class SplitterSystem {
	public:
		SplitterSystem();
		SplitterSystem(SDL_Surface *screenSurface);
		~SplitterSystem();

		void drawParticles(float dt, SDL_Rect area);

	private:
		SDL_Surface *surfaceScreen;
		SplitterParticle particles[100];

		void fillRect(SplitterParticle particle);
};

