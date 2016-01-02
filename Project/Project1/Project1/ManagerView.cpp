#include "ManagerView.h"
#include "ManagerModel.h"
#include "NewPlayer.h"

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

			++keyPress;
			int diff = keyPress - OldKeyPress;
			if (diff >= 80) {
				btnIsPressed = true;
				OldKeyPress = keyPress;

				if (keyPress == INT_MAX) {
					keyPress = 0;
					OldKeyPress = 0;
				}
			}
		}
	}

	bool ManagerView::OnPlayerUpdatedAnimation(const Model::NewPlayer *player) {
		for (auto &sprite : mSprites) {
			if (sprite.mEntity == player) {
				sprite.mClip.x = (player->params.animation.mCurrentFrame % 4) * player->params.mSize.x;
				sprite.mClip.y = (player->params.animation.mCurrentFrame / 4) * player->params.mSize.y;
				
				if (btnIsPressed) {
					btnIsPressed = false;
					return true;
				}
			}
		}
		return false;
	}

	void ManagerView::OnPlayerUpdatedPhysics(Model::NewPlayer *player, const HiResTimer &timer) {
		for (auto &sprite : mSprites) {
			if (sprite.mEntity == player) {

				player->params.mPos.x += player->params.mDir.x * player->params.mAcc.x * timer.getDeltaSeconds();
				player->params.mPos.y += player->params.mDir.y * player->params.mAcc.y * timer.getDeltaSeconds();

				sprite.mPosition.x = player->params.mPos.x;
				sprite.mPosition.y = player->params.mPos.y;
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
		sprite.mPosition = player->params.mPos;

		sprite.mScale = player->params.mScale;
		sprite.mOrigin = Vec2(0);
		sprite.mClip = { 0, 0, 116, 140 };
		sprite.mTint = Color::White;
		sprite.mRotation = player->params.mRotation;

		mSprites.push_back(sprite);
	}

	void ManagerView::OnPlayerMoved(const Model::NewPlayer *player) {
		for (SpriteDef &sprite : mSprites) {
			if (sprite.mEntity == player) {
				sprite.mPosition = player->params.mPos;
			}
		}
	}

	void ManagerView::OnPlayerDied(const Model::NewPlayer *player) {
		//Remove player.
	}

}