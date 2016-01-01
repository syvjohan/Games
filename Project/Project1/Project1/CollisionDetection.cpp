#include "CollisionDetection.h"

namespace Model {
	CollisionDetection::CollisionDetection() {}

	CollisionDetection::~CollisionDetection() {}

	PairCollision CollisionDetection::AsteroidAndBullet(std::vector<Vec4> bullets, std::vector<Vec4> asteroids) {
		PairCollision pair = { -1, -1 };
		if (asteroids.size() != 0 && bullets.size() != 0) {
			for (auto &it : asteroids) {
				for (auto &it2 : bullets) {
					float asteroidRadius = std::max(it2.w / 2.0f, it2.z / 2.0f);
					float bulletRadius = std::max(it.w / 2.0f, it.z / 2.0f);

					Vec2 bullet(it.x, it.y);
					Vec2 asteroid(it2.x, it2.y);

					Vec2 diff = asteroid - bullet;

					if (Vec2::length(diff) < asteroidRadius + bulletRadius) {
						pair.first = &it - &(*asteroids.begin());
						pair.second = &it2 - &(*bullets.begin());
						return pair;
					}
				}
			}
		}
		return pair;
	}

	PairCollision CollisionDetection::AsteroidAndPlayer(Vec4 player, std::vector<Vec4> asteroids) {
		PairCollision pair = { -1, -1 };
		int countIt = 0;
		for (auto &it : asteroids) {
			++countIt;
			float asteroidRadius = std::max(it.w / 2.0f, it.z / 2.0f);
			float playerRadius = std::max(player.w / 2.0f, player.z / 2.0f);

			Vec2 player(player.x, player.y);
			Vec2 asteroid(it.x, it.y);

			Vec2 diff = asteroid - player;

			if (Vec2::length(diff) < asteroidRadius + playerRadius) {
				pair.first = &it - &(*asteroids.begin());
				pair.second = 1;
				return pair;
			}
		}
		return pair;
	}
}