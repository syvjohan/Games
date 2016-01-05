#pragma once

#include <framework.h>
#include <algorithm>

#include "Entity.h"

namespace Model {
	class ManagerModel;

		class NewExplosion : public Entity {
		public:
			NewExplosion();
			~NewExplosion();

			void OnInit(ManagerModel *m);
			void OnUpdate();
			bool IsDead();

			inline EntityType Type() { return ENTITY_EXPLOSION; }

			inline  Vec2 GetPosition() const { return mPos; }
			inline float GetRadius() const { return std::max(mSize.x / 2, mSize.y / 2); }

			void OnUpdateAnimation(const float dt);

			Vec2 startPosition;
			Vec2 mPos;
			Vec2 mSize;
			Vec2 mScale;
			float mRotation;

			float mFrameTime;
			int mCurrentFrame;
			int mLifeTime;
	};
}