//
// Created by martin on 14.1.18.
//

#ifndef PROJECT_PLAYERCREATOR_H
#define PROJECT_PLAYERCREATOR_H

#include <string>
#include <entityx/entityx.h>
#include <BulletDynamics/Dynamics/btDynamicsWorld.h>
#include "json.hpp"

class PlayerCreator {
public:
    static const std::string name;
    static entityx::Entity create(entityx::EntityManager& manager, std::shared_ptr<btDynamicsWorld>& world, const nlohmann::json& data);
};


#endif //PROJECT_PLAYERCREATOR_H
