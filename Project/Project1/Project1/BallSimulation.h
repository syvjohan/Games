#pragma once

#include "Ball.h"

namespace Model {
	class BallSimulation {
		public:
			BallSimulation();
			BallSimulation(Common &common, Vec2 scale, Vec2 screen, const float boarderMargin);
			~BallSimulation();

			void InitBall(Model::Ball *b, Vec2 scale);
			void InitEmitter(Vec2 screen, Vec2 scale, const float boarderMargin);
			void InitParams(Common &common);

			Model::BallParams& getParams();
			Model::BallEmitter& getEmitter();

		private:
			void GetParams();

			float r1();
			float r2();

			float InRange(float min, float max);
			
			Model::BallParams params;
			Model::BallEmitter emitter;
	};
}

