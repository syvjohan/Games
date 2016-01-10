#include "Help.h"
#include "MenuModel.h"

namespace Model {
	Help::Help() {}

	Help::~Help() {}

	void Help::OnInit(MenuModel *m) {
		Entity::OnInit(m);
		
		mText = "default";
		mPos = Vec2(GetMenuModel()->GetMenuArea().x / 2, GetMenuModel()->GetMenuArea().y / 2 + 100);
		mColor = Color::Blue;
		mRotation = 0;
		mScale = Vec2(1, 1);

		switch (m->helpRow) {
			case 0:
				UpdateTextHeader();
				break;
			case 1:
				UpdateTextDescript1();
				break;
			case 2:
				UpdateTextDescript2();
				break;
			case 3:
				UpdateTextHeader2();
				break;
			case 4:
				UpdateTextDescript3();
				break;
			case 5:
				UpdateTextDescript4();
				break;
		}

		++m->helpRow;
	}

	void Help::OnUpdate() {
		GetMenuModel()->OnHelpUpdated(this);
	}

	void Help::UpdateTextHeader() {
		mText = "Instructions";
		mPos = Vec2(GetMenuModel()->GetMenuArea().x / 2, GetMenuModel()->GetMenuArea().y / 2 + 100);
		mColor = Color::Blue;
		mIsHeader = true;
	}

	void Help::UpdateTextDescript1() {
		mText = "Avoid to get hit by the asteroids, on a second hit by the asteroids the ship will explode..";
		mPos = Vec2(GetMenuModel()->GetMenuArea().x / 2 + 100, GetMenuModel()->GetMenuArea().y / 2 + 140);
		mColor = Color::LightGray;
		mIsHeader = false;
	}

	void Help::UpdateTextDescript2() {
		mText = "There is 3 levels and each level is 30 seconds";
		mPos = Vec2(GetMenuModel()->GetMenuArea().x / 2 + 60, GetMenuModel()->GetMenuArea().y / 2 + 160);
		mColor = Color::LightGray;
		mIsHeader = false;
	}

	void Help::UpdateTextHeader2() {
		mText = "Controlls";
		mPos = Vec2(GetMenuModel()->GetMenuArea().x / 2, GetMenuModel()->GetMenuArea().y / 2 + 220);
		mColor = Color::Blue;
		mIsHeader = true;
	}

	void Help::UpdateTextDescript3() {
		mText = "Stear with 'w', 'a', 's', 'd' and shot with 'space.";
		mPos = Vec2(GetMenuModel()->GetMenuArea().x / 2 + 60, GetMenuModel()->GetMenuArea().y / 2 + 260);
		mColor = Color::LightGray;
		mIsHeader = false;
	}

	void Help::UpdateTextDescript4() {
		mText = "Navigate between game and menu with 'Esc'. Exit game by clicking the cross in upper right corner.";
		mPos = Vec2(GetMenuModel()->GetMenuArea().x / 2 + 100, GetMenuModel()->GetMenuArea().y / 2 + 280);
		mColor = Color::LightGray;
		mIsHeader = false;
	}
}