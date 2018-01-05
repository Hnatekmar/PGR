//
// Created by martin on 3.1.18.
//

#ifndef PROJECT_SHOOTINGSYSTEM_H
#define PROJECT_SHOOTINGSYSTEM_H

#include <entityx/System.h>

class ShootingSystem: public entityx::System<ShootingSystem> {
public:
    void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override;
};


#endif //PROJECT_SHOOTINGSYSTEM_H
