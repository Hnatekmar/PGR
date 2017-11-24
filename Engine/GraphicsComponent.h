//
// Created by martin on 24.11.17.
//

#ifndef PROJECT_GRAPHICCOMPONENT_H
#define PROJECT_GRAPHICCOMPONENT_H

#include <glm/vec3.hpp>
#include "IDrawable.h"
#include <memory>

struct GraphicsComponent {
    GraphicsComponent(glm::vec3 p, float a, glm::vec3 av, std::shared_ptr<IDrawable> d): position(p),
                                                                                        angle(a),
                                                                                        angleVec(av),
                                                                                        drawable(d)
    {}
    glm::vec3 position;
    float angle;
    glm::vec3 angleVec;
    std::shared_ptr<IDrawable> drawable;
};

#endif //PROJECT_GRAPHICCOMPONENT_H
