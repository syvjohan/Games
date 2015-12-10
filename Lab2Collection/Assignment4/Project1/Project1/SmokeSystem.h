#pragma once

#include "Particle.h"
#include "Defs.h"

#include <framework.h>

class SmokeSystem {
	public:
		SmokeSystem();
		SmokeSystem(Common &common, Vec2 scale, Vec2 screen);
		~SmokeSystem();
		
		void UpdateEmitter( const float dt);
		void RenderEmitter(Renderer2D *renderer);

	private:
		float r1();
		float r2();
		float InRange(float min, float max);
		void InitParticle(Particle *p);
		void InitEmitter(float metersToPixels, Vec2 screen, Vec2 scale);
		void InitParams(Common &common);
		void GetParams();

		ParticleEmitter emitter;
		ParticleParams params;
};

