#pragma once

#include <framework.h>

#include "Entity.h"

namespace Model {
	class ManagerModel;

	struct AsteroidAnimation {
		float mFrameTime;
		int mCurrentFrame;
	};

	struct AsteroidParams {
		Vec2 mPos;
		Vec2 mDir;
		Vec2 mVel;

		Vec2 mSize;
		Vec2 mScale;
		int mType;
		float mHealth;
		float mRotation;

		AsteroidAnimation animation;
	};
}

namespace Model {
	class NewAsteroid : public Entity {
		public:
		NewAsteroid();
		~NewAsteroid();

		void OnInit(ManagerModel *m);
		void OnUpdate();
		bool IsDead();

		inline EntityType Type() { return ENTITY_ASTEROID; }

		void OnUpdateFrameTimes(const float dt);
		void OnUpdatePhysics(const float dt);

		float InRange(float min, float max);
		float r1();

		AsteroidParams asteroidParams;

		private:
		const int defaulthealth = 100;
	};
}
