#pragma once

#include <framework.h>

#include "Entity.h"

namespace Model {
	class MenuModel;

	class ContinueGame : public Entity {
		public:
			ContinueGame();
			~ContinueGame();

			void OnInit(MenuModel *m);
			void OnUpdate();
			inline bool IsDead() { return false; }
			void GameState(bool isGameStarted);

			inline  Vec2 GetPosition() const { return mPos; }
			inline float GetRadius() const { return 0; }

			EntityType Type() { return ENTITY_CONTINUE; }

			Vec2 mPos;
			char *mText;
			Color mColor;
			float mRotation;
			Vec2 mScale;
	};
}

