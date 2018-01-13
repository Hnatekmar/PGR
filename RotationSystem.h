//
// Created by martin on 12.1.18.
//

#ifndef PROJECT_ROTATIONSYSTEM_H
#define PROJECT_ROTATIONSYSTEM_H

#include <entityx/entityx.h>
class RotationSystem: public entityx::System<RotationSystem> {
public:
    void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override;

};


#endif //PROJECT_ROTATIONSYSTEM_H
