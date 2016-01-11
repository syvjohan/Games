#pragma once

#include <framework.h>
#include <vector>

#include "Defs.h"
#include "Entity.h"

namespace View {
	class ManagerView;
}

namespace Model {
	struct CollisionPair {
		Entity *mEntityA;
		Entity *mEntityB;

		bool operator==(const CollisionPair &pair) const {
			return mEntityA == pair.mEntityA && mEntityB == pair.mEntityB;
		}
	};

	class Player;
	class Shot;
	class Asteroid;
	class Explosion;
	class HealthKeeper;
	class ScoreKeeper;
	class HealthPackage;
	class EnemieBoss;
	class EnemieBossShot;

	class ManagerModel {
		public:
			ManagerModel();
			~ManagerModel();

			void Init(Vec2 screen, int asteroidType1, int asteroidType2, int maxScore);
			void AddView(View::ManagerView *v);
			void RemoveView(View::ManagerView *v);
			void OnUpdate(const float dt);

			//Player
			void OnPlayerMoved(Player *p); //outgoing..
			void OnMovePlayer(const Vec2 &delta); //incoming..
			Vec2 GetStartPositionForShot();
			
			//Shot
			void OnMoveShot(); //incoming..
			void OnShotMoved(Shot *s); //outgoing..
			void AddShot(Vec2 startPosition);

			//Asteroid
			void OnMoveAsteroid(); //incoming..
			void OnAsteroidMoved(Asteroid *a); //outgoing..
			void AddAsteroid(int type, int length, Vec2 scale, Vec2 startPosition);

			//Health package
			void OnMoveHealthPackage();
			void OnHealthPackageMoved(HealthPackage *h);
			void AddHealthPackage();

			//Explosion
			void OnMoveExplosion(Explosion *e);
			void OnExplosionMoved(Explosion *e);
			void AddExplosion(Vec2 startPosition, Model::EntityType);
			void RemoveDeadExplosion();

			//Score
			void OnScoreUpdated(ScoreKeeper *s);
			void AddScore(int score);
			int GetScore();

			//Enemie boss
			void OnEnemieBossMoved(EnemieBoss *e);
			void OnMoveEnemieBoss();
			bool DelayEnemieBossMove(EnemieBoss *e, const float dt);
			void AddEnemieBoss();

			//Enemie boss shot
			void OnMoveEnemieBossShot();
			void OnEnemieBossShotMoved(EnemieBossShot *s);
			void AddEnemieBossShot(Vec2 startPosition);
			void EvalRequestNewBullet(const float dt);

			//health player.
			void SetHealth(int health);
			int GetHealth();

			void OnHpUpdated(HealthKeeper *h);

			int maxScore;

			Vec2 GetPlayArea();

			bool WonRound();
			bool LostRound();

		private:
			std::vector<View::ManagerView*> mViews;
			std::vector<Entity*> mEntities;

			bool mLostRound = false;
			bool mWonRound = false;

			int mCountAsteroids = 0;
			const float asteroidRespawnDelay = 2;

			const float timePeriodSpawnHealtPackage = 5;
			float timerHealthPackage = timePeriodSpawnHealtPackage;

			void ColissionWall();
			std::vector<CollisionPair> CollisionEntities() const;
			void ProcessCollisions(const std::vector<CollisionPair> &collisions);
			void RemoveEntity(Entity *e);

			void SetPlayArea(Vec2 screen);
			Vec2 mPlayArea;
	};
}