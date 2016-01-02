#include "ManagerModel.h"
#include "ManagerView.h"
#include "NewPlayer.h"

namespace Model {
	ManagerModel::ManagerModel() {}

	ManagerModel::~ManagerModel() {}

	void ManagerModel::Init(Vec2 screen, Vec2 border) {
		SetPlayArea(screen, border);

		// Create a player..
		NewPlayer *player = DBG_NEW NewPlayer();
		mEntities.push_back(player);

		// TODO: Add enemies

		for (Entity *e : mEntities) {
			e->OnInit(this);

			switch (e->Type()) {
				case ENTITY_PLAYER:
					for (auto *view : mViews) {
						view->OnPlayerSpawned((NewPlayer*)e);
					}
					break;
					/*case ENTITY_ASTEROID:
						for (View::ManagerView *view : mViews) {
						view->OnEnemySpawned((NewAsteroid*)e);
						}
						break;*/
			}
		}
	}

	void ManagerModel::AddView(View::ManagerView *v) {
		mViews.push_back(v);
	}

	void ManagerModel::RemoveView(View::ManagerView *v) {
		for (auto it = mViews.begin(); it != mViews.end(); ++it) {
			if (*it == v) {
				mViews.erase(it);
				return;
			}
		}
	}

	void ManagerModel::OnUpdate(const HiResTimer &timer) {
		for (Entity *e : mEntities) {
			e->OnUpdate(timer);
			if (e->Type() == ENTITY_PLAYER) {
				for (auto view : mViews) {
					bool btnIsPressed = view->OnPlayerUpdatedAnimation((NewPlayer*)e);
					((NewPlayer*)e)->OnUpdateFrameTimes(btnIsPressed); //Update frame

					view->OnPlayerUpdatedPhysics((NewPlayer*)e, timer);
				}
			}
		}

		//Collision
		OnColissionWall();
		OnCollisionUnits();
	}

	void ManagerModel::OnColissionWall() {
		for (Entity *e : mEntities) {
			if (e->Type() == ENTITY_PLAYER) {
				NewPlayer *player = ((NewPlayer*)e);

				if (player->params.mPos.x < border.x) {
					player->params.mPos.x = border.x;
				}

				if (player->params.mPos.x + player->params.mSize.x + (border.x * 2) > mPlayArea.x) {
					player->params.mPos.x = mPlayArea.x - player->params.mSize.x - (border.x * 2);
				}

				if (player->params.mPos.y < border.y + player->params.mSize.x) {
					player->params.mPos.y = border.y + player->params.mSize.x; //Sprite is rotated.
				}

				if (player->params.mPos.y > mPlayArea.y) {
					player->params.mPos.y = mPlayArea.y;
				}
			}
		}
	}

	void ManagerModel::OnCollisionUnits() {

	}

	void ManagerModel::OnPlayerMoved(NewPlayer *p) {
		for (View::ManagerView *v : mViews) {
			v->OnPlayerMoved(p);
		}
	}

	void ManagerModel::OnMovePlayer(const Vec2 &delta) {
		for (Entity *e : mEntities) {
			if (e->Type() == ENTITY_PLAYER) {
				((NewPlayer*)e)->params.mDir += delta;
			}
		}
	}

	void ManagerModel::SetPlayArea(Vec2 screen, Vec2 border) {
		this->border = border;

		mPlayArea.x = screen.x;
		mPlayArea.y = screen.y;
	}

	Vec2 ManagerModel::GetPlayArea() {
		return mPlayArea;
	}
}