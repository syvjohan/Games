#ifndef HIRESTIMER_H
#define HIRESTIMER_H

#include "frameworkdefs.h"


class HiResTimer {
public:
    HiResTimer();

    void restart();
    
    // Updates the timer
    void tick();

    float getDeltaMillis() const;
    float getDeltaSeconds() const;
    float getDeltaMinutes() const;
    float getDeltaHours() const;

    float getTotalMillis() const;
    float getTotalSeconds() const;
    float getTotalMinutes() const;
    float getTotalHours() const;
    
private:
    u64 mTick;
    u64 mLastTick;
    u64 mFrequency;
    u64 mStartTick;
};

inline float HiResTimer::getDeltaMillis() const {
    return ((float)(mTick - mLastTick) / (float)mFrequency) * 1000.0f;
}

inline float HiResTimer::getDeltaSeconds() const {
    return ((float)(mTick - mLastTick) / (float)mFrequency);
}

inline float HiResTimer::getDeltaMinutes() const {
    return ((float)(mTick - mLastTick) / (float)mFrequency) / 60.0f;
}

inline float HiResTimer::getDeltaHours() const {
    return ((float)(mTick - mLastTick) / (float)mFrequency) / 3600.0f;
}

inline float HiResTimer::getTotalMillis() const {
    return ((float)(mTick - mStartTick) / (float)mFrequency) * 1000.0f;
}

inline float HiResTimer::getTotalSeconds() const {
    return ((float)(mTick - mStartTick) / (float)mFrequency);
}

inline float HiResTimer::getTotalMinutes() const {
    return ((float)(mTick - mStartTick) / (float)mFrequency) / 60.0f;
}

inline float HiResTimer::getTotalHours() const {
    return ((float)(mTick - mStartTick) / (float)mFrequency) / 3600.0f;
}


#endif // !HIRESTIMER_H
