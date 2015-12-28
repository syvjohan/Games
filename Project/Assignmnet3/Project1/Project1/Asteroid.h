#pragma once

#include <framework.h>

class Texture2D;

namespace Model {

	struct AsteroidAnimation {
		Vec2 mStart;
		Vec2 mFrameSize;
		float mFrameTime;
		int mFrameCount;
		Texture2D* mTexture;
		int mCurrentFrame;
	};

	struct Asteroid {
		Vec2 mPos;
		Vec2 mDir;
		Vec2 mScale;
		Vec2 mVel;

		Vec2 mSize;

		Model::AsteroidAnimation animation;
	};
}