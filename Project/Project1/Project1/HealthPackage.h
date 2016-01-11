#pragma once

#include <framework.h>

#include "Entity.h"
#include <algorithm>

namespace Model {
	class ManagerModel;

	class HealthPackage : public Entity {
		public:
		HealthPackage();
		~HealthPackage();

		void OnInit(ManagerModel *m);
		void OnUpdate();
		bool IsDead() { return false; };

		inline EntityType Type() { return ENTITY_HEALTHPACKAGE; }

		void OnUpdateAnimation(const float dt);
		void OnUpdatePhysics(const float dt);
		void Cleavage(Vec2 startPosition, Vec2 scale);

		float InRange(float min, float max);
		float r1();

		inline  Vec2 GetPosition() const { return mPos; }
		inline float GetRadius() const { return std::max((mSize.x * mScale.x) / 2, (mSize.y * mScale.y) / 2); }

		void SetType(int type);

		Vec2 mPos;
		Vec2 mDir;
		Vec2 mVel;
		Vec2 mSize;
		Vec2 mScale;
		float mRotation;
		Color mColor;
	};
}
