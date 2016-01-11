#include "EnemieBossShot.h"
#include "ManagerModel.h"

namespace Model {
	EnemieBossShot::EnemieBossShot() {}

	EnemieBossShot::~EnemieBossShot() {}

	void EnemieBossShot::OnInit(ManagerModel *m) {
		Entity::OnInit(m);

		mPos = Vec2(startPosition.x + -10, startPosition.y + 60);
		mVel = Vec2(15, 0);
		mDir = Vec2(1, 0);
		mAcc = Vec2(15, 0);
		mScale = Vec2(.1, .1);
		mSize = Vec2(128, 128);
		mColor = Color::YellowGreen;
		mRotation = 0;
	}

	void EnemieBossShot::OnUpdate() {
		GetModel()->OnEnemieBossShotMoved(this);
	}

	void EnemieBossShot::OnUpdatedPhysics(const float dt) {
		mAcc += Vec2(5, 0);
		mPos -= mVel + mAcc * dt / 2;
	}

	bool EnemieBossShot::IsDead() {
		return isDead;
	}
}
