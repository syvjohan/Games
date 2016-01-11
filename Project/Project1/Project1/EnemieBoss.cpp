#include "EnemieBoss.h"
#include "ManagerModel.h"

namespace Model {
	EnemieBoss::EnemieBoss() {}

	EnemieBoss::~EnemieBoss() {}

	void EnemieBoss::OnInit(ManagerModel *m) {
		Entity::OnInit(m);
		
		mVel = Vec2(7, 7);
		mAcc = Vec2(7, 7);
		mDir = Vec2(1, 1);
		mScale = Vec2(1, 1);
		mRotation = 4.71f;
		mSize = Vec2(116, 140);
		mPos.x = m->GetPlayArea().x - (mSize.x * 4);
		mPos.y = m->GetPlayArea().y / 2;
		mColor = Color::Aquamarine;
		mHealth = defaultHealth;

		mCurrentFrame = 0;
		mFrameTime = 0.0f;
		mFrameTimeIsHit = coolDownIsHit;
	}

	void EnemieBoss::OnUpdate() {
		GetModel()->OnEnemieBossMoved(this);
	}

	void EnemieBoss::OnUpdatePhysics(const float dt) {
		if (dt < 2.0f) {
			mCurrentMoveTime -= dt;
			if (mCurrentMoveTime >= 0) {
				mCurrentPauseTime = pauseMoveTime;
				mPos.x += mDir.x * mAcc.x * mVel.x * dt;
				mPos.y += mDir.y * mAcc.y * mVel.y * dt;
			}

			if (mCurrentMoveTime < 0) {
				mCurrentPauseTime -= dt;
				if (mCurrentPauseTime <= 0) { 
					++countRounds;
					if (countRounds <= 2) {
						mDir.x = -1;
						mDir.y = -1;
					} else if (countRounds > 2 && countRounds <= 4) {
						mDir.x = 1;
						mDir.y = 1;
					} else if (countRounds > 4 && countRounds <= 6) {
						mDir.x = -1;
						mDir.y = -1;
					} else if (countRounds > 6 && countRounds <= 8) {
						mDir.x = 0;
						mDir.y = 1;
					} else if (countRounds > 8 && countRounds <= 9) {
						mDir.x = 0;
						mDir.y = -1;
					} else if(countRounds > 9 && countRounds <= 10) {
						mDir.x = 1;
						mDir.y = 0;
					} else {
						mDir.x = 1;
						mDir.y = 1;
						countRounds = 0;
					}
					mCurrentMoveTime = mMoveTime;
					isPaused = false;
				} else {
					isPaused = true;
				}
			}
		}
	}

	void EnemieBoss::OnUpdateAnimation(const float dt, bool isUpdate) {
		if (dt < 2.0f) {
			mFrameTime += dt; //cooldown.
			if (isUpdate && !isPaused) {
				if (mCurrentFrame >= 3) {
					mCurrentFrame = 3;
				} else {
					mCurrentFrame++;
				}
				mFrameTime = 0;
				mFrameTime = 0;
			} 

			if (isPaused) {
				if (mFrameTime > 0.3f) {
					if (mCurrentFrame > 0) {
						mCurrentFrame--;
					} else {
						mCurrentFrame = 0;
					}
					mFrameTime = 0;
				}
			}

			if (isHit && mFrameTimeIsHit > 0) {
				mFrameTimeIsHit -= dt;
			} else if (isHit && mFrameTimeIsHit <= 0) {
				if (mFrameTimeIsHit <= 0) {
					mFrameTimeIsHit = 0;
					mColor = Color::Aquamarine;
				}
			}
		}
	}

	void EnemieBoss::Hit() {
		isHit = true;
		mHealth = defaultHealth / 2;
		mColor = Color::Red;
	}

	bool EnemieBoss::IsDead() {
		if (mHealth <= 0) {
			return true;
		}
		return false;
	}
}
