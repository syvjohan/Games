#include "HealthPackage.h"
#include "ManagerModel.h"

namespace Model {
	HealthPackage::HealthPackage() {}

	HealthPackage::~HealthPackage() {}

	void HealthPackage::OnInit(ManagerModel *m) {
		Entity::OnInit(m);

		mPos.x = m->GetPlayArea().x;
		mPos.y = InRange(0, m->GetPlayArea().y);
		mDir = Vec2(InRange(-1, -10), InRange(-2, 2));
		mVel += Vec2(InRange(.2f, .2f), 0);
		mScale = Vec2(0.2f, 0.2f);
		mSize = Vec2(150, 150);
		mColor = Color::White;
		mRotation = 0;
	}

	float HealthPackage::InRange(float min, float max) {
		return min + (max - min) * r1();
	}

	float HealthPackage::r1() {
		return (float)(rand() % 10001) / 10000.0f;
	}

	void HealthPackage::OnUpdate() {
		GetModel()->OnHealthPackageMoved(this);
	}

	void HealthPackage::OnUpdatePhysics(const float dt) {
		mPos.x += mDir.x * mVel.x;
		mPos.y += mDir.y * mVel.y;
	}
}