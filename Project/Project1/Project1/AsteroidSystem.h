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

			void InitAsteroids();

			void Update(const float dt);
			void Render(Renderer2D *renderer);
			void ExtendAsteroidBelt(const float dt);
			
			void AsteroidIsHit(int index);
			std::vector<Vec4> GetAsteroidPositions();

		private:
			float r1();
			float r2();
			float InRange(float min, float max);
		
			void AddAsteroids(int length, int type, Vec2 startPosition);
			void RemoveAsteroids(int index);

			Common common;
			Vec2 playArea;

			float time;

			std::vector<Model::Asteroid> asteroids;
	};

}