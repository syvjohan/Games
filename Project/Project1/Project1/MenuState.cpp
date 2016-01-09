#include "MenuState.h"
#include "NewGame.h"
#include "ContinueGame.h"
#include "Instructions.h"
#include "Background.h"

namespace Controller {
	MenuState::MenuState() {}

	MenuState::MenuState(Common *common) {
		mCommon = common;
	}

	MenuState::~MenuState() {}

	void MenuState::Init(Vec2 screen) {
		SetMenuArea(screen);

		Background *background = DBG_NEW Background();
		mEntities.push_back(background);

		Model::NewGame *newGame = DBG_NEW Model::NewGame();
		mEntities.push_back(newGame);

		ContinueGame *continueGame = DBG_NEW ContinueGame();
		mEntities.push_back(continueGame);


		Instructions *instructions = DBG_NEW Instructions();
		mEntities.push_back(instructions);
	}

	void MenuState::OnUpdate(float dt) {
		InputState inputState;
		mCommon->getInputState(&inputState);

		accumulatorKeyPress -= dt;
		if (accumulatorKeyPress <= 0) {
			accumulatorKeyPress = 0;
		}
		if (inputState.isDown(Button::BUTTON_MOUSELEFT) && accumulatorKeyPress == 0) {
			CheckInput(Vec2(inputState.mMouseX, inputState.mMouseY));
			accumulatorKeyPress = delayKeyPress;
		}
	}

	void MenuState::OnRender() {

	}

	void MenuState::CheckInput(Vec2 coordinates) {
		Vec4 hitbox;
		for (Entity *e : mEntities) {
			if (e->Type() == ENTITY_CONTINUE) {
				hitbox.x = ((ContinueGame*)e)->GetPosition().x - 100;
				hitbox.y = ((ContinueGame*)e)->GetPosition().y - 8;
				hitbox.w = 200;
				hitbox.z = 16;

				if ((coordinates.x > hitbox.x && coordinates.x < hitbox.x + hitbox.w) && ((coordinates.y > hitbox.y && coordinates.y < hitbox.y + hitbox.z))) {
					clickedContinueGame = true;
				}
			} else if (e->Type() == ENTITY_HELP) {
				hitbox.x = ((Controlls*)e)->GetPosition().x - 55;
				hitbox.y = ((Controlls*)e)->GetPosition().y - 8;
				hitbox.w = 110;
				hitbox.z = 16;

				if ((coordinates.x > hitbox.x && coordinates.x < hitbox.x + hitbox.w) && ((coordinates.y > hitbox.y && coordinates.y < hitbox.y + hitbox.z))) {
					clickedContinueGame = true;
				}
			} else if (e->Type() == ENTITY_NEWGAME) {
				hitbox.x = ((Model::NewGame*)e)->GetPosition().x - 65;
				hitbox.y = ((Model::NewGame*)e)->GetPosition().y - 8;
				hitbox.w = 130;
				hitbox.z = 16;

				if ((coordinates.x > hitbox.x && coordinates.x < hitbox.x + hitbox.w) && ((coordinates.y > hitbox.y && coordinates.y < hitbox.y + hitbox.z))) {
					clickedNewGame = true;
				}
			}
		}
	}

	void MenuState::CollissionWall() {
		int index = 0;
		while (index < mEntities.size()) {
			Entity *e = mEntities[index];
			if (e->Type() == ENTITY_BACKGROUND) {
				Background *background = ((Background*)e);
				if (background->mPos.x < 20) {
					background->mDir = Vec2(0, 1);
				}

				if (background->mPos.x > GetMenuArea().x - 20) {
					background->mDir = Vec2(0, -1);
				}

				if (background->mPos.y < 20 && background->mPos.x < GetMenuArea().x - 20) {
					background->mDir = Vec2(-1, 0);
				}

				if (background->mPos.y > GetMenuArea().y - 20 && background->mPos.x > 20) {
					background->mDir = Vec2(1, 0);
				}
			}
			++index;
		}
	}

	void MenuState::SetMenuArea(Vec2 screen) {
		mMenuArea.x = screen.x;
		mMenuArea.y = screen.y;
	}

	Vec2 MenuState::GetMenuArea() {
		return mMenuArea;
	}
}