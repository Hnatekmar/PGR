//
// Created by martin on 17.1.18.
//

#ifndef PROJECT_AISYSTEM_H
#define PROJECT_AISYSTEM_H

#include <entityx/entityx.h>

class AISystem: public entityx::System<AISystem> {
public:
    void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override;
};


#endif //PROJECT_AISYSTEM_H
