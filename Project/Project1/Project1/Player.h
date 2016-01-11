#pragma once

#include <framework.h>

#include "Entity.h"
#include <algorithm>

namespace Model {
	class ManagerModel;
	class Score;

	class Player : public Entity {
		public:
			Player();
			~Player();

			void OnInit(ManagerModel *m);
			void OnUpdate();
			bool IsDead();

			inline EntityType Type() { return ENTITY_PLAYER; }

			void OnUpdateAnimation(bool btnIsPressed, const float dt);
			void OnUpdatePhysics(const float dt);

			inline  Vec2 GetPosition() const { return mPos; }
			inline float GetRadius() const { return std::max(mSize.x / 2, mSize.y / 2) * 0.8f; }

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
			const float coolDownIsHit = 1.5f;
			float mFrameTimeIsHit;
			bool isHit = false;

			const int defaultHealth = 100;

	};
}