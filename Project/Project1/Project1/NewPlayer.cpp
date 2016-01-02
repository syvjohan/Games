#include "NewPlayer.h"
#include "ManagerModel.h"

namespace Model {
	NewPlayer::NewPlayer() {}

	NewPlayer::~NewPlayer() {}

	void NewPlayer::OnInit(ManagerModel *m) {
		Entity::OnInit(m);

		params.mPos.y = m->GetPlayArea().x / 12;
		params.mPos.y = m->GetPlayArea().y / 2;
		params.mVel = Vec2(1, 1);
		params.mAcc = Vec2(5, 5);
		params.mDir = Vec2(0, 0);
		params.mScale = Vec2(1, 1);
		params.mRotation = 1.58f;
		params.mSize = Vec2(116, 140);
		params.mColor = Color::White;
		params.mHealth = defaultHealth;

		params.animation.mCurrentFrame = 0;
		params.animation.mFrameTime = 0.0f;
		params.animation.mFrameTimeIsHit = 0.0f;
	}

	void NewPlayer::OnUpdate(const HiResTimer &timer) {
		GetModel()->OnPlayerMoved(this);
	}

	void NewPlayer::OnUpdateFrameTimes(bool btnIsPressed) {		
		if (btnIsPressed) {
			if (params.animation.mCurrentFrame >= 3) {
				params.animation.mCurrentFrame = 3;
			} else {
				params.animation.mCurrentFrame++;
			}
			coolDown = 0;
			oldCoolDown = 0;
		} else {
			coolDown++;
			int diff = coolDown - oldCoolDown;
			if (diff >= 80) {
				if (params.animation.mCurrentFrame <= 0) {
					params.animation.mCurrentFrame = 0;
				} else {
					params.animation.mCurrentFrame--;
					oldCoolDown = coolDown;
				}
			}
		}
	}
			
	bool NewPlayer::IsDead() {
		if (params.mHealth <= 0) {
			return true;
		}
		return false;
	}
}