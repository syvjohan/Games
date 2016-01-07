#include "MenuModel.h"
#include "MenuView.h"
#include "NewGame.h"
#include "ContinueGame.h"
#include "Instructions.h"
#include "Controlls.h"
#include "Background.h"

namespace Model {
	MenuModel::MenuModel() {}

	MenuModel::~MenuModel() {}

	void MenuModel::Init(Vec2 screen) {
		SetMenuArea(screen);

		Background *background = DBG_NEW Background();
		mEntities.push_back(background);

		Model::NewGame *newGame = DBG_NEW Model::NewGame();
		mEntities.push_back(newGame);

		ContinueGame *continueGame = DBG_NEW ContinueGame();
		mEntities.push_back(continueGame);

		Controlls *controlls = DBG_NEW Controlls();
		mEntities.push_back(controlls);

		Instructions *instructions = DBG_NEW Instructions();
		mEntities.push_back(instructions);

		for (Entity *e : mEntities) {
			e->OnInit(this);

			switch (e->Type()) {
				case ENTITY_BACKGROUND_MENU:
					for (auto *view : mViews) {
						view->OnBackgroundInit((Background*)e);
					}
					break;
				case ENTITY_NEWGAME:
					for (auto *view : mViews) {
						view->OnNewGameInit((Model::NewGame*)e);
					}
					break;
				case ENTITY_CONTINUE:
					for (auto *view : mViews) {
						view->OnContinueGameInit((ContinueGame*)e);
					}
					break;
				case ENTITY_CONTROLLS:
					for (auto *view : mViews) {
						view->OnControllsInit((Controlls*)e);
					}
					break;
				case ENTITY_INSTRUCTIONS:
					for (auto *view : mViews) {
						view->OnInstructionsInit((Instructions*)e);
					}
					break;
			}
		}
	}

	void MenuModel::AddView(View::MenuView *v) {
		mViews.push_back(v);
	}

	void MenuModel::RemoveView(View::MenuView *v) {
		for (auto it = mViews.begin(); it != mViews.end(); ++it) {
			if (*it == v) {
				mViews.erase(it);
				return;
			}
		}
	}

	void MenuModel::OnUpdate(const float dt, bool isGameStarted) {
		CollissionWall();

		for (Entity *e : mEntities) {
			e->OnUpdate();
			if (e->Type() == ENTITY_BACKGROUND_MENU) {
				for (auto view : mViews) {
					((Background*)e)->OnUpdatePhysics(dt);
					view->OnBackgroundUpdatedPhysics((Background*)e);
				}
			} else if (e->Type() == ENTITY_CONTINUE) {
				for (auto view : mViews) {
					((ContinueGame*)e)->GameState(isGameStarted);
					view->OnContinueGameUpdate((ContinueGame*)e);
				}
			}
		}
	}

	void MenuModel::OnNewGameUpdated(Model::NewGame *g) {
		for (View::MenuView *v : mViews) {
			v->OnNewGameUpdate(g);
		}
	}

	void MenuModel::OnContinueGameUpdated(ContinueGame *g) {
		for (View::MenuView *v : mViews) {
			v->OnContinueGameUpdate(g);
		}
	}

	void MenuModel::OnControllsUpdated(Controlls *c) {
		for (View::MenuView *v : mViews) {
			v->OnControllsUpdate(c);
		}
	}

	void MenuModel::OnInstructionsUpdated(Instructions *i) {
		for (View::MenuView *v : mViews) {
			v->OnInstructionsUpdate(i);
		}
	}

	void MenuModel::OnBackgroundUpdated(Background *b) {
		for (View::MenuView *v : mViews) {
			v->OnBackgroundMoved(b);
		}
	}

	void MenuModel::OnMoveBackground() {
		for (Entity *e : mEntities) {
			if (e->Type() == ENTITY_BACKGROUND_MENU) {
				((Background*)e)->mPos.x -= 1;
			}
		}
	}

	void MenuModel::CollissionWall() {
		int index = 0;
		while (index < mEntities.size()) {
			Entity *e = mEntities[index];
			if (e->Type() == ENTITY_BACKGROUND_MENU) {
				Background *background = ((Background*)e);
				if (background->mPos.x < 20) {
					background->mDir = Vec2(0, 1);
				}

				if (background->mPos.x > GetMenuArea().x - 20) {
					background->mDir = Vec2(0, -1);
				}

				if (background->mPos.y < 20 && background->mPos.x < GetMenuArea().x - 20) {
					background->mDir = Vec2(-1, 0);
				}

				if (background->mPos.y > GetMenuArea().y - 20 && background->mPos.x > 20) {
					background->mDir = Vec2(1, 0);
				}
			}
			++index;
		}
	}

	void MenuModel::CheckInput(Vec2 coordinates) {
		Vec4 hitbox;
		for (Entity *e : mEntities) {
			if (e->Type() == ENTITY_CONTINUE) {
				hitbox.x = ((ContinueGame*)e)->GetPosition().x - 100;
				hitbox.y = ((ContinueGame*)e)->GetPosition().y - 8;
				hitbox.w = 200;
				hitbox.z = 16;

				if ((coordinates.x > hitbox.x && coordinates.x < hitbox.x + hitbox.w) && ((coordinates.y > hitbox.y && coordinates.y < hitbox.y + hitbox.z))) {
					clickedContinueGame = true;
				}
			} else if (e->Type() == ENTITY_CONTROLLS) {
				hitbox.x = ((Controlls*)e)->GetPosition().x - 55;
				hitbox.y = ((Controlls*)e)->GetPosition().y - 8;
				hitbox.w = 110;
				hitbox.z = 16;

				if ((coordinates.x > hitbox.x && coordinates.x < hitbox.x + hitbox.w) && ((coordinates.y > hitbox.y && coordinates.y < hitbox.y + hitbox.z))) {
					clickedContinueGame = true;
				}
			} else if (e->Type() == ENTITY_NEWGAME) {
				hitbox.x = ((Model::NewGame*)e)->GetPosition().x - 65;
				hitbox.y = ((Model::NewGame*)e)->GetPosition().y - 8;
				hitbox.w = 130;
				hitbox.z = 16;

				if ((coordinates.x > hitbox.x && coordinates.x < hitbox.x + hitbox.w) && ((coordinates.y > hitbox.y && coordinates.y < hitbox.y + hitbox.z))) {
					clickedNewGame = true;
				}
			} else if (e->Type() == ENTITY_INSTRUCTIONS) {
				hitbox.x = ((Instructions*)e)->GetPosition().x - 75;
				hitbox.y = ((Instructions*)e)->GetPosition().y - 8;
				hitbox.w = 130;
				hitbox.z = 16;

				if ((coordinates.x > hitbox.x && coordinates.x < hitbox.x + hitbox.w) && ((coordinates.y > hitbox.y && coordinates.y < hitbox.y + hitbox.z))) {
					clickedContinueGame = true;
				}
			}
		}
	}

	bool MenuModel::IsPaused() {
		if (clickedContinueGame) {
			clickedContinueGame = false;
			return true;
		}
		return false;
	}

	bool MenuModel::IsNewGame() {
		if (clickedNewGame) {
			clickedNewGame = false;
			return true;
		}
		return false;
	}

	void MenuModel::SetMenuArea(Vec2 screen) {
		mMenuArea.x = screen.x;
		mMenuArea.y = screen.y;
	}

	Vec2 MenuModel::GetMenuArea() {
		return mMenuArea;
	}
}