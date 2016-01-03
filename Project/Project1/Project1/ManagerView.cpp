#include "ManagerView.h"
#include "ManagerModel.h"
#include "NewPlayer.h"
#include "Shot.h"
#include "NewAsteroid.h"

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

	void ManagerView::OnUpdate(const HiResTimer timer) {
		const float dt = timer.getDeltaSeconds();
		OnUpdatePlayer(dt);
		OnUpdateShot(dt);
		OnUpdateAsteroid(dt);
	}

	void ManagerView::OnUpdatePlayer(const float dt) {
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
			playerDelta = Vec2::normalize(playerDelta) * dt * 50.0f;
			frameTimePlane += dt;
			if (frameTimePlane > 0.8) {
				frameTimePlane = 0.0f;
				mModel->AddShot(mModel->GetStartPositionForShot());
			}

			mModel->OnMovePlayer(playerDelta);

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

	void ManagerView::OnUpdateShot(const float dt) {
		InputState input;
		mCommon->getInputState(&input);

		frameTimeBullet += dt;
		if (input.isDown(Button::BUTTON_SPACE)) {
			if (frameTimeBullet > 0.4) {
				frameTimeBullet = 0.0f;
				mModel->AddShot(mModel->GetStartPositionForShot());
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

	void ManagerView::OnShotUpdatePhysics(const Model::Shot *shot) {
		for (auto &sprite : mSprites) {
			if (sprite.mEntity == shot) {
				sprite.mPosition.x = shot->bulletParams.mPos.x;
				sprite.mPosition.y = shot->bulletParams.mPos.y;
			}
		}
	}

	void ManagerView::OnAsteroidSpawned(Model::NewAsteroid *asteroid) {
		SpriteDef sprite;
		sprite.mEntity = asteroid;
		sprite.mTexture = mCommon->getTextureResource("asteroid1");
		sprite.mPosition = asteroid->asteroidParams.mPos;

		sprite.mScale = asteroid->asteroidParams.mScale;
		sprite.mOrigin = Vec2(0);
		sprite.mClip = { 0, 0, 72, 72 };
		sprite.mTint = Color::White;
		sprite.mRotation = asteroid->asteroidParams.mRotation;

		mSprites.push_back(sprite);
	}

	void ManagerView::OnAsteroidMoved(Model::NewAsteroid *asteroid) {
		for (SpriteDef &sprite : mSprites) {
			if (sprite.mEntity == asteroid) {
				sprite.mPosition = asteroid->asteroidParams.mPos;
			}
		}
	}

	void ManagerView::OnMoveAsteroid(const Model::NewAsteroid *asteroid) {
		for (SpriteDef &sprite : mSprites) {
			if (sprite.mEntity == asteroid) {
				sprite.mPosition = asteroid->asteroidParams.mPos;
			}
		}
	}

	void ManagerView::OnAsteroidUpdatedPhysics(Model::NewAsteroid *asteroid) {
		for (auto &sprite : mSprites) {
			if (sprite.mEntity == asteroid) {
				sprite.mPosition.x = asteroid->asteroidParams.mPos.x;
				sprite.mPosition.y = asteroid->asteroidParams.mPos.y;
			}
		}
	}

	void ManagerView::OnAsteroidUpdatedAnimation(const Model::NewAsteroid *asteroid) {
		for (auto &sprite : mSprites) {
			if (sprite.mEntity == asteroid) {
				sprite.mClip.x = (asteroid->asteroidParams.animation.mCurrentFrame % 5) * asteroid->asteroidParams.mSize.x;
				sprite.mClip.y = (asteroid->asteroidParams.animation.mCurrentFrame / 5) * asteroid->asteroidParams.mSize.y;
			}
		}
	}

	void ManagerView::OnUpdateAsteroid(const float dt) {
		mModel->OnMoveAsteroid();
	}
}