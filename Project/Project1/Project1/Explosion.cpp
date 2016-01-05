#include "Explosion.h"
#include "ManagerModel.h"

namespace Model {
	Explosion::Explosion() {}

	Explosion::~Explosion() {}

	void Explosion::OnInit(ManagerModel *m) {
		Entity::OnInit(m);

		mPos = startPosition;
		mSize = Vec2(128, 128);
		mScale = Vec2(1, 1);
		mRotation = 0.0f;

		mFrameTime = 0.0f;
		mCurrentFrame = 0.0f;
		mLifeTime = 24;
	}

	void Explosion::OnUpdate() {
		GetModel()->OnExplosionMoved(this);
	}

	void Explosion::OnUpdateAnimation(const float dt) {
		mFrameTime += dt;

		if (mFrameTime >= 0.021) {
			mFrameTime = 0.0;
			mCurrentFrame++;

			mLifeTime--;

			if (mCurrentFrame > 24) {
				mCurrentFrame = 0;
			}
		}
	}

	bool Explosion::IsDead() {
		if (mLifeTime <= 0) {
			return true;
		}
		return false;
	}
}