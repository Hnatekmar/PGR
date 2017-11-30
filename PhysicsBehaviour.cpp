//
// Created by martin on 30.11.17.
//

#include "PhysicsBehaviour.h"

void PhysicsBehaviour::update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) {
    assert(m_world != nullptr);
    m_world->stepSimulation(dt, 10);
}

void PhysicsBehaviour::configure(entityx::EntityManager &entities, entityx::EventManager &events) {
    entityx::BaseSystem::configure(entities, events);
    m_broadphase = std::make_unique<btDbvtBroadphase>();
    m_collisionConfiguration = std::make_unique<btDefaultCollisionConfiguration>();
    m_collisionDispatcher = std::make_unique<btCollisionDispatcher>(m_collisionConfiguration.get());
    m_impulseSolver = std::make_unique<btSequentialImpulseConstraintSolver>();
    m_world = std::make_unique<btDiscreteDynamicsWorld>(
            m_collisionDispatcher.get(),
            m_broadphase.get(),
            m_impulseSolver.get(),
            m_collisionConfiguration.get()
    );
    m_world->setGravity(btVector3(0, -9.807f, 0));
}
