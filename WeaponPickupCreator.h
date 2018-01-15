//
// Created by martin on 15.1.18.
//

#ifndef PROJECT_WEAPONPICKUPCREATOR_H
#define PROJECT_WEAPONPICKUPCREATOR_H

#include <entityx/entityx.h>
#include <BulletDynamics/Dynamics/btDynamicsWorld.h>
#include "json.hpp"

class WeaponPickupCreator {
public:
    static const std::string name;
    static entityx::Entity create(entityx::EntityManager& manager, std::shared_ptr<btDynamicsWorld>& world, const nlohmann::json& data);
};


#endif //PROJECT_WEAPONPICKUPCREATOR_H
