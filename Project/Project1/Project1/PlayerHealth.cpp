#include "PlayerHealth.h"

namespace View {
	PlayerHealth::PlayerHealth(Common &common, Graphics *graphics) {
		health = 100;
		textColor = Color::White;
		font = common.getFontResource("sans16");
		text = graphics->createRenderText(font, "gg");
	}


	PlayerHealth::~PlayerHealth() {
		delete text;
	}

	void PlayerHealth::UpdateHealth(int health) {
		this->health = health;
	}

	void PlayerHealth::Update() {
		sprintf(buffer, "Hp: %i%%", health);
		text->setText(buffer);
	}

	void PlayerHealth::Render(Renderer2D *renderer) {
		int width, height;
		text->getTexture()->getDimensions(&width, &height);

		if (health <= 50) {
			textColor = Color::Red;
		}

		renderer->draw(text->getTexture(),
					   Vec2(120, 20),
					   { 0, 0, width, height },
					   Vec2(0),
					   0.0f,
					   Vec2(1, 1),
					   textColor,
					   0.0f
					   );
	}
}