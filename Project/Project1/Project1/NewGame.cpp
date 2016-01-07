#include "NewGame.h"
#include "MenuModel.h"

namespace Model {
	NewGame::NewGame() {}

	NewGame::~NewGame() {}

	void NewGame::OnInit(MenuModel *m) {
		Entity::OnInit(m);

		mText = "New Game";
		mPos = Vec2(m->GetMenuArea().x / 2, m->GetMenuArea().y / 2 - 100);
		mColor = Color::Blue;
		mRotation = 0;
		mScale = Vec2(1, 1);
	}

	void NewGame::OnUpdate() {
		GetMenuModel()->OnNewGameUpdated(this);
	}
}