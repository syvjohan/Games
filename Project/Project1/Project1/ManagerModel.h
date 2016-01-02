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

	class ManagerModel {
		public:
		ManagerModel();
		~ManagerModel();

		void Init(Vec2 screen, Vec2 border);
		void AddView(View::ManagerView *v);
		void RemoveView(View::ManagerView *v);
		void OnUpdate(const HiResTimer &timer);

		void OnPlayerMoved(NewPlayer *p); //outgoing..
		void OnMovePlayer(const Vec2 &delta); //incoming..
		
		void OnColissionWall();
		void OnCollisionUnits();


		Vec2 GetPlayArea();

		private:
		std::vector<View::ManagerView*> mViews;
		std::vector<Entity*> mEntities;

		void SetPlayArea(Vec2 screen, Vec2 border);
		Vec2 mPlayArea;
		Vec2 border;
	};

}