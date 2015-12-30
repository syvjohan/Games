#pragma once

#include <framework.h>

#include <vector>

class Texture2D;

//class GameObject {
//
//};
//
//class Player : public GameObject {
//
//};
//
//class Asteroid : public GameObject {
//
//};
//
//std::vector<GameObject*> objects;
//objects.push_back(new Player());
//objects.push_back(new Asteroid());

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
		Vec2 mVel;

		Vec2 mSize;
		Vec2 mScale;
		Vec2 mPlayArea;
		int mType;
		float mHealth;

		Model::AsteroidAnimation animation;
	};
}