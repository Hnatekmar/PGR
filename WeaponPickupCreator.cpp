//
// Created by martin on 15.1.18.
//

#include <glm/vec3.hpp>
#include <fstream>
#include "WeaponPickupCreator.h"
#include "Engine/IDrawable.h"
#include "Billboard.h"
#include "RotationComponent.h"
#include "ProximityComponent.h"
#include "Engine/GraphicsComponent.h"
#include "GuiComponent.h"
#include "WeaponInfo.h"

const std::string WeaponPickupCreator::name = "Weapon";
entityx::Entity WeaponPickupCreator::create(entityx::EntityManager &manager, std::shared_ptr<btDynamicsWorld> &world,
                                            const nlohmann::json &data) {
    auto entity = manager.create();
    auto x = data.at("x").get<float>();
    auto y = data.at("y").get<float>();
    auto z = data.at("z").get<float>();
    std::string baseDir = "weapons/"+ data.at("weapon").get<std::string>();
    std::ifstream weaponInfo(baseDir + "/info.json");
    nlohmann::json weaponJson;
    weaponInfo >> weaponJson;
    weaponInfo.close();
    std::map<std::string, std::vector<std::string>> animations = {
            {"idle", {baseDir + "/" + weaponJson.at("icon").get<std::string>()}}
    };
    std::shared_ptr<IDrawable> graphics = std::make_shared<Billboard>(animations, 0.5, 0.5);
    entity.assign<GraphicsComponent>(
            glm::vec3(x, y, z),
            0.0,
            glm::vec3(0.0, 1.0, 0.0),
            graphics
    );
    entity.assign<RotationComponent>(true);
    entity.assign<ProximityComponent<std::function<void(entityx::Entity, entityx::Entity)>>>(
            glm::vec3(x, y, z),
                    1,
                    [weaponJson, baseDir](entityx::Entity pickupEntity, entityx::Entity player) {
                        auto idle = weaponJson.at("idle").get<std::vector<std::string>>();
                        auto shoot = weaponJson.at("shoot").get<std::vector<std::string>>();
                        std::for_each(idle.begin(), idle.end(), [baseDir](std::string& path){
                                        path = baseDir + "/" + path;
                                      });
                        std::for_each(shoot.begin(), shoot.end(), [baseDir](std::string& path){
                            path = baseDir + "/" + path;
                        });
                        std::map<std::string, std::vector<std::string>> animations = {
                                {"idle", idle},
                                {"shoot", shoot}
                        };
                        player.component<GuiComponent>().get()->gun = std::make_shared<Billboard>(animations, 0.5, 0.5);
                        auto weaponInfo = player.component<WeaponInfo>().get();
                        weaponInfo->damage = weaponJson.at("damage").get<unsigned int>();
                        weaponInfo->damage = weaponJson.at("clipSize").get<unsigned int>();
                        pickupEntity.destroy();
                    }
    );
    return entity;
}
