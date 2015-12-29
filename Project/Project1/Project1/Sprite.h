#include <framework.h>

class Texture2D;

namespace Model {

	struct Animation {
		Vec2 mPos;
		Vec2 mStart;
		Vec2 mFrameSize;
		float mFrameTime;
		Vec2 mScale;
		int mFrameCount;
		Texture2D* mTexture;
		int mCurrentFrame;
	};
}








