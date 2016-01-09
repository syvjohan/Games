#pragma once

namespace Controller {
	enum GameStates_e {
		GS_MENU = 0,
		GS_HELP,
		GS_PLAY,
		GS_QUIT,
	};

	class IGameState {
		public:
		IGameState();
		~IGameState();

		virtual void OnUpdate(float dt) = 0;
		virtual void OnRender() = 0;

		virtual GameStates_e NextState() const = 0;
		virtual GameStates_e State() const = 0;

		virtual void OnActivate() {};
		virtual void OnDeactivate() {};
	};
}