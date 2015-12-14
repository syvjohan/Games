#include "BallView.h"

namespace View {
	BallView::BallView() {}

	BallView::BallView( Model::BallEmitter &emitter, Model::BallParams &params ) {
		this->emitter = emitter;
		this->params = params;
	}

	BallView::~BallView() {}

	void BallView::UpdateEmitter(const float dt) {
		for (int ballIndex = 0; ballIndex < emitter.mBallCount; ++ballIndex) {
			Model::Ball *ball = emitter.mBalls + ballIndex;
			ball->mTime -= dt;

			//Game physics
			ball->mPos += ball->mVel * dt;

			if (ball->mPos.x < emitter.mPlayArea.x) {
				ball->mPos.x = emitter.mPlayArea.x;
			}

			if (ball->mPos.x > (emitter.mPlayArea.x + ball->mSize.x) - ball->mSize.x) {
				ball->mPos.x = (emitter.mPlayArea.x + ball->mSize.x) - ball->mSize.x;
			}

			if (ball->mPos.y < emitter.mPlayArea.y) {
				ball->mPos.y = emitter.mPlayArea.y;
			}

			if (ball->mPos.y > (emitter.mPlayArea.y + ball->mSize.y) - ball->mSize.y) {
				ball->mPos.y = (emitter.mPlayArea.x + ball->mSize.x) - ball->mSize.x;
			}
		}
	}

	void BallView::RenderEmitter(Renderer2D *renderer) {
		int width, height;
		emitter.mParams.mTexture->getDimensions(&width, &height);
		width *= emitter.mBalls->mScale.x;
		height *= emitter.mBalls->mScale.y;

		RectangleF clip = { 0, 0, width, height };
		Vec2 origin = { width / 2.0f, height / 2.0f };

		for (int i = 0; i < emitter.mBallCount; ++i) {
			Vec4 tint = Vec4::lerp(
			{ emitter.mBalls[i].mTint.R, emitter.mBalls[i].mTint.G, emitter.mBalls[i].mTint.B, 0.0f },
				emitter.mBalls[i].mTint,
				emitter.mBalls[i].mTime / emitter.mBalls[i].mMaxTime
			);

			renderer->draw(emitter.mParams.mTexture,
						   (emitter.mBalls[i].mPos),
						   clip,
						   origin,
						   emitter.mBalls[i].mOrientation,
						   emitter.mBalls[i].mScale * .3f, //change size of image to desired size.
						   tint,
						   0.0f
						   );
		}
	}
}