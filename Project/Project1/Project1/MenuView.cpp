#include "MenuView.h"
#include "MenuModel.h"
#include "NewGame.h"
#include "ContinueGame.h"
#include "Help.h"
#include "Background.h"

namespace View {
	MenuView::MenuView() {}
	
	MenuView::MenuView(Common *common, Model::MenuModel *m) {
		mCommon = common;
		mModel = m;
		Graphics *g = common->getGraphics();

		mRenderer = g->createRenderer2D();

		mFont = mCommon->getFontResource("lobsterBold");
		mFont2 = mCommon->getFontResource("sans20");
	}

	MenuView::~MenuView() {}

	void MenuView::OnRender() {
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

	void MenuView::OnUpdate(const float dt) {
		InputState inputState;
		mCommon->getInputState(&inputState);

		accumulatorKeyPress -= dt;
		if (accumulatorKeyPress <= 0) {
			accumulatorKeyPress = 0;
		}
		if (inputState.isDown(Button::BUTTON_MOUSELEFT) && accumulatorKeyPress == 0) {
			mModel->CheckInput(Vec2(inputState.mMouseX, inputState.mMouseY));
			accumulatorKeyPress = delayKeyPress;
		}
	}

	void MenuView::OnBackgroundUpdate(const float dt) {}

	void MenuView::OnBackgroundMoved(const Model::Background *background) {
		for (SpriteDef &sprite : mSprites) {
			if (sprite.mEntity == background) {
				sprite.mPosition = background->mPos;
				sprite.mTint = background->mColor;
				sprite.mRotation = background->mRotation;
				sprite.mScale = background->mScale;
			}
		}
	}

	void MenuView::OnBackgroundInit(Model::Background *background) {
		SpriteDef sprite;
		sprite.mEntity = background;
		sprite.mTexture = mCommon->getTextureResource("background_menu");
		sprite.mPosition = background->mPos;

		sprite.mScale = background->mScale;
		sprite.mOrigin = Vec2(background->mSize / 2);
		sprite.mClip = { 0, 0, background->mSize.x, background->mSize.y };
		sprite.mTint = background->mColor;
		sprite.mRotation = background->mRotation;

		mSprites.push_back(sprite);
	}

	void MenuView::OnMoveBackground(const Model::Background *background) {
		for (SpriteDef &sprite : mSprites) {
			if (sprite.mEntity == background) {
				sprite.mPosition = background->mPos;
				sprite.mRotation = background->mRotation;
				sprite.mScale = background->mScale;
			}
		}
	}

	void MenuView::OnBackgroundUpdatedPhysics(Model::Background *background) {
		for (auto &sprite : mSprites) {
			if (sprite.mEntity == background) {
				sprite.mPosition.x = background->mPos.x;
				sprite.mPosition.y = background->mPos.y;
			}
		}
	}

	void MenuView::OnNewGameInit(Model::NewGame *newGame) {
		SpriteDef sprite;
		sprite.mEntity = newGame;
		sprite.mTexture = mCommon->getGraphics()->createRenderText(mFont, newGame->mText)->getTexture();
		sprite.mPosition = newGame->mPos;
		sprite.mScale = newGame->mScale;

		int width, heigth;
		sprite.mTexture->getDimensions(&width, &heigth);

		sprite.mOrigin = Vec2(width / 2, heigth / 2);
		sprite.mClip = { 0, 0, width, heigth };
		sprite.mTint = newGame->mColor;
		sprite.mRotation = newGame->mRotation;

		mSprites.push_back(sprite);
	}

	void MenuView::OnNewGameUpdate(const Model::NewGame *newGame) {
		for (SpriteDef &sprite : mSprites) {
			if (sprite.mEntity == newGame) {
				sprite.mPosition = newGame->mPos;
				sprite.mTint = newGame->mColor;
				sprite.mRotation = newGame->mRotation;
				sprite.mScale = newGame->mScale;
				sprite.mTexture = mCommon->getGraphics()->createRenderText(mFont, newGame->mText)->getTexture();
			}
		}
	}

	void MenuView::OnContinueGameInit(Model::ContinueGame *continueGame) {
		SpriteDef sprite;
		sprite.mEntity = continueGame;
		sprite.mTexture = mCommon->getGraphics()->createRenderText(mFont, continueGame->mText)->getTexture();
		sprite.mPosition = continueGame->mPos;
		sprite.mScale = continueGame->mScale;

		int width, heigth;
		sprite.mTexture->getDimensions(&width, &heigth);

		sprite.mOrigin = Vec2(width / 2, heigth / 2);
		sprite.mClip = { 0, 0, width, heigth };
		sprite.mTint = continueGame->mColor;
		sprite.mRotation = continueGame->mRotation;

		mSprites.push_back(sprite);
	}

	void MenuView::OnContinueGameUpdate(const Model::ContinueGame *continueGame) {
		for (SpriteDef &sprite : mSprites) {
			if (sprite.mEntity == continueGame) {
				sprite.mPosition = continueGame->mPos;
				sprite.mTint = continueGame->mColor;
				sprite.mRotation = continueGame->mRotation;
				sprite.mScale = continueGame->mScale;
				sprite.mTexture = mCommon->getGraphics()->createRenderText(mFont, continueGame->mText)->getTexture();
			}
		}
	}

	void MenuView::OnHelpUpdate(const Model::Help *help) {
		for (SpriteDef &sprite : mSprites) {
			if (sprite.mEntity == help) {
				sprite.mPosition = help->mPos;
				sprite.mTint = help->mColor;
				sprite.mRotation = help->mRotation;
				sprite.mScale = help->mScale;
				if (help->mIsHeader) {
					sprite.mTexture = mCommon->getGraphics()->createRenderText(mFont, help->mText)->getTexture();
				} else {
					sprite.mTexture = mCommon->getGraphics()->createRenderText(mFont2, help->mText)->getTexture();
				}
			}
		}
	}

	void MenuView::OnHelpInit(Model::Help *help) {
		SpriteDef sprite;
		sprite.mEntity = help;
		sprite.mTexture = mCommon->getGraphics()->createRenderText(mFont, help->mText)->getTexture();
		sprite.mPosition = help->mPos;
		sprite.mScale = help->mScale;

		int width, heigth;
		sprite.mTexture->getDimensions(&width, &heigth);

		sprite.mOrigin = Vec2(width / 2, heigth / 2);
		sprite.mClip = { 0, 0, width, heigth };
		sprite.mTint = help->mColor;
		sprite.mRotation = help->mRotation;

		mSprites.push_back(sprite);
	}

	void MenuView::RemoveSprite(int index) {
		mSprites.erase(mSprites.begin() + index);
	}
}