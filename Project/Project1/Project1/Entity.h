#pragma once

namespace Model {
	enum EntityType {
		ENTITY_NONE = 0,
		ENTITY_PLAYER,
		ENTITY_ASTEROID,
		ENTITY_BULLET,
		ENTITY_EXPLOSION
	};

	class ManagerModel;

	class Entity {
		public:
			Entity() { mModel = NULL; }
			virtual ~Entity() {};

			virtual void OnInit(ManagerModel *m) { mModel = m; }
			virtual void OnUpdate() = 0;
			virtual Vec2 GetPosition() const = 0;
			virtual float GetRadius() const = 0;

			virtual EntityType Type() = 0;

			ManagerModel* GetModel() { return mModel; }

		private:
			ManagerModel* mModel;
	};

}