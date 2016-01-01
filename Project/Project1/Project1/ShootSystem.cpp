#include "ShootSystem.h"

namespace View {
	ShootSystem::ShootSystem() {}

	ShootSystem::ShootSystem(Common *common, Vec2 playArea) {
		this->playArea = playArea;
		this->common = common;

		source = common->getAudio()->getSource();
	}

	ShootSystem::~ShootSystem() {}

	void ShootSystem::AddBullet(Vec2 scale, Vec2 startPosition) {
		Model::Bullet b;
		b.mTexture = common->getTextureResource("shoot");
		b.mPos = startPosition;
		b.mVel = Vec2(10, 0);
		b.mDir = Vec2(10, 0);
		b.mAcc = Vec2(1, 0);
		b.mScale = scale;

		int width, height;
		b.mTexture->getDimensions(&width, &height);
		b.mSize = Vec2(width, height);

		bullets.push_back(b);

		SoundEffect();
	}

	void ShootSystem::Update(const float dt) {
		for (auto it = bullets.begin(); it != bullets.end(); ++it) {
			if (it->mPos.x > playArea.x) {
				it = bullets.erase(it);
				if (it == bullets.end()) {
					break;
				}
			} else {
				it->mAcc += Vec2(.1f, 0);
				it->mPos += it->mVel + it->mAcc * dt / 2;
			}
		}
	}

	void ShootSystem::Render(Renderer2D *renderer) {
		RectangleF clip = { 0, 0, 0, 0 };
		Vec2 origin = { 0, 0 };

		for (int i = 0; i != bullets.size(); ++i) {
			Model::Bullet *b = &bullets[i];

			clip = { 0, 0, b->mSize.x, b->mSize.y };
			origin = { clip.w / 2.0f, clip.h / 2.0f };

			renderer->draw(b->mTexture,
							b->mPos,
							clip,
							origin,
							0,
							b->mScale * .15f,
							Color::Red,
							0.0f
							);
		}
	}

	std::vector<Vec4> ShootSystem::GetBulletsPositions() {
		std::vector<Vec4> b;
		for (auto it = bullets.begin(); it != bullets.end(); ++it) {
			b.push_back(Vec4(it->mPos.x, it->mPos.y, (it->mSize.x * .15f) * it->mScale.x, (it->mSize.y * .15f) * it->mScale.y));
		}
		return b;
	}

	void ShootSystem::RemoveBullet(int index) {
		if (index != -1) {
			bullets.erase(bullets.begin() + index);
		}
	}

	void ShootSystem::SoundEffect() {
		if (source) {
			source->play(common->getSoundResource("soundShoot"));

		}
	}
}