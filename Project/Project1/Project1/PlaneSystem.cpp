#include "PlaneSystem.h"

namespace View {

	PlaneSystem::PlaneSystem() {}

	PlaneSystem::PlaneSystem(Common &common, Vec2 scale, Vec2 screen, float boarderMargin) {
		InitParams(common);
		//128 size of image.
		InitEmitter(140 / 1.f, scale, screen, boarderMargin);
	}

	PlaneSystem::~PlaneSystem() {}

	void PlaneSystem::InitParams(Common &common) {
		params.mTexture = common.getTextureResource("plane");
		GetParams();
	}

	void PlaneSystem::GetParams() {
		params.mMaxParticles = 1;
		params.mMinParticles = 1;
		params.mGravity = Vec2(0, 9.82);
	}

	void PlaneSystem::InitParticle(Model::Particle *p, Vec2 scale) {
		p->mPos = emitter.mPosition;
		p->mVel = Vec2(1, 1);
		p->mDir = Vec2(0, 0);
		p->mTint = Color::White;
		p->mScale = scale;
		p->mOrientation = 1.58f;
		p->mSize = Vec2(116, 140);
	}

	void PlaneSystem::InitEmitter(float metersToPixels, Vec2 scale, Vec2 screen, float boarderMargin) {
		emitter.mPlayArea = Vec2(screen.x * scale.x, screen.y * scale.y);
		
		emitter.mPosition.x = emitter.mPlayArea.x / 12;
		emitter.mPosition.y = emitter.mPlayArea.y / 2;

		emitter.mParams = params;

		emitter.mParticleCapacity = params.mMaxParticles;
		emitter.mParticles = DBG_NEW Model::Particle[1];
		emitter.mParticleCount = 1;

		emitter.mParticleCount = 1;

		emitter.mMetersToPixels = metersToPixels * scale.x;

		emitter.mParticles->mScale = scale;

		// create particles.
		InitParticle(emitter.mParticles + 0, scale);
	}

	void PlaneSystem::UpdateEmitter(const float dt, const float boarderMargin) {
		Model::Particle *plane = emitter.mParticles + 0;

		//Game physics
		plane->mPos = plane->mVel * dt * dt;
		plane->mPos += plane->mDir;

		if (plane->mPos.x < boarderMargin) {
			plane->mPos.x = boarderMargin;
		}

		if (plane->mPos.x > emitter.mPlayArea.x - plane->mSize.x - boarderMargin) {
			plane->mPos.x = emitter.mPlayArea.x - plane->mSize.x - boarderMargin;
		}

		if (plane->mPos.y < plane->mSize.y - boarderMargin) {
			plane->mPos.y = plane->mSize.y - boarderMargin;
		}

		if (plane->mPos.y > emitter.mPlayArea.y - boarderMargin) {
			plane->mPos.y = emitter.mPlayArea.y - boarderMargin;
		}
	}

	void PlaneSystem::RenderEmitter(Renderer2D *renderer) {
		RectangleF clip = { 0, 0, emitter.mParticles->mSize.x, emitter.mParticles->mSize.y };
		Vec2 origin = { clip.x / 2.0f, clip.y / 2.0f };

		renderer->draw(emitter.mParams.mTexture,
					   (emitter.mParticles[0].mPos),
						clip,
						origin,
						emitter.mParticles->mOrientation,
						emitter.mParticles[0].mScale,
						Color::White,
						0.0f
						);
	}

	void PlaneSystem::Move(int dir) {
		Model::Particle *plane = emitter.mParticles + 0;
		//plane->mVel = Vec2(.0001f, .0001f);

		switch (dir) {
			case 1:
				plane->mDir.y -= 10; //Upp
				break;
			case 2:
				plane->mDir.y += 10; //Down
				break;
			case 3:
				plane->mDir.x -= 10; //Back
				break;
			case 4:
				plane->mDir.x += 10; //Forward
				break;
			default:
				break;
		}
	}

	Vec2 PlaneSystem::GetFirePosition() {
		return Vec2(emitter.mParticles[0].mPos.x + emitter.mParticles->mSize.x + 120, emitter.mParticles[0].mPos.y - 2);
	}
}