#pragma once

#include <SDL.h>

class BoarderView {
	public:
	BoarderView();
	~BoarderView();

	void renderBorder(SDL_Surface *surf, const SDL_Rect &area, int borderWidth = 2);
	SDL_Rect getPlayArea(SDL_Window *window, int borderW, int borderH);

};