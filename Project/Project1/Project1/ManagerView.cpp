#include "ManagerView.h"
#include "ManagerModel.h"
#include "Player.h"
#include "Shot.h"
#include "Asteroid.h"
#include "Explosion.h"

namespace View {
	ManagerView::ManagerView() {}

	ManagerView::ManagerView(Common *common, Model::ManagerModel *m) {
		mCommon = common;
		mModel = m;
		Graphics *g = common->getGraphics();

		mRenderer = g->createRenderer2D();

		font = common->getFontResource("sans16");
		textScore = g->createRenderText(font, "gg");
		textHealth = g->createRenderText(font, "gg");
	}

	ManagerView::~ManagerView() {}

	void ManagerView::OnRender() {
		mRenderer->begin(Renderer2D::SPRITE_SORT_DEFERRED, Renderer2D::SPRITE_BLEND_ALPHA);
		
		OnRenderSprites();
		OnRenderText();

		mRenderer->end();
	}

	void ManagerView::OnRenderSprites() {
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
	}

	void ManagerView::OnRenderText() {
		int width, height;

		textScore->getTexture()->getDimensions(&width, &height);
		mRenderer->draw(textScore->getTexture(),
					   Vec2(20, 20),
					   { 0, 0, width, height },
					   Vec2(0),
					   0.0f,
					   Vec2(1, 1),
					   Color::Yellow,
					   0.0f
					   );

		textHealth->getTexture()->getDimensions(&width, &height);
		Color color = Color::Yellow;
		if (mModel->healthKeeper.mHealth <= mModel->healthKeeper.mMaxHealth / 2) {
			color = Color::Red;
		}
		mRenderer->draw(textHealth->getTexture(),
						Vec2(120, 20),
						{ 0, 0, width, height },
						Vec2(0),
						0.0f,
						Vec2(1, 1),
						color,
						0.0f
						);
	}

	void ManagerView::OnUpdate(const float dt) {
		OnUpdatePlayer(dt);
		OnUpdateShot(dt);
		OnUpdateAsteroid(dt);

		OnUpdateText();
	}

