#pragma once
#include "Sprite.h"

#include <framework.h>

class AnimationSystem {
	public:
		AnimationSystem();
		AnimationSystem(Common &common);
		~AnimationSystem();
		
		void UpdateEmitter( const float dt);
		void RenderEmitter(Renderer2D *renderer);
		void FreeMem();

	private:
		void InitAnimation(Common &common);

		Animation animation;
};

