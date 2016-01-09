#include "HelpState.h"
#include "Entity.h"

namespace Controller {
	HelpState::HelpState() {}

	HelpState::HelpState(Common *common) {
		mCommon = common;
	}

	HelpState::~HelpState() {}

	void HelpState::OnActivate() {
		mNextState = GS_HELP;
	}

	void HelpState::OnDeactivate() {}

	void HelpState::OnUpdate(float dt) {

	}

	void HelpState::OnRender() {

	}
}