	void ManagerView::OnUpdateText() {
		char buffer[128];
		sprintf(buffer, "Score: %i", mModel->scoreKeeper.mScore);
		textScore->setText(buffer);

		char buffer2[128];
		sprintf(buffer2, "HP: %i%%", mModel->healthKeeper.mHealth);
		textHealth->setText(buffer2);
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

	bool ManagerView::OnPlayerUpdatedAnimation(const Model::Player *player) {
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

	void ManagerView::OnPlayerUpdatedPhysics(const Model::Player *player) {
		for (auto &sprite : mSprites) {
			if (sprite.mEntity == player) {
				sprite.mPosition.x = player->mPos.x;
				sprite.mPosition.y = player->mPos.y;
			}
		}
	}

	void ManagerView::OnPlayerSpawned(Model::Player *player) {
		SpriteDef sprite;
		sprite.mEntity = player;
		sprite.mTexture = mCommon->getTextureResource("plane");
		sprite.mPosition = player->mPos;

		sprite.mScale = player->mScale;
		sprite.mOrigin = Vec2(player->mSize / 2);
		sprite.mClip = { 0, 0, player->mSize.x, player->mSize.y };
		sprite.mTint = player->mColor;
		sprite.mRotation = player->mRotation;

		mSprites.push_back(sprite);
	}

	void ManagerView::OnPlayerMoved(const Model::Player *player) {
		for (SpriteDef &sprite : mSprites) {
			if (sprite.mEntity == player) {
				sprite.mPosition = player->mPos;
				sprite.mTint = player->mColor;
				sprite.mRotation = player->mRotation;
				sprite.mScale = player->mScale;
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
		sprite.mOrigin = Vec2(shot->mSize / 2);
		sprite.mClip = { 0, 0, shot->mSize.x, shot->mSize.y};
		sprite.mTint = Color::Red;
		sprite.mRotation = shot->mRotation;

		mSprites.push_back(sprite);
	}

	void ManagerView::OnMoveShot(const Model::Shot *shot) {
		for (SpriteDef &sprite : mSprites) {
			if (sprite.mEntity == shot) {
				sprite.mPosition = shot->mPos;
				sprite.mRotation = shot->mRotation;
				sprite.mScale = shot->mScale;
			}
		}
	}

	void ManagerView::OnShotMoved(const Model::Shot *shot) {
		for (SpriteDef &sprite : mSprites) {
			if (sprite.mEntity == shot) {
				sprite.mPosition = shot->mPos;
				sprite.mRotation = shot->mRotation;
				sprite.mScale = shot->mScale;
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

	void ManagerView::PlayShotSoundEffect(const Model::Shot *shot) {
		if (source = mCommon->getAudio()->getSource()) {
			source->setVolume(.1f);
			source->play(mCommon->getSoundResource("soundShoot"));			
		}
	}

	void ManagerView::OnAsteroidSpawned(Model::Asteroid *asteroid) {
		SpriteDef sprite;
		sprite.mEntity = asteroid;
		sprite.mTexture = mCommon->getTextureResource("asteroid1");
		sprite.mPosition = asteroid->mPos;

		sprite.mScale = asteroid->mScale;
		sprite.mOrigin.x = asteroid->mSize.x / 2 * asteroid->mScale.x;
		sprite.mOrigin.y = asteroid->mSize.y / 2 * asteroid->mScale.y;
		sprite.mClip = { 0, 0, asteroid->mSize.x, asteroid->mSize.y };
		sprite.mTint = Color::White;
		sprite.mRotation = asteroid->mRotation;

		mSprites.push_back(sprite);
	}

	void ManagerView::OnAsteroidMoved(Model::Asteroid *asteroid) {
		for (SpriteDef &sprite : mSprites) {
			if (sprite.mEntity == asteroid) {
				sprite.mPosition = asteroid->mPos;
				sprite.mRotation = asteroid->mRotation;
				sprite.mScale = asteroid->mScale;
			}
		}
	}

	void ManagerView::OnMoveAsteroid(const Model::Asteroid *asteroid) {
		for (SpriteDef &sprite : mSprites) {
			if (sprite.mEntity == asteroid) {
				sprite.mPosition = asteroid->mPos;
				sprite.mRotation = asteroid->mRotation;
				sprite.mScale = asteroid->mScale;
			}
		}
	}

	void ManagerView::OnAsteroidUpdatedPhysics(Model::Asteroid *asteroid) {
		for (auto &sprite : mSprites) {
			if (sprite.mEntity == asteroid) {
				sprite.mPosition.x = asteroid->mPos.x;
				sprite.mPosition.y = asteroid->mPos.y;
			}
		}
	}

	void ManagerView::OnAsteroidUpdatedAnimation(const Model::Asteroid *asteroid) {
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

	void ManagerView::OnExplosionSpawned(Model::Explosion *explosion) {
		SpriteDef sprite;
		sprite.mEntity = explosion;
		sprite.mTexture = mCommon->getTextureResource("explosion");
		sprite.mPosition = explosion->mPos;

		sprite.mScale = explosion->mScale;
		sprite.mOrigin = explosion->mSize / 2;
		sprite.mClip = { 0, 0, sprite.mOrigin.x * 2, sprite.mOrigin.y * 2 };
		sprite.mTint = Color::White;
		sprite.mRotation = explosion->mRotation;

		mSprites.push_back(sprite);
	}

	void ManagerView::OnExplosionUpdateAnimation(const Model::Explosion *explosion) {
		for (auto &sprite : mSprites) {
			if (sprite.mEntity == explosion) {
				sprite.mClip.x = (explosion->mCurrentFrame % 4) * explosion->mSize.x;
				sprite.mClip.y = (explosion->mCurrentFrame / 4) * explosion->mSize.y;
			}
		}
	}

	void ManagerView::OnExplossionMoved(const Model::Explosion *explosion) {
		for (SpriteDef &sprite : mSprites) {
			if (sprite.mEntity == explosion) {
				sprite.mPosition = explosion->mPos;
				sprite.mRotation = explosion->mRotation;
				sprite.mScale = explosion->mScale;
			}
		}
	}

	void ManagerView::OnMoveExplossion(const Model::Explosion *explosion) {
		for (SpriteDef &sprite : mSprites) {
			if (sprite.mEntity == explosion) {
				sprite.mPosition = explosion->mPos;
				sprite.mRotation = explosion->mRotation;
				sprite.mScale = explosion->mScale;
			}
		}
	}

	void ManagerView::PlayExplosionSoundEffect(const Model::Explosion *explosion) {
		if(source = mCommon->getAudio()->getSource()) {
			source->setVolume(.1f);
			source->play(mCommon->getSoundResource("soundExplosion"));
		}
	}

	void ManagerView::OnEntityDied(int index) {
		mSprites.erase(mSprites.begin() + index);
	}
}