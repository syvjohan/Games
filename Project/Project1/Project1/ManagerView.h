#pragma once

#include <framework.h>
#include <vector>

namespace Model {
	class Entity;
	class ManagerModel;
	class NewPlayer;
	class Shot;
	class NewAsteroid;
}

namespace View {
	struct SpriteDef {
		Texture2D   *mTexture;
		Vec2         mPosition;
		Vec2         mScale;
		float        mRotation;
		Vec2         mOrigin;
		RectangleF   mClip;
		Vec4         mTint;
		Model::Entity *mEntity;
	};

	class ManagerView {
		public:
				ManagerView();
				ManagerView(Common *common, Model::ManagerModel *m);
				~ManagerView();

				void OnUpdate(const float dt);
				void OnRender();

				// Player
				void OnPlayerSpawned(Model::NewPlayer *player);
				void OnPlayerMoved(const Model::NewPlayer *player);
				bool OnPlayerUpdatedAnimation(const Model::NewPlayer *player);
				void OnPlayerUpdatedPhysics(const Model::NewPlayer *player);

				//Asteroids
				void OnAsteroidSpawned(Model::NewAsteroid *asteroid);
				void OnAsteroidMoved(Model::NewAsteroid *asteroid);
				void OnMoveAsteroid(const Model::NewAsteroid *asteroid);
				void OnAsteroidUpdatedPhysics(Model::NewAsteroid *asteroid);
				void OnAsteroidUpdatedAnimation(const Model::NewAsteroid *asteroid);

				//Bullets
				void OnShotSpawned(Model::Shot *shot);
				void OnMoveShot(const Model::Shot *shot);
				void OnShotMoved(const Model::Shot *shot);
				void OnShotUpdatePhysics(const Model::Shot *shot);

				void OnEntityDied(int index);
		private:
			Common *mCommon;
			Model::ManagerModel *mModel;
			Renderer2D *mRenderer;
			std::vector<SpriteDef> mSprites;

			bool btnIsPressedPlane = false; //controlling frames from fires behind plane.
		
			float frameTimeBullet = 0.0f;
			float frameTimePlane = 0.0f;

			void OnUpdatePlayer(const float dt);
			void OnUpdateShot(const float dt);
			void OnUpdateAsteroid(const float dt);
	};
}