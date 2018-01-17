//
// Created by martin on 17.1.18.
//

#include <glm/gtx/rotate_vector.hpp>
#include <btBulletCollisionCommon.h>
#include "AISystem.h"
#include "WeaponInfo.h"
#include "Engine/GraphicsComponent.h"
#include "RigidBodyComponent.h"
#include "Health.h"
#include "Billboard.h"
#include "AIComponent.h"
#include "Util.h"
#include "Engine/Camera.h"
#include "LookingDirection.h"
#include <btBulletDynamicsCommon.h>

void AISystem::update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) {
    entities.each<WeaponInfo, Health, RigidBody, GraphicsComponent, AIComponent, LookingDirection>(
            [&](entityx::Entity entity, WeaponInfo& weapon, Health& health, RigidBody& body, GraphicsComponent& graphicsComponent, AIComponent& ai, LookingDirection& direction) {
                std::shared_ptr<Billboard> animation = std::dynamic_pointer_cast<Billboard>(graphicsComponent.drawable);
                if(health.healthPoints <= 0) {
                    if(animation->getCurrentAnimation() != "die" && !ai.dieAnimationTriggered) {
                        animation->play("die");
                        ai.dieAnimationTriggered = true;
                    } else {
                        if(animation->getCurrentAnimation() != "die") {
                            entity.destroy();
                        }
                    }
                }
                auto start = body.rigidBody->getCenterOfMassPosition();
                auto dirVector = convert<btVector3>(glm::rotateY(glm::vec3(0, 0, 100), glm::radians(graphicsComponent.angle)));
                start = dirVector * 0.1;
                auto end = start + dirVector;
                graphicsComponent.angleVec;
                btCollisionWorld::ClosestRayResultCallback rayCallback(start, end);
                weapon.world->rayTest(start, end, rayCallback);
                if(rayCallback.hasHit() && animation->getCurrentAnimation() == "idle") {
                    if(rayCallback.m_collisionObject->getUserPointer() != nullptr) {
                        auto entity = static_cast<entityx::Entity *>(rayCallback.m_collisionObject->getUserPointer());
                        if(entity->component<CameraComponent>()) {
                            weapon.shooting = true;
                            animation->play("shoot");
                            direction.yaw = graphicsComponent.angle;
                            body.rigidBody->setLinearVelocity(btVector3(0.0, 0.0, 0.0));
                        } else {
                            animation->play("walk");
                            body.rigidBody->setLinearVelocity(dirVector * 0.05);
                        }
                    }
                }
                if(animation->getCurrentAnimation() == "idle") {
                    animation->play("walk");
                }
            }
    );
}
