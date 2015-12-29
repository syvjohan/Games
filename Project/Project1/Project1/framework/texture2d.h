#ifndef TEXTURE2D_H
#define TEXTURE2D_H
#include "frameworkdefs.h"

#define MAX_TEXTURE_SLOTS 8

class Graphics;

enum TextureFilterMode {
    TEXTURE_FILTER_NEAREST = 0,
    TEXTURE_FILTER_LINEAR,
    TEXTURE_FILTER_ANISOTROPIC,
};

enum TextureMapMode {
    TEXTURE_MAP_WRAP,
    TEXTURE_MAP_CLAMP,
};

class Texture2D {
public:
    friend class Graphics;
    ~Texture2D();

    void getFilterMode(TextureFilterMode *min, TextureFilterMode *mag);
    void getMapMode(TextureMapMode *mapU, TextureMapMode *mapV);
    
    void setFilterMode(TextureFilterMode minFilter, TextureFilterMode magFilter);
    void setMapMode(TextureMapMode mapU, TextureMapMode mapV);

    void getDimensions(s32 *width, s32 *height);

    // Data is required to be in RGBA 32bit format.
    void setData(u8 *data, s32 width, s32 height);
   
private:
    Texture2D(Graphics *graphics);

    Graphics          *mGraphics;
    u32                mHandle;
    TextureMapMode     mMapModeU;
    TextureMapMode     mMapModeV;
    TextureFilterMode  mFilterMin;
    TextureFilterMode  mFilterMag;
    s32                mWidth;
    s32                mHeight;
};

#endif // !TEXTURE2D_H
