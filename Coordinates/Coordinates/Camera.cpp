#include "Camera.h"

Camera::Camera() {
	sizeOfTileX = 64;
	sizeofTileY = 64;
	borderSizeX = 64;
	borderSizeY = 64;

	borderSizeBlackX = 64 * 8;
	borderSizeBlackY = 64 * 8;
}

Camera::~Camera() {
	if (visualCoordinates != NULL) {
		delete[]visualCoordinates;
	}
}

coordinate_t* Camera::createVisualCoordinatesWhite(const coordinate_t *logicalCoordinates, const int len) {
	visualCoordinates = new coordinate_t[len];

	for (int i = 0; i != len; ++i) {
		visualCoordinates[i].x = borderSizeX + logicalCoordinates[i].x * sizeOfTileX;
		visualCoordinates[i].y = borderSizeY + logicalCoordinates[i].y * sizeofTileY;
	}

	return visualCoordinates;
}

coordinate_t* Camera::createVisualCoordinatesBlack(const coordinate_t *logicalCoordinates, const int len) {
	visualCoordinates = new coordinate_t[len];

	for (int i = 0; i != len; ++i) {
		visualCoordinates[i].x = borderSizeBlackX - logicalCoordinates[i].x * sizeOfTileX;
		visualCoordinates[i].y = borderSizeBlackY - logicalCoordinates[i].y * sizeofTileY;
	}

	return visualCoordinates;
}

void Camera::scale(int sizeX, int sizeY) {
	borderSizeX = sizeX;
	borderSizeY = sizeY;

	sizeOfTileX = sizeX;
	sizeofTileY = sizeY;

	borderSizeBlackX = sizeX * 8;
	borderSizeBlackY = sizeY * 8;
}