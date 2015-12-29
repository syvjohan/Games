#ifndef RENDERTEXT_H
#define RENDERTEXT_H

#include "frameworkdefs.h"

class Graphics;
class RenderFont;
class Texture2D;

class RenderText {
public:
    friend class Graphics;
    ~RenderText();

    void        setText(const char *text);
    void        setFont(RenderFont *font);
    
    const char* getText()    const;
    u32         getLength()  const;
    Texture2D*  getTexture() const;
    RenderFont* getFont()    const;
    
private:
    RenderText(Graphics *graphics, RenderFont *font);
    void updateTexture();
    
    Graphics   *mGraphics;
    RenderFont *mFont;
    char       *mData;
    u32         mLength;
    Texture2D*  mTexture;
};

inline const char *RenderText::getText() const {
    return mData;
}

inline u32 RenderText::getLength() const {
    return mLength;
}

inline Texture2D* RenderText::getTexture() const {
    return mTexture;
}

inline RenderFont* RenderText::getFont() const {
    return mFont;
}

#endif // !RENDERTEXT_H
