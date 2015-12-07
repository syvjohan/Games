#include "SplitterSystem.h"

SplitterSystem::SplitterSystem() {}

SplitterSystem::SplitterSystem(Common &common, float scale, float screenW, float screenH) {
	InitParams(common);
	//128 size of image(spark).
	InitEmitter(128 / 1.f, scale, screenW, screenH);
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
	params.mTexture = common.getTextureResource("spark");
	params.mMaxParticles = 100;
	params.mMinParticles = 100;
	params.mMinLifeTimeMs = 1800;
	params.mMaxLifeTimeMs = 2500;
	params.mGravity = Vec2(0, 9.82);
}

void SplitterSystem::InitParticle(Particle *p, float scale) {
	p->mPos = emitter.mPosition;
	p->mVel = Vec2(0, 0);
	p->mMaxTime = InRange(emitter.mParams.mMinLifeTimeMs, emitter.mParams.mMaxLifeTimeMs) / 1000.0f;
	p->mTime = p->mMaxTime;
	p->mOrientation = InRange(0.0f, 3.141592f * 2.0f * scale);
	p->mTint = Color::White;
	p->mScale = Vec2(scale, scale);
	p->mAngularVelocity = r2() * 5.0f;

	float t = r2() * 70;

	p->mAcc = Vec2(t, r1() * -150);
}

void SplitterSystem::InitEmitter(float metersToPixels, float scale, float screenW, float screenH) {
	emitter.mPosition.x = screenW / 2 / 100 - 2 * scale;
	emitter.mPosition.y = screenH / 2 / 100 - 2 * scale;
	if (scale <= .7f && scale >= .5f) {
		emitter.mPosition.x -= 1.3;
		emitter.mPosition.y += 1.f;
	} else if (scale <= .5f) {
		emitter.mPosition.x -= 3;
		emitter.mPosition.y += 2;
	}

	emitter.mParams = params;

	emitter.mParticleCapacity = params.mMaxParticles;
	emitter.mParticles = DBG_NEW Particle[emitter.mParticleCapacity];
	emitter.mParticleCount = emitter.mParams.mMinParticles;

	emitter.mMetersToPixels = metersToPixels * scale;

	emitter.mParticles->mScale.x = scale;
	emitter.mParticles->mScale.y = scale;

	// create particles.
	for (int i = 0; i < emitter.mParams.mMinParticles; ++i) {
		InitParticle(emitter.mParticles + i, scale);
	}
}

void SplitterSystem::UpdateEmitter(const float dt) {
	for (int particleIndex = 0; particleIndex < emitter.mParticleCount; ++particleIndex) {
		Particle *part = emitter.mParticles + particleIndex;
		part->mTime -= dt;

		//Game physics!
		part->mAcc += emitter.mParams.mGravity;
		part->mPos = part->mPos + part->mVel + part->mAcc * dt * dt / 2;
		part->mVel = part->mVel + part->mAcc * dt * dt;

		part->mOrientation = part->mAngularVelocity * dt * part->mScale.x; //to controll direction

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
					   (emitter.mParticles[i].mPos * emitter.mMetersToPixels),
					   clip,
					   origin,
 					   emitter.mParticles[i].mOrientation,
					   emitter.mParticles[i].mScale * .15f, //change size of image to desired size.
					   tint,
					   0.0f
					   );
	}
}

void SplitterSystem::FreeMem() {
	delete emitter.mParticles;
}