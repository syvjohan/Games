#include <framework.h>

namespace Model {
	struct PlaneAnimation {
		float mFrameTime;
		int mCurrentFrame;

		float mFrameTimeBtnRelease;
		float mFramTimeIsHit;
	};

	struct Plane {
		Texture2D *mTexture;
		Vec2 mPos;
		Vec2 mVel;
		Vec2 mAcc;
		Vec2 mDir;
		Vec2 mScale;
		Vec2 mSize;
		
		float mOrientation;
		int mHealth;

		Color mColor;
		Vec2 mPlayArea;

		Model::PlaneAnimation animation;
	};
}