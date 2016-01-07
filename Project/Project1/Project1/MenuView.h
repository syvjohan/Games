#pragma once

#include <framework.h>

#include "Defs.h"

namespace Model {
	class MenuModel;
	class NewGame;
	class Entity;
	class ContinueGame;
	class Instructions;
	class Controlls;
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

			void OnInstructionsUpdate(const Model::Instructions *instruction);
			void OnInstructionsInit(Model::Instructions *instruction);

			void OnControllsUpdate(const Model::Controlls *controlls);
			void OnControllsInit(Model::Controlls *controlls);

			//Render
			void OnRender();

		private:
			Common *mCommon;
			Model::MenuModel *mModel;
			Renderer2D *mRenderer;

			RenderFont	*mFont;

			const float delayKeyPress = 0.5f;
			float accumulatorKeyPress = delayKeyPress;

			std::vector<SpriteDef> mSprites;
	};
}
