#pragma once

#include "Camera.h"

#include <SDL.h>

class BoarderView {
	public:
	BoarderView();
	~BoarderView();

	void setScale(float size);
	float getScale();

	void renderBorder(SDL_Surface *surf, const SDL_Rect &area, int borderWidth = 2);
	SDL_Rect getPlayArea(SDL_Window *window, int borderSize);

	private:
	Camera *camera;
};