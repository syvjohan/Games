#include "NewAsteroid.h"
#include "ManagerModel.h"

namespace Model {
	NewAsteroid::NewAsteroid() {}

	NewAsteroid::~NewAsteroid() {}

	void NewAsteroid::OnInit(ManagerModel *m) {
		Entity::OnInit(m);

		mPos.x = m->GetPlayArea().x;
		mPos.y = InRange(0, m->GetPlayArea().y);
		mDir = Vec2(InRange(-1, -10), InRange(-2, 2));
		mVel += Vec2(InRange(.02f, .02f), 0);
		mSize = Vec2(72, 72);
		mScale = Vec2(1, 1);
		mType = 1;
		mHealth = defaulthealth;
		mRotation = 0;

		mFrameTime = 0.0f;
		mCurrentFrame = 0;
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

	void NewAsteroid::OnUpdateAnimation(const float dt) {
		mFrameTime += dt;

		if (mFrameTime >= 0.09f) {
			mFrameTime = 0.0;

			mCurrentFrame++;
			if (mCurrentFrame == 19) {
				mCurrentFrame++;
			}

			if (mCurrentFrame > 19) {
				mCurrentFrame = 0;
			}
		}
	}

	void NewAsteroid::OnUpdatePhysics(const float dt) {
		mVel += Vec2(.0005f, .0005f);
		mPos.x += mDir.x * mVel.x;
		mPos.y += mDir.y * mVel.y;
	}
}