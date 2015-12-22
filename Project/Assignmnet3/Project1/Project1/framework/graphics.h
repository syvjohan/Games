#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "gamemath.h"

class Common;
class Effect;
class Renderer2D;
class Texture2D;
class RenderText;
class RenderFont;

// ******
// class Graphics
// ******
class Graphics {
public:
    friend class Common;
    static const int MAX_TEXTURE_SLOT = 8;
    
    ~Graphics();

    void clear(const Vec4 &color, bool depth);

    void present();

    // Wrappers around context methods
    void setViewport(float left, float top, float right, float bottom);
    
    // Create a shader program
    bool createProgram(const char *vsPath, const char *fsPath, int *outProgram);
    bool createProgramFromSource(const char *vSource, const char *fSource, int *outProgram);

    void getContextSize(int *x, int *y) const;

    // Factory methods for OpenGL objects
    Renderer2D* createRenderer2D();
    Texture2D*  createTexture2D();
    Texture2D*  loadTextureFromFile(const char *path);
    
    // Textures
    Texture2D* getBoundTexture(int slot);
    Texture2D* bindTexture(Texture2D* texture, int slot = 0);  // Returns previously bound texture

    // Text
    RenderText* createRenderText(RenderFont *font, const char *txt = 0);
    
private:
    explicit Graphics(Common *common);
    
    Common *mCommon;

    Texture2D *mTextureSlots[MAX_TEXTURE_SLOT];
};




#endif // !GRAPHICS_H
