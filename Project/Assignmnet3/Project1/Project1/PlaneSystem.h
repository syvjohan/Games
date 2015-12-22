#pragma once

#include "Defs.h"
#include "Particle.h"

#include <framework.h>

namespace View {
	class PlaneSystem {
		public:
		PlaneSystem();
		PlaneSystem(Common &common, Vec2 scale, Vec2 screen, float boarderMargin);
		~PlaneSystem();

		void UpdateEmitter(const float dt, const float BoarderMargin);
		void RenderEmitter(Renderer2D *renderer);

		void Back();
		void Forward();
		void Upp();
		void Down();

		Vec2 GetFirePosition();

		private:
		void InitParticle(Model::Particle *p, Vec2 scale);
		void InitEmitter(float metersToPixels, Vec2 scale, Vec2 screen, float boarderMargin);
		void InitParams(Common &common);
		void GetParams();

		Model::ParticleEmitter emitter;
		Model::ParticleParams params;
	};
}

