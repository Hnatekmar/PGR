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
        if(m_leftPressed) {
            state.yaw += 50 * dt;
        }
        if(m_rightPressed) {
            state.yaw -= 50 * dt;
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
        fpsCamera.setDirection(fpsCamera.getPosition() + dirVector);
        if(!m_forwardPressed && !m_backwardPressed) body.rigidBody->clearForces();
        if(m_forwardPressed) {
            auto btDirVector = btVector3(dirVector.x, 0, dirVector.z).normalize();
            body.rigidBody->setLinearVelocity(btDirVector * 5);
        }
        if(m_backwardPressed) {
            auto btDirVector = btVector3(dirVector.x, 0, dirVector.z).normalize();
            body.rigidBody->setLinearVelocity(-btDirVector * 5);
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
        if(event.event.key.keysym.sym == SDLK_LEFT) {
            m_leftPressed = true;
        }
        if(event.event.key.keysym.sym == SDLK_RIGHT) {
            m_rightPressed = true;
        }
    } else if(event.event.type == SDL_KEYUP) {
        if(event.event.key.keysym.sym == SDLK_UP){
            m_forwardPressed = false;
        }
        if(event.event.key.keysym.sym == SDLK_DOWN) {
            m_backwardPressed = false;
        }
        if(event.event.key.keysym.sym == SDLK_LEFT) {
            m_leftPressed = false;
        }
        if(event.event.key.keysym.sym == SDLK_RIGHT) {
            m_rightPressed = false;
        }
    }
}

void PlayerMotionSystem::configure(entityx::EventManager &events) {
    events.subscribe<SDLEvent>(*this);
}
