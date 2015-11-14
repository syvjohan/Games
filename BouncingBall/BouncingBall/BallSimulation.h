#pragma once

#include "Ball.h"

class BallSimulation {
	public:
		BallSimulation();
		~BallSimulation();
		bool collision();

		void Update();

		void SetPosition();

		void MoveLeft();
		void MoveRight();
		void MoveUp();
		void MoveDown();

	private:
		Ball *ball;
};