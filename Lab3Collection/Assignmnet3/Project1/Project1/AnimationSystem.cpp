#include "AnimationSystem.h"

namespace View {

	AnimationSystem::AnimationSystem() {}

	AnimationSystem::AnimationSystem(Common &common, Vec2 scale, Vec2 screen) {
		InitAnimation(common, scale, screen);
	}

	AnimationSystem::~AnimationSystem() {}

	void AnimationSystem::InitAnimation(Common &common, Vec2 scale, Vec2 screen) {
		animation.mTexture = common.getTextureResource("explosion");

		animation.mPos.x = screen.x / 2 * scale.x;
		animation.mPos.y = screen.y / 2 * scale.y;
		animation.mCurrentFrame = 0;
		animation.mFrameTime = 0.0f;
		animation.mScale = scale;
	}

	void AnimationSystem::UpdateEmitter(const float dt) {
		animation.mFrameTime += dt;

		if (animation.mFrameTime >= 0.021) {
			animation.mFrameTime = 0.0;
			animation.mCurrentFrame++;

			if (animation.mCurrentFrame > 24) {
				animation.mCurrentFrame = 0;
			}
		}
	}

	void AnimationSystem::RenderEmitter(Renderer2D *renderer) {
		RectangleF clip = { 0, 0, 128, 128 };

		clip.x = (animation.mCurrentFrame % 4) * 128;
		clip.y = (animation.mCurrentFrame / 4) * 128;

		renderer->draw(animation.mTexture,
					   animation.mPos, //position
					   clip,
					   Vec2(0),
					   0.0f,
					   animation.mScale,
					   Color::White,
					   0.0f);
	}
}