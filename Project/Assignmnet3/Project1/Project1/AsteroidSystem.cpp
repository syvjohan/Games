#include "AsteroidSystem.h"

namespace View {
	AsteroidSystem::AsteroidSystem() {}

	AsteroidSystem::AsteroidSystem(Common &common, Vec2 scale, Vec2 playArea) {
		InitAnimation(common, scale, playArea);
	}

	AsteroidSystem::~AsteroidSystem() {}

	float AsteroidSystem::r1() {
		return (float)(rand() % 10001) / 10000.0f;
	}

	float AsteroidSystem::r2() {
		return r1() * 2.0f - 1.0f;
	}

	float AsteroidSystem::InRange(float min, float max) {
		return min + (max - min) * r1();
	}

	void AsteroidSystem::InitAnimation(Common &common, Vec2 scale, Vec2 playArea) {
		for (int i = 0; i != 3; ++i) {
			Model::Asteroid a;
			a.animation.mTexture = common.getTextureResource("asteroid1");

			a.mPos.x = InRange((playArea.x / 2) * scale.x, playArea.x * scale.x);
			a.mPos.y = InRange(100 * scale.y, playArea.y * scale.y);
			a.animation.mCurrentFrame = 0;
			a.animation.mFrameTime = 0.0f;
			a.mScale = scale;
			asteroids1.push_back(a);
		}

		for (int i = 0; i != 4; ++i) {
			Model::Asteroid a;
			a.animation.mTexture = common.getTextureResource("asteroid3");

			a.mPos.x = InRange((playArea.x / 2) * scale.x, playArea.x * scale.x);
			a.mPos.y = InRange(100 * scale.y, playArea.y * scale.y);
			a.animation.mCurrentFrame = 0;
			a.animation.mFrameTime = 0.0f;
			a.mScale = scale;
			asteroids2.push_back(a);
		}
	}

	void AsteroidSystem::RenderAnimation(Renderer2D *renderer) {
		RectangleF clip1 = { 0, 0, 72, 72 };
		for (int i = 0; i != asteroids1.size(); ++i) {
			clip1.x = (asteroids1[i].animation.mCurrentFrame % 5) * 72;
			clip1.y = (asteroids1[i].animation.mCurrentFrame / 5) * 72;

			renderer->draw(asteroids1[i].animation.mTexture,
						   asteroids1[i].mPos, //position
						   clip1,
						   Vec2(36, 36),
						   0.0f,
						   asteroids1[i].mScale,
						   Color::White,
						   0.0f);
		}

		RectangleF clip2 = { 0, 0, 32, 32 };
		for (int i = 0; i != asteroids2.size(); ++i) {
			clip2.x = (asteroids2[i].animation.mCurrentFrame % 5) * 32;
			clip2.y = (asteroids2[i].animation.mCurrentFrame / 5) * 32;

			renderer->draw(asteroids2[i].animation.mTexture,
						   asteroids2[i].mPos, //position
						   clip2,   
						   Vec2(32, 32),
						   0.0f,
						   asteroids2[i].mScale,
						   Color::White,
						   0.0f);
		}
	}

	void AsteroidSystem::UpdateAnimation(const float dt) {
		for (int i = 0; i != asteroids1.size(); ++i) {
			asteroids1[i].animation.mFrameTime += dt;

			if (asteroids1[i].animation.mFrameTime >= 0.4) {
				asteroids1[i].animation.mFrameTime = 0.0;

				asteroids1[i].animation.mCurrentFrame++;
				if (asteroids1[i].animation.mCurrentFrame == 19) {
					asteroids1[i].animation.mCurrentFrame++;
				}

				if (asteroids1[i].animation.mCurrentFrame > 19) {
					asteroids1[i].animation.mCurrentFrame = 0;
				}
			}
		}

		for (int i = 0; i != asteroids2.size(); ++i) {
			asteroids2[i].animation.mFrameTime += dt;

			if (asteroids2[i].animation.mFrameTime >= 0.6) {
				asteroids2[i].animation.mFrameTime = 0.0;

				asteroids2[i].animation.mCurrentFrame++;
				if (asteroids2[i].animation.mCurrentFrame == 19) {
					asteroids2[i].animation.mCurrentFrame++;
				}

				if (asteroids2[i].animation.mCurrentFrame > 19) {
					asteroids2[i].animation.mCurrentFrame = 0;
				}
			}
		}
	}
}