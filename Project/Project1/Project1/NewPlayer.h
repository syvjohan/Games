#pragma once

#include <framework.h>

#include "Entity.h"

namespace Model {
	class ManagerModel;

	struct Animation { 
		float mFrameTime;
		int mCurrentFrame;

		float mFrameTimeIsHit;
	};

	struct PlaneParams {
		Texture2D *mTexture;
		Vec2 mPos;
		Vec2 mVel;
		Vec2 mAcc;
		Vec2 mDir;
		Vec2 mScale;
		Vec2 mSize;

		float mRotation;
		int mHealth;

		Color mColor;

		Animation animation;
	};

	class NewPlayer : public Entity {
		public:
			NewPlayer();
			~NewPlayer();

			void OnInit(ManagerModel *m);
			void OnUpdate(const HiResTimer &timer);
			bool IsDead();

			inline EntityType Type() { return ENTITY_PLAYER; }

			void OnUpdateFrameTimes(bool btnIsPressed);
			void OnUpdatePlayerPhysics(const HiResTimer &timer);

			PlaneParams planeParams;

			int coolDown = 0;
			int oldCoolDown = 0;

		private:
			const int defaultHealth = 100;
			float oldTime = 80;
	};
}