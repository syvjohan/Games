#pragma once

#include <framework.h>
#include <vector>

namespace Model {
	class Entity;
	class ManagerModel;
	class NewPlayer;
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

		void OnUpdate(const HiResTimer &timer);
		void OnRender();

		// Player
		void OnPlayerSpawned(Model::NewPlayer *player);
		void OnPlayerMoved(Model::NewPlayer *player);
		void OnPlayerDied(Model::NewPlayer *player);
		void OnPlayerUpdatedAnimation(Model::NewPlayer *player);
		void OnPlayerUpdatedPhysics(Model::NewPlayer *player, const HiResTimer &timer);

		////Asteroids
		//void        OnAsteroidsSpawned(Model::NewPlayer *player);
		//void        OnAsteroidsMoved(Player *player);
		//void        OnAsteroidsDied(Player *player);

		////Bullets
		//void        OnBulletsSpawned(Player *player);
		//void        OnBulletsMoved(Player *player);
		//void        OnBulletsDied(Player *player);

		private:
		Common *mCommon;
		Model::ManagerModel *mModel;
		Renderer2D *mRenderer;
		std::vector<SpriteDef> mSprites;

		void OnUpdatePlayer(const HiResTimer &timer);
	};

}