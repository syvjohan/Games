#pragma once

#include <framework.h>

#include "Entity.h"
#include <algorithm>

namespace Model {
	class ManagerModel;
}

namespace Model {
	class NewAsteroid : public Entity {
		public:
			NewAsteroid();
			~NewAsteroid();

			void OnInit(ManagerModel *m);
			void OnUpdate();

			inline EntityType Type() { return ENTITY_ASTEROID; }

			void OnUpdateAnimation(const float dt);
			void OnUpdatePhysics(const float dt);

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
			float mHealth;
			float mRotation;

			float mFrameTime;
			int mCurrentFrame;

		private:
			const int defaulthealth = 100;
	};	
}
