#ifndef FRAMEWORK_AUDIO_H
#define FRAMEWORK_AUDIO_H

#include "frameworkdefs.h"
#include "gamemath.h"
#include <vector>

class Common;

class AudioSource;
class Audio;
class Sound;
class Music;

// Used to play sounds and music in the world.
class AudioSource {
public:
    friend class Audio;

    void play(const Sound *sound);
    void play(const Music *music);
    void stop();
    
    void setPosition(const Vec3 &pos);
    void setVelocity(const Vec3 &vel);
    void setVolume(float v);
    void setPitch(float v);
    void setLooping(bool value);

    // Figure out if this source is busy.
    bool isPlaying() const;
    
private:
    AudioSource(u32 source);
    ~AudioSource();
    
    Audio       *mAudio;
    Vec3         mPosition;
    Vec3         mVelocity;
    float        mVolume;
    float        mPitch;
    bool         mLooping;
    u32          mSource;
};


// Intended for short sound effects.
class Sound {
public:
    friend class Common;
    friend class AudioSource;
    friend class Audio;
    
    int numChannels();
    int rate();
    
    // No copying
    Sound(const Sound &) = delete;
    const Sound& operator=(const Sound &) = delete;
private:
    Sound(u32 buffer, u32 format, u32 channels, u32 rate);
    ~Sound();
    
    u32 mBuffer;
    u32 mFormat;
    u32 mChannels;
    u32 mRate;
};

// Streaming music
class Music {
public:
    friend class Audio;
    
private:
    Music();
    ~Music();
    
};

class Audio {
public:
    friend class Common;

    // Returns any available source (null if none exist).
    AudioSource *getSource();

    // Listener configuration.
    void setListenerPosition(const Vec3 &position);
    void setListenerVelocity(const Vec3 &velocity);
    Vec3 getListenerPosition() const;
    Vec3 getListenerVelocity() const;

    Sound* loadSoundFromFile(const char *path); // Use for small sounds, like effects.
    Music* loadMusicFromFile(const char *path); // Use for longer sounds, like music.

    // Load parts of a sound from disk, return value is a vector containing each sprite.
    std::vector<Sound*> loadSoundSpritesFromFile(const char *path,
                                                 int *marks, int markPairCount);
    
    // No Copy
    Audio(const Audio &) = delete;
    const Audio& operator=(const Audio &) = delete;
private:
    
    struct SampleData {
        u8      *mSamples;
        usize    mSize;
        u32      mFormat;
        int      mRate;
        int      mChannels;
        int      mBitsPerChannel;
    };

    Audio(Common *common);
    ~Audio();

    // NOTE: This should be enough and works pretty much everywhere.
    static const int MAX_SOURCES = 16;
    
    bool init(); // Called once to initialize the OpenAL context
    bool decodeOgg(const char *path, SampleData *out);
    bool createSources();
    
    Common *mCommon;

    std::vector<AudioSource *> mSources;
};

inline AudioSource *Audio::getSource() {
    for (AudioSource *src : mSources) {
        if (src->isPlaying() == false) {
            return src;
        }
    }

    return NULL;
}

#endif // !FRAMEWORK_AUDIO_H
