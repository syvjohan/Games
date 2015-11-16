#include "BoarderView.h"

BoarderView::BoarderView() {}

BoarderView::~BoarderView() {}

//Update the screen surface.
void BoarderView::renderBorder(SDL_Surface *surf, const SDL_Rect &area, int borderWidth /*int borderWidth = 2*/) {
	SDL_Rect outer = area;
	outer.x -= borderWidth;
	outer.y -= borderWidth;
	outer.w += borderWidth * 2; //need both multiplier otherwise bord will only be on left and upper side.
	outer.h += borderWidth * 2; //need both multiplier otherwise bord will only be on left and upper side.

	const Uint32 BORDER_COLOR = 0xFFFFFF;
	const Uint32 AREA_COLOR = 0x000000;

	SDL_FillRect(surf, &outer, BORDER_COLOR); //x = 38 y = 38 h = 724 w = 724.
	SDL_FillRect(surf, &area, AREA_COLOR);
}

//Calculate new size for play area (area inside border).
SDL_Rect BoarderView::getPlayArea(SDL_Window *window, int borderW, int borderH) {
	SDL_Rect result;
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	result.x = borderW;
	result.y = borderH;
	result.w = w - borderW *2;
	result.h = h - borderH * 2;
	return result;
}