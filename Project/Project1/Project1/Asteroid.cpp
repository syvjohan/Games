#include "Asteroid.h"
#include "ManagerModel.h"

namespace Model {
	Asteroid::Asteroid() {}

	Asteroid::~Asteroid() {}

	void Asteroid::OnInit(ManagerModel *m) {
		Entity::OnInit(m);

		mPos.x = m->GetPlayArea().x;
		mPos.y = InRange(0, m->GetPlayArea().y);
		mDir = Vec2(InRange(-1, -10), InRange(-2, 2));
		mVel += Vec2(InRange(.02f, .02f), 0);
		mScale = Vec2(1, 1);
		mHealth = defaulthealth;
		mRotation = 0;

		mFrameTime = 0.0f;
		mCurrentFrame = 0;
	}

	void Asteroid::SetType(int type) {
		switch (type) {
			case 1:
				mSize = Vec2(72, 72);
				break;
			case 2:
				mSize = Vec2(64, 64);
				break;
			case 3:
				mSize = Vec2(32, 32);
				break;
			case 4:
				mSize = Vec2(32, 32);
				break;
			case 5:
				mSize = Vec2(72, 72);
				break;
			case 6:
				mSize = Vec2(64, 64);
				break;
		}
		mType = type;
	}

	float Asteroid::InRange(float min, float max) {
		return min + (max - min) * r1();
	}

	float Asteroid::r1() {
		return (float)(rand() % 10001) / 10000.0f;
	}

	void Asteroid::OnUpdate() {
		GetModel()->OnAsteroidMoved(this);
	}

	void Asteroid::OnUpdateAnimation(const float dt) {
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

	void Asteroid::OnUpdatePhysics(const float dt) {
		mVel += Vec2(.0005f, .0005f);
		mPos.x += mDir.x * mVel.x;
		mPos.y += mDir.y * mVel.y;
	}

	void Asteroid::Cleavage(Vec2 startPosition, Vec2 scale) {
		if (startPosition.x != 0 && startPosition.y != 0) {
			mPos = startPosition;
			mHealth /= 2;
		}
		mScale = scale;
	}

	bool Asteroid::IsDead() {
		if (mHealth <= 0) {
			return true;
		}
		return false;
	}
}