//
// Created by martin on 15.1.18.
//

#include "MedkitCreator.h"
#include "Engine/IDrawable.h"
#include "Billboard.h"
#include "Engine/GraphicsComponent.h"
#include "RotationComponent.h"
#include "ProximityComponent.h"
#include "Health.h"

const std::string MedkitCreator::name = "Medkit";

entityx::Entity MedkitCreator::create(entityx::EntityManager &manager, std::shared_ptr<btDynamicsWorld> &world,
                                      const nlohmann::json &data) {
    auto entity = manager.create();
    auto x = data.at("x").get<float>();
    auto y = data.at("y").get<float>();
    auto z = data.at("z").get<float>();
    std::map<std::string, std::vector<std::string>> animations = {
            {"idle", {"medkit.png"}}
    };
    std::shared_ptr<IDrawable> medkitGraphics = std::make_shared<Billboard>(animations, 0.5, 0.5);
    entity.assign<GraphicsComponent>(
            glm::vec3(x, y, z),
            0.0,
            glm::vec3(0.0, 1.0, 0.0),
            medkitGraphics
    );
    entity.assign<RotationComponent>(true);
    entity.assign<ProximityComponent<std::function<void(entityx::Entity, entityx::Entity)>>>(
            glm::vec3(x, y, z),
            1,
            [](entityx::Entity medkitEntity, entityx::Entity player) {
                auto playerHealth = player.component<Health>();
                if(playerHealth.get()->healthPoints < 100) {
                    playerHealth.get()->healthPoints = std::min(100, playerHealth.get()->healthPoints + 50);
                    medkitEntity.destroy();
                }
            }
    );
    return entity;
}
