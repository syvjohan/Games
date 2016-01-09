#include "GameStateManager.h"

#include "PlayState.h"
#include "MenuState.h"
#include "HelpState.h"
#include "IGameState.h"

namespace Controller {
	GameStateManager::GameStateManager() {}

	GameStateManager::GameStateManager(Common *common) {
		this->mCommon = common;
		mHelpState = NULL;
		mPlayState = NULL;

		mMenuState = DBG_NEW MenuState(common);
		mMenuState->OnActivate();
		mCurrent = mMenuState;
	}

	GameStateManager::~GameStateManager() {}

	void GameStateManager::OnUpdate(float dt) {
		mCurrent->OnUpdate(dt);
		mCurrent->OnRender();

		IGameState *nextState = NULL;

		if (mCurrent->NextState() != mCurrent->State()) {
			switch (mCurrent->NextState()) {
				case GS_MENU:
					if (mMenuState == NULL) {
						mMenuState = DBG_NEW MenuState(mCommon);
					}
					nextState = mMenuState;
					break;
				case GS_HELP:
					if (mHelpState == NULL) {
						mHelpState = DBG_NEW HelpState(mCommon);
					}

					nextState = mHelpState;
					break;
				case GS_PLAY:
					if (mPlayState == NULL) {
						// Creating new game
						mPlayState = new PlayState(mCommon);
					}
					mCurrent = mPlayState;
					break;
				case GS_QUIT:
					// TODO: Start shutdown process..
					break;
				default:
					assert(false && "Invalid state");
					break;
			}
		}

		if (nextState) {
			// Should we delete previous state?

			mCurrent->OnDeactivate();
			nextState->OnActivate();
			mCurrent = nextState;
		}
	}
}