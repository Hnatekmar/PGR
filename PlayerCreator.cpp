//
// Created by martin on 14.1.18.
//

#include <BulletCollision/CollisionShapes/btCapsuleShape.h>
#include "PlayerCreator.h"
#include "LookingDirection.h"
#include "RigidBodyComponent.h"
#include "Engine/Camera.h"
#include "WeaponInfo.h"
#include "Health.h"
#include <chrono>

const std::string PlayerCreator::name = "Player";

using namespace std::chrono_literals;
entityx::Entity PlayerCreator::create(entityx::EntityManager& manager, std::shared_ptr<btDynamicsWorld>& world, const nlohmann::json &data) {
    auto player = manager.create();
    auto playerShape = std::make_shared<btCapsuleShape>(0.7, 1.0);
    player.assign<LookingDirection>();

    auto x = data.at("x").get<float>();
    auto y = data.at("y").get<float>();
    auto z = data.at("z").get<float>();
    player.assign<RigidBody>(
            btQuaternion(0.0, 0.0, 0.0, 1.0),
            btVector3(x, y, z),
            playerShape,
            10,
            btVector3(0, 0, 0)
    );
    player.component<RigidBody>().get()->rigidBody->setAngularFactor(btVector3(0, 0, 0));
    player.component<RigidBody>().get()->rigidBody->setActivationState(DISABLE_DEACTIVATION);
    player.assign<CameraComponent>(
            glm::vec3(0, 0, 0),
            glm::vec3(0, 0, 1),
            glm::vec3(0, 1, 0),
            45.0f,
            4.0 / 3.0,
            0.01,
            200.0
    );
    player.assign<WeaponInfo>(
            (unsigned)100,
            (unsigned)10,
            1000.0ms,
            (unsigned)500,
            world
    );
    player.assign<Health>(
            100,
            0
    );
    return player;
}
