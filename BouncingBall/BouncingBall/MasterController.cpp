#include "MasterController.h"

SDL_Window *window = NULL;
SDL_Event event;
SDL_Renderer *render = NULL;
SDL_Surface *surfaceScreen, *surfaceBall = NULL;

#define SDL_SRCCOLORKEY  0x00001000

float screenWidth = 800;
float screenHeight = 800;

float border = 40;

SDL_Rect rectBall;
SDL_Rect rectArea;

MasterController::MasterController() {}
MasterController::~MasterController() {}

//Function for printing to Output console. Uses winapi.
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

SDL_Surface* MasterController::loadImage(char *cStr) {

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

void FillRectBall(int x, int y, int w, int h) {
	rectBall = { x, y, w, h };

	Uint32 grey = SDL_MapRGB(surfaceBall->format, 0, 0, 0);
	SDL_SetColorKey(surfaceBall, SDL_SRCCOLORKEY, grey);

	SDL_BlitScaled(surfaceBall, NULL, surfaceScreen, &rectBall);
}

void MasterController::freeMem() {
	/*delete ballSimulation;
	ballSimulation = NULL;

	delete ballView;
	ballView = NULL;

	delete boarderView;
	boarderView = NULL;*/

}

void MasterController::gameLoop() {
	ballSimulation = new BallSimulation();
	ballSimulation->init();

	ballView = new BallView(ballSimulation);
	boarderView = new BoarderView();

	//OBSERVE SET PROGRAM SCALE HERE!!!!!!
	ballView->setScale(0.9f); //need to be called before changing to ballSimulation is done!


	SDL_Init(SDL_INIT_EVERYTHING);

	window = SDL_CreateWindow("BouncingBall", 400, 200, screenWidth * boarderView->getScale(), screenHeight * boarderView->getScale(), SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN); //Second and third argument is for screen position
	render = SDL_CreateRenderer(window, 0, 0);
	surfaceScreen = SDL_GetWindowSurface(window);

	surfaceBall = loadImage("ball.png");

	Uint64 frequency = SDL_GetPerformanceFrequency();
	Uint64 thisTick = SDL_GetPerformanceCounter();
	Uint64 lastTick = thisTick;
	float deltaTime;

	bool running = 1;
	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = 0;
			} else if (event.type == SDL_WINDOWEVENT) {
				if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
					//Rezise window
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
		rectArea = boarderView->getPlayArea(window, border * boarderView->getScale());
		boarderView->renderBorder(surfaceScreen, rectArea);

		//draw ball.
		rectBall = ballView->drawBall(deltaTime, rectArea);
		FillRectBall(rectBall.x, rectBall.y, rectBall.w, rectBall.h);

		SDL_UpdateWindowSurface(window);
		SDL_Delay(0);
	}

	SDL_FreeSurface(surfaceScreen);
	SDL_FreeSurface(surfaceBall);

	freeMem();

	SDL_DestroyWindow(window);
	SDL_Quit();
}
