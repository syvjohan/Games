#pragma once
#include <framework.h>

#include "Entity.h"

namespace Model {
	class Controlls : public Entity {
		public:
			Controlls();
			~Controlls();

			void OnInit(MenuModel *m);
			void OnUpdate();
			inline bool IsDead() { return false; }

			inline  Vec2 GetPosition() const { return mPos; }
			inline float GetRadius() const { return 0; }

			inline EntityType Type() { return ENTITY_CONTROLLS; }

			Vec2 mPos;
			char *mText;
			Color mColor;
			float mRotation;
			Vec2 mScale;
	};
}

