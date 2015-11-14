#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <Windows.h>

#include "Camera.h"

SDL_Window *window = NULL;
SDL_Event event;
SDL_Renderer *render = NULL;
SDL_Surface *surfaceScreen, *surfaceBall = NULL;

#define SDL_SRCCOLORKEY  0x00001000
#define SIZESCREEN 800
#define SIZE 40

float screenWidth = SIZESCREEN;
float screenHeight = SIZESCREEN;

float border = SIZE;

float scale = 1; // master, decide size of everything.

float ballSizeW = SIZE;
float ballSizeH = SIZE;
float ballX = SIZE;
float ballY = SIZE;

SDL_Rect rectBall;

typedef struct coordinate_s {
	float x;
	float y;
}coordinate_t;

coordinate_t *logicalCoordinates;
coordinate_t *visualCoordinates;
int index = 0;
int len;

//Winapi
int outputf(const char *fmt, ...) {
	va_list va;
	va_start(va, fmt);

	char buffer[4096];

	int len = vsprintf(buffer, fmt, va);
	buffer[len] = '\n';
	buffer[len + 1] = '\0';

	OutputDebugString(buffer);

	va_end(va);
}

void setScaleBalle(float s) {
	ballSizeH *= s;
	ballSizeW *= s;

	ballX *= s;
	ballX *= s;
}

void setScale(float s) {
	scale = s;
	setScaleBalle(s);
}

float getScale() {
	return scale;
}

struct v2 {
	float x, y;

	v2 operator+(const v2& v1) {
		v2 v;
		v.x = x + v1.x;
		v.y = y + v1.y;
		return v;
	}

	v2 operator*(float s) {
		v2 v;
		v.x = x * s;
		v.y = y * s;
		return v;
	}

	void normalize() {
		float l = sqrtf(x * x + y * y);
		if (fabsf(l) > FLT_EPSILON) { //uses FLT_EPSILON because we dont wannt to compare with 0 (Difference between 1 and the least value greater than 1 that is representable).
			x /= l;
			y /= l;
		}
	}
};

struct Physics {
	v2 position;
	v2 velocity; //speed.
	float restitution; //speed slowingdown.

	void applyForce(const v2 &force) {
		velocity = velocity + force;
	}

	void update(float delta, const SDL_Rect &area) {
		position = position + velocity * delta;

		if (position.x < area.x) {
			velocity.x *= -restitution;
			position.x = area.x;
		}

		if (position.x >(area.x + area.w) - ballSizeW) {
			velocity.x *= -restitution;
			position.x = (area.x + area.w) - ballSizeW;
		}

		if (position.y < area.y) {
			velocity.y *= -restitution;
			position.y = area.y;
		}

		if (position.y >(area.y + area.h) - ballSizeH) {
			velocity.y *= -restitution;
			position.y = (area.y + area.h) - ballSizeW;
		}
	}
};


void FillRectBall(int x, int y, int w, int h) {
	rectBall = { x, y, w, h };

	Uint32 grey = SDL_MapRGB(surfaceBall->format, 0, 0, 0);
	SDL_SetColorKey(surfaceBall, SDL_SRCCOLORKEY, grey);

	SDL_BlitScaled(surfaceBall, NULL, surfaceScreen, &rectBall);
}

SDL_Surface *loadImage(char *cStr) {

	SDL_Surface *loadedSurface = IMG_Load(cStr);

	if (loadedSurface == NULL) {
		outputf("Unable to load image %s! SDL_image Error: %s\n", cStr, IMG_GetError());
	} else {
		//The final optimized image
		SDL_Surface *optimizedSurface = NULL;

		//Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface(loadedSurface, surfaceScreen->format, NULL);
		if (optimizedSurface == NULL) {
			outputf("Unable to optimize image %s! SDL Error: %s\n", cStr, SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
		return optimizedSurface;
	}
}

void renderBorder(SDL_Surface *surf, const SDL_Rect &area, int borderWidth = 2) {
	SDL_Rect outer = area;
	outer.x -= borderWidth;
	outer.y -= borderWidth;
	outer.w += borderWidth * 2; //need both multiplier otherwise bord will only be on left and upper side.
	outer.h += borderWidth * 2; //need both multiplier otherwise bord will only be on left and upper side.

	const Uint32 BORDER_COLOR = 0xFFFFFF;
	const Uint32 AREA_COLOR = 0x000000;

	SDL_FillRect(surf, &outer, BORDER_COLOR);
	SDL_FillRect(surf, &area, AREA_COLOR);
}

SDL_Rect getPlayArea(SDL_Window *window, int borderSize) {
	SDL_Rect result;
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	result.x = borderSize;
	result.y = borderSize;
	result.w = w - borderSize * 2;
	result.h = h - borderSize * 2;
	return result;
}

int main(int, char**) {
	//OBSERVE SET PROGRAM SCALE HERE!!!!!!
	setScale(0.9f);

	SDL_Init(SDL_INIT_EVERYTHING);

	window = SDL_CreateWindow("BouncingBall", 400, 200, screenWidth * getScale(), screenHeight * getScale(), SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN); //Second and third argument is for screen position
	render = SDL_CreateRenderer(window, 0, 0);
	surfaceScreen = SDL_GetWindowSurface(window);

	surfaceBall = loadImage("ball.png");

	//Init rect.
	rectBall.w = ballSizeW;
	rectBall.h = ballSizeH;
	rectBall.x = ballX;
	rectBall.y = ballY;

	Uint64 frequency = SDL_GetPerformanceFrequency();
	Uint64 thisTick = SDL_GetPerformanceCounter();
	Uint64 lastTick = thisTick;
	float deltaTime;

	//start values.
	Physics ballPhysics = {
		{ ballX, ballY},
		{ 1, 1 },
		0.95f //0.99995 velocity decreases slowly, 0.95 velocity decreases fast.
	};

	bool running = 1;
	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = 0;
			} else if (event.type == SDL_WINDOWEVENT) {
				if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
					surfaceScreen = SDL_GetWindowSurface(window);
					outputf("Window resized");
				}
			}
		}

		// Clear screen
		SDL_FillRect(surfaceScreen, NULL, 0);

		thisTick = SDL_GetPerformanceCounter();
		// Delta time in milliseconds.
		deltaTime = ((float)(thisTick - lastTick) / (float)frequency) * 1000.0f;
		lastTick = thisTick;

		// Render game board
		SDL_Rect area = getPlayArea(window, border * getScale());
		renderBorder(surfaceScreen, area);

		ballPhysics.update(deltaTime, area);

		rectBall.x = (int)(ballPhysics.position.x + 0.5f);
		rectBall.y = (int)(ballPhysics.position.y + 0.5f);

		//draw ball.
		FillRectBall(rectBall.x, rectBall.y, rectBall.w, rectBall.h);

		SDL_UpdateWindowSurface(window);
		SDL_Delay(0);
	}

	SDL_FreeSurface(surfaceScreen);
	SDL_FreeSurface(surfaceBall);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}