#pragma once
#include <framework.h>
#include "Sprite.h"

class Texture2D;

namespace Model {

	struct ParticleParams {
		Texture2D *mTexture;

		int mMaxParticles;
		int mMinParticles;

		int mMinLifeTimeMs;
		int mMaxLifeTimeMs;

		Vec2 mGravity;
	};

	struct Particle {
		Vec2 mPos;
		Vec2 mVel;
		Vec2 mAcc;
		Vec2 mDir;

		Vec4 mTint;
		Vec2 mScale;
		Vec2 mSize;

		float mOrientation;
		float mAngularVelocity;
		float mTime;
		float mMaxTime;
	};

	struct ParticleEmitter {
		int mParticleCapacity;
		int mParticleCount;
		Particle *mParticles;

		ParticleParams mParams;

		Vec2 mPosition;

		Vec2 mPlayArea;
		float mMetersToPixels;
	};

}
