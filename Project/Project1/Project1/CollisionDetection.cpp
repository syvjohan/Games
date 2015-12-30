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

				float asteroidRadius = std::max(it->w / 2.0f, it->z / 2.0f);
				float bulletRadius = std::max(it2->w / 2.0f, it2->z / 2.0f);

				Vec2 bullet(it->x, it->y);
				Vec2 asteroid(it2->x, it2->y);

				Vec2 diff = asteroid - bullet;

				if (Vec2::length(diff) < asteroidRadius + bulletRadius) {
					pair.first = i;
					pair.second = k;
					return pair;
				}
			}
		}
		return pair;
	}
}