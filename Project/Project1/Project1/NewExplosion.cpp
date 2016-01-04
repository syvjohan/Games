#include "NewExplosion.h"
#include "ManagerModel.h"

namespace Model {
	NewExplosion::NewExplosion() {}

	NewExplosion::~NewExplosion() {}

	void NewExplosion::OnInit(ManagerModel *m) {
		Entity::OnInit(m);

		mPos = startPosition;
		mScale = Vec2(1, 1);
		mRotation = 0.0f;

		mFrameTime = 0.0f;
		mCurrentFrame = 0.0f;
		mLifeTime = 24.0f;
	}

	void NewExplosion::OnUpdate() {
		//GetModel()->OnShotMoved(this);
	}

	void NewExplosion::OnUpdateAnimation(const float dt) {
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
}