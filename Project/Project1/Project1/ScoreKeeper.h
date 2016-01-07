#pragma once

#include <framework.h>

#include "Entity.h"

namespace Model {
	class ScoreKeeper : public Entity {
		public:
		ScoreKeeper();
		~ScoreKeeper();

		void OnInit(ManagerModel *m);
		void OnUpdate();
		inline bool IsDead() { return false; }

		inline  Vec2 GetPosition() const { return mPos; }
		inline float GetRadius() const { return 0; }

		inline EntityType Type() { return ENTITY_SCORE; }

		Vec2 mPos;
		char mText[128];
		Color mColor;
		float mRotation;
		Vec2 mScale;

		int mScore;

		private:
		ManagerModel* mModel;
	};
}

