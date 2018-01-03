//
// Created by martin on 1.12.17.
//

#include "PlayerMotionSystem.h"
#include "Engine/Camera.h"
#include "RigidBodyComponent.h"
#include "LookingDirection.h"
#include <glm/gtx/rotate_vector.hpp>
#include <iostream>

void PlayerMotionSystem::update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) {
    entities.each<LookingDirection, RigidBody, CameraComponent>([&](entityx::Entity entity,
                                                               LookingDirection& state,
                                                               RigidBody& body,
                                                               CameraComponent& fpsCamera) {
        state.pitch += 5.0 * m_mouseDelta.y * dt;
        state.yaw -= 10.0 * m_mouseDelta.x * dt;
        if(state.pitch > 180) {
            state.pitch = 180;
        } else if(state.pitch < -180) {
            state.pitch = -180;
        }
        if(abs(state.yaw) > 360) {
            if(state.yaw > 0) {
                state.yaw -= 360;
            } else {
                state.yaw += 360;
            }
        }
        btTransform trans;
        body.rigidBody->getMotionState()->getWorldTransform(trans);
        fpsCamera.setPosition(glm::vec3(
                trans.getOrigin().x(),
                trans.getOrigin().y(),
                trans.getOrigin().z()
        ));
        auto dirVector = glm::rotateX(glm::rotateY(glm::vec3(0, 0, 100),
                                                   glm::radians(state.yaw)),
                                      glm::radians(state.pitch));
        dirVector /= dirVector.length();
        fpsCamera.setDirection(fpsCamera.getPosition() + dirVector);
        if(!m_forwardPressed && !m_backwardPressed) body.rigidBody->clearForces();
        if(m_forwardPressed) {
            auto btDirVector = btVector3(dirVector.x, 0, dirVector.z).normalize();
            body.rigidBody->applyCentralImpulse(btDirVector * 10.5f);
        }
        if(m_backwardPressed) {
            auto btDirVector = btVector3(dirVector.x, 0, dirVector.z).normalize();
            body.rigidBody->applyCentralImpulse(btDirVector * -10.5f);
        }
        if(!m_backwardPressed && !m_forwardPressed) {
            body.rigidBody->applyCentralImpulse(-body.rigidBody->getLinearVelocity());
        }
    });
}

void PlayerMotionSystem::receive(const SDLEvent &event) {
    if(event.event.type == SDL_KEYDOWN) {
        if(event.event.key.keysym.sym == SDLK_UP){
            m_forwardPressed = true;
        }
        if(event.event.key.keysym.sym == SDLK_DOWN) {
            m_backwardPressed = true;
        }
    } else if(event.event.type == SDL_KEYUP) {
        if(event.event.key.keysym.sym == SDLK_UP){
            m_forwardPressed = false;
        }
        if(event.event.key.keysym.sym == SDLK_DOWN) {
            m_backwardPressed = false;
        }
    }
    if(event.event.type == SDL_MOUSEMOTION) {
        m_mouseDelta.x = event.event.motion.xrel;
        if(abs(event.event.motion.xrel) <= 5) m_mouseDelta.x = 0;
        m_mouseDelta.y = event.event.motion.yrel;
        if(abs(event.event.motion.yrel) <= 5) m_mouseDelta.y = 0;
    }
}

void PlayerMotionSystem::configure(entityx::EventManager &events) {
    events.subscribe<SDLEvent>(*this);
}
