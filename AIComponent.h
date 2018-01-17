//
// Created by martin on 13.1.18.
//

#ifndef PROJECT_AICOMPONENT_H
#define PROJECT_AICOMPONENT_H
struct AIComponent {
    unsigned maximumDistance;
    bool dieAnimationTriggered;
    bool shotAtPlayer;
    AIComponent(unsigned maximumDistance): maximumDistance(maximumDistance) {
        dieAnimationTriggered = false;
        shotAtPlayer = false;
    }
};
#endif //PROJECT_AICOMPONENT_H
