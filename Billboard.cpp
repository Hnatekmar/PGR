//
// Created by martin on 6.1.18.
//

#include "Billboard.h"
#include "Engine/Primitives/Vertex.h"
#include <vector>

void Billboard::draw(const glm::mat4 &transform, GLuint shader) {
    glUniformMatrix4fv(glGetUniformLocation(shader, "transform"), 1, GL_FALSE, &transform[0][0]);
    glBindVertexArray(m_vao);
    { HANDLE_GL_ERRORS() }
    m_bilboardTexture.bind(shader);
    { HANDLE_GL_ERRORS() }
    glDrawArrays(GL_TRIANGLES, 0, m_vbo->count());
    glBindVertexArray(0);
}

Billboard::Billboard(std::string imagePath, float width, float height): m_bilboardTexture(TextureType::diffuse, imagePath),
                                             m_vbo(nullptr) {
    std::vector<Vertex> vboData{
            {
                    {0, -height / 2, 0},
                    {0, 0, 1},
                    {1, 1}
            },
            {
                    {0, height / 2, 0},
                    {0, 0, 1},
                    {1, 0}
            },
            {
                    {width, height / 2, 0},
                    {0, 0, 1},
                    {0, 0}
            },
            {
                    {width, height / 2, 0},
                    {0, 0, 1},
                    {0, 0}
            },
            {
                {width, -height / 2, 0},
                {0, 0, 1},
                {0, 1}
            },
            {
                    {0, -height / 2, 0},
                    {0, 0, 1},
                    {1, 1}
            }
    };
    m_vbo = std::make_unique<Buffer<Vertex>>(vboData.data(), vboData.size(), GL_STATIC_DRAW);
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);
    m_vbo->bind();

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) 0);
    { HANDLE_GL_ERRORS() }
    // Normály
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) sizeof(glm::vec3));
    { HANDLE_GL_ERRORS() }

    // Pozice v textuře
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) (sizeof(glm::vec3) * 2));
    glBindVertexArray(0);

    glBindVertexArray(0);
    { HANDLE_GL_ERRORS() }
}
