#include "ExplosionAnimation.h"

namespace View {
	ExplosionAnimation::ExplosionAnimation() {}

	ExplosionAnimation::ExplosionAnimation(Common *common, Vec2 scale, Vec2 startPosition) {
		this->common = common;
		InitAnimation(scale, startPosition);

		source = common->getAudio()->getSource();
		PlaySoundEffect();
	}

	ExplosionAnimation::~ExplosionAnimation() {

	}

	void ExplosionAnimation::InitAnimation(Vec2 scale, Vec2 startPosition) {
		animation.mTexture = common->getTextureResource("explosion");

		animation.mPos.x = startPosition.x * scale.x;
		animation.mPos.y = startPosition.y * scale.y;
		animation.mCurrentFrame = 0;
		animation.mFrameTime = 0.0f;
		animation.mScale = scale;
		animation.lifetime = 24.0f;
	}

	void ExplosionAnimation::Update(const float dt) {
		animation.mFrameTime += dt;

		if (animation.mFrameTime >= 0.021) {
			animation.mFrameTime = 0.0;
			animation.mCurrentFrame++;

			animation.lifetime--;

			if (animation.mCurrentFrame > 24) {
				animation.mCurrentFrame = 0;
			}
		}
	}

	void ExplosionAnimation::Render(Renderer2D *renderer) {
		int width = 128;
		int height = 128;
		RectangleF clip = { 0, 0, width, height };
		Vec2 origin = Vec2(clip.w / 2, clip.h / 2);

		clip.x = (animation.mCurrentFrame % 4) * width;
		clip.y = (animation.mCurrentFrame / 4) * height;

		renderer->draw(animation.mTexture,
					   animation.mPos, //position
					   clip,
					   origin,
					   0.0f,
					   animation.mScale,
					   Color::White,
					   0.0f);
	}

	int ExplosionAnimation::HasEnd() {
		if (animation.lifetime == 0) {
			return 1;
		}
		return -1;
	}

	void ExplosionAnimation::PlaySoundEffect() {
		if (source) {
			source->play(common->getSoundResource("soundExplosion"));
		}
	}
}