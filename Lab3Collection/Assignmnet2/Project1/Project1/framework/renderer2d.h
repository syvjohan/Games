#ifndef RENDERER2D_H
#define RENDERER2D_H

#include "gamemath.h"
#include "frameworkdefs.h"
#include "glinclude.h"
#include "stb_image.h"
#include <cassert>

class Graphics;
class Texture2D;

struct RectangleF {
    float x;
    float y;
    float w;
    float h;
};

class Renderer2D {
public:
    friend class Graphics;

    enum SortMode {
        SPRITE_SORT_IMMEDIATE = 0,
        SPRITE_SORT_DEFERRED = 1,
        SPRITE_SORT_TEXTURE = 2,
        SPRITE_SORT_LAYER = 3,
    };

    enum BlendMode {
        SPRITE_BLEND_OPAQUE = 0,
        SPRITE_BLEND_ALPHA = 1,
        SPRITE_BLEND_ADDITIVE = 2,
    };
    
    ~Renderer2D();

    bool init();
    
    // Called to begin drawing a frame.
    void begin(SortMode sortMode = SPRITE_SORT_DEFERRED, BlendMode blendMode = SPRITE_BLEND_OPAQUE);

    // Called to end the current frame.
    void end();

    void draw(Texture2D *texture, const Vec2 &pos, const RectangleF &clip,
              const Vec2 &origin, float rotation, const Vec2 &scale,
              const Vec4 &tint, float layer);

    void debugLine(float x0, float y0, float x1, float y1, const Vec4 &tint);
    void debugRect(float minX, float minY, float maxX, float maxY, const Vec4 &tint);
    void debugRect(const Vec2 &center, const Vec2 &extents, const Vec4 &tint);
    void debugAxis(float x, float y, float angle);
    
private:
    Renderer2D(Graphics *graphics);

    static const u32 SPRITE_BATCH_SIZE = 2048;
    
    struct SpriteData {
        Vec2 mPosition;
        Texture2D* mTexture; // TODO: Implement textures

        RectangleF mClip;
        Vec2 mOrigin;
        Vec2 mScale;
        float mRotation;
        Vec4 mTint;
        float mLayer;
    };

    struct Batch {
        SpriteData mSprites[SPRITE_BATCH_SIZE];
        u32 mSpriteCount;
    };

    void renderBatch(Batch *batch);
    void flushBatch(Batch *batch);
    
    Batch mCurrentBatch;
    SortMode mCurrentSortMode;
    BlendMode mCurrentBlendMode;

    // OpenGL resources
    u32 mVertexArray;
    u32 mVertexBuffer;
    u32 mIndexBuffer;
    s32 mSpriteProgram;
    s32 mUniformProjection;
    s32 mUniformTexture;

    Graphics *mGraphics;

    // Texture used internally for debug rendering
    Texture2D *mPixelTexture;
};

#endif // !RENDERER2D_H
