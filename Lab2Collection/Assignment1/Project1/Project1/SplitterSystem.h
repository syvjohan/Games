#pragma once
#include "SplitterParticle.h"

#include <framework.h>

class SplitterSystem {
	public:
		SplitterSystem();
		SplitterSystem(Common &common, float scale, float screenW, float screenH);
		~SplitterSystem();
		
		void UpdateEmitter( const float dt);
		void RenderEmitter(Renderer2D *renderer);
		void FreeMem();

	private:
		float r1();
		float r2();
		float InRange(float min, float max);
		void InitParticle(Particle *p, float scale);
		void InitEmitter(float metersToPixels, float scale, float screenW, float screenH);
		void InitParams(Common &common);

		ParticleEmitter emitter;
		ParticleParams params;
};

