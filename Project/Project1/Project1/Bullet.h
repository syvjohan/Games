#pragma once
#include <framework.h>

#include <vector>

class Texture2D;

namespace Model {
	struct Bullet {
		Texture2D *mTexture;
		Vec2 mPos;
		Vec2 mVel;
		Vec2 mAcc;
		Vec2 mDir;
		Vec2 mSize;
		Vec2 mScale;
	};
}