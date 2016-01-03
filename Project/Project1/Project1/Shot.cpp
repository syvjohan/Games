#include "Shot.h"
#include "ManagerModel.h"

namespace Model {
	Shot::Shot(Vec2 startPosition) {
		bulletParams.mPos = Vec2(startPosition.x, startPosition.y);
		bulletParams.mVel = Vec2(8, 0);
		bulletParams.mDir = Vec2(1, 0);
		bulletParams.mAcc = Vec2(1, 0);
		bulletParams.mScale = Vec2(.1, .1);
		bulletParams.mSize = Vec2(128, 128);
		bulletParams.mRotation = 0;
	}

	Shot::Shot() {}


	Shot::~Shot() {}
	
	void Shot::OnInit(ManagerModel *m) {
		Entity::OnInit(m);
	}

	void Shot::OnUpdate(const HiResTimer &timer) {
		GetModel()->OnShotMoved(this);
	}

	void Shot::OnUpdatedPhysics(const HiResTimer &timer) {
		bulletParams.mAcc += Vec2(.1f, 0);
		bulletParams.mPos += bulletParams.mVel + bulletParams.mAcc * timer.getDeltaSeconds() / 2;
	}

	bool Shot::IsDead() {
		if (isDead) {
			return true;
		}
		return false;
	}

}