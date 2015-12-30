#pragma once

#include <framework.h>

namespace View {
	class Score {
		public:
			Score(RenderText &text);
			Score();
			~Score();

			void Update(const float dt);
			void Render(Renderer2D *renderer);
			void UpdateScore(int i);

		private:
			int score;
			char buffer[128];
			RenderText *text;
	};
}
