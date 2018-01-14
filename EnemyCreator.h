//
// Created by martin on 14.1.18.
//

#ifndef PROJECT_ENEMYCREATOR_H
#define PROJECT_ENEMYCREATOR_H


#include <entityx/Entity.h>
#include <BulletDynamics/Dynamics/btDynamicsWorld.h>
#include "json.hpp"

class EnemyCreator {
public:
    static const std::string name;
    static entityx::Entity create(entityx::EntityManager& manager, std::shared_ptr<btDynamicsWorld>& world, const nlohmann::json& data);
};


#endif //PROJECT_ENEMYCREATOR_H
