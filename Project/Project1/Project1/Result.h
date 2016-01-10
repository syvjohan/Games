#pragma once

#include <framework.h>
#include <algorithm>

#include "Entity.h"

namespace Model {
	class MenuModel;

	class Result : public Entity {
		public:
		Result();
		~Result();

		void OnInit(MenuModel *m);
		void OnUpdate();
		bool IsDead() { return false; };

		inline EntityType Type() { return ENTITY_RESULT; }

		inline  Vec2 GetPosition() const { return mPos; }
		inline float GetRadius() const { return std::max(mSize.x / 2, mSize.y / 2); }

		void UpdateText1();
		void UpdateText2();
		void UpdateText3();

		Vec2 mPos;
		Vec2 mSize;
		Vec2 mScale;
		float mRotation;
		Color mColor;
		char *mText;
	};
}