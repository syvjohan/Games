#include "Shot.h"
#include "ManagerModel.h"

namespace Model {
	Shot::Shot() {}

	Shot::~Shot() {}
	
	void Shot::OnInit(ManagerModel *m) {
		Entity::OnInit(m);

		mPos = Vec2(startPosition.x, startPosition.y);
		mVel = Vec2(8, 0);
		mDir = Vec2(1, 0);
		mAcc = Vec2(1, 0);
		mScale = Vec2(.1, .1);
		mSize = Vec2(128, 128);
		mRotation = 0;
	}

	void Shot::OnUpdate() {
		GetModel()->OnShotMoved(this);
	}

	void Shot::OnUpdatedPhysics(const float dt) {
		mAcc += Vec2(.1f, 0);
		mPos += mVel + mAcc * dt / 2;
	}

	bool Shot::IsDead() {
		return isDead;
	}
}