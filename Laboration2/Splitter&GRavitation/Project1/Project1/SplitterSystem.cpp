#include "SplitterSystem.h"

SplitterSystem::SplitterSystem() {}

SplitterSystem::~SplitterSystem() {}

void SplitterSystem::init(SDL_Surface *surfaceScreen) {
	this->surfaceScreen = surfaceScreen;

	params = { loadImage("image/spark.png"), loadImage("image/particlesmoke.tga") };

	for (int i = 0; i != sizeof(particles) / sizeof(particles[0]); ++i) {
		Particle &p = particles[i];

		p.position = { 500, 100 };
		p.size = { SIZE, SIZE };

		p.velocity = { generateRandomNumber(50.f, 1.f), generateRandomNumber(50.f, 1.f) };
		p.velocity.normalize();
		p.velocity = p.velocity * (((generateRandomNumber(50.f, 1.f) + 2.0f) / 2.0f) * 5 + 5);
	}
}

void SplitterSystem::drawParticles(float dt) {
	for (int i = 0; i != sizeof(particles) / sizeof(particles[0]); ++i) {
		Particle &p = particles[i];

		p.acceleration.y = 1.5f;

		p.velocity.y += p.acceleration.y * dt; //gravity.

		p.velocity *= 0.99995f;

		p.position += p.velocity * dt;

		fillRect(p, params.imgParticle);
	}
}

SDL_Surface* SplitterSystem::loadImage(char *path) {
	SDL_Surface *img = IMG_Load(path);
	assert(img != NULL && "Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
	
	return img;
}

void SplitterSystem::fillRect(Particle particle, SDL_Surface *img) {
	SDL_Rect rect = { particle.position.x, particle.position.y, particle.size.x, particle.size.y };

	Uint32 color = SDL_MapRGB(img->format, 0, 0, 0);
	SDL_SetColorKey(img, 0x00001000, color);

	SDL_BlitScaled(img, NULL, surfaceScreen, &rect);
}

float SplitterSystem::generateRandomNumber(float min, float max) {
	//return ((float(rand()) / float(RAND_MAX)) * (max - min)) + min;
	return ((rand() & 100) / min) - max;
}