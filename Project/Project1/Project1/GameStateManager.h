#pragma once

#include <framework.h>

namespace Controller {
	class IGameState;
	class PlayState;
	class MenuState;
	class HelpState;

	class GameStateManager {
		public:
		GameStateManager();
		GameStateManager(Common *common);
		~GameStateManager();

			virtual void OnUpdate(float dt);

		private:
			IGameState *mCurrent;
			Common *mCommon;
			PlayState *mPlayState;
			MenuState *mMenuState;
			HelpState *mHelpState;
	};
}