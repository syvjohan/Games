#include "NewAsteroid.h"
#include "ManagerModel.h"

namespace Model {
	NewAsteroid::NewAsteroid() {}

	NewAsteroid::~NewAsteroid() {}

	void NewAsteroid::OnInit(ManagerModel *m) {
		Entity::OnInit(m);

		asteroidParams.mPos.x = m->GetPlayArea().x;
		asteroidParams.mPos.y = InRange(0, m->GetPlayArea().y);
		asteroidParams.mDir = Vec2(InRange(-1, -10), InRange(-1, 1));
		asteroidParams.mVel += Vec2(InRange(.2f, .2f), 0);
		asteroidParams.mSize = Vec2(72, 72);
		asteroidParams.mScale = Vec2(1, 1);
		asteroidParams.mType = 1;
		asteroidParams.mHealth = defaulthealth;
		asteroidParams.mRotation = 0;

		asteroidParams.animation.mFrameTime = 0.0f;
		asteroidParams.animation.mCurrentFrame = 0;
	}

	float NewAsteroid::InRange(float min, float max) {
		return min + (max - min) * r1();
	}

	float NewAsteroid::r1() {
		return (float)(rand() % 10001) / 10000.0f;
	}

	void NewAsteroid::OnUpdate() {
		GetModel()->OnAsteroidMoved(this);
	}

	bool NewAsteroid::IsDead() {
		return false;
	}

	void NewAsteroid::OnUpdateFrameTimes(const float dt) {
		asteroidParams.animation.mFrameTime += dt;

		if (asteroidParams.animation.mFrameTime >= 0.00028) {
			asteroidParams.animation.mFrameTime = 0.0;

			asteroidParams.animation.mCurrentFrame++;
			if (asteroidParams.animation.mCurrentFrame == 19) {
				asteroidParams.animation.mCurrentFrame++;
			}

			if (asteroidParams.animation.mCurrentFrame > 19) {
				asteroidParams.animation.mCurrentFrame = 0;
			}
		}
	}

	void NewAsteroid::OnUpdatePhysics(const float dt) {
		asteroidParams.mVel += Vec2(.0005f, .0005f);
		asteroidParams.mPos.x += asteroidParams.mDir.x * asteroidParams.mVel.x;
		asteroidParams.mPos.y += asteroidParams.mDir.y * asteroidParams.mVel.y;
	}
}