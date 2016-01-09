#include "PlayState.h"

namespace Controller {
	PlayState::PlayState() {}

	PlayState::~PlayState() {}

	GameStates_e PlayState::NextState() const {
		return mNextState;
	}

	GameStates_e PlayState::State() const {
		return GS_PLAY;
	}

	void PlayState::OnActivate() {
		mNextState = GS_PLAY;
	};

	void PlayState::OnDeactivate() {
		//..
	}
}