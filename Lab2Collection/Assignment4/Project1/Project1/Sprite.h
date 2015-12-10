#include <framework.h>

class Texture2D;

struct Animation {
	Vec2 pos;
	Vec2 start;
	Vec2 frameSize;
	float frameTime;
	Vec2 scale;
	int frameCount;
	Texture2D* texture;
	int currentFrame;
};







