#pragma once

#include <framework.h>

#include "Entity.h"
#include <algorithm>

namespace Model {
	class ManagerModel;
}

namespace Model {
	class Asteroid : public Entity {
		public:
			Asteroid();
			~Asteroid();

			void OnInit(ManagerModel *m);
			void OnUpdate();
			bool IsDead();

			inline EntityType Type() { return ENTITY_ASTEROID; }

			void OnUpdateAnimation(const float dt);
			void OnUpdatePhysics(const float dt);
			void Cleavage(Vec2 startPosition, float scale);

			float InRange(float min, float max);
			float r1();

			inline  Vec2 GetPosition() const { return mPos; }
			inline float GetRadius() const { return std::max(mSize.x / 2, mSize.y / 2); }
		
			Vec2 mPos;
			Vec2 mDir;
			Vec2 mVel;
			Vec2 mSize;
			Vec2 mScale;
			int mType;
			int mHealth;
			float mRotation;

			float mFrameTime;
			int mCurrentFrame;

			const int defaulthealth = 100;
	};	
}
