#pragma once

#include <framework.h>

#include "Entity.h"
#include <algorithm>

namespace Model {
	class ManagerModel;

	class EnemieBoss : public Entity {
		public:
		EnemieBoss();
		~EnemieBoss();

		void OnInit(ManagerModel *m);
		void OnUpdate();
		bool IsDead();

		inline EntityType Type() { return ENTITY_ENEMIEBOSS; }

		void OnUpdateAnimation(const float dt, bool isUpdate);
		void OnUpdatePhysics(const float dt);

		inline  Vec2 GetPosition() const { return mPos; }
		inline float GetRadius() const { return std::max(mSize.x / 2, mSize.y / 2); }

		void Hit();

		Vec2 mPos;
		Vec2 mVel;
		Vec2 mAcc;
		Vec2 mDir;
		Vec2 mScale;
		Vec2 mSize;
		float mRotation;
		int mHealth;
		Color mColor;

		float mFrameTime;
		int mCurrentFrame;
		const float coolDownIsHit = 1;
		float mFrameTimeIsHit;
		bool isHit = false;

		const float mMoveTime = 3;
		float mCurrentMoveTime = mMoveTime;
		const float pauseMoveTime = 4;
		float mCurrentPauseTime = pauseMoveTime;

		const float delayAnimation = 0.7f;
		float timeAnimation = delayAnimation;
		bool isPaused = false;

		int countRounds = 0;

		const int defaultHealth = 100;
	};
}

