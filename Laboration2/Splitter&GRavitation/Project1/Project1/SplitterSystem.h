#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include "Particle.h"

class SplitterSystem {
	public:
		SplitterSystem();
		~SplitterSystem();

		void init(SDL_Surface *surfaceScreen);

		void drawParticles(float dt);

	private:
		SDL_Surface *surfaceScreen;
		Particle particles[100];

		ParticleParams params;

		void fillRect(Particle particle, SDL_Surface *surfaceImg);
		float generateRandomNumber(float min, float max);
		SDL_Surface *loadImage(char *path);
};

