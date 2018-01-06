//
// Created by martin on 6.1.18.
//

#ifndef PROJECT_HEALTH_H
#define PROJECT_HEALTH_H

#include <algorithm>
#include <assert.h>

struct Health {
    int healthPoints;
    int defense;

    Health(int healthPoints, int defense) : healthPoints(healthPoints), defense(defense) {}

    void hit(int damage) {
        assert(damage > 0);
        healthPoints -= std::max<int>(0, damage - defense);
    }
};
#endif //PROJECT_HEALTH_H
