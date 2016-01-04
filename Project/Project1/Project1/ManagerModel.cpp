#include "ManagerModel.h"
#include "ManagerView.h"
#include "NewPlayer.h"
#include "Shot.h"
#include "NewAsteroid.h"
//#include "NewExplosion.h"

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

	void ManagerModel::OnUpdate(const float dt) {
		//Collision
		ColissionWall();
		auto collisions = CollisionEntities();
		if (collisions.size() > 0) {
			ProcessCollisions(collisions);
		}


		for (Entity *e : mEntities) {
			e->OnUpdate();
			if (e->Type() == ENTITY_PLAYER) {
				for (auto view : mViews) {
					bool btnIsPressed = view->OnPlayerUpdatedAnimation((NewPlayer*)e);
					((NewPlayer*)e)->OnUpdateAnimation(btnIsPressed, dt);

					((NewPlayer*)e)->OnUpdatePhysics(dt);
					view->OnPlayerUpdatedPhysics((NewPlayer*)e);
				}
			} else if (e->Type() == ENTITY_BULLET) {
				for (auto view : mViews) {
					((Shot*)e)->OnUpdatedPhysics(dt);
					view->OnShotUpdatePhysics((Shot*)e);
				}
			} else if (e->Type() == ENTITY_ASTEROID) {
				for (auto view : mViews) {
					((NewAsteroid*)e)->OnUpdateAnimation(dt);
					view->OnAsteroidUpdatedAnimation(((NewAsteroid*)e));

					((NewAsteroid*)e)->OnUpdatePhysics(dt);
					view->OnAsteroidUpdatedPhysics((NewAsteroid*)e);
				}
			}
		}
	}

	void ManagerModel::ColissionWall() {
		int index = 0;
		while(index < mEntities.size()) {
			Entity *e = mEntities[index];
			if (e->Type() == ENTITY_PLAYER) {
				NewPlayer *player = ((NewPlayer*)e);
				if (player->mPos.x < player->GetRadius() + 10) {
					player->mPos.x = player->GetRadius() + 10;
				}

				if (player->mPos.x + player->GetRadius() > mPlayArea.x - 15) {
					player->mPos.x = mPlayArea.x - player->GetRadius() - 15;//Sprite is rotated.
				}

				if (player->mPos.y < player->GetRadius()) {
					player->mPos.y = player->GetRadius();
				}

				if (player->mPos.y > mPlayArea.y - player->GetRadius()) {
					player->mPos.y = mPlayArea.y - player->GetRadius();
				}

			} else if (e->Type() == ENTITY_BULLET) {
				Shot *bullet = ((Shot*)e);
				if (bullet->mPos.x > mPlayArea.x) {
					RemoveEntity(e);
					--index;
				}
			} else if (e->Type() == ENTITY_ASTEROID) {
				NewAsteroid *asteroid = ((NewAsteroid*)e);
				if (asteroid->mPos.x + asteroid->GetRadius() < 0 ||
					asteroid->mPos.y + asteroid->GetRadius() < 0) {
					RemoveEntity(e);
					AddAsteroid(0, 0);
					--index;
				}
			}
			++index;
		}
	}

	std::vector<CollisionPair> ManagerModel::CollisionEntities() const {
		if (mEntities.size() < 2) {
			return {};
		}

		std::vector<CollisionPair> pairs;

		for (Entity *A : mEntities) {
			for (Entity *B : mEntities) {
				if (A == B) continue;

				if (Vec2::length(A->GetPosition() - B->GetPosition()) < A->GetRadius() + B->GetRadius()) {
					CollisionPair pair;
					pair.mEntityA = A;
					pair.mEntityB = B;

					bool exists = false;
					for (const CollisionPair &oldPair : pairs) {
						if (oldPair == pair) {
							exists = true;
							break;
						}
					}

					if (!exists) {
						pairs.push_back(pair);
					}
				}
			}
		}

		return pairs;
	}

#define GET_ENTITY(CLASS, TYPE, P) (CLASS*)(P.mEntityA->Type() == TYPE ? P.mEntityA : (P.mEntityB->Type() == TYPE ? P.mEntityB : NULL))

	void ManagerModel::ProcessCollisions(const std::vector<CollisionPair> &collisions) {

		for (const CollisionPair &pair : collisions) {
			NewPlayer *player = GET_ENTITY(NewPlayer, ENTITY_PLAYER, pair);
			Shot *shot = GET_ENTITY(Shot, ENTITY_BULLET, pair);
			NewAsteroid *asteroid = GET_ENTITY(NewAsteroid, ENTITY_ASTEROID, pair);

			if (player && asteroid) {
				RemoveEntity(asteroid);
				RemoveEntity(player);
				AddAsteroid(0, 0);
			} else if (asteroid && shot) {
				AddAsteroid(0, 0);
				RemoveEntity(asteroid);
				RemoveEntity(shot);
			} else if (asteroid && !player && !shot) {
				RemoveEntity(pair.mEntityA);
				RemoveEntity(pair.mEntityB);			
			}
		}
	}

	void ManagerModel::RemoveEntity(Entity *e) {
		for (auto it = mEntities.begin(); it != mEntities.end(); ++it) {
			if (*it == e) {
				for (View::ManagerView *view : mViews) {
					view->OnEntityDied(it - mEntities.begin());
				}

				mEntities.erase(it);
				break;
			}
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
				((NewPlayer*)e)->mDir += delta;
			}
		}
	}

	Vec2 ManagerModel::GetStartPositionForShot() {
		Vec2 position = Vec2(0, 0);
		for (Entity *e : mEntities) {
			if (e->Type() == ENTITY_PLAYER) {
				float x = ((NewPlayer*)e)->mPos.x + ((NewPlayer*)e)->mSize.x + 6;
				float y = ((NewPlayer*)e)->mPos.y - 65;
				position = Vec2(x, y);
			}
		}
		return position;
	}

	void ManagerModel::OnMoveShot() {
		for (Entity *e : mEntities) {
			if (e->Type() == ENTITY_BULLET) {
				((Shot*)e)->mPos.x += 1;
			}
		}
	}

	void ManagerModel::OnShotMoved(Shot *s) {
		for (auto *view : mViews) {
			view->OnShotMoved(s);
		}
	}

	void ManagerModel::AddShot(Vec2 startPosition) {
		Shot *shot = DBG_NEW Shot();
		shot->startPosition = startPosition;
		shot->OnInit(this);
		mEntities.push_back(shot);

		for (auto *view : mViews) {
			view->OnShotSpawned((Shot*)shot);
		}
	}

	void ManagerModel::OnMoveAsteroid() {
		for (Entity *e : mEntities) {
			if (e->Type() == ENTITY_ASTEROID) {
				((NewAsteroid*)e)->mPos.x -= 1;
			}
		}
	}

	void ManagerModel::OnAsteroidMoved(NewAsteroid *a) {
		for (auto *view : mViews) {
			view->OnAsteroidMoved(a);
		}
	}

	void ManagerModel::AddAsteroid(int type, int length) {
		NewAsteroid *asteroid = DBG_NEW NewAsteroid();
		asteroid->OnInit(this);
		mEntities.push_back(asteroid);

		for (auto *view : mViews) {
			view->OnAsteroidSpawned((NewAsteroid*)asteroid);
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