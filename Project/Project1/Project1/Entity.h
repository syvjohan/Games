#pragma once

namespace Model {
	enum EntityType {
		ENTITY_NONE = 0,
		ENTITY_PLAYER,
		ENTITY_ENEMIEBOSS,
		ENTITY_ASTEROID,
		ENTITY_BULLET,
		ENTITY_BULLETENEMIEBOSS,
		ENTITY_HEALTHPACKAGE,
		ENTITY_EXPLOSION,
		ENTITY_NEWGAME,
		ENTITY_CONTINUE,
		ENTITY_HELP,
		ENTITY_BACKGROUND_MENU,
		ENTITY_BACKGROUND_AFTER_GAME,
		ENTITY_HP,
		ENTITY_SCORE,
		ENTITY_RESULT
	};

	class ManagerModel;
	class MenuModel;

	class Entity {
		public:
			Entity() { mModel = NULL; }
			virtual ~Entity() {};

			virtual void OnInit(ManagerModel *m) { mModel = m; }
			virtual void OnInit(MenuModel *m) { mModel2 = m; }
			virtual void OnUpdate() = 0;
			virtual bool IsDead() = 0;

			virtual Vec2 GetPosition() const = 0;
			virtual float GetRadius() const = 0;

			virtual EntityType Type() = 0;

			ManagerModel* GetModel() { return mModel; }
			MenuModel* GetMenuModel() { return mModel2; }

		private:
			ManagerModel* mModel;
			MenuModel* mModel2;
	};

}