#pragma once

#include <framework.h>

#include "Entity.h"

namespace Model {
	class ManageModel;

	struct BulletParams {
		Texture2D *mTexture;
		Vec2 mPos;
		Vec2 mVel;
		Vec2 mAcc;
		Vec2 mDir;
		Vec2 mSize;
		Vec2 mScale;
		float mRotation;
	};

	class Shot : public Entity {
		public:
		Shot(Vec2 startPosition);
		Shot();
		~Shot();

		void OnInit(ManagerModel *m);
		void OnUpdate(const HiResTimer &timer);
		bool IsDead();

		inline EntityType Type() { return ENTITY_BULLET; }

		void OnUpdatedPhysics(const HiResTimer &timer);

		BulletParams bulletParams;

		bool isDead;
	};
}
