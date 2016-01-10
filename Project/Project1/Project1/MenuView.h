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
	class BackgroundAfterGame;
	class Result;
}

namespace View {
	class MenuView {
		public:
			MenuView();
			MenuView(Common *common, Model::MenuModel *m);
			~MenuView();

			void OnUpdate(const float dt);
			void OnRenderMenu();
			void OnRenderAfterGame();

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

			void OnResultUpdate(const Model::Result *result);
			void OnResultInit(Model::Result *result);

			void OnBackgroundAfterGameUpdate(const Model::BackgroundAfterGame *background);
			void OnBackgroundAfterGameInit(Model::BackgroundAfterGame *background);

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
