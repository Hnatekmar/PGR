//
// Created by martin on 30.11.17.
//

#include "PhysicsBehaviour.h"
#include "Engine/GraphicsComponent.h"
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>

void PhysicsBehaviour::update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) {
    assert(m_world != nullptr);
    entities.each<RigidBody, GraphicsComponent>([](entityx::Entity entity, RigidBody& body, GraphicsComponent& graphics) {
        btTransform trans;
        body.rigidBody->getMotionState()->getWorldTransform(trans);
        graphics.position.x = trans.getOrigin().x();
        graphics.position.y = trans.getOrigin().y();
        graphics.position.z = trans.getOrigin().z();
        auto quaternion = glm::quat(trans.getRotation().w(), trans.getRotation().x(), trans.getRotation().y(), trans.getRotation().z());
        graphics.angleVec = glm::axis(quaternion);
        graphics.angle = glm::angle(quaternion);
    });
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
    events.subscribe<entityx::ComponentAddedEvent<RigidBody>>(*this);
}

void PhysicsBehaviour::receive(const entityx::ComponentAddedEvent<RigidBody> &event) {
    m_world->addRigidBody(event.component->rigidBody.get());
}
