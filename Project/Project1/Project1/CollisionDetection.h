#pragma once

#include <vector>
#include <framework.h>
#include <algorithm>

#include "Asteroid.h"

struct PairCollision {
	int first;
	int second;
};

namespace Model {
	class CollisionDetection {
		public:
		CollisionDetection();
		~CollisionDetection();

		PairCollision AsteroidAndBullet(std::vector<Vec4> bullets, std::vector<Vec4> asteroids);
	
	};
}

