#pragma once

#include <framework.h>
#include <vector>

namespace Model {
	class Entity;
	class ManagerModel;
	class NewPlayer;
	class Shot;
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
		void OnPlayerMoved(const Model::NewPlayer *player);
		bool OnPlayerUpdatedAnimation(const Model::NewPlayer *player);
		void OnPlayerUpdatedPhysics(const Model::NewPlayer *player);

		////Asteroids
		//void        OnAsteroidsSpawned(Model::NewPlayer *player);
		//void        OnAsteroidsMoved(Player *player);
		//void        OnAsteroidsDied(Player *player);

		////Bullets
		void OnShotSpawned(Model::Shot *shot);
		void OnMoveShot(const Model::Shot *shot);
		void OnShotMoved(const Model::Shot *shot);
		void OnShotUpdatedPhysics(const Model::Shot *shot);

		private:
		Common *mCommon;
		Model::ManagerModel *mModel;
		Renderer2D *mRenderer;
		std::vector<SpriteDef> mSprites;

		bool btnIsPressedPlane = false; //controlling frames from fires behind plane.
		int OldKeyPressPlane = 0;
		int keyPressPlane = 0;

		bool btnIsPressedShot = false;
		int oldKeyPressShot = 0;
		int keyPressShot = 0;

		void OnUpdatePlayer(const HiResTimer &timer);
		void OnUpdateShot(const HiResTimer &timer);
	};
}