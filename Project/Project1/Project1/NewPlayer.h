#pragma once

#include <framework.h>

#include "Entity.h"
#include <algorithm>

namespace Model {
	class ManagerModel;

	class NewPlayer : public Entity {
		public:
			NewPlayer();
			~NewPlayer();

			void OnInit(ManagerModel *m);
			void OnUpdate();

			inline EntityType Type() { return ENTITY_PLAYER; }

			void OnUpdateAnimation(bool btnIsPressed, const float dt);
			void OnUpdatePhysics(const float dt);

			inline  Vec2 GetPosition() const { return mPos; }
			inline float GetRadius() const { return std::max(mSize.x / 2, mSize.y / 2) * 0.8f; }
		
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
			float mFrameTimeIsHit;

		private:
			const int defaultHealth = 100;
			float oldTime = 80;
	};
}