#include "SplitterParticle.h"

SplitterParticle::SplitterParticle() {
	x = 500;
	y = 150;
	
	w = SIZE;
	h = SIZE;

	v2 position;
	position.x = x;
	position.y = y;

	v2 size;
	size.x = w;
	size.y = h;

	v2 velocity;
	velocity.x = 1.f;
	velocity.y = 1.f;

	Physics p(position, size, velocity, 0.9995f);
	this->physics = p;
}

SplitterParticle::~SplitterParticle() {}

void SplitterParticle::loadImage(char *path) {
	image = IMG_Load(path);

	assert(image == NULL && "Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
}

void SplitterParticle::update(float dt, SDL_Rect area) {
	physics.update(dt, area);

	x = physics.getPosition().x;
	y = physics.getPosition().y;
	h = physics.getSize().x;
	w = physics.getSize().y;
}