#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>

typedef struct coordinate_s {
	int x;
	int y;
}coordinate_t;

class Camera {
public:
	Camera();
	~Camera();

	coordinate_t* createVisualCoordinatesWhite(const coordinate_t *logicalCoordinates, const int len);
	coordinate_t* createVisualCoordinatesBlack(const coordinate_t *logicalCoordinates, const int len);
	void scale(int sizeX, int sizeY);

private:
	int sizeOfTileX;
	int sizeofTileY;
	int borderSizeX;
	int borderSizeY;

	int borderSizeBlackX;
	int borderSizeBlackY;

	coordinate_t *visualCoordinates;
};

#endif //!CAMERA_H