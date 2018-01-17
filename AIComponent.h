//
// Created by martin on 13.1.18.
//

#ifndef PROJECT_AICOMPONENT_H
#define PROJECT_AICOMPONENT_H
struct AIComponent {
    unsigned maximumDistance;
    bool dieAnimationTriggered;
    AIComponent(unsigned maximumDistance): maximumDistance(maximumDistance) {
        dieAnimationTriggered = false;
    }
};
#endif //PROJECT_AICOMPONENT_H
