#pragma once

#include "Defs.h"
#include "Bullet.h"

#include <framework.h>

namespace View {
	class ShootSystem {
		public:
			ShootSystem();
			ShootSystem(Common *common, Vec2 playArea);
			~ShootSystem();

			void AddBullet(Vec2 scale, Vec2 startPosition);
			void Update(const float dt);
			void Render(Renderer2D *renderer);
			void RemoveBullet(int index);

			std::vector<Vec4> GetBulletsPositions();

		private:
			void InitBullet(Model::Bullet *p, Vec2 scale);
			void Init(Common &common, Vec2 scale, Vec2 playArea);

			void SoundEffect();

			AudioSource *source;
			Vec2 playArea;
			Common *common;

			std::vector<Model::Bullet> bullets;
	};
}
