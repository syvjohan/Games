#include "SplitterSystem.h"

namespace View {

	SplitterSystem::SplitterSystem() {}

	SplitterSystem::SplitterSystem(Common &common, Vec2 scale, Vec2 screen, Vec2 startPosition) {
		InitParams(common);
		//128 size of image.
		InitEmitter(128 / 1.f, scale, screen, startPosition);
	}

	SplitterSystem::~SplitterSystem() {
		delete[] emitter.mParticles;
		emitter.mParticles = NULL;
	}

	float SplitterSystem::r1() {
		return (float)(rand() % 10001) / 10000.0f;
	}

	float SplitterSystem::r2() {
		return r1() * 2.0f - 1.0f;
	}

	float SplitterSystem::InRange(float min, float max) {
		return min + (max - min) * r1();
	}

	void SplitterSystem::InitParams(Common &common) {
		params.mTexture = common.getTextureResource("spark");
		GetParams();
	}

	void SplitterSystem::GetParams() {
		params.mMaxParticles = 100;
		params.mMinParticles = 100;
		params.mMinLifeTimeMs = 1200;
		params.mMaxLifeTimeMs = 1600;
		params.mGravity = Vec2(0, 9.82);
	}

	void SplitterSystem::InitParticle(Model::Particle *p, Vec2 scale) {
		p->mPos = emitter.mPosition;
		p->mVel = Vec2(0, 0);
		p->mMaxTime = InRange(emitter.mParams.mMinLifeTimeMs, emitter.mParams.mMaxLifeTimeMs) / 1000.0f;
		p->mTime = p->mMaxTime;
		p->mOrientation = InRange(0.0f, 3.141592f * 2.0f);
		p->mDir = { InRange(-.6f, .6f), InRange(-.6f, .6f) };
		p->mTint = Color::White;
		p->mScale = scale;
		p->mAngularVelocity = r2() * 5.0f;

		float t = r2() * 70;

		p->mAcc = Vec2(t, r1() * -150);
	}

	void SplitterSystem::InitEmitter(float metersToPixels, Vec2 scale, Vec2 screen, Vec2 startPosition) {
		emitter.mPosition.x = startPosition.x * scale.x;
		emitter.mPosition.y = startPosition.y * scale.y;

		/*if (scale.x <= .7f && scale.x >= .5f) {
			emitter.mPosition.x -= 1.3;
			emitter.mPosition.y += 1.f;
		} else if (scale.x <= .5f) {
			emitter.mPosition.x -= 3;
			emitter.mPosition.y += 2;
		}*/

		emitter.mParams = params;

		emitter.mParticleCapacity = params.mMaxParticles;
		emitter.mParticles = DBG_NEW Model::Particle[emitter.mParticleCapacity];
		emitter.mParticleCount = emitter.mParams.mMinParticles;

		emitter.mMetersToPixels = metersToPixels * scale.x;

		emitter.mParticles->mScale = scale;

		// create particles.
		for (int i = 0; i < emitter.mParams.mMinParticles; ++i) {
			InitParticle(emitter.mParticles + i, scale);
		}
	}

	void SplitterSystem::UpdateEmitter(const float dt) {
		for (int particleIndex = 0; particleIndex < emitter.mParticleCount; ++particleIndex) {
			Model::Particle *part = emitter.mParticles + particleIndex;
			part->mTime -= dt;

			//Game physics!
			part->mAcc += emitter.mParams.mGravity;

			part->mPos = part->mPos + part->mVel + part->mAcc * dt * dt / 2;
			part->mVel = part->mVel + part->mAcc * dt * 4.5f;

			part->mAcc = Vec2(0, 0);
		}
	}

	void SplitterSystem::RenderEmitter(Renderer2D *renderer) {
		// set Particle size.
		int width, height;
		emitter.mParams.mTexture->getDimensions(&width, &height);
		width *= emitter.mParticles->mScale.x;
		height *= emitter.mParticles->mScale.y;

		RectangleF clip = { 0, 0, width, height };
		Vec2 origin = { width / 2.0f, height / 2.0f };

		for (int i = 0; i < emitter.mParticleCount; ++i) {

			Vec4 tint = Vec4::lerp(
			{ emitter.mParticles[i].mTint.R, emitter.mParticles[i].mTint.G, emitter.mParticles[i].mTint.B, 0.0f },
			emitter.mParticles[i].mTint,
			emitter.mParticles[i].mTime / emitter.mParticles[i].mMaxTime
			);

			renderer->draw(emitter.mParams.mTexture,
						   (emitter.mParticles[i].mPos /** emitter.mMetersToPixels*/),
						   clip,
						   origin,
						   emitter.mParticles[i].mOrientation,
						   emitter.mParticles[i].mScale * 0.15f, //change size of image to desired size.
						   tint,
						   0.0f
						   );
		}
	}
}