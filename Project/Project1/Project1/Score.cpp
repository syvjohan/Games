#include "Score.h"

namespace View {
	Score::Score(RenderText &text) {
		score = 0;
		text = text;
	}

	Score::Score() {}

	Score::~Score() {}

	void Score::Update(const float dt) {
		sprintf(buffer, "Score: , %i", score);
		text->setText(buffer);
	}

	void Score::Render(Renderer2D *renderer) {
		int width, height;
		text->getTexture()->getDimensions(&width, &height);

		renderer->draw(text->getTexture(),
					   Vec2(20, 20),
					   { 0, 0, width, height },
					   Vec2(0),
					   0.0f,
					   Vec2(1, 1),
					   Color::White,
					   0.0f
					   );
	}

	void Score::UpdateScore(int i) {
		score += i;
	}
}