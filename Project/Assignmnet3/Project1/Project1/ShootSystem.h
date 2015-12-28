#pragma once

#include "Defs.h"
#include "Particle.h"

#include <framework.h>

namespace View {
	class ShootSystem {
		public:
		ShootSystem();
		ShootSystem(Common &common, Vec2 scale, Vec2 playArea);
		~ShootSystem();

		void AddShoot(Vec2 startPosition);
		void UpdateEmitter(const float dt);
		void RenderEmitter(Renderer2D *renderer);

		private:
		void InitParticle(Model::Particle *p, Vec2 scale);
		void InitEmitter(float metersToPixels, Vec2 scale, Vec2 playArea);
		void InitParams(Common &common);
		void GetParams();

		Model::ParticleEmitter emitter;
		Model::ParticleParams params;
	};
}
