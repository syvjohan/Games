#include "HealthKeeper.h"
#include "ManagerModel.h"

namespace Model {
	HealthKeeper::HealthKeeper() {}

	HealthKeeper::~HealthKeeper() {}

	void HealthKeeper::OnInit(ManagerModel *m) {
		Entity::OnInit(m);

		sprintf(mText, "HP: %i%%", mHealth);
		mPos = Vec2(140, 20);
		mColor = Color::Yellow;
		mRotation = 0;
		mScale = Vec2(1, 1);
	}

	void HealthKeeper::OnUpdate() {
		if (mHealth == mMaxHealth / 2) {
			mColor = Color::Red;
		}

		sprintf(mText, "HP: %i%%", mHealth);

		GetModel()->OnHpUpdated(this);
	}
}