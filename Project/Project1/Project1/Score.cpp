#include "Score.h"

namespace View {
	Score::Score(Common &common, Graphics *graphics) {
		score = 0;

		font = common.getFontResource("sans16");
		text = graphics->createRenderText(font, "gg");	
	}

	Score::Score() {}

	Score::~Score() {
		delete text;
	}

	void Score::Update() {
		sprintf(buffer, "Score: %i", score);
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