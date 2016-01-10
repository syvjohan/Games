#pragma once

#include <framework.h>
#include <algorithm>

#include "Entity.h"

namespace Model {
	class MenuModel;

	class BackgroundAfterGame : public Entity {
		public:
		BackgroundAfterGame();
		~BackgroundAfterGame();

		void OnInit(MenuModel *m);
		void OnUpdate();
		bool IsDead() { return false; };

		inline EntityType Type() { return ENTITY_BACKGROUND_AFTER_GAME; }

		inline  Vec2 GetPosition() const { return mPos; }
		inline float GetRadius() const { return std::max(mSize.x / 2, mSize.y / 2); }

		Vec2 mPos;
		Vec2 mSize;
		Vec2 mScale;
		float mRotation;
		Color mColor;
	};
}