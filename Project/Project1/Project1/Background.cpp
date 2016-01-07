#include "Background.h"
#include "MenuModel.h"

namespace Model {
	Background::Background() {}

	Background::~Background() {}

	void Background::OnInit(MenuModel *m) {
		Entity::OnInit(m);

		mPos = Vec2(20, 20);
		mVel = Vec2(70, 70);
		mDir = Vec2(-1, 0);
		mScale = Vec2(1, 1);
		mSize = Vec2(2560, 1600);
		mColor = Color::White;
		mRotation = 0;
	}

	void Background::OnUpdate() {
		GetMenuModel()->OnBackgroundUpdated(this);
	}

	void Background::OnUpdatePhysics(const float dt) {
		mPos.x -= mDir.x * mVel.x * dt;
		mPos.y -= mDir.y * mVel.y * dt;
	}

}