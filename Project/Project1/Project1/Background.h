#pragma once

#include <framework.h>
#include <algorithm>

#include "Entity.h"

namespace Model {
	class MenuModel;

	class Background : public Entity {
		public:
			Background();
			~Background();
			void OnInit(MenuModel *m);
			void OnUpdate();
			inline bool IsDead() { return false; }

			inline  Vec2 GetPosition() const { return mPos; }
			inline float GetRadius() const { return std::max(mSize.x / 2, mSize.y / 2); }

			inline EntityType Type() { return ENTITY_BACKGROUND_MENU; }

			void OnUpdatePhysics(const float dt);

			Vec2 mPos;
			Vec2 mVel;
			Vec2 mDir;
			char *mText;
			Color mColor;
			float mRotation;
			Vec2 mScale;
			Vec2 mSize;
	};
}

