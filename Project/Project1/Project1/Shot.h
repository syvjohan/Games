#pragma once

#include <framework.h>

#include "Entity.h"
#include <algorithm>

namespace Model {
	class ManageModel;

	class Shot : public Entity {
		public:
			Shot();
			~Shot();

			void OnInit(ManagerModel *m);
			void OnUpdate();
			bool IsDead();

			inline EntityType Type() { return ENTITY_BULLET; }

			void OnUpdatedPhysics(const float dt);

			Vec2 startPosition;

			inline  Vec2 GetPosition() const { return mPos; }
			inline float GetRadius() const { return std::max(mSize.x / 2, mSize.y / 2); }

			Vec2 mPos;
			Vec2 mVel;
			Vec2 mAcc;
			Vec2 mDir;
			Vec2 mSize;
			Vec2 mScale;
			float mRotation;
			bool isDead;

		private:
	};
}
