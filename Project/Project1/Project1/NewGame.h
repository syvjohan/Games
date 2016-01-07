#pragma once

#include <framework.h>

#include "Entity.h"

namespace Model {
	class MenuModel;

	class NewGame : public Entity {
		public:
			NewGame();
			~NewGame();

			void OnInit(MenuModel *m);
			void OnUpdate();
			inline bool IsDead() { return false; }

			inline  Vec2 GetPosition() const { return mPos; }
			inline float GetRadius() const { return 0; }
			
			inline EntityType Type() { return ENTITY_NEWGAME; }

			Vec2 mPos;
			char *mText;
			Color mColor;
			float mRotation;
			Vec2 mScale;

		private:
			MenuModel* mModel;
	};
}
