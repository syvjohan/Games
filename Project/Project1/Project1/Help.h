#pragma once
#include <framework.h>

#include "Entity.h"

namespace Model {
	class Help : public Entity {
		public:
		Help();
			~Help();

			void OnInit(MenuModel *m);
			void OnUpdate();

			inline bool IsDead() { return false; }

			inline  Vec2 GetPosition() const { return mPos; }
			inline float GetRadius() const { return 0; }

			virtual EntityType Type() { return ENTITY_HELP; }

			void UpdateTextHeader();
			void UpdateTextHeader2();
			void UpdateTextDescript1();
			void UpdateTextDescript2();
			void UpdateTextDescript3();
			void UpdateTextDescript4();

			Vec2 mPos;
			char *mText;
			Color mColor;
			float mRotation;
			Vec2 mScale;
			bool mIsHeader;
	};
}

