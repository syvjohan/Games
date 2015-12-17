#ifndef EVENTPROCESSOR_H
#define EVENTPROCESSOR_H

class IEventProcessor {
public:
    virtual ~IEventProcessor() {}

    // Mouse input
    virtual void onMouseMove(int relativeX, int relativeY, int absoluteX, int absoluteY) {}
    virtual void onMouseButtonDown(int x, int y, int button) {}
    virtual void onMouseButtonUp(int x, int y, int button) {}

    // Keyboard input
    virtual void onKeyDown(int key) {}
    virtual void onKeyUp(int key) {}

    // Window events
    virtual void onWindowClose() {}
    virtual void onWindowMove() {}
    virtual void onWindowFocusGained() {}
    virtual void onWindowFocusLost() {}
};

#endif // !EVENTPROCESSOR_H
