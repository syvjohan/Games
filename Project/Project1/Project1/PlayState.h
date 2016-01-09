#pragma once

#include <framework.h>
#include "IGameState.h"

namespace Controller {
	class PlayState : public IGameState {
		public:
		PlayState();
		PlayState(Common *common);
		~PlayState();

		void OnUpdate(float dt);
		void OnRender();

		GameStates_e NextState() const;
		GameStates_e State() const;

		virtual void OnActivate();

		virtual void OnDeactivate();

		private:
		Common *mCommon;
		GameStates_e mNextState;

	};
}