#pragma once

#include "Particle.h"
#include "Defs.h"

#include <framework.h>

class Shockwave {
	public:
		Shockwave();
		Shockwave(Common &common, Vec2 scale, Vec2 screen);
		~Shockwave();

		void UpdateEmitter(const float dt);
		void RenderEmitter(Renderer2D *renderer);

	private:
		float r1();
		float r2();
		float InRange(float min, float max);
		void InitParticle(Particle *p, Vec2 scale);
		void InitEmitter(float metersToPixels, Vec2 scale, Vec2 screen);
		void InitParams(Common &common);
		void GetParams();

		ParticleEmitter emitter;
		ParticleParams params;
};

