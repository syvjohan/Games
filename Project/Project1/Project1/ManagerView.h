#pragma once

#include <framework.h>
#include <vector>

namespace Model {
	class Entity;
	class ManagerModel;
	class Player;
	class Shot;
	class Asteroid;
	class Explosion;
	class ScoreKeeper;
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

	struct TextDef {
		RenderText  *mTexture;
		Vec2         mPosition;
		Vec2         mScale;
		float        mRotation;
		Vec2         mOrigin;
		RectangleF   mClip;
		Vec4         mTint;
	};

	struct SoundDef {

	};

	class ManagerView {
		public:
				ManagerView();
				ManagerView(Common *common, Model::ManagerModel *m);
				~ManagerView();

				void OnUpdate(const float dt);

				//Render
				void OnRender();
				void OnRenderSprites();
				void OnRenderText();

				// Player
				void OnPlayerSpawned(Model::Player *player);
				void OnPlayerMoved(const Model::Player *player);
				bool OnPlayerUpdatedAnimation(const Model::Player *player);
				void OnPlayerUpdatedPhysics(const Model::Player *player);

				//Asteroids
				void OnAsteroidSpawned(Model::Asteroid *asteroid);
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

				//Text
				void OnUpdateText();

		private:
			Common *mCommon;
			Model::ManagerModel *mModel;
			Renderer2D *mRenderer;

			std::vector<SpriteDef> mSprites;
			std::vector<TextDef> mTexts;

			RenderFont *font;
			RenderText *textScore;
			RenderText *textHealth;

			AudioSource *source;

			bool btnIsPressedPlane = false; //controlling frames from fires behind plane.
		
			float frameTimeBullet = 0.0f;
			float frameTimePlane = 0.0f;

			void OnUpdatePlayer(const float dt);
			void OnUpdateShot(const float dt);
			void OnUpdateAsteroid(const float dt);
	};
}