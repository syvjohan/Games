#include "AsteroidSystem.h"

namespace View {
	AsteroidSystem::AsteroidSystem() {}

	AsteroidSystem::AsteroidSystem(Common &common, Vec2 scale, Vec2 playArea) {
		this->common = common;
		this->playArea = playArea;

		InitAsteroids();
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
			AddAsteroids(InRange(1, 10), 1, Vec2(-1, -1));
			AddAsteroids(InRange(1, 10), 2, Vec2(-1, -1));

			time = 0;
		}
	}

	void AsteroidSystem::AddAsteroids(int length, int type, Vec2 startPosition) {
		switch (type) {
			case 1:
				for (int i = 0; i != length; ++i) {
					Model::Asteroid a;
					a.animation.mTexture = common.getTextureResource("asteroid1");
					a.mType = 1;
					a.mScale = Vec2(1, 1);
					if (startPosition.x == -1 && startPosition.y == -1) {
						a.mPos.x = playArea.x + 72;
						a.mPos.y = InRange(72 * a.mScale.y, playArea.y * a.mScale.y);
					} else {
						a.mScale = Vec2(a.mScale / 2);
						a.mPos = startPosition;
						a.mVel.y = InRange(-10, 10);
					}
					
					a.mDir = Vec2(InRange(-1, -10), InRange(-1, 1));
					a.mVel += Vec2(InRange(.1f, 1.f), 0);
					a.mSize = Vec2(72, 72);

					a.animation.mCurrentFrame = 0;
					a.animation.mFrameTime = 0.0f;

					asteroids.push_back(a);
				}
				break;
			case 2:
				for (int i = 0; i != length; ++i) {
					Model::Asteroid a;
					a.animation.mTexture = common.getTextureResource("asteroid2");
					a.mType = 2;
					a.mScale = Vec2(1, 1);
					if (startPosition.x == -1 && startPosition.y == -1) {
						a.mPos.x = playArea.x + 64;
						a.mPos.y = InRange(64 * a.mScale.y, playArea.y * a.mScale.y);
					} else {
						a.mScale = Vec2(a.mScale / 2);
						a.mPos = startPosition;
						a.mVel.y = InRange(-10, 10);
					}

					a.mDir = Vec2(InRange(-1, -10), InRange(-1, 1));
					a.mVel += Vec2(InRange(.1f, 1.f), 0);
					a.mSize = Vec2(64, 64);

					a.animation.mCurrentFrame = 0;
					a.animation.mFrameTime = 0.0f;

					asteroids.push_back(a);
				}
				break;
			case 3:
				for (int i = 0; i != length; ++i) {
					Model::Asteroid a;
					a.animation.mTexture = common.getTextureResource("asteroid3");
					a.mType = 3;
					a.mScale = Vec2(1, 1);
					if (startPosition.x == -1 && startPosition.y == -1) {
						a.mPos.x = playArea.x + 32;
						a.mPos.y = InRange(32 * a.mScale.y, playArea.y * a.mScale.y);
					} else {
						a.mScale = Vec2(a.mScale / 2);
						a.mPos = startPosition;
						a.mVel.y = InRange(-10, 10);
					}

					a.mDir = Vec2(InRange(-1, -10), InRange(-1, 1));
					a.mVel += Vec2(InRange(.1f, 1.f), 0);
					a.mSize = Vec2(32, 32);

					a.animation.mCurrentFrame = 0;
					a.animation.mFrameTime = 0.0f;

					asteroids.push_back(a);
				}
				break;
			case 4:
				for (int i = 0; i != length; ++i) {
					Model::Asteroid a;
					a.animation.mTexture = common.getTextureResource("asteroid4");
					a.mType = 4;
					a.mScale = Vec2(1, 1);
					if (startPosition.x == -1 && startPosition.y == -1) {
						a.mPos.x = playArea.x + 32;
						a.mPos.y = InRange(32 * a.mScale.y, playArea.y * a.mScale.y);
					} else {
						a.mScale = Vec2(a.mScale / 2);
						a.mPos = startPosition;
						a.mVel.y = InRange(-10, 10);
					}

					a.mDir = Vec2(InRange(-1, -10), InRange(-1, 1));
					a.mVel += Vec2(InRange(.1f, 1.f), 0);
					a.mSize = Vec2(32, 32);

					a.animation.mCurrentFrame = 0;
					a.animation.mFrameTime = 0.0f;

					asteroids.push_back(a);
				}
				break;
			case 5:
				for (int i = 0; i != length; ++i) {
					Model::Asteroid a;
					a.animation.mTexture = common.getTextureResource("asteroid5");
					a.mType = 5;
					a.mScale = Vec2(1, 1);
					if (startPosition.x == -1 && startPosition.y == -1) {
						a.mPos.x = playArea.x + 72;
						a.mPos.y = InRange(72 * a.mScale.y, playArea.y * a.mScale.y);
					} else {
						a.mScale = Vec2(a.mScale / 2);
						a.mPos = startPosition;
						a.mVel.y = InRange(-10, 10);
					}

					a.mDir = Vec2(InRange(-1, -10), InRange(-1, 1));
					a.mVel += Vec2(InRange(.1f, 1.f), 0);
					a.mSize = Vec2(72, 72);

					a.animation.mCurrentFrame = 0;
					a.animation.mFrameTime = 0.0f;

					asteroids.push_back(a);
				}
				break;
			case 6:
				for (int i = 0; i != length; ++i) {
					Model::Asteroid a;
					a.animation.mTexture = common.getTextureResource("asteroid6");
					a.mType = 6;
					a.mScale = Vec2(1, 1);
					if (startPosition.x == -1 && startPosition.y == -1) {
						a.mPos.x = playArea.x + 64;
						a.mPos.y = InRange(64 * a.mScale.y, playArea.y * a.mScale.y);
					} else {
						a.mScale = Vec2(a.mScale / 2);
						a.mPos = startPosition;
						a.mVel.y = InRange(-10, 10);
					}

					a.mDir = Vec2(InRange(-1, -10), InRange(-1, 1));
					a.mVel += Vec2(InRange(.1f, 1.f), 0);
					a.mSize = Vec2(64, 64);

					a.animation.mCurrentFrame = 0;
					a.animation.mFrameTime = 0.0f;

					asteroids.push_back(a);
				}
				break;
		}
	}

	void AsteroidSystem::InitAsteroids() {
		AddAsteroids(4, 1, Vec2(-1, -1));
		AddAsteroids(4, 2, Vec2(-1, -1));
		AddAsteroids(3, 3, Vec2(-1, -1));
		AddAsteroids(4, 4, Vec2(-1, -1));
		AddAsteroids(4, 5, Vec2(-1, -1));
		AddAsteroids(4, 6, Vec2(-1, -1));
	}

	void AsteroidSystem::Render(Renderer2D *renderer) {
		RectangleF clip = { 0, 0, 0, 0 };
		for (int i = 0; i != asteroids.size(); ++i) {
			Model::Asteroid *a = &asteroids[i];
			clip.x = (a->animation.mCurrentFrame % 5) * a->mSize.x;
			clip.y = (a->animation.mCurrentFrame / 5) * a->mSize.y;
			clip.w = a->mSize.x;
			clip.h = a->mSize.y;

			renderer->draw(a->animation.mTexture,
						   a->mPos,
						   clip,
						   Vec2(clip.w / 2, clip.h / 2),
						   0.0f,
						   a->mScale,
						   Color::White,
						   0.0f);
		}
	}

	void AsteroidSystem::Update(const float dt) {

		for (auto it = asteroids.begin(); it != asteroids.end(); ++it) {
			if (it->mPos.x + it->mSize.x < 0) {
				it = asteroids.erase(it);
				if (it == asteroids.end()) {
					break;
				}
			} else {
				it->animation.mFrameTime += dt;

				if (it->animation.mFrameTime >= 0.041) {
					//Physics
					it->mVel += Vec2(.01f, .01f);
					it->mPos.x += it->mDir.x * it->mVel.x;
					it->mPos.y += it->mDir.y * it->mVel.y;

					//Animation
					it->animation.mFrameTime = 0.0;

					it->animation.mCurrentFrame++;
					if (it->animation.mCurrentFrame == 19) {
						it->animation.mCurrentFrame++;
					}

					if (it->animation.mCurrentFrame > 19) {
						it->animation.mCurrentFrame = 0;
					}
				}
			}
		}
	}

	std::vector<Vec4> AsteroidSystem::GetAsteroidPositions() {
		std::vector<Vec4> a;
		for (auto it = asteroids.begin(); it != asteroids.end(); ++it) {
			a.push_back(Vec4(it->mPos.x, it->mPos.y, it->mSize.x * it->mScale.x, it->mSize.y * it->mScale.y));
		}
		return a;
	}

	void AsteroidSystem::AsteroidIsHit(int index) {
		if (index != -1) {
			AddAsteroids(2, asteroids.at(index).mType, Vec2(asteroids.at(index).mPos));
			RemoveAsteroids(index);
		}
	}

	void AsteroidSystem::RemoveAsteroids(int index) {
		asteroids.erase(asteroids.begin() + index);
	}
}