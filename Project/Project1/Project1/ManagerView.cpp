#include "ManagerView.h"
#include "ManagerModel.h"
#include "Player.h"
#include "Shot.h"
#include "Asteroid.h"
#include "Explosion.h"
#include "HealthKeeper.h"
#include "ScoreKeeper.h"
#include "HealthPackage.h"
#include "EnemieBoss.h"

namespace View {
	ManagerView::ManagerView() {}

	ManagerView::ManagerView(Common *common, Model::ManagerModel *m) {
		mCommon = common;
		mModel = m;
		Graphics *g = common->getGraphics();

		mRenderer = g->createRenderer2D();
		
		mFont = mCommon->getFontResource("sans16");
	}

	ManagerView::~ManagerView() {}

	void ManagerView::OnRender() {
		mRenderer->begin(Renderer2D::SPRITE_SORT_DEFERRED, Renderer2D::SPRITE_BLEND_ALPHA);
		for (SpriteDef &sprite : mSprites) {
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

	void ManagerView::OnScoreInit(Model::ScoreKeeper *scoreKeeper) {
		SpriteDef sprite;
		sprite.mEntity = scoreKeeper;
		sprite.mTexture = mCommon->getGraphics()->createRenderText(mFont, scoreKeeper->mText)->getTexture();
		sprite.mPosition = scoreKeeper->mPos;
		sprite.mScale = scoreKeeper->mScale;

		int width, heigth;
		sprite.mTexture->getDimensions(&width, &heigth);

		sprite.mOrigin = Vec2(width / 2, heigth / 2);
		sprite.mClip = { 0, 0, width, heigth };
		sprite.mTint = scoreKeeper->mColor;
		sprite.mRotation = scoreKeeper->mRotation;

		mSprites.push_back(sprite);
	}

	void ManagerView::OnScoreupdate(const Model::ScoreKeeper *scoreKeeper) {
		for (SpriteDef &sprite : mSprites) {
			if (sprite.mEntity == scoreKeeper) {
				sprite.mPosition = scoreKeeper->mPos;
				sprite.mTint = scoreKeeper->mColor;
				sprite.mRotation = scoreKeeper->mRotation;
				sprite.mScale = scoreKeeper->mScale;
				sprite.mTexture = mCommon->getGraphics()->createRenderText(mFont, scoreKeeper->mText)->getTexture();
			}
		}
	}

	void ManagerView::OnHPInit(Model::HealthKeeper *healthKeeper) {
		SpriteDef sprite;
		sprite.mEntity = healthKeeper;
		sprite.mTexture = mCommon->getGraphics()->createRenderText(mFont, healthKeeper->mText)->getTexture();
		sprite.mPosition = healthKeeper->mPos;
		sprite.mScale = healthKeeper->mScale;

		int width, heigth;
		sprite.mTexture->getDimensions(&width, &heigth);

		sprite.mOrigin = Vec2(width / 2, heigth / 2);
		sprite.mClip = { 0, 0, width, heigth };
		sprite.mTint = healthKeeper->mColor;
		sprite.mRotation = healthKeeper->mRotation;

		mSprites.push_back(sprite);
	}

	void ManagerView::OnHPUpdate(const Model::HealthKeeper *healthKeeper) {
		for (SpriteDef &sprite : mSprites) {
			if (sprite.mEntity == healthKeeper) {
				sprite.mPosition = healthKeeper->mPos;
				sprite.mTint = healthKeeper->mColor;
				sprite.mRotation = healthKeeper->mRotation;
				sprite.mScale = healthKeeper->mScale;
				sprite.mTexture = mCommon->getGraphics()->createRenderText(mFont, healthKeeper->mText)->getTexture();
			}
		}
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
		sprite.mTexture = GetAsteroidTexture(asteroid);
		sprite.mPosition = asteroid->mPos;

		sprite.mScale = asteroid->mScale;
		sprite.mOrigin.x = asteroid->mSize.x / 2 * asteroid->mScale.x;
		sprite.mOrigin.y = asteroid->mSize.y / 2 * asteroid->mScale.y;
		sprite.mClip = { 0, 0, asteroid->mSize.x, asteroid->mSize.y };
		sprite.mTint = Color::White;
		sprite.mRotation = asteroid->mRotation;

		mSprites.push_back(sprite);
	}

	Texture2D* ManagerView::GetAsteroidTexture(Model::Asteroid *asteroid) {
		Texture2D *texture = NULL;
		switch (asteroid->mType) {
			case 1:
				texture = mCommon->getTextureResource("asteroid1");
				break;
			case 2:
				texture = mCommon->getTextureResource("asteroid2");
				break;
			case 3:
				texture = mCommon->getTextureResource("asteroid3");
				break;
			case 4:
				texture = mCommon->getTextureResource("asteroid4");
				break;
			case 5:
				texture = mCommon->getTextureResource("asteroid5");
				break;
			case 6:
				texture = mCommon->getTextureResource("asteroid6");
				break;
		}
		return texture;
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

	void ManagerView::OnHealthPackageSpawned(Model::HealthPackage *healthPackage) {
		SpriteDef sprite;
		sprite.mEntity = healthPackage;
		sprite.mTexture = mCommon->getTextureResource("health_package");
		sprite.mPosition = healthPackage->mPos;

		sprite.mScale = healthPackage->mScale;
		sprite.mOrigin.x = healthPackage->mSize.x / 2 * healthPackage->mScale.x;
		sprite.mOrigin.y = healthPackage->mSize.y / 2 * healthPackage->mScale.y;
		sprite.mClip = { 0, 0, healthPackage->mSize.x, healthPackage->mSize.y };
		sprite.mTint = healthPackage->mColor;
		sprite.mRotation = healthPackage->mRotation;

		mSprites.push_back(sprite);
	}

	void ManagerView::OnHealthPackageMoved(Model::HealthPackage *healthPackage) {
		for (SpriteDef &sprite : mSprites) {
			if (sprite.mEntity == healthPackage) {
				sprite.mPosition = healthPackage->mPos;
				sprite.mRotation = healthPackage->mRotation;
				sprite.mScale = healthPackage->mScale;
			}
		}
	}

	void ManagerView::OnMoveHealthPackage(const Model::HealthPackage *healthPackage) {
		for (SpriteDef &sprite : mSprites) {
			if (sprite.mEntity == healthPackage) {
				sprite.mPosition = healthPackage->mPos;
				sprite.mRotation = healthPackage->mRotation;
				sprite.mScale = healthPackage->mScale;
			}
		}
	}

	void ManagerView::OnHealthPackageUpdatedPhysics(Model::HealthPackage *healthPackage) {
		for (auto &sprite : mSprites) {
			if (sprite.mEntity == healthPackage) {
				sprite.mPosition.x = healthPackage->mPos.x;
				sprite.mPosition.y = healthPackage->mPos.y;
			}
		}
	}

	void ManagerView::OnEnemieBossSpawned(Model::EnemieBoss *enemieBoss) {
		SpriteDef sprite;
		sprite.mEntity = enemieBoss;
		sprite.mTexture = mCommon->getTextureResource("plane");
		sprite.mPosition = enemieBoss->mPos;

		sprite.mScale = enemieBoss->mScale;
		sprite.mOrigin.x = enemieBoss->mSize.x / 2 * enemieBoss->mScale.x;
		sprite.mOrigin.y = enemieBoss->mSize.y / 2 * enemieBoss->mScale.y;
		sprite.mClip = { 0, 0, enemieBoss->mSize.x, enemieBoss->mSize.y };
		sprite.mTint = enemieBoss->mColor;
		sprite.mRotation = enemieBoss->mRotation;

		mSprites.push_back(sprite);
	}

	void ManagerView::OnEnemieBossMoved(Model::EnemieBoss *enemieBoss) {
		for (SpriteDef &sprite : mSprites) {
			if (sprite.mEntity == enemieBoss) {
				sprite.mPosition = enemieBoss->mPos;
				sprite.mRotation = enemieBoss->mRotation;
				sprite.mScale = enemieBoss->mScale;
				sprite.mTint = enemieBoss->mColor;
			}
		}
	}

	void ManagerView::OnMoveEnemieBoss(const Model::EnemieBoss *enemieBoss) {
		for (SpriteDef &sprite : mSprites) {
			if (sprite.mEntity == enemieBoss) {
				sprite.mPosition = enemieBoss->mPos;
				sprite.mRotation = enemieBoss->mRotation;
				sprite.mScale = enemieBoss->mScale;
				sprite.mTint = enemieBoss->mColor;
			}
		}
	}

	void ManagerView::OnEnemieBossUpdatedPhysics(Model::EnemieBoss *enemieBoss) {
		for (auto &sprite : mSprites) {
			if (sprite.mEntity == enemieBoss) {
				sprite.mPosition.x = enemieBoss->mPos.x;
				sprite.mPosition.y = enemieBoss->mPos.y;
			}
		}
	}

	void ManagerView::OnEntityDied(int index) {
		mSprites.erase(mSprites.begin() + index);
	}
}