//
// Created by martin on 16.1.18.
//

#ifndef PROJECT_GUIBAR_H
#define PROJECT_GUIBAR_H

#include "Billboard.h"

class GuiBar {
    Billboard m_gauge;
public:
    GuiBar(const std::string& gauge);
    void draw(const glm::mat4 &transform, GLuint shader, float value, float maximum);
};


#endif //PROJECT_GUIBAR_H
