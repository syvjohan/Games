#pragma once

#include <framework.h>

#include "Defs.h"

namespace Model {
	class MenuModel;
	class NewGame;
	class Entity;
	class ContinueGame;
	class Help;
	class Background;
}

namespace View {
	class MenuView {
		public:
			MenuView();
			MenuView(Common *common, Model::MenuModel *m);
			~MenuView();

			void OnUpdate(const float dt);

			void OnBackgroundUpdate(const float dt);
			void OnBackgroundInit(Model::Background *background);
			void OnBackgroundMoved(const Model::Background *background);
			void OnMoveBackground(const Model::Background *background);
			void OnBackgroundUpdatedPhysics(Model::Background *background);

			void OnNewGameUpdate(const Model::NewGame *newGame);
			void OnNewGameInit(Model::NewGame *newGame);

			void OnContinueGameUpdate(const Model::ContinueGame *continueGame);
			void OnContinueGameInit(Model::ContinueGame *continueGame);

			void OnHelpUpdate(const Model::Help *help);
			void OnHelpInit(Model::Help *help);

			//Render
			void OnRender();

			void RemoveSprite(int index);

		private:
			Common *mCommon;
			Model::MenuModel *mModel;
			Renderer2D *mRenderer;

			RenderFont	*mFont;
			RenderFont *mFont2;

			const float delayKeyPress = 0.5f;
			float accumulatorKeyPress = delayKeyPress;

			std::vector<SpriteDef> mSprites;
	};
}
