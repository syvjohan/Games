#include "MasterController.h"

SDL_Window *window = NULL;
SDL_Event event;
SDL_Renderer *render = NULL;
SDL_Surface *surfaceScreen, *surfaceBall, *surfaceOldScreen = NULL;

#define SDL_SRCCOLORKEY  0x00001000

float screenWidth = 850;
float screenHeight = 800;

float border = 40;

SDL_Rect rectBall;
SDL_Rect rectArea;

MasterController::MasterController() {}
MasterController::~MasterController() {}

void FillRectBall(int x, int y, int w, int h) {
	rectBall = { x, y, w, h };

	Uint32 grey = SDL_MapRGB(surfaceBall->format, 0, 0, 0);
	SDL_SetColorKey(surfaceBall, SDL_SRCCOLORKEY, grey);

	SDL_BlitScaled(surfaceBall, NULL, surfaceScreen, &rectBall);
}

void MasterController::freeMem() {
	if (ballSimulation) {
		delete ballSimulation;
		ballSimulation = NULL;
	} 
	
	if (ballView) {
		delete ballView;
		ballView = NULL;
	} 
	
	if (boarderView) {
		delete boarderView;
		boarderView = NULL;
	} 
	
	if (scale) {
		delete scale;
		scale = NULL;
	}
}

void MasterController::gameLoop() {
	scale = new Scale();
	//Set scale here!!!
	scale->set(1.f, 1.f);

	ballSimulation = new BallSimulation();
	ballSimulation->init();

	ballView = new BallView(ballSimulation);
	boarderView = new BoarderView();

	SDL_Init(SDL_INIT_EVERYTHING);

	window = SDL_CreateWindow("BouncingBall", 400, 200, screenWidth * scale->getW(), screenHeight * scale->getH(), SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
	render = SDL_CreateRenderer(window, 0, 0);
	surfaceScreen = SDL_GetWindowSurface(window);

	surfaceBall = ballSimulation->loadImage("ball.png", *surfaceScreen);
	if (surfaceBall == NULL) {
		printf("could not get ball image");
	}

	Uint64 frequency = SDL_GetPerformanceFrequency();
	Uint64 thisTick = SDL_GetPerformanceCounter();
	Uint64 lastTick = thisTick;
	float deltaTime;

	float h;
	float w;

	bool running = 1;
	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = 0;
			} else if (event.type == SDL_WINDOWEVENT) {
				if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
					//Rezise window
					surfaceScreen = SDL_GetWindowSurface(window);

					//calculate new scaling.
					h = surfaceScreen->h - surfaceOldScreen->h + surfaceOldScreen->h;
					w = surfaceScreen->w - surfaceOldScreen->w + surfaceOldScreen->w;
					
					w = abs(w);
					h = abs(h);
					
					w /= 1000;
					h /= 1000;

					if (w == 0) {
						w = scale->getW();
					} else if (h == 0) {
						h = scale->getH();;
					} 

					scale->set(w, h);
				}
			} else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
				running = 0;
			} else {
				surfaceOldScreen = SDL_GetWindowSurface(window);
			}
		}

		// Clear screen
		SDL_FillRect(surfaceScreen, NULL, 0);

		thisTick = SDL_GetPerformanceCounter();
		// Delta time in milliseconds.
		deltaTime = ((float)(thisTick - lastTick) / (float)frequency) * 1000.0f;
		lastTick = thisTick;

		// Render game board
		rectArea = boarderView->getPlayArea(window, border * scale->getW(), border * scale->getH());
		boarderView->renderBorder(surfaceScreen, rectArea);

		//draw ball.
		rectBall = ballView->drawBall(deltaTime, rectArea, scale->getH(), scale->getW());
		FillRectBall(rectBall.x, rectBall.y, rectBall.w, rectBall.h);

		SDL_UpdateWindowSurface(window);
		SDL_Delay(0);
	}

	//Free memory.
	SDL_FreeSurface(surfaceScreen);
	SDL_FreeSurface(surfaceBall);

	freeMem();

	SDL_DestroyWindow(window);
	SDL_Quit();
}
