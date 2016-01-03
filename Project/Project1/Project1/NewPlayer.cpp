#include "NewPlayer.h"
#include "ManagerModel.h"

namespace Model {
	NewPlayer::NewPlayer() {}

	NewPlayer::~NewPlayer() {}

	void NewPlayer::OnInit(ManagerModel *m) {
		Entity::OnInit(m);

		planeParams.mPos.y = m->GetPlayArea().x / 12;
		planeParams.mPos.y = m->GetPlayArea().y / 2;
		planeParams.mVel = Vec2(1, 1);
		planeParams.mAcc = Vec2(5, 5);
		planeParams.mDir = Vec2(0, 0);
		planeParams.mScale = Vec2(1, 1);
		planeParams.mRotation = 1.58f;
		planeParams.mSize = Vec2(116, 140);
		planeParams.mColor = Color::White;
		planeParams.mHealth = defaultHealth;

		planeParams.animation.mCurrentFrame = 0;
		planeParams.animation.mFrameTime = 0.0f;
		planeParams.animation.mFrameTimeIsHit = 0.0f;
	}

	void NewPlayer::OnUpdate() {
		GetModel()->OnPlayerMoved(this);
	}

	void NewPlayer::OnUpdatePlayerPhysics(const float dt) {
		planeParams.mPos.x += planeParams.mDir.x * planeParams.mAcc.x * dt;
		planeParams.mPos.y += planeParams.mDir.y * planeParams.mAcc.y * dt;
	}

	void NewPlayer::OnUpdateAnimation(bool btnIsPressed, const float dt) {
		frameTimePlane += dt;
		if (btnIsPressed) {
			if (planeParams.animation.mCurrentFrame >= 3) {
				planeParams.animation.mCurrentFrame = 3;
			} else {
				planeParams.animation.mCurrentFrame++;
			}
			/*coolDown = 0;
			oldCoolDown = 0;*/
		} else {
			if (frameTimePlane > 0.8) {
				if (planeParams.animation.mCurrentFrame <= 0) {
					planeParams.animation.mCurrentFrame = 0;
				} else {
					planeParams.animation.mCurrentFrame--;
					frameTimePlane = 0;
				}
			} 

			/*coolDown++;
			int diff = coolDown - oldCoolDown;
			if (diff >= 80) {
				if (planeParams.animation.mCurrentFrame <= 0) {
					planeParams.animation.mCurrentFrame = 0;
				} else {
					planeParams.animation.mCurrentFrame--;
					oldCoolDown = coolDown;
				}
			}*/
		}
	}
			
	bool NewPlayer::IsDead() {
		if (planeParams.mHealth <= 0) {
			return true;
		}
		return false;
	}
}