
#include <framework.h>
#include "Defs.h"

class Texture2D;

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

	Vec4 mTint;
	Vec2 mScale;

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

	float mMetersToPixels;
};


