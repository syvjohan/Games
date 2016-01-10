#include "Result.h"
#include "MenuModel.h"

namespace Model {
	Result::Result() {}

	Result::~Result() {}

	void Result::OnInit(MenuModel *m) {
		Entity::OnInit(m);

		mPos = Vec2(GetMenuModel()->GetMenuArea().x / 2, GetMenuModel()->GetMenuArea().y / 2);
		mScale = Vec2(1, 1);
		mColor = Color::LightGray;
		mRotation = 0;
		mText = "default!!!default!!!default!!!default!!!default!!!default!!!default!!!default!!!";
	}

	void Result::UpdateText1() {
		mText = "Congratulations! Next level starts in 3 seconds.";
		mPos = Vec2(GetMenuModel()->GetMenuArea().x / 2 + 70, GetMenuModel()->GetMenuArea().y / 2);
	}

	void Result::UpdateText2() {
		mText = "You died! Same level starts in 3 seconds...";
		mPos = Vec2(GetMenuModel()->GetMenuArea().x / 2 + 70, GetMenuModel()->GetMenuArea().y / 2);
	}

	void Result::UpdateText3() {
		mText = "You have successfully finish the game. Redirecting back to menu.";
		mPos = Vec2(GetMenuModel()->GetMenuArea().x / 2, GetMenuModel()->GetMenuArea().y / 2);
	}

	void Result::OnUpdate() {
		GetMenuModel()->OnResultUpdated(this);
	}
}