#include "BallSimulation.h"
#include "Defs.h"

namespace Model {
	BallSimulation::BallSimulation() {}

	BallSimulation::BallSimulation(Common &common, Vec2 scale, Vec2 screen, const float boarderMargin) {
		InitParams(common);
		InitEmitter(screen, scale, boarderMargin);
	}
	BallSimulation::~BallSimulation() {}

	void BallSimulation::InitParams(Common &common) {
		params.mTexture = common.getTextureResource("ball");
		GetParams();
	}

	void BallSimulation::GetParams() {
		params.mMaxBalls = 10;
		params.mMinBalls = 10;
	}

	float BallSimulation::r1() {
		return (float)(rand() % 10001) / 10000.0f;
	}

	float BallSimulation::r2() {
		return r1() * 2.0f - 1.0f;
	}

	float BallSimulation::InRange(float min, float max) {
		return min + (max - min) * r1();
	}

	void BallSimulation::InitBall(Model::Ball *b, Vec2 scale) {
		b->mPos.x = InRange(emitter.mPosition.x, emitter.mPosition.x);
		b->mPos.y = InRange(emitter.mPosition.y, emitter.mPosition.y);
		
		b->mScale = scale;
		b->mTint = Color::White;
		b->mAngularVelocity = 0;
		b->mOrientation = 0;
		b->mMaxTime = 10000;
		b->mTime = b->mMaxTime;

		b->mVel = Vec2(200 * scale.x, 200 * scale.y);
		b->mDir = Vec2(InRange(-10, 10), InRange(-10, 10));

		int width, height;
		emitter.mParams.mTexture->getDimensions(&width, &height);
		b->mSize.x = width;
		b->mSize.y = height;

		b->mStop = 1;
	}

	void BallSimulation::InitEmitter(Vec2 screen, Vec2 scale, const float boarderMargin) { 
		emitter.mPosition.x = screen.x / 2;
		emitter.mPosition.y = screen.y / 2;

		emitter.mPlayArea = Vec2(screen.x -= boarderMargin, screen.y -= boarderMargin);

		emitter.mParams = params;

		emitter.mBallCapacity = params.mMaxBalls;
		emitter.mBallCapacity = params.mMaxBalls;
		emitter.mBalls = DBG_NEW Model::Ball[emitter.mBallCapacity];
		emitter.mBallCount = emitter.mParams.mMinBalls;

		for (int i = 0; i < emitter.mParams.mMinBalls; ++i) {
			InitBall(emitter.mBalls + i, scale);
		}
	}

	Model::BallParams& BallSimulation::getParams() {
		return this->params;
	}

	Model::BallEmitter& BallSimulation::getEmitter() {
		return this->emitter;
	}
}