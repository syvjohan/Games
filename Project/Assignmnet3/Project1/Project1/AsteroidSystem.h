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

			void InitAnimation();

			void RenderAsteroids(Renderer2D *renderer);
			void UpdateAsteroids(const float dt);
		
			void ExtendAsteroidBelt(const float dt);

		private:
			float r1();
			float r2();
			float InRange(float min, float max);
		
			void AddAsteroids(int length, int type);
			void Update(const float dt, std::vector<Model::Asteroid> &container);
			void Render(Renderer2D *renderer, std::vector<Model::Asteroid> &container);

			Common common;
			Vec2 scale;
			Vec2 playArea;

			float time;

			std::vector<Model::Asteroid> asteroids1;
			std::vector<Model::Asteroid> asteroids2;
			std::vector<Model::Asteroid> asteroids3;
			std::vector<Model::Asteroid> asteroids4;
			std::vector<Model::Asteroid> asteroids5;
			std::vector<Model::Asteroid> asteroids6;
	};

}