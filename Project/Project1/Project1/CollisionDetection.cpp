#include "CollisionDetection.h"

namespace Model {
	CollisionDetection::CollisionDetection() {}


	CollisionDetection::~CollisionDetection() {}

	PairCollision CollisionDetection::AsteroidAndBullet(std::vector<Vec4> bullets, std::vector<Vec4> asteroids) {
		PairCollision pair = { -1, -1 };
		int i = 0;
		int k = 0;
		for (auto it = bullets.begin(); it != bullets.end(); ++it, ++k) {
			for (auto it2 = asteroids.begin(); it2 != asteroids.end(); ++it2, ++i) {

				Vec2 bullet(it->x, it->y);
				Vec2 asteroid(it2->x, it2->y);

				if (bullet.x + (it->w * .15f) > asteroid.x) {
					pair.first = i;
					pair.second = k;
					return pair;
				}
			}
		}
		return pair;
	}
}