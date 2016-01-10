#pragma once

#include <framework.h>
#include <vector>

#include "Entity.h"
#include "Defs.h"

namespace View {
	class MenuView;
}

namespace Model {
	class NewGame;
	class ContinueGame;
	class Help;
	class Background;
	class BackgroundAfterGame;
	class Result;

	class MenuModel {
		public:
			MenuModel();
			~MenuModel();

			void Init(Vec2 screen);
			void AddView(View::MenuView *v);
			void RemoveView(View::MenuView *v);
			void OnUpdate(const float dt, bool isGameStarted);
			Vec2 GetMenuArea();

			void OnNewGameUpdated(NewGame *g);

			void OnContinueGameUpdated(ContinueGame *c);

			void OnHelpUpdated(Help *i);

			void OnResultUpdated(Result *i);

			void OnBackgroundUpdated(Background *b);
			void OnMoveBackground();

			void OnBackgroundAfterGameUpdated(BackgroundAfterGame *b);

			void CollissionWall();
			void CheckInput(Vec2 coordinates);

			void ShowWonRound();
			void ShowLostRound();
			void ShowWonGame();

			bool IsPaused();
			bool IsNewGame();

			int helpRow = 0;

		private:
			std::vector<View::MenuView*> mViews;
			std::vector<Entity*> mEntities;
			Vec2 mMenuArea;

			void SetMenuArea(Vec2 screen);

			bool clickedContinueGame = false;
			bool clickedNewGame = false;
	};
}