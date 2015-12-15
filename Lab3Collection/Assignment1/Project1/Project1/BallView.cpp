#include "BallView.h"

namespace View {
	BallView::BallView() {}

	BallView::BallView( Model::BallEmitter &emitter, Model::BallParams &params ) {
		this->emitter = emitter;
		this->params = params;
	}

	BallView::~BallView() {}

	void BallView::UpdateEmitter(const float dt, const float BoarderMargin) {
		for (int ballIndex = 0; ballIndex < emitter.mBallCount; ++ballIndex) {
			Model::Ball *ball = emitter.mBalls + ballIndex;
			ball->mTime -= dt;

			//Game physics
			ball->mPos += ball->mVel * dt;
			ball->mPos += ball->mDir;

			if (ball->mPos.x < ball->mSize.x - BoarderMargin) {
				ball->mPos.x = ball->mSize.x - BoarderMargin;
				ball->mDir.x = 10;
			}

			if (ball->mPos.x > emitter.mPlayArea.x - BoarderMargin) {
				ball->mPos.x = emitter.mPlayArea.x - BoarderMargin;
				ball->mDir.x = -10;
			}

			if (ball->mPos.y < ball->mSize.y - BoarderMargin) {
				ball->mPos.y = ball->mSize.y - BoarderMargin;
				ball->mDir.y = 10;
			}

			if (ball->mPos.y > emitter.mPlayArea.y - BoarderMargin) {
				ball->mPos.y = emitter.mPlayArea.y - BoarderMargin;
				ball->mDir.y = -10;
			}
		}
	}

	void BallView::RenderEmitter(Renderer2D *renderer) {

		for (int i = 0; i < emitter.mBallCount; ++i) {
			RectangleF clip = { 0, 0, emitter.mBalls[i].mSize.x, emitter.mBalls[i].mSize.y };
			Vec2 origin = { clip.w / 2.0f, clip.h / 2.0f };
					
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
						   emitter.mBalls[i].mScale, //change size of image to desired size.
						   tint,
						   0.0f
						   );
		}
	}
}