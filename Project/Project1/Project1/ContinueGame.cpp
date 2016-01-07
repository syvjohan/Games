#include "ContinueGame.h"
#include "MenuModel.h"

namespace Model {
	ContinueGame::ContinueGame() {}

	ContinueGame::~ContinueGame() {}

	void ContinueGame::OnInit(MenuModel *m) {
		Entity::OnInit(m);

		mText = "Continue";
		mPos = Vec2(m->GetMenuArea().x / 2, m->GetMenuArea().y / 2);
		mColor = Color::Blue;
		mRotation = 0;
		mScale = Vec2(1, 1);
	}

	void ContinueGame::OnUpdate() {
		GetMenuModel()->OnContinueGameUpdated(this);
	}
}