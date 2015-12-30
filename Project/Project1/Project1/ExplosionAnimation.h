#pragma once

#include "Explosion.h"

#include <framework.h>

namespace View {
	class ExplosionAnimation {
		public:
		ExplosionAnimation();
		ExplosionAnimation(Common &common, Vec2 scale, Vec2 startPosition);
		~ExplosionAnimation();

		void Update(const float dt);
		void Render(Renderer2D *renderer);
		int HasEnd();
		void PlaySoundEffect();

		private:
		void InitAnimation(Vec2 scale, Vec2 startPosition);

		Model::ExplosionAnimation animation;

		AudioSource *source;
		Common common;
	};
}