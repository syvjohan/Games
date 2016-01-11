#include "ManagerModel.h"
#include "ManagerView.h"
#include "Player.h"
#include "Shot.h"
#include "Asteroid.h"
#include "Explosion.h"
#include "HealthKeeper.h"
#include "ScoreKeeper.h"
#include "HealthPackage.h"
#include "EnemieBoss.h"

#include <algorithm>

namespace Model {
	ManagerModel::ManagerModel() {}

	ManagerModel::~ManagerModel() {}

	void ManagerModel::Init(Vec2 screen, int asteroidType1, int asteroidType2, int maxScore) {
		this->maxScore = maxScore;

		SetPlayArea(screen);

		Player *player = DBG_NEW Player();
		mEntities.push_back(player);

		EnemieBoss *enemieBoss = DBG_NEW EnemieBoss();
		mEntities.push_back(enemieBoss);

		/*ScoreKeeper *scoreKeeper = DBG_NEW ScoreKeeper();
		scoreKeeper->mScore = 0;
		mEntities.push_back(scoreKeeper);

		HealthKeeper *healthKeeper = DBG_NEW HealthKeeper();
		healthKeeper->mHealth = player->defaultHealth;
		healthKeeper->mMaxHealth = player->defaultHealth;
		mEntities.push_back(healthKeeper);

		Asteroid *asteroid = DBG_NEW Asteroid();
		asteroid->SetType(asteroidType1);
		mEntities.push_back(asteroid);

		Asteroid *asteroid2 = DBG_NEW Asteroid();
		asteroid2->SetType(asteroidType2);
		mEntities.push_back(asteroid2);*/

		for (Entity *e : mEntities) {
			e->OnInit(this);

			switch (e->Type()) {
				case ENTITY_PLAYER:
					for (auto *view : mViews) {
						view->OnPlayerSpawned((Player*)e);
					}
					break;
				/*case ENTITY_ASTEROID:
					for (View::ManagerView *view : mViews) {
						view->OnAsteroidSpawned((Asteroid*)e);
					}
					break;
				case ENTITY_HP:
					for (View::ManagerView *view : mViews) {
						view->OnHPInit((HealthKeeper*)e);
					}
					break;
				case ENTITY_SCORE:
					for (View::ManagerView *view : mViews) {
						view->OnScoreInit((ScoreKeeper*)e);
					}
					break;*/
				case ENTITY_ENEMIEBOSS:
					for (auto *view : mViews) {
						view->OnEnemieBossSpawned((EnemieBoss*)e);
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
		//Exit if score is over rhs.
		if (GetScore() >= maxScore) {
			mWonRound = true;
		}

		//Add health package if time delta is right
		timerHealthPackage -= dt;
		if (timerHealthPackage <= 0) {
			timerHealthPackage = timePeriodSpawnHealtPackage;
			AddHealthPackage();
		}

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
					bool btnIsPressed = view->OnPlayerUpdatedAnimation((Player*)e);
					((Player*)e)->OnUpdateAnimation(btnIsPressed, dt);

					((Player*)e)->OnUpdatePhysics(dt);
					view->OnPlayerUpdatedPhysics((Player*)e);

					SetHealth(((Player*)e)->mHealth);
				}
			} else if (e->Type() == ENTITY_BULLET) {
				for (auto view : mViews) {
					((Shot*)e)->OnUpdatedPhysics(dt);
					view->OnShotUpdatePhysics((Shot*)e);
				}
			} else if (e->Type() == ENTITY_ASTEROID) {
				for (auto view : mViews) {
					((Asteroid*)e)->OnUpdateAnimation(dt);
					view->OnAsteroidUpdatedAnimation(((Asteroid*)e));

					((Asteroid*)e)->OnUpdatePhysics(dt);
					view->OnAsteroidUpdatedPhysics((Asteroid*)e);
				}
			} else if (e->Type() == ENTITY_EXPLOSION) {
				for (auto view : mViews) {
					((Explosion*)e)->OnUpdateAnimation(dt);
					view->OnExplosionUpdateAnimation((Explosion*)e);
				}
			} else if (e->Type() == ENTITY_HEALTHPACKAGE) {
				for (auto view : mViews) {
					((HealthPackage*)e)->OnUpdatePhysics(dt);
					view->OnHealthPackageUpdatedPhysics((HealthPackage*)e);
				}
			} else if (e->Type() == ENTITY_ENEMIEBOSS) {
				for (auto *view : mViews) {
					((EnemieBoss*)e)->OnUpdatePhysics(dt);
					view->OnEnemieBossUpdatedPhysics((EnemieBoss*)e);
				}
			}
		}

		RemoveDeadExplosion();
	}

