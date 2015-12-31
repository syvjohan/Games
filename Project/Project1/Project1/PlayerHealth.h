#pragma once

#include <framework.h>

namespace View {
	class PlayerHealth {
		public:
			PlayerHealth();
			PlayerHealth(Common &common, Graphics *graphics);
			~PlayerHealth();

			void Render(Renderer2D *renderer);
			void Update();
			void UpdateHealth(int health);

		private:
			int health;
			Color textColor;
			char buffer[128];
			RenderText *text;
			RenderFont *font;
	};
}