//
// Created by martin on 16.1.18.
//

#ifndef PROJECT_LIGHTCOMPONENT_H
#define PROJECT_LIGHTCOMPONENT_H
#include <glm/vec3.hpp>

struct LightComponent {
    glm::vec3 position;
    LightComponent(glm::vec3 pos): position(pos) {
    }
};


#endif //PROJECT_LIGHTCOMPONENT_H
