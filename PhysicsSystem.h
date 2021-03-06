//
// Created by martin on 30.11.17.
//

#ifndef PROJECT_PHYSICSBEHAVIOUR_H
#define PROJECT_PHYSICSBEHAVIOUR_H


#include <entityx/System.h>
#include <memory>
#include <btBulletCollisionCommon.h>
#include <BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h>
#include <BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>
#include "RigidBodyComponent.h"

class PhysicsSystem: public entityx::System<PhysicsSystem>, public entityx::Receiver<PhysicsSystem> {
    // TODO: Tohle by asi chtělo zabalit do nějákého konfiguračního objektu
    std::unique_ptr<btBroadphaseInterface> m_broadphase;
    std::unique_ptr<btDefaultCollisionConfiguration> m_collisionConfiguration;
    std::unique_ptr<btCollisionDispatcher> m_collisionDispatcher;
    std::unique_ptr<btSequentialImpulseConstraintSolver> m_impulseSolver;
    std::shared_ptr<btDiscreteDynamicsWorld> m_world;

public:
    void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override;

    void configure(entityx::EntityManager &entities, entityx::EventManager &events) override;

    void receive(const entityx::ComponentAddedEvent<RigidBody>& event);
    void receive(const entityx::ComponentRemovedEvent<RigidBody>& event);
    std::shared_ptr<btDynamicsWorld> getWorld() const {
        return m_world;
    }
};


#endif //PROJECT_PHYSICSBEHAVIOUR_H
