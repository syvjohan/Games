#pragma once

#include <framework.h>

#include "Defs.h"
#include "IGameState.h"

namespace Controller {
	enum MenuStates {
		ENTITY_NEWGAME,
		ENTITY_CONTINUE,
		ENTITY_HELP,
		ENTITY_BACKGROUND,
	};

	class Entity;
	class NewGame;
	class ContinueGame;
	class Controlls;
	class Instructions;
	class Background;

	class MenuState : public IGameState {
		public:
		MenuState();
		MenuState(Common *common);
		~MenuState();

		void Init(Vec2 screen);

		void OnUpdate(float dt);

		void OnRender();

		GameStates_e NextState() const;
		GameStates_e State() const { return GS_MENU; }

		virtual void OnActivate() { mNextState = GS_MENU; }

		virtual void OnDeactivate() { };

		void CheckInput(Vec2 coordinates);

		Vec2 GetMenuArea();

		void CollissionWall();

		private:
			Common *mCommon;
			GameStates_e mNextState;

			const float delayKeyPress = 0.5f;
			float accumulatorKeyPress = delayKeyPress;
			std::vector<Entity*> mEntities;
			Vec2 mMenuArea;

			void SetMenuArea(Vec2 screen);
	};
}
