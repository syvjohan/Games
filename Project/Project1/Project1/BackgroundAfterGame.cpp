#include "BackgroundAfterGame.h"
#include "MenuModel.h"

namespace Model {
	BackgroundAfterGame::BackgroundAfterGame() {}

	BackgroundAfterGame::~BackgroundAfterGame() {}

	void BackgroundAfterGame::OnInit(MenuModel *m) {
		Entity::OnInit(m);

		mPos = Vec2(600, 540);
		mScale = Vec2(1, 1);
		mSize = Vec2(1920, 1080);
		mColor = Color::White;
		mRotation = 0;
	}

	void BackgroundAfterGame::OnUpdate() {
		GetMenuModel()->OnBackgroundAfterGameUpdated(this);
	}
}