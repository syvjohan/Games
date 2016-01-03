#pragma once

#include <framework.h>
#include <vector>

#include "Defs.h"
#include "entity.h"

namespace View {
	class ManagerView;
}

namespace Model {

	class ManagerModel;
	class NewPlayer;
	class Shot;
	class NewAsteroid;

	class ManagerModel {
		public:
		ManagerModel();
		~ManagerModel();

		void Init(Vec2 screen);
		void AddView(View::ManagerView *v);
		void RemoveView(View::ManagerView *v);
		void OnUpdate(HiResTimer &timer);

		void OnPlayerMoved(NewPlayer *p); //outgoing..
		void OnMovePlayer(const Vec2 &delta); //incoming..
		Vec2 GetStartPositionForShot();
		
		void OnMoveShot(); //incoming..
		void OnShotMoved(Shot *s); //outgoing..
		void AddShot(Vec2 startPosition);

		void OnMoveAsteroid(); //incoming..
		void OnAsteroidMoved(NewAsteroid *s); //outgoing..
		void AddAsteroid();

		void OnColissionWall();
		void OnCollisionEntities();

		Vec2 GetPlayArea();

		private:
		std::vector<View::ManagerView*> mViews;
		std::vector<Entity*> mEntities;

		void RemoveEntity(int index);
		void SetPlayArea(Vec2 screen);
		Vec2 mPlayArea;
	};
}