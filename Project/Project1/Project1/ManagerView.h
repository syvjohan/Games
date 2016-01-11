#pragma once

#include <framework.h>
#include <vector>

#include "Defs.h"

namespace Model {
	class Entity;
	class ManagerModel;
	class Player;
	class Shot;
	class Asteroid;
	class Explosion;
	class ScoreKeeper;
	class HealthKeeper;
	class HealthPackage;
	class EnemieBoss;
}

namespace View {
	class ManagerView {
		public:
				ManagerView();
				ManagerView(Common *common, Model::ManagerModel *m);
				~ManagerView();

				void OnUpdate(const float dt);

				//Render
				void OnRender();

				// Player
				void OnPlayerSpawned(Model::Player *player);
				void OnPlayerMoved(const Model::Player *player);
				bool OnPlayerUpdatedAnimation(const Model::Player *player);
				void OnPlayerUpdatedPhysics(const Model::Player *player);

				//Asteroids
				void OnAsteroidSpawned(Model::Asteroid *asteroid);
				Texture2D* GetAsteroidTexture(Model::Asteroid *asteoid);
				void OnAsteroidMoved(Model::Asteroid *asteroid);
				void OnMoveAsteroid(const Model::Asteroid *asteroid);
				void OnAsteroidUpdatedPhysics(Model::Asteroid *asteroid);
				void OnAsteroidUpdatedAnimation(const Model::Asteroid *asteroid);

				//Bullets
				void OnShotSpawned(Model::Shot *shot);
				void OnMoveShot(const Model::Shot *shot);
				void OnShotMoved(const Model::Shot *shot);
				void OnShotUpdatePhysics(const Model::Shot *shot);
				void PlayShotSoundEffect(const Model::Shot *shot);

				//Explosion
				void OnExplosionSpawned(Model::Explosion *explosion);
				void OnExplosionUpdateAnimation(const Model::Explosion *explosion);
				void OnExplossionMoved(const Model::Explosion *explosion);
				void OnMoveExplossion(const Model::Explosion *explosison);
				void PlayExplosionSoundEffect(const Model::Explosion *explosion);

				void OnEntityDied(int index);

				//Score
				void OnScoreInit(Model::ScoreKeeper *scoreKeeper);
				void OnScoreupdate(const Model::ScoreKeeper *scoreKeeper);

				//HP
				void OnHPInit(Model::HealthKeeper *healthKeeper);
				void OnHPUpdate(const Model::HealthKeeper *healthKeeper);

				//HealthPackage
				void OnHealthPackageSpawned(Model::HealthPackage *healthPackage);
				void OnHealthPackageMoved(Model::HealthPackage *healthPackage);
				void OnMoveHealthPackage(const Model::HealthPackage *healthPackage);
				void OnHealthPackageUpdatedPhysics(Model::HealthPackage *healthPackage);

				//Enemie boss
				void OnEnemieBossSpawned(Model::EnemieBoss *enemieBoss);
				void OnEnemieBossMoved(Model::EnemieBoss *enemieBoss);
				void OnMoveEnemieBoss(const Model::EnemieBoss *enemieBoss);
				void OnEnemieBossUpdatedPhysics(Model::EnemieBoss *enemieBoss);
				void OnEnemieBossUpdatedAnimation(const Model::EnemieBoss *enemieBoss);
		private:
			Common *mCommon;
			Model::ManagerModel *mModel;
			Renderer2D *mRenderer;

			std::vector<SpriteDef> mSprites;

			RenderFont	*mFont;

			AudioSource *source;

			bool btnIsPressedPlane = false; //controlling frames from fires behind plane.
		
			float frameTimeBullet = 0.0f;
			float frameTimePlane = 0.0f;

			void OnUpdatePlayer(const float dt);
			void OnUpdateShot(const float dt);
			void OnUpdateAsteroid(const float dt);
	};
}