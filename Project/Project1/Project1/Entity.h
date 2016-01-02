#pragma once

namespace Model {
	enum EntityType {
		ENTITY_NONE = 0,
		ENTITY_PLAYER,
		ENTITY_ASTEROID,
		ENTITY_BULLET
	};

	class ManagerModel;

	class Entity {
		public:
			Entity() { mModel = NULL; }
			virtual ~Entity() {};

			virtual void OnInit(ManagerModel *m) { mModel = m; }
			virtual void OnUpdate(const HiResTimer &timer) = 0;
			virtual bool IsDead() = 0;

			virtual EntityType Type() = 0;

			ManagerModel* GetModel() { return mModel; }

		private:
			ManagerModel* mModel;
	};

}