#ifndef FRAMEWORK_ANIMATOR2D_H
#define FRAMEWORK_ANIMATOR2D_H

#include <vector>
#include <unordered_map>

class Texture2D;

class IAnimationCallback2D {
public:
    virtual ~IAnimationCallback2D() {}

    virtual void onAnimationDone(const Animation &) {};
    virtual void onAnimationStart(const Animation &) {};
};

struct AnimationFrame {
    int x;
    int y;
    int w;
    int h;
};

class Animation {
public:
    AnimationFrame mCurrentFrame;
    
    Animation();
    ~Animation();

    void setFrameSize(int w, int h);
    void addFrame(int x, int y);
    
    void setTimePerFrame(float ms);

    void update(float timeMs);
    
private:
    std::vector<AnimationFrame>  mFrames;
    float                        mFrameTimerMs;
    float                        mTimePerFrameMs;
    Texture2D                   *mTexture;
    AnimationFrame              *mCurrentFrame;
    int                          mFrameWidth;
    int                          mFrameHeight;
};


class Animator2D {
public:
    Animator2D();
    ~Animator2D();

    void addCallback(IAnimationCallback2D *callback);

    void addAnimation(const std::string &name, const Animation &a);

    void play(const std::string &name);
    void pause();
    void stop();

    void update(float dt);

    // Retrieve current animation data.
    AnimationFrame*     getCurrentFrame();
    Texture2D*          getCurrentTexture();
    
private:
    std::unordered_map<std::string, Animation> mAnimations;
    std::vector<IAnimationCallback2D*> mCallbacks;

    Animation *mCurrentAnimation;
};

#endif // !FRAMEWORK_ANIMATOR2D_H
