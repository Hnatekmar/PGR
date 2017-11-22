//
// Created by martin on 24.10.17.
//

#ifndef PROJECT_IDRAWABLE_H
#define PROJECT_IDRAWABLE_H

#include <glm/mat4x4.hpp>
#include <GL/glew.h>

/**
 * @brief Generický interface pro cokoliv vykreslitelného
 */
class IDrawable {
public:
    virtual void draw(const glm::mat4& transform, GLuint shader) = 0;
};

#endif //PROJECT_IDRAWABLE_H
