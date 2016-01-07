#include "ContinueGame.h"
#include "MenuModel.h"

namespace Model {
	ContinueGame::ContinueGame() {}

	ContinueGame::~ContinueGame() {}

	void ContinueGame::OnInit(MenuModel *m) {
		Entity::OnInit(m);

		mText = "No Current Game";
		mPos = Vec2(m->GetMenuArea().x / 2, m->GetMenuArea().y / 2 - 100);
		mColor = Color::Blue;
		mRotation = 0;
		mScale = Vec2(1, 1);
	}

	void ContinueGame::OnUpdate() {
		GetMenuModel()->OnContinueGameUpdated(this);
	}

	void ContinueGame::GameState(bool isGameStarted) {
		if (isGameStarted) {
			mText = "Continue Game!";
			mColor = Color::Blue;
		} else {
			mText = "No Current Game";
			mColor = Color::LightGray;
		}
	}
}