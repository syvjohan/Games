#ifndef COMMON_H
#define COMMON_H

#include "frameworkdefs.h"
#include "hirestimer.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <unordered_map>
#include <cassert>

class IEventProcessor;
class Graphics;
class RenderFont;
class Audio;
class Texture2D;
class Sound;

enum Button {
    BUTTON_NONE = 0,
    
    // MouseButtons
    BUTTON_MOUSELEFT,
    BUTTON_MOUSERIGHT,
    BUTTON_MOUSEMIDDLE,
    BUTTON_MOUSEX1,
    BUTTON_MOUSEX2,
    BUTTON_MOUSEWHEELUP,
    BUTTON_MOUSEWHEELDOWN,
    
    BUTTON_ESCAPE,

    // Function Keys
    BUTTON_F1,
    BUTTON_F2,
    BUTTON_F3,
    BUTTON_F4,
    BUTTON_F5,
    BUTTON_F6,
    BUTTON_F7,
    BUTTON_F8,
    BUTTON_F9,
    BUTTON_F10,
    BUTTON_F11,
    BUTTON_F12,

    BUTTON_PRINTSCREEN,
    BUTTON_SCROLLLOCK,
    BUTTON_PAUSE,

    // NOTE: Sometimes called tilde, 1/2(half) or grave accent.
    BUTTON_BACKQUOTE,

    // Number Keys
    BUTTON_0,
    BUTTON_1,
    BUTTON_2,
    BUTTON_3,
    BUTTON_4,
    BUTTON_5,
    BUTTON_6,
    BUTTON_7,
    BUTTON_8,
    BUTTON_9,

    BUTTON_MINUS,
    BUTTON_EQUALS,
    BUTTON_BACKSPACE,

    // Numpad
    BUTTON_NUMLOCK,
    BUTTON_NUMPAD_DIVIDE,
    BUTTON_NUMPAD_MULTIPLY,
    BUTTON_NUMPAD_MINUS,
    BUTTON_NUMPAD_7,
    BUTTON_NUMPAD_8,
    BUTTON_NUMPAD_9,
    BUTTON_NUMPAD_4,
    BUTTON_NUMPAD_5,
    BUTTON_NUMPAD_6,
    BUTTON_NUMPAD_1,
    BUTTON_NUMPAD_2,
    BUTTON_NUMPAD_3,
    BUTTON_NUMPAD_0,
    BUTTON_NUMPAD_PERIOD,
    BUTTON_NUMPAD_ENTER,

    // Home Cluster
    BUTTON_INSERT,
    BUTTON_HOME,
    BUTTON_PAGEUP,
    BUTTON_DELETE,
    BUTTON_END,
    BUTTON_PAGEDOWN,

    BUTTON_TAB,

    // First row alphabet
    BUTTON_Q,
    BUTTON_W,
    BUTTON_E,
    BUTTON_R,
    BUTTON_T,
    BUTTON_Y,
    BUTTON_U,
    BUTTON_I,
    BUTTON_O,
    BUTTON_P,

    BUTTON_CAPSLOCK,

    // Second row alphabet
    BUTTON_A,
    BUTTON_S,
    BUTTON_D,
    BUTTON_F,
    BUTTON_G,
    BUTTON_H,
    BUTTON_J,
    BUTTON_K,
    BUTTON_L,

    BUTTON_LSHIFT,
    BUTTON_BACKSLASH,

    // Third row of alphabet
    BUTTON_Z,
    BUTTON_X,
    BUTTON_C,
    BUTTON_V,
    BUTTON_B,
    BUTTON_N,
    BUTTON_M,

    BUTTON_COMMA,
    BUTTON_PERIOD,
    BUTTON_SLASH,
    BUTTON_RSHIFT,

    BUTTON_LCTRL,
    BUTTON_APPLICATION,
    BUTTON_LALT,
    BUTTON_SPACE,
    BUTTON_RALT,
    // NOTE: Right windows key should be here, not sure what it's called.
    // NOTE: Function key should be here, but not sure if SDL lists it.
    BUTTON_RCTRL,

    // Arrow Keys
    BUTTON_UP,
    BUTTON_DOWN,
    BUTTON_LEFT,
    BUTTON_RIGHT,

    BUTTON_MAX_COUNT,
};

struct WindowParams {
    int mWidth;
    int mHeight;
    int mPosX;
    int mPosY;
    bool mFullscreen;
    const char *mTitle;
};

struct InputState {
    static const int MAX_BUTTONS = 255;

    inline InputState() { memset(this, 0, sizeof(*this)); }
    
    bool mButtons[MAX_BUTTONS];

    int mMouseX;
    int mMouseY;
    int mMouseDeltaX;
    int mMouseDeltaY;
    int mWheelDelta;

    inline bool isDown(Button button) const {
        return mButtons[(int)button];
    }

    inline bool isUp(Button button) const {
        return !isDown(button);
    }

    inline bool wasPressed(const InputState &state, Button button) const {
        return isDown(button) && state.isUp(button);
    }

    inline bool wasReleased(const InputState &state, Button button) const {
        return isUp(button) && state.isDown(button);
    }
};

enum ResourceType {
    RESOURCE_NONE = 0,
    RESOURCE_TEXTURE = 1,
    RESOURCE_SOUND = 2,
    RESOURCE_FONT = 3
};

// Initializes common systems, opens gamewindow.
class Common {
public:
    Common();
    ~Common();

    // Called once on application startup to initialize SDL
    bool init(const WindowParams &wParams);

    // Called once per frame to process all OS events.
    // Also does bookkeeping of resources etc.
    void frame();
    
    void setEventProcessor(IEventProcessor*);

    // Retrieve managed singletons representing graphics and audio devices.
    Graphics *getGraphics();
    Audio *getAudio();

    // Windowing
    void setWindowDimensions(int width, int height);
    void getWindowDimensions(int *width, int *height) const;
    void swapWindowBuffers();

    // Fonts
    RenderFont* createRenderFont(const char *path, s32 size);

    // Resources
    void registerTextureResource(const std::string &name, const std::string &path);
    void registerFontResource(const std::string &name, int size, const std::string &path);
    void registerSoundResource(const std::string &name, const std::string &path);
    void registerSoundResource(const std::string &name, Sound *sound);
    //void registerMusicResource(const std::string &name, const std::string &path);
    
    Texture2D* getTextureResource(const std::string &name);
    RenderFont* getFontResource(const std::string &name);
    Sound* getSoundResource(const std::string &name);
    //Music* getMusicResource(const std::string &name);
    
    // IO methods, mainly for testing
    u8*  ioReadEntireFile(const std::string &path, usize *length); // delete[] after use.
    bool ioWriteFile(const std::string &path, void *data, usize size, bool append = false);

    // Input
    void getInputState(InputState *state) const;
    const char* getButtonName(Button button) const;
    
    
private:
    struct Resource {
        ResourceType mType;
        void *mData;
        float mStamp;
    };
    
    typedef std::unordered_map<std::string, Resource> ResourceMap;
    
    SDL_Window          *mWindow;
    SDL_GLContext        mContext;
    IEventProcessor     *mEventProcessor;
    Graphics            *mGraphics;
    ResourceMap          mResources;
    HiResTimer           mTimer;
    Audio               *mAudio;
    InputState           mCurrentInputState;
    InputState           mPreviousInputState;
};

inline void Common::getInputState(InputState *state) const {
    *state = mCurrentInputState;
}

inline void Common::getWindowDimensions(int *w, int *h) const {
    SDL_GetWindowSize(mWindow, w, h);
}

#endif // COMMON_H
