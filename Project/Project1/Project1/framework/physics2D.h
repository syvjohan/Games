#ifndef FRAMEWORK_PHYSICS2D_H
#define FRAMEWORK_PHYSICS2D_H

#include "gamemath.h"
#include <vector>

struct BoundingBox {
    Vec2         mCenter;
    Vec2         mExtents;
    Entity      *mEntity;
};

class ICollisionListener {
public:
    virtual ~ICollisionListener() {}

    virtual bool onCollision(BoundingBox *a, BoundingBox *b) = 0;
};

class Physics2D {
public:
    Physics2D();
    ~Physics2D();

    void add(BoundingBox *box);
    void remove(BoundingBox *box);

    void addListener(ICollisionListener *);
    void removeListener(ICollisionListener *);
    
    void frame(float deltaSeconds);
    
    Physics2D(const Physics2D &) = delete;
    const Physics2D& operator=(const Physics2D &) = delete;
private:
    bool exists(BoundingBox *) const;
    
    std::vector<BoundingBox*> mBoxes;
    std::vector<ICollisionListener*> mListeners;
};

#endif // ! FRAMEWORK_PHYSICS2D_H

