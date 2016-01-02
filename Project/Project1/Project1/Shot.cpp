#include "Shot.h"
#include "ManagerModel.h"

namespace Model {
	Shot::Shot() {}


	Shot::~Shot() {}
	
	void Shot::OnInit(ManageModel *m) {
		Entity::OnInit(m);

		bulletParams.mPos = Vec2(0, 0);
		bulletParams.mVel = Vec2(10, 0);
		bulletParams.mDir = Vec2(10, 0);
		bulletParams.mAcc = Vec2(1, 0);
		bulletParams.mScale = Vec2(1, 1);
		bulletParams.mSize = Vec2(128, 128);
		bulletParams.mRotation = 0;


	}

	void Shot::OnUpdate(const HiResTimer &timer) {
		GetModel()->OnPlayerMoved(this);
	}

	bool Shot::IsDead() {
		if (isDead) {
			return true;
		}
		return false;
	}

}