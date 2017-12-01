//
// Created by martin on 1.12.17.
//

#ifndef PROJECT_PLAYERSTATE_H
#define PROJECT_PLAYERSTATE_H

#include <LinearMath/btVector3.h>

struct PlayerState {
    float yaw;
    float pitch;
    PlayerState(float yaw, float pitch) {
        this->yaw = yaw;
        this->pitch = pitch;
    }
};

#endif //PROJECT_PLAYERSTATE_H
