#include "BallSimulation.h"
#include "Defs.h"

namespace Model {
	BallSimulation::BallSimulation() {}

	BallSimulation::BallSimulation(Common &common, Vec2 scale, Vec2 screen) {
		InitParams(common);
		InitEmitter(screen, scale);
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
		b->mSize.x = 40;
		b->mSize.y = 40;	
		b->mScale = scale;
		b->mTint = Color::White;
		b->mAngularVelocity = 0;
		b->mOrientation = 0;
		b->mMaxTime = 10000;
		b->mTime = b->mMaxTime;
		b->mVel = Vec2(.1f, .1f);
	}

	void BallSimulation::InitEmitter(Vec2 screen, Vec2 scale) {
		emitter.mPosition.x = screen.x / 2; //screen.x / 2 * scale.x;
		emitter.mPosition.y = screen.y / 2; // screen.y / 2 * scale.y;

		emitter.mPlayArea = screen;

		emitter.mParams = params;

		emitter.mBallCapacity = params.mMaxBalls;
		emitter.mBallCapacity = params.mMaxBalls;
		emitter.mBalls = DBG_NEW Model::Ball[emitter.mBallCapacity];
		emitter.mBallCount = emitter.mParams.mMinBalls;

		emitter.mBalls->mScale = scale;

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