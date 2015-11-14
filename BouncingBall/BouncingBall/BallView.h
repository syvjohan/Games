#pragma once

#include "Camera.h"
#include "BallSimulation.h"

class BallView {
	public:
		BallView();
		~BallView();

		void Draw();

	private:
		Camera *camera;
		BallSimulation *ballSimulation;
};

