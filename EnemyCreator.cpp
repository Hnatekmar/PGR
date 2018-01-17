//
// Created by martin on 14.1.18.
//

#include <BulletCollision/CollisionShapes/btCapsuleShape.h>
#include <fstream>
#include "EnemyCreator.h"
#include "Engine/GraphicsComponent.h"
#include "RigidBodyComponent.h"
#include "RotationComponent.h"
#include "Health.h"
#include "Billboard.h"
#include "WeaponInfo.h"
#include "AIComponent.h"
#include "LookingDirection.h"

const std::string EnemyCreator::name = "Enemy";

entityx::Entity EnemyCreator::create(entityx::EntityManager &manager, std::shared_ptr<btDynamicsWorld> &world,
                                     const nlohmann::json &data) {
    auto enemy = manager.create();
    auto x = data.at("x").get<float>();
    auto y = data.at("y").get<float>();
    auto z = data.at("z").get<float>();
    enemy.assign<Health>(10, 0);
    auto enemyShape = std::make_shared<btCapsuleShape>(0.7, 0.6);
    enemy.assign<RigidBody>(
            btQuaternion(0.0, 0.0, 0.0, 1.0),
            btVector3(x, y, z),
            enemyShape,
            10,
            btVector3(0, 0, 0)
    );
    std::string baseDir = "enemies/"+ data.at("enemy").get<std::string>();
    std::ifstream weaponInfo(baseDir + "/info.json");
    nlohmann::json weaponJson;
    weaponInfo >> weaponJson;
    weaponInfo.close();
    enemy.assign<RotationComponent>(true);
    enemy.component<RigidBody>().get()->rigidBody->setAngularFactor(btVector3(0, 0, 0));
    enemy.component<RigidBody>().get()->rigidBody->setActivationState(DISABLE_DEACTIVATION);
    enemy.component<RigidBody>().get()->copyRotation = false;
    auto shoot = weaponJson.at("shoot").get<std::vector<std::string>>();
    std::for_each(shoot.begin(), shoot.end(), [baseDir](std::string& path){ path = baseDir + "/" + path; });
    auto walk = weaponJson.at("walk").get<std::vector<std::string>>();
    std::for_each(walk.begin(), walk.end(), [baseDir](std::string& path){ path = baseDir + "/" + path; });
    auto idle = weaponJson.at("idle").get<std::vector<std::string>>();
    std::for_each(idle.begin(), idle.end(), [baseDir](std::string& path){ path = baseDir + "/" + path; });
    auto die = weaponJson.at("die").get<std::vector<std::string>>();
    std::for_each(die.begin(), die.end(), [baseDir](std::string& path){ path = baseDir + "/" + path; });
    std::map<std::string, std::vector<std::string>> animations = {
            {"shoot", shoot},
            {"walk", walk},
            {"idle", idle},
            {"die", die}
    };
    std::shared_ptr<IDrawable> enemyGraphicsObject = std::make_shared<Billboard>(animations, 0.7, 2);
    enemy.assign<GraphicsComponent>(
            glm::vec3(0, -5, 0),
            0.0,
            glm::vec3(0.0, 1.0, 0.0),
            enemyGraphicsObject
    );
    enemy.assign<WeaponInfo>(
            weaponJson.at("damage").get<unsigned>(),
            100,
            250ms,
            1000000,
            world
    );
    enemy.assign<LookingDirection>(0.0, 0.0);
    enemy.assign<AIComponent>(
            500
    );
    return enemy;
}
