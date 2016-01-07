#pragma once
#include <framework.h>

#include "Entity.h"

namespace Model {
	class Instructions : public Entity {
		public:
		Instructions();
		~Instructions();

		void OnInit(MenuModel *m);
		void OnUpdate();
		inline bool IsDead() { return false; }

		inline  Vec2 GetPosition() const { return mPos; }
		inline float GetRadius() const { return 0; }

		virtual EntityType Type() { return ENTITY_CONTROLLS; }

		Vec2 mPos;
		char *mText;
		Color mColor;
		float mRotation;
		Vec2 mScale;
	};
}

