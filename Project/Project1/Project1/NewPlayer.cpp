#include "NewPlayer.h"
#include "ManagerModel.h"

namespace Model {
	NewPlayer::NewPlayer() {}

	NewPlayer::~NewPlayer() {}

	void NewPlayer::OnInit(ManagerModel *m) {
		Entity::OnInit(m);

		mPos.y = m->GetPlayArea().x / 12;
		mPos.y = m->GetPlayArea().y / 2;
		mVel = Vec2(1, 1);
		mAcc = Vec2(5, 5);
		mDir = Vec2(0, 0);
		mScale = Vec2(1, 1);
		mRotation = 1.58f;
		mSize = Vec2(116, 140);
		mColor = Color::White;
		mHealth = defaultHealth;

		mCurrentFrame = 0;
		mFrameTime = 0.0f;
		mFrameTimeIsHit = 0.0f;
	}

	void NewPlayer::OnUpdate() {
		GetModel()->OnPlayerMoved(this);
		char buffer[128];
		sprintf(buffer, "(%.2f, %.2f)\n", mPos.x, mPos.y);
		OutputDebugString(buffer);
	}

	void NewPlayer::OnUpdatePhysics(const float dt) {
		mPos.x += mDir.x * mAcc.x * dt;
		mPos.y += mDir.y * mAcc.y * dt;
	}

	void NewPlayer::OnUpdateAnimation(bool btnIsPressed, const float dt) {
		mFrameTime += dt; //cooldown.
		if (btnIsPressed) {
			if (mCurrentFrame >= 3) {
				mCurrentFrame = 3;
			} else {
				mCurrentFrame++;
			}
			mFrameTime = 0;
			mFrameTime = 0;
		} else {
			if (mFrameTime > 0.4f) {
				if (mCurrentFrame > 0) {
					mCurrentFrame--;
				} else {
					mCurrentFrame = 0;
				}
				mFrameTime = 0;
			} 
		}
	}
}