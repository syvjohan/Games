
#include <framework.h>
#include "Defs.h"

class Texture2D;

struct Animation {
	Vec2 start;
	Vec2 frameSize;
	float frameTime;
	int frameCount;
	Texture2D* texture;
	int currentFrame;
};







