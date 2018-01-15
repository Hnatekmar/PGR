//
// Created by martin on 14.1.18.
//

#include <BulletCollision/CollisionShapes/btCapsuleShape.h>
#include "EnemyCreator.h"
#include "Engine/GraphicsComponent.h"
#include "RigidBodyComponent.h"
#include "RotationComponent.h"
#include "Health.h"
#include "Billboard.h"

const std::string EnemyCreator::name = "Enemy";

entityx::Entity EnemyCreator::create(entityx::EntityManager &manager, std::shared_ptr<btDynamicsWorld> &world,
                                     const nlohmann::json &data) {
    auto enemy = manager.create();
    auto x = data.at("x").get<float>();
    auto y = data.at("y").get<float>();
    auto z = data.at("z").get<float>();
    enemy.assign<Health>(100, 0);
    auto enemyShape = std::make_shared<btCapsuleShape>(0.7, 1.0);
    enemy.assign<RigidBody>(
            btQuaternion(0.0, 0.0, 0.0, 1.0),
            btVector3(x, y, z),
            enemyShape,
            10,
            btVector3(0, 0, 0)
    );
    enemy.assign<RotationComponent>(true);
    enemy.component<RigidBody>().get()->rigidBody->setAngularFactor(btVector3(0, 0, 0));
    enemy.component<RigidBody>().get()->rigidBody->setActivationState(DISABLE_DEACTIVATION);
    enemy.component<RigidBody>().get()->copyRotation = false;
    std::map<std::string, std::vector<std::string>> animations = {
            {"idle", {"guard-0.png", "guard-1.png", "guard-2.png", "guard-3.png"}}
    };
    std::shared_ptr<IDrawable> enemyGraphicsObject = std::make_shared<Billboard>(animations, 0.7, 2);
    enemy.assign<GraphicsComponent>(
            glm::vec3(0, -5, 0),
            0.0,
            glm::vec3(0.0, 1.0, 0.0),
            enemyGraphicsObject
    );
    return enemy;
}