	void ManagerModel::ColissionWall() {
		int index = 0;
		while(index < mEntities.size()) {
			Entity *e = mEntities[index];
			if (e->Type() == ENTITY_PLAYER) {
				Player *player = ((Player*)e);
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
				Asteroid *asteroid = ((Asteroid*)e);
				if (asteroid->mPos.x + asteroid->GetRadius() < 0 ||
					asteroid->mPos.y + asteroid->GetRadius() < 0) {
					int type = asteroid->mType;
					RemoveEntity(e);
					AddAsteroid(type, 2, Vec2(1, 1), Vec2(0));
					--index;
				}
			} else if (e->Type() == ENTITY_HEALTHPACKAGE) {
				HealthPackage *healthPackage = ((HealthPackage*)e);
				if (healthPackage->mPos.x + healthPackage->GetRadius() < 0 ||
					healthPackage->mPos.y + healthPackage->GetRadius() < 0) {

					RemoveEntity(e);
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
			Player *player = GET_ENTITY(Player, ENTITY_PLAYER, pair);
			Shot *shot = GET_ENTITY(Shot, ENTITY_BULLET, pair);
			Asteroid *asteroid = GET_ENTITY(Asteroid, ENTITY_ASTEROID, pair);
			HealthPackage *healthPackage = GET_ENTITY(HealthPackage, ENTITY_HEALTHPACKAGE, pair);

			if (player && asteroid) {
				int type = asteroid->mType;
				if (player->mHealth == player->defaultHealth / 2) {
					if (player->mFrameTimeIsHit <= 0) {
						AddExplosion(player->GetPosition(), ENTITY_PLAYER);

						SetHealth(0);

						RemoveEntity(player);
						RemoveEntity(asteroid);

						player->isHit = false;
						mLostRound = true;

						AddAsteroid(type, 2, Vec2(1, 1), Vec2(0));
					}
				} else {
					player->Hit();
					SetHealth(player->mHealth);
					AddExplosion(asteroid->GetPosition(), ENTITY_PLAYER);
					RemoveEntity(asteroid);
					
					AddAsteroid(type, 2, Vec2(1, 1), Vec2(0));		
				}

			} else if (asteroid && shot) {
				RemoveEntity(shot);
				if (asteroid->mHealth == asteroid->defaulthealth) {
					Vec2 pos = Vec2(asteroid->mPos.x, asteroid->mPos.y);
					float health = asteroid->defaulthealth / 2;
					int type = asteroid->mType;
					RemoveEntity(asteroid);
					
					AddScore(1);
					AddAsteroid(type, 2, Vec2(health / 100, health / 100), pos);

				} else if (asteroid->mHealth == asteroid->defaulthealth / 2) {
					AddExplosion(asteroid->GetPosition(), ENTITY_ASTEROID);
					if (mCountAsteroids == 4) {
						AddAsteroid(asteroid->mType, 2, Vec2(1, 1), Vec2(0));
						mCountAsteroids = 0;
					} else {
						++mCountAsteroids;
					}
					RemoveEntity(asteroid);
					AddScore(2);
				}
			} else if (healthPackage && player) {
				RemoveEntity(healthPackage);
				player->mHealth = player->defaultHealth;
				player->isHit = false;
				player->mFrameTimeIsHit = player->coolDownIsHit;

			} else if (asteroid && !player && !shot) {
				//RemoveEntity(pair.mEntityA);
				//RemoveEntity(pair.mEntityB);			
			}
		}
	}

	void ManagerModel::RemoveDeadExplosion() {
		int index = 0;
		while (index < mEntities.size()) {
			Entity *e = mEntities[index];
			if (e->Type() == ENTITY_EXPLOSION) {
				if (e->IsDead()) {
					RemoveEntity(e);
					--index;
				}
			}
			++index;
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

	void ManagerModel::OnPlayerMoved(Player *p) {
		for (View::ManagerView *v : mViews) {
			v->OnPlayerMoved(p);
		}
	}

	void ManagerModel::OnMovePlayer(const Vec2 &delta) {
		for (Entity *e : mEntities) {
			if (e->Type() == ENTITY_PLAYER) {
				((Player*)e)->mDir += delta;
			}
		}
	}

	Vec2 ManagerModel::GetStartPositionForShot() {
		Vec2 position = Vec2(0, 0);
		for (Entity *e : mEntities) {
			if (e->Type() == ENTITY_PLAYER) {
				float x = ((Player*)e)->mPos.x + (((Player*)e)->GetRadius() * 2);
				float y = ((Player*)e)->mPos.y + ((Player*)e)->GetRadius();
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
			view->PlayShotSoundEffect((Shot*)shot);
		}
	}

	void ManagerModel::OnMoveAsteroid() {
		for (Entity *e : mEntities) {
			if (e->Type() == ENTITY_ASTEROID) {
				((Asteroid*)e)->mPos.x -= 1;
			}
		}
	}

	void ManagerModel::OnAsteroidMoved(Asteroid *a) {
		for (auto *view : mViews) {
			view->OnAsteroidMoved(a);
		}
	}

	void ManagerModel::AddAsteroid(int type, int length, Vec2 scale, Vec2 startPosition) {
		for (int i = 0; i != length; ++i) {
			Asteroid *asteroid = DBG_NEW Asteroid();
			asteroid->OnInit(this);
			asteroid->mType = type;
			asteroid->SetType(type);
			asteroid->Cleavage(startPosition, scale);

			mEntities.push_back(asteroid);
			for (auto *view : mViews) {
				view->OnAsteroidSpawned((Asteroid*)asteroid);
			}
		}
	}

	void ManagerModel::OnExplosionMoved(Explosion *e) {
		for (auto *view : mViews) {
			view->OnExplossionMoved(e);
		}
	}

	void ManagerModel::OnMoveExplosion(Explosion *e) {
		/*for (Entity *e : mEntities) {
			if (e->Type() == ENTITY_ASTEROID) {
				((NewAsteroid*)e)->mPos.x -= 1;
			}
		}*/
	}

	void ManagerModel::AddExplosion(Vec2 startPosition, Model::EntityType entity) {
		Explosion *explosion = DBG_NEW Explosion();
		explosion->OnInit(this);
		explosion->mPos = startPosition;
		if (entity == ENTITY_ASTEROID) {
			explosion->mScale /= 1.5;
		} else if (entity == ENTITY_PLAYER) {
			explosion->mScale *= 2;
		}
		mEntities.push_back(explosion);

		for (auto *view : mViews) {
			view->OnExplosionSpawned((Explosion*)explosion);
			view->PlayExplosionSoundEffect((Explosion*)explosion);
		}
	}

	void ManagerModel::OnHpUpdated(HealthKeeper *h) {
		for (View::ManagerView *v : mViews) {
			v->OnHPUpdate(h);
		}
	}

	void ManagerModel::SetHealth(int health) {
		for (Entity *e : mEntities) {
			if (e->Type() == ENTITY_HP) {
				((HealthKeeper*)e)->mHealth = health;
			}
		}
	}

	int ManagerModel::GetHealth() {
		int health = 0;
		for (Entity *e : mEntities) {
			if (e->Type() == ENTITY_SCORE) {
				health = ((HealthKeeper*)e)->mHealth;
			}
		}
		return health;
	}

	void ManagerModel::OnScoreUpdated(ScoreKeeper *s) {
		for (View::ManagerView *v : mViews) {
			v->OnScoreupdate(s);
		}
	}

	void ManagerModel::AddScore(int score) {
		for (Entity *e : mEntities) {
			if (e->Type() == ENTITY_SCORE) {
				((ScoreKeeper*)e)->mScore += score;
			}
		}
	}

	int ManagerModel::GetScore() {
		int score = 0;
		for (Entity *e : mEntities) {
			if (e->Type() == ENTITY_SCORE) {
				score = ((ScoreKeeper*)e)->mScore;
			}
		}
		return score;
	}

	void ManagerModel::OnMoveHealthPackage() {
		for (Entity *e : mEntities) {
			if (e->Type() == ENTITY_HEALTHPACKAGE) {
				((HealthPackage*)e)->mDir.x += 1;
				((HealthPackage*)e)->mDir.y += 1;
			}
		}
	}

	void ManagerModel::OnHealthPackageMoved(HealthPackage *h) {
		for (View::ManagerView *v : mViews) {
			v->OnHealthPackageMoved(h);
		}
	}

	void ManagerModel::AddHealthPackage() {
		HealthPackage *healthPackage = DBG_NEW HealthPackage();
		healthPackage->OnInit(this);

		mEntities.push_back(healthPackage);
		for (auto *view : mViews) {
			view->OnHealthPackageSpawned((HealthPackage*)healthPackage);
		}
	}

	void ManagerModel::OnEnemieBossMoved(EnemieBoss *e) {
		for (View::ManagerView *v : mViews) {
			v->OnEnemieBossMoved(e);
		}
	}

	void ManagerModel::OnMoveEnemieBoss() {
		for (Entity *e : mEntities) {
			if (e->Type() == ENTITY_HEALTHPACKAGE) {
				((EnemieBoss*)e)->mDir.x += 1;
				((EnemieBoss*)e)->mDir.y += 1;
			}
		}
	}

	void ManagerModel::AddEnemieBoss() {
		EnemieBoss *enemieBoss = DBG_NEW EnemieBoss();
		enemieBoss->OnInit(this);

		mEntities.push_back(enemieBoss);
		for (auto *view : mViews) {
			view->OnEnemieBossSpawned((EnemieBoss*)enemieBoss);
		}
	}

	bool ManagerModel::WonRound() {
		return mWonRound;
	}

	bool ManagerModel::LostRound() {
		return mLostRound;
	}

	void ManagerModel::SetPlayArea(Vec2 screen) {
		mPlayArea.x = screen.x;
		mPlayArea.y = screen.y;
	}

	Vec2 ManagerModel::GetPlayArea() {
		return mPlayArea;
	}
}