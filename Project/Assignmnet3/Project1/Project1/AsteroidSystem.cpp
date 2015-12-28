#include "AsteroidSystem.h"

namespace View {
	AsteroidSystem::AsteroidSystem() {}

	AsteroidSystem::AsteroidSystem(Common &common, Vec2 scale, Vec2 playArea) {
		this->common = common;
		this->scale = scale;
		this->playArea = playArea;

		InitAnimation();
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

	void AsteroidSystem::ExtendAsteroidBelt(const float dt) {
		time += dt; //Seconds
		if (time > 6) {
			AddAsteroids(InRange(1, 10), 1);
			AddAsteroids(InRange(1, 10), 2);

			time = 0;
		}
	}

	void AsteroidSystem::AddAsteroids(int length, int type) {
		int width = 0, height = 0;
		switch (type) {
			case 1:
				for (int i = 0; i != length; ++i) {
					Model::Asteroid a;
					a.animation.mTexture = common.getTextureResource("asteroid1");

					a.animation.mTexture->getDimensions(&width, &height);
					a.mPos.x = playArea.x + width;
					a.mPos.y = InRange(100 * scale.y, playArea.y * scale.y);
					a.mDir = Vec2(InRange(-1, -10));
					a.mScale = scale;
					a.mVel = Vec2(InRange(.1f, 1.f), InRange(.1f, 1.f));
					a.mSize = Vec2(72, 72);

					a.animation.mCurrentFrame = 0;
					a.animation.mFrameTime = 0.0f;

					asteroids1.push_back(a);
				}
				break;
			case 2:
				for (int i = 0; i != length; ++i) {
					Model::Asteroid a;
					a.animation.mTexture = common.getTextureResource("asteroid2");
					
					a.animation.mTexture->getDimensions(&width, &height);
					a.mPos.x = playArea.x + width;
					a.mPos.y = InRange(100 * scale.y, playArea.y * scale.y);
					a.mDir = Vec2(InRange(-1, -10));
					a.mScale = scale;
					a.mVel = Vec2(InRange(.1f, 1.f), InRange(.1f, 1.f));
					a.mSize = Vec2(64, 64);

					a.animation.mCurrentFrame = 0;
					a.animation.mFrameTime = 0.0f;

					asteroids2.push_back(a);
				}
				break;
			case 3:
				for (int i = 0; i != length; ++i) {
					Model::Asteroid a;
					a.animation.mTexture = common.getTextureResource("asteroid3");

					a.animation.mTexture->getDimensions(&width, &height);
					a.mPos.x = playArea.x + width;
					a.mPos.y = InRange(100 * scale.y, playArea.y * scale.y);
					a.mDir = Vec2(InRange(-1, -10));
					a.mScale = scale;
					a.mVel = Vec2(InRange(.1f, 1.f), InRange(.1f, 1.f));
					a.mSize = Vec2(32, 32);

					a.animation.mCurrentFrame = 0;
					a.animation.mFrameTime = 0.0f;

					asteroids3.push_back(a);
				}
				break;
			case 4:
				for (int i = 0; i != length; ++i) {
					Model::Asteroid a;
					a.animation.mTexture = common.getTextureResource("asteroid4");

					a.animation.mTexture->getDimensions(&width, &height);
					a.mPos.x = playArea.x + width;
					a.mPos.y = InRange(100 * scale.y, playArea.y * scale.y);
					a.mDir = Vec2(InRange(-1, -10));
					a.mScale = scale;
					a.mVel = Vec2(InRange(.1f, 1.f), InRange(.1f, 1.f));
					a.mSize = Vec2(32, 32);
	
					a.animation.mCurrentFrame = 0;
					a.animation.mFrameTime = 0.0f;

					asteroids4.push_back(a);
				}
				break;
			case 5:
				for (int i = 0; i != length; ++i) {
					Model::Asteroid a;
					a.animation.mTexture = common.getTextureResource("asteroid5");

					a.animation.mTexture->getDimensions(&width, &height);
					a.mPos.x = playArea.x + width;
					a.mPos.y = InRange(100 * scale.y, playArea.y * scale.y);
					a.mDir = Vec2(InRange(-1, -10));
					a.mScale = scale;
					a.mVel = Vec2(InRange(.1f, 1.f), InRange(.1f, 1.f));
					a.mSize = Vec2(72, 72);

					a.animation.mCurrentFrame = 0;
					a.animation.mFrameTime = 0.0f;

					asteroids4.push_back(a);
				}
				break;
			case 6:
				for (int i = 0; i != length; ++i) {
					Model::Asteroid a;
					a.animation.mTexture = common.getTextureResource("asteroid6");

					a.animation.mTexture->getDimensions(&width, &height);
					a.mPos.x = playArea.x + width;
					a.mPos.y = InRange(100 * scale.y, playArea.y * scale.y);
					a.mDir = Vec2(InRange(-1, -10));
					a.mScale = scale;
					a.mVel = Vec2(InRange(.1f, 1.f), InRange(.1f, 1.f));
					a.mSize = Vec2(64, 64);

					a.animation.mCurrentFrame = 0;
					a.animation.mFrameTime = 0.0f;

					asteroids4.push_back(a);
				}
				break;
		}
	}

	void AsteroidSystem::InitAnimation() {
		AddAsteroids(4, 1);
		AddAsteroids(4, 2);
		AddAsteroids(3, 3);
		AddAsteroids(4, 4);
		AddAsteroids(4, 5);
		AddAsteroids(4, 6);
	}

	void AsteroidSystem::Render(Renderer2D *renderer, std::vector<Model::Asteroid> &container) {
		RectangleF clip = { 0, 0, 0, 0 };
		for (int i = 0; i != container.size(); ++i) {
			clip.x = (container[i].animation.mCurrentFrame % 5) * container[i].mSize.x;
			clip.y = (container[i].animation.mCurrentFrame / 5) * container[i].mSize.y;
			clip.w = container[i].mSize.x;
			clip.h = container[i].mSize.y;

			renderer->draw(container[i].animation.mTexture,
						   container[i].mPos,
						   clip,
						   Vec2(clip.w / 2, clip.h / 2),
						   0.0f,
						   container[i].mScale,
						   Color::White,
						   0.0f);
		}
	}

	void AsteroidSystem::RenderAsteroids(Renderer2D *renderer) {
		Render(renderer, asteroids1);
		Render(renderer, asteroids2);
		Render(renderer, asteroids3);
		Render(renderer, asteroids4);
		Render(renderer, asteroids5);
		Render(renderer, asteroids6);
	}

	void AsteroidSystem::Update(const float dt, std::vector<Model::Asteroid> &container) {
		for (int i = 0; i != container.size(); ++i) {
			Model::Asteroid *a = &container[i];
			a->animation.mFrameTime += dt;

			if (a->animation.mFrameTime >= 0.041) {
				//Physics
				a->mVel += Vec2(.01f, .01f);
				a->mPos.x += a->mDir.x * a->mVel.x;

				//Animation
				a->animation.mFrameTime = 0.0;

				a->animation.mCurrentFrame++;
				if (a->animation.mCurrentFrame == 19) {
					a->animation.mCurrentFrame++;
				}

				if (a->animation.mCurrentFrame > 19) {
					a->animation.mCurrentFrame = 0;
				}
			}
		}
	}

	void AsteroidSystem::UpdateAsteroids(const float dt) {
		Update(dt, asteroids1);
		Update(dt, asteroids2);
		Update(dt, asteroids3);
		Update(dt, asteroids4);
		Update(dt, asteroids5);
		Update(dt, asteroids6);
	}
}