#pragma once

#include "Defs.h"
#include "Particle.h"

#include <framework.h>

namespace View {
	class SplitterSystem {
		public:
		SplitterSystem();
		SplitterSystem(Common &common, Vec2 scale, Vec2 screen);
		~SplitterSystem();

		void UpdateEmitter(const float dt);
		void RenderEmitter(Renderer2D *renderer);

		private:
		float r1();
		float r2();
		float InRange(float min, float max);
		void InitParticle(Model::Particle *p, Vec2 scale);
		void InitEmitter(float metersToPixels, Vec2 scale, Vec2 screen);
		void InitParams(Common &common);
		void GetParams();

		Model::ParticleEmitter emitter;
		Model::ParticleParams params;
	};
}