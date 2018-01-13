//
// Created by martin on 30.11.17.
//

#ifndef PROJECT_RIGIDBODYCOMPONENT_H
#define PROJECT_RIGIDBODYCOMPONENT_H

#include <memory>
#include <BulletCollision/CollisionShapes/btCollisionShape.h>
#include <LinearMath/btDefaultMotionState.h>
#include <BulletDynamics/Dynamics/btRigidBody.h>

struct RigidBody {
    std::shared_ptr<btCollisionShape> collisionShape;
    std::shared_ptr<btDefaultMotionState> motionState;
    std::shared_ptr<btRigidBody> rigidBody;
    bool copyRotation = true;
    RigidBody(btQuaternion orientation, btVector3 centerOfMass, std::shared_ptr<btCollisionShape> shape, btScalar mass, btVector3 inertia) {
        assert(shape != nullptr);
        collisionShape = shape;
        motionState = std::make_shared<btDefaultMotionState>(btTransform(orientation, centerOfMass));
        btRigidBody::btRigidBodyConstructionInfo info(mass, motionState.get(), collisionShape.get(), inertia);
        rigidBody = std::make_shared<btRigidBody>(info);
    }
};

#endif //PROJECT_RIGIDBODYCOMPONENT_H
