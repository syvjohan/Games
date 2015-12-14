#pragma once

#include "Ball.h"

namespace Model {
	class BallSimulation {
		public:
			BallSimulation();
			BallSimulation(Common &common, Vec2 scale, Vec2 screen);
			~BallSimulation();

			void InitBall(Model::Ball *b, Vec2 scale);
			void InitEmitter(Vec2 screen, Vec2 scale);
			void InitParams(Common &common);

			Model::BallParams& getParams();
			Model::BallEmitter& getEmitter();

		private:
			void GetParams();
			
			Model::BallParams params;
			Model::BallEmitter emitter;
	};
}

