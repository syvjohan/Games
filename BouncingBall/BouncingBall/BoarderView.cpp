#include "BoarderView.h"

BoarderView::BoarderView() {
	camera = new Camera();
}

BoarderView::~BoarderView() {}

void BoarderView::renderBorder(SDL_Surface *surf, const SDL_Rect &area, int borderWidth /*int borderWidth = 2*/) {
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

SDL_Rect BoarderView::getPlayArea(SDL_Window *window, int borderSize) {
	SDL_Rect result;
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	result.x = borderSize;
	result.y = borderSize;
	result.w = w - borderSize * 2;
	result.h = h - borderSize * 2;
	return result;
}

void BoarderView::setScale(float size) {
	camera->setScale(size);
}

float BoarderView::getScale() {
	return camera->getScale();
}