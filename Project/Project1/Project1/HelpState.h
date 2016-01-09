#pragma once

#include <framework.h>

#include "IGameState.h"

namespace Controller {
	class HelpState : public IGameState {
		public:
		HelpState();
		HelpState(Common *common);
		~HelpState();

		void OnUpdate(float dt);

		void OnRender();

		GameStates_e NextState() const;
		GameStates_e State() const { return GS_HELP; }

		virtual void OnActivate();

		virtual void OnDeactivate();

		private:
		Common *mCommon;
		GameStates_e mNextState;
	};
}