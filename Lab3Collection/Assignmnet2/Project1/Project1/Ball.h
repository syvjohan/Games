#pragma once

#include <framework.h>

class Texture2D;

namespace Model {

	struct BallParams {
		Texture2D *mTexture;

		int mMaxBalls;
		int mMinBalls;

		int mMinLifeTimeMs;
		int mMaxLifeTimeMs;

		Vec2 mGravity;
	};

	struct Ball {
		Vec2 mSize;
		Vec2 mPos;
		Vec2 mDir;
		Vec2 mScale;

		Vec2 mVel;

		float mOrientation;
		float mAngularVelocity;

		Vec4 mTint;
		float mMaxTime;
		float mTime;
	};

	struct BallEmitter {
		int mBallCapacity;
		int mBallCount;
		Ball *mBalls;
		
		BallParams mParams;

		Vec2 mPosition;
		Vec2 mPlayArea;
	};

}