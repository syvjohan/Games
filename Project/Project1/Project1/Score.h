#pragma once

#include <framework.h>

class RenderText;

namespace View {
	class Score {
		public:
			Score(Common &common, Graphics *graphics);
			Score();
			~Score();

			void Update();
			void Render(Renderer2D *renderer);
			void UpdateScore(int i);

		private:
			int score;
			char buffer[128];
			RenderText *text;
			RenderFont *font;
	};
}
