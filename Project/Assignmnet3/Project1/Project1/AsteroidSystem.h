#pragma once

#include <framework.h>
#include <vector>

#include "Asteroid.h"
#include "Defs.h"

namespace View {
	class AsteroidSystem {
		public:
		AsteroidSystem();
		AsteroidSystem(Common &common, Vec2 scale, Vec2 playArea);
		~AsteroidSystem();

		void InitAnimation(Common &common, Vec2 scale, Vec2 playArea);

		void RenderAnimation(Renderer2D *renderer);
		void UpdateAnimation(const float dt);

		private:
		float r1();
		float r2();
		float InRange(float min, float max);
		
		std::vector<Model::Asteroid> asteroids1;
		std::vector<Model::Asteroid> asteroids2;
	};

}