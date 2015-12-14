#include "Shockwave.h"


Shockwave::Shockwave() {}

Shockwave::Shockwave(Common &common, Vec2 scale, Vec2(screen)) {
	InitParams(common);

	InitEmitter(128 / 1.f, scale, screen);
}

Shockwave::~Shockwave() {
	delete [] emitter.mParticles;
	emitter.mParticles = NULL;
}

float Shockwave::r1() {
	return (float)(rand() % 10001) / 10000.0f;
}

float Shockwave::r2() {
	return r1() * 2.0f - 1.0f;
}

float Shockwave::InRange(float min, float max) {
	return min + (max - min) * r1();
}

void Shockwave::InitParams(Common &common) {
	params.mTexture = common.getTextureResource("spark");
	GetParams();
}

void Shockwave::GetParams() {
	params.mMaxParticles = 1;
	params.mMinParticles = 1;
	params.mMinLifeTimeMs = 3000;
	params.mMaxLifeTimeMs = 3000;
	params.mGravity = Vec2(0, 9.82);
}

void Shockwave::InitParticle(Particle *p, Vec2 scale) {
	p->mPos = emitter.mPosition;
	p->mVel = Vec2(0, 0);
	p->mMaxTime = InRange(emitter.mParams.mMinLifeTimeMs, emitter.mParams.mMaxLifeTimeMs) / 1000.0f;
	p->mTime = p->mMaxTime;
	p->mOrientation = 0;
	p->mDir = Vec2(0, 0);
	p->mTint = Color::Red;
	p->mScale = Vec2(scale.x * 0.f, scale.y * 0.f); //Start size is 0.f
	p->mAngularVelocity = 0;

	p->mAcc = Vec2(0.f,0.f);
}

void Shockwave::InitEmitter(float metersToPixels, Vec2 scale, Vec2 screen) {
	emitter.mPosition.x = screen.x / 3 * scale.x;
	emitter.mPosition.y = screen.y / 4 * scale.y;

	emitter.mParams = params;

	emitter.mParticleCapacity = params.mMaxParticles;
	emitter.mParticles = DBG_NEW Particle[emitter.mParticleCapacity];
	emitter.mParticleCount = emitter.mParams.mMinParticles;

	emitter.mMetersToPixels = metersToPixels * scale.x;

	emitter.mParticles->mScale = scale;

	// create particles.
	for (int i = 0; i < emitter.mParams.mMinParticles; ++i) {
		InitParticle(emitter.mParticles + i, scale);
	}
}

void Shockwave::UpdateEmitter(const float dt) {
	for (int particleIndex = 0; particleIndex < emitter.mParticleCount; ++particleIndex) {
		Particle *part = emitter.mParticles + particleIndex;
		part->mTime -= dt;

		//Game physics!
		part->mScale += Vec2(.1f, .1f);

		if (part->mTime < 0) {
			GetParams();
			InitParticle(part, part->mScale);
		}
	}
}

void Shockwave::RenderEmitter(Renderer2D *renderer) {
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
					   (emitter.mParticles[i].mPos),
					   clip,
					   origin,
					   emitter.mParticles[i].mOrientation,
					   emitter.mParticles[i].mScale,
					   tint,
					   0.0f
					   );
	}
}