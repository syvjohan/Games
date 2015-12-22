#include "ShootSystem.h"

namespace View {
	ShootSystem::ShootSystem() {}

	ShootSystem::ShootSystem(Common &common, Vec2 scale, Vec2 screen) {
		InitParams(common);
		//128 size of image.
		InitEmitter(128 / 1.f, scale, screen);
	}

	ShootSystem::~ShootSystem() {}

	void ShootSystem::InitParams(Common &common) {
		params.mTexture = common.getTextureResource("shoot");
		GetParams();
	}

	void ShootSystem::GetParams() {
		params.mMaxParticles = 100;
		params.mMinParticles = 0;
		params.mGravity = Vec2(0, 9.82);
	}

	void ShootSystem::InitParticle(Model::Particle *p, Vec2 startPosition) {
		p->mPos = startPosition;
		p->mVel = Vec2(10, 0);
		p->mOrientation = 0;
		p->mDir = Vec2(10, 0);
		p->mTint = Color::White;
		p->mAngularVelocity = .0f;

		p->mAcc = Vec2(1, 0);
	}

	void ShootSystem::InitEmitter(float metersToPixels, Vec2 scale, Vec2 screen) {
		emitter.mParams = params;

		emitter.mParticleCapacity = params.mMaxParticles;
		emitter.mParticles = DBG_NEW Model::Particle[100];
		emitter.mParticleCount = emitter.mParams.mMinParticles;

		emitter.mMetersToPixels = metersToPixels * scale.x;

		emitter.mParticles->mScale = scale;
	}

	void ShootSystem::UpdateEmitter(const float dt) {
		for (int particleIndex = 0; particleIndex < emitter.mParticleCount; ++particleIndex) {
			Model::Particle *part = emitter.mParticles + particleIndex;

			//Game physics!
			part->mAcc += Vec2(.1f, 0);
			part->mPos += part->mVel + part->mAcc * dt / 2;
		}
	}

	void ShootSystem::AddShoot(Vec2 startPosition) {
		InitParticle(emitter.mParticles + emitter.mParticleCount, startPosition);
		++emitter.mParticleCount;
	}

	void ShootSystem::RenderEmitter(Renderer2D *renderer) {
		// set Particle size.
		int width, height;
		emitter.mParams.mTexture->getDimensions(&width, &height);
		width *= emitter.mParticles->mScale.x;
		height *= emitter.mParticles->mScale.y;

		RectangleF clip = { 0, 0, width, height };
		Vec2 origin = { width / 2.0f, height / 2.0f };

		for (int i = 0; i < emitter.mParticleCount; ++i) {
			renderer->draw(emitter.mParams.mTexture,
						   (emitter.mParticles[i].mPos),
						   clip,
						   origin,
						   emitter.mParticles[i].mOrientation,
						   emitter.mParticles[i].mScale * .15f,
						   Color::White,
						   0.0f
						   );
		}
	}
}