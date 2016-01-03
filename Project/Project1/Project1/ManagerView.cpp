#include "ManagerView.h"
#include "ManagerModel.h"
#include "NewPlayer.h"
#include "Shot.h"

namespace View {
	ManagerView::ManagerView() {

	}

	ManagerView::ManagerView(Common *common, Model::ManagerModel *m) {
		mCommon = common;
		mModel = m;
		Graphics *g = common->getGraphics();

		mRenderer = g->createRenderer2D();
	}

	ManagerView::~ManagerView() {

	}

	void ManagerView::OnUpdate(const HiResTimer &timer) {
		OnUpdatePlayer(timer);
		OnUpdateShot(timer);
	}

	void ManagerView::OnUpdatePlayer(const HiResTimer &timer) {
		InputState input;
		mCommon->getInputState(&input);

		Vec2 playerDelta(0);

		if (input.isDown(Button::BUTTON_A)) {
			playerDelta.x -= 10;
		}

		if (input.isDown(Button::BUTTON_D)) {
			playerDelta.x += 10;
		}

		if (input.isDown(Button::BUTTON_W)) {
			playerDelta.y -= 10;
		}

		if (input.isDown(Button::BUTTON_S)) {
			playerDelta.y += 10;
		}

		if (Vec2::length(playerDelta) > 0) {
			playerDelta = Vec2::normalize(playerDelta) * timer.getDeltaSeconds() * 50.0f;

			mModel->OnMovePlayer(playerDelta);

			++keyPressPlane;
			int diff = keyPressPlane - OldKeyPressPlane;
			if (diff >= 80) {
				btnIsPressedPlane = true;
				OldKeyPressPlane = keyPressPlane;

				if (keyPressPlane == INT_MAX) {
					keyPressPlane = 0;
					OldKeyPressPlane = 0;
				}
			}
		}
	}

	bool ManagerView::OnPlayerUpdatedAnimation(const Model::NewPlayer *player) {
		for (auto &sprite : mSprites) {
			if (sprite.mEntity == player) {
				sprite.mClip.x = (player->planeParams.animation.mCurrentFrame % 4) * player->planeParams.mSize.x;
				sprite.mClip.y = (player->planeParams.animation.mCurrentFrame / 4) * player->planeParams.mSize.y;
				
				if (btnIsPressedPlane) {
					btnIsPressedPlane = false;
					return true;
				}
			}
		}
		return false;
	}

	void ManagerView::OnPlayerUpdatedPhysics(const Model::NewPlayer *player) {
		for (auto &sprite : mSprites) {
			if (sprite.mEntity == player) {
				sprite.mPosition.x = player->planeParams.mPos.x;
				sprite.mPosition.y = player->planeParams.mPos.y;
			}
		}
	}

	void ManagerView::OnRender() {
		mRenderer->begin(Renderer2D::SPRITE_SORT_DEFERRED, Renderer2D::SPRITE_BLEND_ALPHA);
		for (auto &sprite : mSprites) {
			mRenderer->draw(sprite.mTexture,
							sprite.mPosition,
							sprite.mClip,
							sprite.mOrigin,
							sprite.mRotation,
							sprite.mScale,
							sprite.mTint,
							0.0f);
		}

		mRenderer->end();
	}

	void ManagerView::OnPlayerSpawned(Model::NewPlayer *player) {
		SpriteDef sprite;
		sprite.mEntity = player;
		sprite.mTexture = mCommon->getTextureResource("plane");
		sprite.mPosition = player->planeParams.mPos;

		sprite.mScale = player->planeParams.mScale;
		sprite.mOrigin = Vec2(0);
		sprite.mClip = { 0, 0, 116, 140 };
		sprite.mTint = Color::White;
		sprite.mRotation = player->planeParams.mRotation;

		mSprites.push_back(sprite);
	}

	void ManagerView::OnPlayerMoved(const Model::NewPlayer *player) {
		for (SpriteDef &sprite : mSprites) {
			if (sprite.mEntity == player) {
				sprite.mPosition = player->planeParams.mPos;
			}
		}
	}

	void ManagerView::OnUpdateShot(const HiResTimer &timer) {
		InputState input;
		mCommon->getInputState(&input);

		if (input.isDown(Button::BUTTON_SPACE)) {
			++keyPressShot;
			int diff = keyPressShot - oldKeyPressShot;
			if (diff >= 60) {
 				mModel->AddShot(mModel->GetStartPositionForShot());

				oldKeyPressShot = keyPressShot;

				if (keyPressShot == INT_MAX) {
					keyPressShot = 0;
					oldKeyPressShot = 0;
				}
			}
		}

		mModel->OnMoveShot();
	}

	void ManagerView::OnShotSpawned(Model::Shot *shot) {
		SpriteDef sprite;
		sprite.mEntity = shot;
		sprite.mTexture = mCommon->getTextureResource("shoot");
		sprite.mPosition = shot->bulletParams.mPos;

		sprite.mScale = shot->bulletParams.mScale;
		sprite.mOrigin = Vec2(0);
		sprite.mClip = { 0, 0, 116, 140 };
		sprite.mTint = Color::Red;
		sprite.mRotation = shot->bulletParams.mRotation;

		mSprites.push_back(sprite);
	}

	void ManagerView::OnMoveShot(const Model::Shot *shot) {
		for (SpriteDef &sprite : mSprites) {
			if (sprite.mEntity == shot) {
				sprite.mPosition = shot->bulletParams.mPos;
			}
		}
	}

	void ManagerView::OnShotMoved(const Model::Shot *shot) {
		for (SpriteDef &sprite : mSprites) {
			if (sprite.mEntity == shot) {
				sprite.mPosition = shot->bulletParams.mPos;
			}
		}
	}

	void ManagerView::OnShotUpdatedPhysics(const Model::Shot *shot) {
		for (auto &sprite : mSprites) {
			if (sprite.mEntity == shot) {
				sprite.mPosition.x = shot->bulletParams.mPos.x;
				sprite.mPosition.y = shot->bulletParams.mPos.y;
			}
		}
	}

}