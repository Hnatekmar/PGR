//
// Created by martin on 15.1.18.
//

#ifndef PROJECT_MEDKITCREATOR_H
#define PROJECT_MEDKITCREATOR_H

#include <string>
#include <entityx/entityx.h>
#include <BulletDynamics/Dynamics/btDynamicsWorld.h>
#include "json.hpp"

class MedkitCreator {
public:
    static const std::string name;
    static entityx::Entity create(entityx::EntityManager& manager, std::shared_ptr<btDynamicsWorld>& world, const nlohmann::json& data);
};


#endif //PROJECT_MEDKITCREATOR_H
