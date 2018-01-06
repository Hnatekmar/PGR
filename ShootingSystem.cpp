//
// Created by martin on 3.1.18.
//

#include <glm/vec3.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "ShootingSystem.h"
#include "WeaponInfo.h"
#include "LookingDirection.h"
#include "RigidBodyComponent.h"
#include "Util.h"

void ShootingSystem::update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) {
    entities.each<WeaponInfo, LookingDirection, RigidBody>([dt](entityx::Entity entity,
                                                                WeaponInfo& weapon,
                                                                LookingDirection& direction,
                                                                RigidBody& body) {
        if(weapon.shooting && weapon.fire()) {
            auto start = body.rigidBody->getCenterOfMassPosition();
            auto dirVector = convert<btVector3>(glm::rotateX(glm::rotateY(glm::vec3(0, 0, 100),
                                                                          glm::radians(direction.yaw)),
                                                             glm::radians(direction.pitch)));
            auto end = start + dirVector;

            btCollisionWorld::ClosestRayResultCallback rayCallback(start, end);
            weapon.world->rayTest(start, end, rayCallback);
            if(rayCallback.hasHit()) {
                if(rayCallback.m_collisionObject->getUserPointer() != nullptr) {
                    auto entity = static_cast<entityx::Entity*>(rayCallback.m_collisionObject->getUserPointer());
                    std::cout << "HIT" << std::endl;
                }
            }
        }
    });
}
