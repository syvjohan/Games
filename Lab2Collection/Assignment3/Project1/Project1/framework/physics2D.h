#ifndef FRAMEWORK_PHYSICS2D_H
#define FRAMEWORK_PHYSICS2D_H

#include "gamemath.h"
#include <vector>

struct CollisionData {
    float       mPenetration;
    Vec2        mNormal;

    Entity *mEntityA;
    Entity *mEntityB;
};

enum ColliderType {
    COLLIDER_NONE = 0,
    COLLIDER_AABB,
    COLLIDER_CIRCLE,
    COLLIDER_OBB
};

// Represents physics data for an entity.
struct PhysicsData {
    Vec2 mPosition;
    Vec2 mVelocity;
    Vec2 mAcceleration;
    
    Entity *mEntity;
    
    ColliderType mType;
    
    union {
        struct {
            Vec2 mExtents;
        } mAABB;
        
        struct {
            float mRadius;
        } mCircle;

        struct {
            Vec2 mExtents;
            float mAngle;
        } mOBB;
        
    } mCollider;
};

class ICollisionCallback {
public:
    virtual ~ICollisionCallback() {}

    virtual bool onCollision(const CollisionData &) = 0;
};

class Physics2D {
public:
    Physics2D();
    ~Physics2D();

    void createPhysicsData(Entity *e, ColliderType type, PhysicsData *out);
    void removePhysicsData(PhysicsData *physics);
    void addListener(ICollisionCallback *callback);
    void removeListener(ICollisionCallback *callback);

    void frame(float dt);
    
    // No Copying
    Physics2D(const Physics2D &) = delete;
    const Physics2D& operator=(const Physics2D &) = delete;
private:
    std::vector<PhysicsData *>        mObjects;
    std::vector<ICollisionCallback *> mCallbacks;
};

#endif // ! FRAMEWORK_PHYSICS2D_H

