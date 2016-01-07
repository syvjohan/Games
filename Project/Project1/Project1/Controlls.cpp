#include "Controlls.h"
#include "MenuModel.h"

namespace Model {
	Controlls::Controlls() {}


	Controlls::~Controlls() {}

	void Controlls::OnInit(MenuModel *m) {
		Entity::OnInit(m);

		mText = "Controlls";
		mPos = Vec2(m->GetMenuArea().x / 2, m->GetMenuArea().y / 2 + 200);
		mColor = Color::Blue;
		mRotation = 0;
		mScale = Vec2(1, 1);
	}

	void Controlls::OnUpdate() {
		GetMenuModel()->OnControllsUpdated(this);
	}
}
