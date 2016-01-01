#pragma once

#include "Defs.h"
#include "Plane.h"
#include "ExplosionAnimation.h"

#include <framework.h>

namespace View {
	class Player {
		public:
			Player();
			Player(Common *common, Vec2 scale, Vec2 playArea);
			~Player();

			void Update(const float dt, float BoarderMargin);
			void Render(Renderer2D *renderer);

			void Move(int dir);

			Vec2 GetFirePosition();
			Vec4 GetPosition();
			int GetHealth();
			void IsHit(int  i);

		private:
			void Init(Vec2 scale, Vec2 playArea);
			void Animation(const float dt);

			void UpdateExplosion(const float dt);
			void RenderExplosion(Renderer2D *renderer);

			int btnUp = 0; //4 steps.
			int btnDown = 0; //4 steps.
			int btnBack = 0; //4 steps.
			int btnForward = 0; //4 steps.

			const int defaultHealth = 100;

			Model::Plane player;
			View::ExplosionAnimation *explosion;
			Common *common;
	};
}

