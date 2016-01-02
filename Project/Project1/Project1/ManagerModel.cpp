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
					((NewPlayer*)e)->OnUpdateFrameTimes(btnIsPressed);

					((NewPlayer*)e)->OnUpdatePlayerPhysics(timer);
					view->OnPlayerUpdatedPhysics((NewPlayer*)e, timer);
				}
			} else if (e->Type() == ENTITY_BULLET) {
				for (auto view : mViews) {

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

				if (player->planeParams.mPos.x < border.x) {
					player->planeParams.mPos.x = border.x;
				}

				if (player->planeParams.mPos.x + player->planeParams.mSize.x + (border.x * 2) > mPlayArea.x) {
					player->planeParams.mPos.x = mPlayArea.x - player->planeParams.mSize.x - (border.x * 2);
				}

				if (player->planeParams.mPos.y < border.y + player->planeParams.mSize.x) {
					player->planeParams.mPos.y = border.y + player->planeParams.mSize.x; //Sprite is rotated.
				}

				if (player->planeParams.mPos.y > mPlayArea.y) {
					player->planeParams.mPos.y = mPlayArea.y;
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
				((NewPlayer*)e)->planeParams.mDir += delta;
			}
		}
	}

	void ManagerModel::OnShotMoved(Shot *p) {
		for (View::ManagerView *v : mViews) {
			v->OnShotMoved(p);
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