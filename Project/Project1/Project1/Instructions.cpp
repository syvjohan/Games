#include "Instructions.h"
#include "MenuModel.h"

namespace Model {
	Instructions::Instructions() {}


	Instructions::~Instructions() {}

	void Instructions::OnInit(MenuModel *m) {
		Entity::OnInit(m);

		mText = "Instructions";
		mPos = Vec2(m->GetMenuArea().x / 2, m->GetMenuArea().y / 2 + 100);
		mColor = Color::Blue;
		mRotation = 0;
		mScale = Vec2(1, 1);
	}

	void Instructions::OnUpdate() {
		GetMenuModel()->OnInstructionsUpdated(this);
	}
}