#pragma once
#include "SplitterParticle.h"

#include <framework.h>

class SplitterSystem {
	public:
		SplitterSystem();
		SplitterSystem(Common &common, float screenH, float screenW);
		~SplitterSystem();
		
		void UpdateEmitter( const float dt);
		void RenderEmitter(Renderer2D *renderer);
		void FreeMem();

	private:
		float r1();
		float r2();
		float InRange(float min, float max);
		void InitParticle(Particle *p);
		void InitEmitter(float metersToPixels, float screenH, float screenW);
		void InitParams(Common &common);
		void getParams();

		ParticleEmitter emitter;
		ParticleParams params;
};

