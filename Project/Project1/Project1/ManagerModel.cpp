#include "ManagerModel.h"
#include "ManagerView.h"
#include "NewPlayer.h"
#include "Shot.h"
#include "NewAsteroid.h"

#include <algorithm>

namespace Model {
	ManagerModel::ManagerModel() {}

	ManagerModel::~ManagerModel() {}

	void ManagerModel::Init(Vec2 screen) {
		SetPlayArea(screen);

		// Create a player..
		NewPlayer *player = DBG_NEW NewPlayer();
		mEntities.push_back(player);

		NewAsteroid *asteroid = DBG_NEW NewAsteroid();
		mEntities.push_back(asteroid);

		for (Entity *e : mEntities) {
			e->OnInit(this);

			switch (e->Type()) {
				case ENTITY_PLAYER:
					for (auto *view : mViews) {
						view->OnPlayerSpawned((NewPlayer*)e);
					}
					break;
				case ENTITY_ASTEROID:
					for (View::ManagerView *view : mViews) {
						view->OnAsteroidSpawned((NewAsteroid*)e);
					}
					break;
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

	void ManagerModel::OnUpdate(HiResTimer &timer) {
		timer.tick();
		float dt = timer.getDeltaSeconds();
		for (Entity *e : mEntities) {
			e->OnUpdate();
			if (e->Type() == ENTITY_PLAYER) {
				for (auto view : mViews) {
					bool btnIsPressed = view->OnPlayerUpdatedAnimation((NewPlayer*)e);
					((NewPlayer*)e)->OnUpdateAnimation(btnIsPressed, dt);

					((NewPlayer*)e)->OnUpdatePlayerPhysics(dt);
					view->OnPlayerUpdatedPhysics((NewPlayer*)e);
				}
			} else if (e->Type() == ENTITY_BULLET) {
				for (auto view : mViews) {
					((Shot*)e)->OnUpdatedPhysics(dt);
					view->OnShotUpdatePhysics((Shot*)e);
				}
			} else if (e->Type() == ENTITY_ASTEROID) {
				for (auto view : mViews) {
					((NewAsteroid*)e)->OnUpdateFrameTimes(dt);
					view->OnAsteroidUpdatedAnimation(((NewAsteroid*)e));

					((NewAsteroid*)e)->OnUpdatePhysics(dt);
					view->OnAsteroidUpdatedPhysics((NewAsteroid*)e);
				}
			}
		}

		//Collision
		OnColissionWall();
		OnCollisionEntities();
	}

	void ManagerModel::OnColissionWall() {
		int index = 0;
		while(index < mEntities.size()) {
			Entity *e = mEntities[index];
			if (e->Type() == ENTITY_PLAYER) {
				NewPlayer *player = ((NewPlayer*)e);

				if (player->planeParams.mPos.x < 0) {
					player->planeParams.mPos.x = 0;
				}

				if (player->planeParams.mPos.x + player->planeParams.mSize.x > mPlayArea.x - 25) {
					player->planeParams.mPos.x = mPlayArea.x - player->planeParams.mSize.x -25;//Sprite is rotated.
				}

				if (player->planeParams.mPos.y < player->planeParams.mSize.x) {
					player->planeParams.mPos.y = player->planeParams.mSize.x;
				}

				if (player->planeParams.mPos.y > mPlayArea.y) {
					player->planeParams.mPos.y = mPlayArea.y;
				}
			} else if (e->Type() == ENTITY_BULLET) {
				Shot *bullet = ((Shot*)e);
				if (bullet->bulletParams.mPos.x > mPlayArea.x) {
					RemoveEntity(index);
					--index;
				}
			} else if (e->Type() == ENTITY_ASTEROID) {
				NewAsteroid *asteroid = ((NewAsteroid*)e);
				if (asteroid->asteroidParams.mPos.x + asteroid->asteroidParams.mSize.x < 0 ||
					asteroid->asteroidParams.mPos.y + asteroid->asteroidParams.mSize.y < 0) {
					RemoveEntity(index);
					--index;
				}
			}
			++index;
		}
	}

	void ManagerModel::OnCollisionEntities() {
		int i = 0;
		int j = 0;
		if (mEntities.size() >= 2) {
			while (i < mEntities.size()) {
				Entity *e = mEntities[i];
				j = i + 1;
				while (j < mEntities.size()) {
					Entity *e2 = mEntities[j];
					if (e->Type() == ENTITY_PLAYER && e2->Type() == ENTITY_ASTEROID) {
						NewPlayer *player = ((NewPlayer*)e);
						NewAsteroid *asteroid = ((NewAsteroid*)e2);

						float asteroidRadius = std::max(asteroid->asteroidParams.mSize.x / 2.0f, asteroid->asteroidParams.mSize.y);
						float playerRadius = std::max(player->planeParams.mSize.x / 2.0f, player->planeParams.mSize.y);

						Vec2 p(player->planeParams.mPos.x, player->planeParams.mPos.y);
						Vec2 a(asteroid->asteroidParams.mPos.x, asteroid->asteroidParams.mPos.y);

						Vec2 diff = a - p;

						if (Vec2::length(diff) < asteroidRadius + playerRadius) {
							RemoveEntity(i);
							--i;
							RemoveEntity(j);
							--j;
						}
					} else if (e->Type() == ENTITY_BULLET && e2->Type() == ENTITY_ASTEROID) {
						Shot *bullet = ((Shot*)e);
						NewAsteroid *asteroid = ((NewAsteroid*)e2);

						float asteroidRadius = std::max(asteroid->asteroidParams.mSize.x / 2.0f, asteroid->asteroidParams.mSize.y);
						float bulletRadius = std::max(bullet->bulletParams.mSize.x / 2.0f, bullet->bulletParams.mSize.y);

						Vec2 p(bullet->bulletParams.mPos.x, bullet->bulletParams.mPos.y);
						Vec2 a(asteroid->asteroidParams.mPos.x, asteroid->asteroidParams.mPos.y);

						Vec2 diff = a - p;

						if (Vec2::length(diff) < asteroidRadius + bulletRadius) {
							RemoveEntity(j);
							--j;
							RemoveEntity(i);
							--i;
						}
					}
					++j;
				}
				++i;
			}
		}
	}

	void ManagerModel::RemoveEntity(int index) {
		if (mEntities.size() > 0 && mEntities.size() >= index) {
			mEntities.erase(mEntities.begin() + index);
		}
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

	Vec2 ManagerModel::GetStartPositionForShot() {
		Vec2 position = Vec2(0, 0);
		for (Entity *e : mEntities) {
			if (e->Type() == ENTITY_PLAYER) {
				float x = ((NewPlayer*)e)->planeParams.mPos.x + ((NewPlayer*)e)->planeParams.mSize.x + 6;
				float y = ((NewPlayer*)e)->planeParams.mPos.y - 65;
				position = Vec2(x, y);
			}
		}
		return position;
	}

	void ManagerModel::OnMoveShot() {
		for (Entity *e : mEntities) {
			if (e->Type() == ENTITY_BULLET) {
				((Shot*)e)->bulletParams.mPos.x += 1;
			}
		}
	}

	void ManagerModel::OnShotMoved(Shot *s) {
		for (auto *view : mViews) {
			view->OnShotMoved(s);
		}
	}

	void ManagerModel::AddShot(Vec2 startPosition) {
		Shot *shot = DBG_NEW Shot(startPosition);
		mEntities.push_back(shot);

		for (Entity *e : mEntities) {
			e->OnInit(this);
			for (auto *view : mViews) {
				view->OnShotSpawned((Shot*)shot);
			}
		}
	}

	void ManagerModel::OnMoveAsteroid() {
		for (Entity *e : mEntities) {
			if (e->Type() == ENTITY_ASTEROID) {
				((NewAsteroid*)e)->asteroidParams.mPos.x -= 1;
			}
		}
	}

	void ManagerModel::OnAsteroidMoved(NewAsteroid *a) {
		for (auto *view : mViews) {
			view->OnAsteroidMoved(a);
		}
	}

	void ManagerModel::AddAsteroid() {
		NewAsteroid *asteroid = DBG_NEW NewAsteroid();
		mEntities.push_back(asteroid);

		for (Entity *e : mEntities) {
			e->OnInit(this);
			for (auto *view : mViews) {
				view->OnAsteroidSpawned((NewAsteroid*)asteroid);
			}
		}
	}

	void ManagerModel::SetPlayArea(Vec2 screen) {
		mPlayArea.x = screen.x;
		mPlayArea.y = screen.y;
	}

	Vec2 ManagerModel::GetPlayArea() {
		return mPlayArea;
	}
}