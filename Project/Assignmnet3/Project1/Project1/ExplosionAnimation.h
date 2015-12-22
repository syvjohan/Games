#pragma once

#include "Sprite.h"

#include <framework.h>

namespace View {
	class ExplosionAnimation {
		public:
		ExplosionAnimation();
		ExplosionAnimation(Common &common, Vec2 scale, Vec2 screen);
		~ExplosionAnimation();

		void UpdateEmitter(const float dt);
		void RenderEmitter(Renderer2D *renderer);
		void FreeMem();

		private:
		void InitAnimation(Common &common, Vec2 scale, Vec2 screen);

		Model::Animation animation;
	};
}