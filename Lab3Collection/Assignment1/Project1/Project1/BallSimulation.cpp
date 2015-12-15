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
		params.mMaxBalls = 1;
		params.mMinBalls = 1;
	}

	void BallSimulation::InitBall(Model::Ball *b, Vec2 scale) {
		b->mPos = emitter.mPosition;
		
		b->mScale = scale;
		b->mTint = Color::White;
		b->mAngularVelocity = 0;
		b->mOrientation = 0;
		b->mMaxTime = 10000;
		b->mTime = b->mMaxTime;
		b->mVel = Vec2(100.f, 100.f);
		b->mDir = Vec2(-10, -10);

		int width, height;
		emitter.mParams.mTexture->getDimensions(&width, &height);
		b->mSize.x = width;
		b->mSize.y = height;
	}

	void BallSimulation::InitEmitter(Vec2 screen, Vec2 scale, const float boarderMargin) { 
		emitter.mPosition.x = screen.x / 2; //screen.x / 2 * scale.x;
		emitter.mPosition.y = screen.y / 2; // screen.y / 2 * scale.y;

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