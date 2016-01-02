#pragma once

#include <framework.h>

#include "Entity.h"

namespace Model {
	class ManagerModel;

	struct Animation { 
		float mFrameTime;
		int mCurrentFrame;

		float mFrameTimeBtnRelease;
		float mFramTimeIsHit;
	};

	struct Params {
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

		Params params;

		private:
		const int defaultHealth = 100;
	};
}