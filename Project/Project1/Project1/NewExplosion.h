#pragma once

#include <framework.h>

#include "Entity.h"

namespace Model {
	class ManagerModel;

		class NewExplosion : public Entity {
		public:
			NewExplosion();
			~NewExplosion();

			void OnInit(ManagerModel *m);
			void OnUpdate();

			inline EntityType Type() { return ENTITY_EXPLOSION; }
			inline  Vec2 GetPosition() const { return mPos; }

			void OnUpdateAnimation(const float dt);

			Vec2 startPosition;
			Vec2 mPos;
			Vec2 mScale;
			float mRotation;

			float mFrameTime;
			int mCurrentFrame;
			float mLifeTime;

		private:
	};
}