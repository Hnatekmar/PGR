//
// Created by martin on 16.1.18.
//

#include <glm/gtc/matrix_transform.hpp>
#include "GuiBar.h"

GuiBar::GuiBar(const std::string &gauge): m_gauge({{"idle", {gauge}}}, 0.5, 0.15) {
    m_gauge.play("idle");
}

void GuiBar::draw(const glm::mat4 &transform, GLuint shader, float value, float maximum) {
    float width = value / maximum;
    m_gauge.draw(glm::translate(glm::scale(transform, glm::vec3(width, 1, 1)), glm::vec3(0.001, 0, 0)), shader);
}
