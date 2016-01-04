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

			//if (sprite.mEntity->Type() == Model::ENTITY_PLAYER) {
			//	Model::PlaneParams params = ((Model::NewPlayer*)sprite.mEntity)->planeParams;

			//	mRenderer->debugCircle(params.mPos.x, params.mPos.y, 20.0f, Color::Red);

			//}
		}

		mRenderer->end();
	}

	void ManagerView::OnUpdate(const float dt) {
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
			playerDelta = Vec2::normalize(playerDelta) * dt * 60.0f;
			frameTimePlane += dt;
			if (frameTimePlane > .2f) {
				frameTimePlane = 0.0f;
				btnIsPressedPlane = true;
			}

			mModel->OnMovePlayer(playerDelta);
		}
	}

	bool ManagerView::OnPlayerUpdatedAnimation(const Model::NewPlayer *player) {
		for (auto &sprite : mSprites) {
			if (sprite.mEntity == player) {
				sprite.mClip.x = (player->mCurrentFrame % 4) * player->mSize.x;
				sprite.mClip.y = (player->mCurrentFrame / 4) * player->mSize.y;
				
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
				sprite.mPosition.x = player->mPos.x;
				sprite.mPosition.y = player->mPos.y;
			}
		}
	}

	void ManagerView::OnPlayerSpawned(Model::NewPlayer *player) {
		SpriteDef sprite;
		sprite.mEntity = player;
		sprite.mTexture = mCommon->getTextureResource("plane");
		sprite.mPosition = player->mPos;

		sprite.mScale = player->mScale;
		sprite.mOrigin = Vec2(player->mSize.x / 2, player->mSize.y / 2);
		sprite.mClip = { 0, 0, player->mSize.x, player->mSize.y };
		sprite.mTint = Color::White;
		sprite.mRotation = player->mRotation;

		mSprites.push_back(sprite);
	}

	void ManagerView::OnPlayerMoved(const Model::NewPlayer *player) {
		for (SpriteDef &sprite : mSprites) {
			if (sprite.mEntity == player) {
				sprite.mPosition = player->mPos;
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
		sprite.mPosition = shot->mPos;

		sprite.mScale = shot->mScale;
		sprite.mOrigin = Vec2(0);
		sprite.mClip = { 0, 0, 116, 140 };
		sprite.mTint = Color::Red;
		sprite.mRotation = shot->mRotation;

		mSprites.push_back(sprite);
	}

	void ManagerView::OnMoveShot(const Model::Shot *shot) {
		for (SpriteDef &sprite : mSprites) {
			if (sprite.mEntity == shot) {
				sprite.mPosition = shot->mPos;
			}
		}
	}

	void ManagerView::OnShotMoved(const Model::Shot *shot) {
		for (SpriteDef &sprite : mSprites) {
			if (sprite.mEntity == shot) {
				sprite.mPosition = shot->mPos;
			}
		}
	}

	void ManagerView::OnShotUpdatePhysics(const Model::Shot *shot) {
		for (auto &sprite : mSprites) {
			if (sprite.mEntity == shot) {
				sprite.mPosition.x = shot->mPos.x;
				sprite.mPosition.y = shot->mPos.y;
			}
		}
	}

	void ManagerView::OnAsteroidSpawned(Model::NewAsteroid *asteroid) {
		SpriteDef sprite;
		sprite.mEntity = asteroid;
		sprite.mTexture = mCommon->getTextureResource("asteroid1");
		sprite.mPosition = asteroid->mPos;

		sprite.mScale = asteroid->mScale;
		sprite.mOrigin = asteroid->mSize / 2;
		sprite.mClip = { 0, 0, sprite.mOrigin.x * 2, sprite.mOrigin.y * 2 };
		sprite.mTint = Color::White;
		sprite.mRotation = asteroid->mRotation;

		mSprites.push_back(sprite);
	}

	void ManagerView::OnAsteroidMoved(Model::NewAsteroid *asteroid) {
		for (SpriteDef &sprite : mSprites) {
			if (sprite.mEntity == asteroid) {
				sprite.mPosition = asteroid->mPos;
			}
		}
	}

	void ManagerView::OnMoveAsteroid(const Model::NewAsteroid *asteroid) {
		for (SpriteDef &sprite : mSprites) {
			if (sprite.mEntity == asteroid) {
				sprite.mPosition = asteroid->mPos;
			}
		}
	}

	void ManagerView::OnAsteroidUpdatedPhysics(Model::NewAsteroid *asteroid) {
		for (auto &sprite : mSprites) {
			if (sprite.mEntity == asteroid) {
				sprite.mPosition.x = asteroid->mPos.x;
				sprite.mPosition.y = asteroid->mPos.y;
			}
		}
	}

	void ManagerView::OnAsteroidUpdatedAnimation(const Model::NewAsteroid *asteroid) {
		for (auto &sprite : mSprites) {
			if (sprite.mEntity == asteroid) {
				sprite.mClip.x = (asteroid->mCurrentFrame % 5) * asteroid->mSize.x;
				sprite.mClip.y = (asteroid->mCurrentFrame / 5) * asteroid->mSize.y;
			}
		}
	}

	void ManagerView::OnUpdateAsteroid(const float dt) {
		mModel->OnMoveAsteroid();
	}

	void ManagerView::OnEntityDied(int index) {
		mSprites.erase(mSprites.begin() + index);
	}
}