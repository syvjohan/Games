#include "AnimationSystem.h"

AnimationSystem::AnimationSystem() {}

AnimationSystem::AnimationSystem(Common &common) {
	InitAnimation(common);
}

AnimationSystem::~AnimationSystem() {}

void AnimationSystem::InitAnimation(Common &common) {
	animation.texture = common.getTextureResource("explosion");

	animation.currentFrame = 0;
	animation.frameTime = 0.0f;
}

void AnimationSystem::UpdateEmitter(const float dt) {
	animation.frameTime += dt;

	if (animation.frameTime >= 0.021) {
		animation.frameTime = 0.0;
		animation.currentFrame++;

		if (animation.currentFrame > 24) {
			animation.currentFrame = 0;
		}
	}
}

void AnimationSystem::RenderEmitter(Renderer2D *renderer) {
	RectangleF clip = { 0, 0, 128, 128 };

	clip.x = (animation.currentFrame % 4) * 128;
	clip.y = (animation.currentFrame / 4) * 128;

	renderer->draw(animation.texture,
				   Vec2(200, 200),
				   clip,
				   Vec2(0),
				   0.0f,
				   Vec2(1, 1),
				   Color::White,
				   0.0f);
}

void AnimationSystem::FreeMem() {}