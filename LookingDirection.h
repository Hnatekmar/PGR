//
// Created by martin on 1.12.17.
//

#ifndef PROJECT_PLAYERSTATE_H
#define PROJECT_PLAYERSTATE_H

#include <LinearMath/btVector3.h>

struct LookingDirection {
    float yaw;
    float pitch;
    explicit LookingDirection(float yaw = 0.0, float pitch = 0.0) {
        this->yaw = yaw;
        this->pitch = pitch;
    }
};

#endif //PROJECT_PLAYERSTATE_H
