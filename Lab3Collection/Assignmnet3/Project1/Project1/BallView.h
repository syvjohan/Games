#pragma once

#include <framework.h>

#include "Ball.h"

namespace View {
	class BallView {
		public:
			BallView();
			BallView(Model::BallEmitter &emitter, Model::BallParams &params);
			~BallView();

			void RenderEmitter(Renderer2D *renderer);
			void UpdateEmitter(const float dt, const float BoarderMargin);

			int Collision(Vec4 hitArea);
			void StopBall(int index);

		private:
		Model::BallEmitter emitter;
		Model::BallParams params;

	};
}

