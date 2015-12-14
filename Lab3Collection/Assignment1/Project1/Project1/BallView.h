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
			void UpdateEmitter(const float dt);

		private:
		Model::BallEmitter emitter;
		Model::BallParams params;

	};
}

