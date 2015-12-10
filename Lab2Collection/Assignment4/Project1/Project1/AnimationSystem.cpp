#include "AnimationSystem.h"

AnimationSystem::AnimationSystem() {}

AnimationSystem::AnimationSystem(Common &common, Vec2 scale, Vec2 screen) {
	InitAnimation(common, scale, screen);
}

AnimationSystem::~AnimationSystem() {}

void AnimationSystem::InitAnimation(Common &common, Vec2 scale, Vec2 screen) {
	animation.texture = common.getTextureResource("explosion");

	animation.pos.x = screen.x / 2 * scale.x;
	animation.pos.y = screen.y / 2 * scale.y;
	animation.currentFrame = 0;
	animation.frameTime = 0.0f;
	animation.scale = scale;
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
				   animation.pos, //position
				   clip,
				   Vec2(0),
				   0.0f,
				   animation.scale,
				   Color::White,
				   0.0f);
}

void AnimationSystem::FreeMem() {}