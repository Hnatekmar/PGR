//
// Created by martin on 15.1.18.
//

#ifndef PROJECT_PROXIMITYSYSTEM_H
#define PROJECT_PROXIMITYSYSTEM_H

#include <entityx/entityx.h>

class ProximitySystem: public entityx::System<ProximitySystem> {
public:
    void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override;
};


#endif //PROJECT_PROXIMITYSYSTEM_H
