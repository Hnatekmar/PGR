//
// Created by martin on 12.1.18.
//

#include "RotationSystem.h"
#include "RotationComponent.h"
#include "Engine/GraphicsComponent.h"
#include "RigidBodyComponent.h"
#include "Engine/Camera.h"
#define PI 3.141592653589793f
#define TO_DEGREES(ang) (180.0f / PI) * ang
#define TO_RADIANS(ang) (PI / 180.0f) * ang

void RotationSystem::update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) {
    entities.each<RotationComponent, GraphicsComponent>(
            [&entities](entityx::Entity entity, RotationComponent& rotation, GraphicsComponent& graphics) {
                if(rotation.rotate) {
                    entities.each<RigidBody, CameraComponent>(
                            [&graphics](entityx::Entity aEntity, RigidBody& body, CameraComponent& cam) {
                                auto pos = cam.getPosition() - graphics.position;
                                graphics.angleVec = glm::vec3(0, 1, 0);
                                graphics.angle = TO_RADIANS(TO_DEGREES(std::atan2(pos.x, pos.z)) + (360 - 90));
                            }
                    );
                }
            });
}
