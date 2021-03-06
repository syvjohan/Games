#include "SplitterSystem.h"

SplitterSystem::SplitterSystem() {}

SplitterSystem::SplitterSystem(Common &common, float screenH, float screenW) {
	InitParams(common);
	//16 size of image(spark).
	InitEmitter(16 / 1.f, screenH, screenW);
}

SplitterSystem::~SplitterSystem() {}

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
	params.mTexture = common.getTextureResource("smoke");
	getParams();
}

void SplitterSystem::getParams() {
	params.mMaxParticles = 120;
	params.mMinParticles = 80;
	params.mMinLifeTimeMs = 4000;
	params.mMaxLifeTimeMs = 6500;
	params.mGravity = Vec2(0, 9.82);
}

void SplitterSystem::InitParticle(Particle *p) {
	p->mPos = emitter.mPosition;
	p->mVel = Vec2(5, 5);
	p->mAcc = Vec2(10, 10);
	p->mMaxTime = InRange(emitter.mParams.mMinLifeTimeMs, emitter.mParams.mMaxLifeTimeMs) / 1000.0f;
	p->mTime = p->mMaxTime;
	p->mOrientation = InRange(0.0f, 3.141592f * 2.0f);
	p->mTint = Color::White;
	p->mScale = Vec2(1, 1);
	p->mAngularVelocity = r2() * .008f;
	p->mDir = { InRange(-.6f, .6f), InRange(-.6f, .6f) };

	p->mAcc = Vec2(r2() * 70, r1() * -750);
}

void SplitterSystem::InitEmitter(float metersToPixels, float screenH, float screenW) {
	emitter.mPosition.x = screenW / 2;
	emitter.mPosition.y = screenH - 10;

	emitter.mParams = params;

	emitter.mParticleCapacity = params.mMaxParticles;
	emitter.mParticles = DBG_NEW Particle[emitter.mParticleCapacity];
	emitter.mParticleCount = emitter.mParams.mMinParticles;

	emitter.mMetersToPixels = metersToPixels;

	//set number of particles.
	int numberOfParticles = InRange(emitter.mParams.mMinParticles, emitter.mParams.mMaxParticles);

	//set particle lifetime.
	float lifetime = InRange(emitter.mParams.mMinLifeTimeMs, emitter.mParams.mMaxLifeTimeMs);
	// create particles.
	for (int i = 0; i != numberOfParticles; ++i) {
		emitter.mParticles[i].mTime = lifetime;
		InitParticle(emitter.mParticles + i);
	}
}

void SplitterSystem::UpdateEmitter(const float dt) {
	for (int particleIndex = 0; particleIndex < emitter.mParticleCount; ++particleIndex) {
		Particle *part = emitter.mParticles + particleIndex;
		part->mTime -= dt;

		//Game physics!
		part->mAcc += { 10.f, 10.f };
		part->mPos.y -= 2.5f;
		
		if (part->mDir.x > 0) {
			part->mPos.x -= part->mDir.x;
		} else {
			part->mPos.x -= part->mDir.x;
		}
		
		part->mVel += part->mAcc * dt;
		part->mOrientation += part->mAngularVelocity;
		part->mScale += { .02f, .02f };

		//Recycling particles(resetting values).
		if (part->mTime < 0) {
			getParams();
			InitParticle(part);
		}
	}
}

void SplitterSystem::RenderEmitter(Renderer2D *renderer) {
	// set Particle size.
	int width, height;
	emitter.mParams.mTexture->getDimensions(&width, &height);
	RectangleF clip = { 0, 0, width, height };
	Vec2 origin = { width / 2.0f, height / 2.0f };

	for (int i = 0; i < emitter.mParticleCount; ++i) {

		Vec4 tint = Vec4::lerp(
		{ emitter.mParticles[i].mTint.R, emitter.mParticles[i].mTint.G, emitter.mParticles[i].mTint.B, 0.0f },
			emitter.mParticles[i].mTint,
			emitter.mParticles[i].mTime / emitter.mParticles[i].mMaxTime
		);

		renderer->draw(emitter.mParams.mTexture,
					   (emitter.mParticles[i].mPos),
					   clip,
					   origin,
 					   emitter.mParticles[i].mOrientation,
					   emitter.mParticles[i].mScale, //change size of image to desired size.
					   tint,
					   0.0f
					   );
	}
}

void SplitterSystem::FreeMem() {
	delete emitter.mParticles;
}