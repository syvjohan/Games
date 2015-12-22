#include "PlaneAnimation.h"

namespace View {
	PlaneAnimation::PlaneAnimation() {}

	PlaneAnimation::PlaneAnimation(Common &common, Vec2 scale, Vec2 screen) {
		InitAnimation(common, scale, screen);
	}

	PlaneAnimation::~PlaneAnimation() {}

	void PlaneAnimation::InitAnimation(Common &common, Vec2 scale, Vec2 screen) {
		animation.mTexture = common.getTextureResource("plane");

		animation.mPos.x = screen.x / 10 * scale.x;
		animation.mPos.y = screen.y / 2 * scale.y;
		animation.mCurrentFrame = 0;
		animation.mFrameTime = 0.0f;
		animation.mScale = scale;
	}

	void PlaneAnimation::UpdateEmitter(const float dt) {
		
	}

	void PlaneAnimation::RenderEmitter(Renderer2D *renderer) {
		RectangleF clip = { 0, 0, 116, 140 };

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