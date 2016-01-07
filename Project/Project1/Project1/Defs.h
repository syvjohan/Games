#ifndef DEFS_H
#define DEFS_H

#include <crtdbg.h>

#ifdef _DEBUG
#define DBG_NEW new(1, __FILE__, __LINE__)
#else
#define DBG_NEW new
#endif

#include "Entity.h"
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
}

#endif //!DEFS_H