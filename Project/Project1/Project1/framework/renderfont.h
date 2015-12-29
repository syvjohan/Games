#ifndef RENDERFONT_H
#define RENDERFONT_H

#include "frameworkdefs.h"

class Common;
class RenderText;

struct _FontData;


class RenderFont {
public:
    friend class Common;
    friend class RenderText;

    ~RenderFont();

    s32 getSize() const;
    
    RenderFont(const RenderFont &)  = delete;
    RenderFont(const RenderFont &&) = delete;
    const RenderFont& operator      = (const RenderFont &) = delete;
    const RenderFont& operator      = (const RenderFont &&) = delete;
private:
    RenderFont(void *font);

    void *mTTF;
    s32   mSize;
};

inline s32 RenderFont::getSize() const {
    return mSize;
}

#endif // !RENDERFONT_H
