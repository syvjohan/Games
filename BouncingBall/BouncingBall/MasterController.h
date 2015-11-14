#pragma once

#include "BallSimulation.h"
#include "BallView.h"

class MasterController {
	public:
		MasterController();
		~MasterController();

	private:
		BallSimulation *ballSimulation;
		BallView *ballView;
};

