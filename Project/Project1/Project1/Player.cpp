#include "Player.h"
#include "ManagerModel.h"

namespace Model {
	Player::Player() {}

	Player::~Player() {}

	void Player::OnInit(ManagerModel *m) {
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
		mFrameTimeIsHit = 1.5f;
	}

	void Player::OnUpdate() {
		GetModel()->OnPlayerMoved(this);
	}

	void Player::OnUpdatePhysics(const float dt) {
		mPos.x += mDir.x * mAcc.x * dt;
		mPos.y += mDir.y * mAcc.y * dt;
	}

	void Player::OnUpdateAnimation(bool btnIsPressed, const float dt) {
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

		if (isHit && mFrameTimeIsHit > 0) {
			mFrameTimeIsHit -= dt;
		} else if(isHit && mFrameTimeIsHit <= 0) {
			if (mFrameTimeIsHit <= 0) {
				mFrameTimeIsHit = 0;
				mColor = Color::White;
			}
		}
	}

	void Player::Hit() {
		isHit = true;
		mHealth = defaultHealth / 2;
		mColor = Color::Red;
	}

	bool Player::IsDead() {
		if (mHealth >= 0) {
			return true;
		}
		return false;
	}
}