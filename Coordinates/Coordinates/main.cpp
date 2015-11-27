#include <iostream>
#include <SDL.h>

#include "Camera.h"

#undef main

SDL_Event event;

int main(int, char**) {
	SDL_Init(SDL_INIT_EVERYTHING);

	bool running = 1;
	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = 0;
			}
		}
		//Inside game loop, place logic here!

		//Test code for Camera.h
		//Uppgift 1
		coordinate_t logicalCoordinates1[4];
		coordinate_t c0;
		c0.x = 0;
		c0.y = 0;

		coordinate_t c1;
		c1.x = 7;
		c1.y = 0;

		coordinate_t c2;
		c2.x = 1;
		c2.y = 7;

		coordinate_t c3;
		c3.x = 7;
		c3.y = 7;

		logicalCoordinates1[0] = c0;
		logicalCoordinates1[1] = c1;
		logicalCoordinates1[2] = c2;
		logicalCoordinates1[3] = c3;

		Camera camera;
		coordinate_t *visualCoordinates1;
		visualCoordinates1 = camera.createVisualCoordinatesWhite(logicalCoordinates1, 4);

		printf("White: \n");
		for (int i = 0; i != 4; ++i) {
			std::cout << visualCoordinates1[i].x << ", " << visualCoordinates1[i].y << std::endl;
		}
		printf("\n\n");

		//uppgift 2
		coordinate_t logicalCoordinates2[4];
		coordinate_t c4;
		c4.x = 0;
		c4.y = 0;

		coordinate_t c5;
		c5.x = 6;
		c5.y = 0;

		coordinate_t c6;
		c6.x = 2;
		c6.y = 7;

		coordinate_t c7;
		c7.x = 7;
		c7.y = 7;

		logicalCoordinates2[0] = c4;
		logicalCoordinates2[1] = c5;
		logicalCoordinates2[2] = c6;
		logicalCoordinates2[3] = c7;

		coordinate_t *visualCoordinates2;
		visualCoordinates2 = camera.createVisualCoordinatesBlack(logicalCoordinates2, 4);

		printf("Black: \n");
		for (int i = 0; i != 4; ++i) {
			std::cout << visualCoordinates2[i].x << ", " << visualCoordinates2[i].y << std::endl;
		}
		printf("\n\n");

		//uppgift 3
		camera.scale(32, 24);
		coordinate_t *visualCoordinates3;
		coordinate_t *visualCoordinates4;

		visualCoordinates3 = camera.createVisualCoordinatesWhite(logicalCoordinates1, 4);
		visualCoordinates4 = camera.createVisualCoordinatesBlack(logicalCoordinates2, 4);

		printf("Scaled\nWhite: \n");
		for (int i = 0; i != 4; ++i) {
			std::cout << visualCoordinates3[i].x << ", " << visualCoordinates3[i].y << std::endl;
		}
		printf("\n\n");

		printf("Scaled\nBlack: \n");
		for (int i = 0; i != 4; ++i) {
			std::cout << visualCoordinates4[i].x << ", " << visualCoordinates4[i].y << std::endl;
		}
		printf("\n\n");

		running = 0;
	}

	system("pause");
	return 0;
}