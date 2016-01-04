#pragma once

#include <framework.h>
#include <vector>

#include "Defs.h"
#include "entity.h"

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

	class ManagerModel;
	class NewPlayer;
	class Shot;
	class NewAsteroid;
	class NewExplsion;

	class ManagerModel {
		public:
			ManagerModel();
			~ManagerModel();

			void Init(Vec2 screen);
			void AddView(View::ManagerView *v);
			void RemoveView(View::ManagerView *v);
			void OnUpdate(const float dt);

			void OnPlayerMoved(NewPlayer *p); //outgoing..
			void OnMovePlayer(const Vec2 &delta); //incoming..
			Vec2 GetStartPositionForShot();
		
			void OnMoveShot(); //incoming..
			void OnShotMoved(Shot *s); //outgoing..
			void AddShot(Vec2 startPosition);

			void OnMoveAsteroid(); //incoming..
			void OnAsteroidMoved(NewAsteroid *s); //outgoing..
			void AddAsteroid(int type, int length);

			/*void OnExplosion(NewExplosion *e);
			void AddExplosion(Vec2 startPosition);*/

			Vec2 GetPlayArea();

		private:
			std::vector<View::ManagerView*> mViews;
			std::vector<Entity*> mEntities;


			void ColissionWall();
			std::vector<CollisionPair> CollisionEntities() const;
			void ProcessCollisions(const std::vector<CollisionPair> &collisions);
			void RemoveEntity(Entity *e);

			void SetPlayArea(Vec2 screen);
			Vec2 mPlayArea;
	};
}