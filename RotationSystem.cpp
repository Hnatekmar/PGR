//
// Created by martin on 12.1.18.
//

#include "RotationSystem.h"
#include "RotationComponent.h"
#include "Engine/GraphicsComponent.h"
#include "RigidBodyComponent.h"
#include "Engine/Camera.h"
#define PI 3.141592653589793f

void RotationSystem::update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) {
    entities.each<RotationComponent, GraphicsComponent>(
            [&entities](entityx::Entity entity, RotationComponent& rotation, GraphicsComponent& graphics) {
                if(rotation.rotate) {
                    entities.each<RigidBody, CameraComponent>(
                            [&graphics](entityx::Entity aEntity, RigidBody& body, CameraComponent& cam) {
                                auto pos = graphics.position - cam.getPosition();
                                graphics.angle = (180.0f / PI) * std::atan2(pos.z, pos.x);
                            }
                    );
                }
            });
}
