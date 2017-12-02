//
// Created by martin on 1.12.17.
//

#include "PlayerMotionSystem.h"
#include "Engine/Camera.h"
#include "RigidBodyComponent.h"
#include "PlayerState.h"
#include <glm/gtx/rotate_vector.hpp>

void PlayerMotionSystem::update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) {
    int mouseX, mouseY;
    SDL_GetGlobalMouseState(&mouseX, &mouseY);
    auto mouseDelta = glm::vec2(mouseX, mouseY) - m_lastMousePos;
    m_lastMousePos = glm::vec2(mouseX, mouseY);
    entities.each<PlayerState, RigidBody, CameraComponent>([&](entityx::Entity entity,
                                                               PlayerState& state,
                                                               RigidBody& body,
                                                               CameraComponent& fpsCamera) {
        state.pitch += 5 * mouseDelta.y * dt;
        state.yaw += 5 * mouseDelta.x * dt;
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
            body.rigidBody->applyCentralImpulse(btDirVector * 5.0f);
        }
        if(m_backwardPressed) {
            auto btDirVector = btVector3(dirVector.x, 0, dirVector.z).normalize();
            body.rigidBody->applyCentralImpulse(btDirVector * -5.0f);
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
}

void PlayerMotionSystem::configure(entityx::EventManager &events) {
    events.subscribe<SDLEvent>(*this);
}
