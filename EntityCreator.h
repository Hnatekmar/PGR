//
// Created by martin on 14.1.18.
//

#ifndef PROJECT_ENTITYCREATOR_H
#define PROJECT_ENTITYCREATOR_H
#include <entityx/entityx.h>
#include <exception>
#include <BulletDynamics/Dynamics/btDynamicsWorld.h>
#include "PlayerCreator.h"
#include "json.hpp"
#include "EnemyCreator.h"

template<typename Factory, typename ... Factories>
entityx::Entity createEntity(entityx::EntityManager& manager, std::shared_ptr<btDynamicsWorld>& world, const nlohmann::json& data) {
    if(Factory::name == data["type"].get<std::string>()) {
        return Factory::create(manager, world, data);
    } else {
        if constexpr(sizeof...(Factories) >= 1) {
            return createEntity<Factories...>(manager, world, data);
        }
        throw std::runtime_error("Invalid type " + data["type"].get<std::string>());
    }
}

#define CREATE_ENTITY createEntity<PlayerCreator, EnemyCreator>

#endif //PROJECT_ENTITYCREATOR_H
