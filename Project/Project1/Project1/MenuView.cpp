#include "MenuView.h"
#include "MenuModel.h"
#include "NewGame.h"
#include "ContinueGame.h"
#include "Controlls.h"
#include "Instructions.h"
#include "Background.h";

namespace View {
	MenuView::MenuView() {}
	
	MenuView::MenuView(Common *common, Model::MenuModel *m) {
		mCommon = common;
		mModel = m;
		Graphics *g = common->getGraphics();

		mRenderer = g->createRenderer2D();

		mFont = mCommon->getFontResource("lobsterBold");
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

	void MenuView::OnInstructionsUpdate(const Model::Instructions *instruction) {
		for (SpriteDef &sprite : mSprites) {
			if (sprite.mEntity == instruction) {
				sprite.mPosition = instruction->mPos;
				sprite.mTint = instruction->mColor;
				sprite.mRotation = instruction->mRotation;
				sprite.mScale = instruction->mScale;
				sprite.mTexture = mCommon->getGraphics()->createRenderText(mFont, instruction->mText)->getTexture();
			}
		}
	}

	void MenuView::OnInstructionsInit(Model::Instructions *instruction) {
		SpriteDef sprite;
		sprite.mEntity = instruction;
		sprite.mTexture = mCommon->getGraphics()->createRenderText(mFont, instruction->mText)->getTexture();
		sprite.mPosition = instruction->mPos;
		sprite.mScale = instruction->mScale;

		int width, heigth;
		sprite.mTexture->getDimensions(&width, &heigth);

		sprite.mOrigin = Vec2(width / 2, heigth / 2);
		sprite.mClip = { 0, 0, width, heigth };
		sprite.mTint = instruction->mColor;
		sprite.mRotation = instruction->mRotation;

		mSprites.push_back(sprite);
	}

	void MenuView::OnControllsUpdate(const Model::Controlls *controlls) {
		for (SpriteDef &sprite : mSprites) {
			if (sprite.mEntity == controlls) {
				sprite.mPosition = controlls->mPos;
				sprite.mTint = controlls->mColor;
				sprite.mRotation = controlls->mRotation;
				sprite.mScale = controlls->mScale;
				sprite.mTexture = mCommon->getGraphics()->createRenderText(mFont, controlls->mText)->getTexture();
			}
		}
	}

	void MenuView::OnControllsInit(Model::Controlls *controlls) {
		SpriteDef sprite;
		sprite.mEntity = controlls;
		sprite.mTexture = mCommon->getGraphics()->createRenderText(mFont, controlls->mText)->getTexture();
		sprite.mPosition = controlls->mPos;
		sprite.mScale = controlls->mScale;

		int width, heigth;
		sprite.mTexture->getDimensions(&width, &heigth);

		sprite.mOrigin = Vec2(width / 2, heigth / 2);
		sprite.mClip = { 0, 0, width, heigth };
		sprite.mTint = controlls->mColor;
		sprite.mRotation = controlls->mRotation;

		mSprites.push_back(sprite);
	}
}