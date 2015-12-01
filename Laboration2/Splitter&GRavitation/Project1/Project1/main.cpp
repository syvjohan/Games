#include "SplitterSystem.h"
#include "Defs.h"

#include <SDL.h>

SDL_Renderer *render = NULL;
SDL_Window *window = NULL;
SDL_Event event;
SDL_Surface *surfaceScreen = NULL;

#define SCREENWIDTH 1000
#define SCREENHEIGHT 500

SplitterSystem splitterSystem;

void gameLoop() {
	SDL_Init(SDL_INIT_EVERYTHING);

	window = SDL_CreateWindow("BouncingBall", 400, 200, SCREENWIDTH, SCREENHEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN); //Second and third argument is for screen position
	render = SDL_CreateRenderer(window, 0, 0);
	surfaceScreen = SDL_GetWindowSurface(window);

	splitterSystem.init(surfaceScreen);

	Uint64 frequency = SDL_GetPerformanceFrequency();
	Uint64 thisTick = SDL_GetPerformanceCounter();
	Uint64 lastTick = thisTick;
	float deltaTime;

	bool running = 1;
	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = 0;
			} else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
				running = 0;
			}
		}

		//Clear the screen.
		SDL_FillRect(surfaceScreen, NULL, 0);

		thisTick = SDL_GetPerformanceCounter();
		// Delta time in milliseconds.
		deltaTime = ((float)(thisTick - lastTick) / (float)frequency) * 10.0f;
		lastTick = thisTick;

		
		splitterSystem.drawParticles(deltaTime);


		SDL_UpdateWindowSurface(window);
		SDL_Delay(0);
	}

	SDL_FreeSurface(surfaceScreen);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int main(int, char**) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	srand(time(NULL));
	
	gameLoop();

	return 0;
}

