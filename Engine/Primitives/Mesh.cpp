//
// Created by martin on 4.11.17.
//

#include "Mesh.h"
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <stdexcept>


Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures):
    m_textures(textures)
{
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);
    { HANDLE_GL_ERRORS() }

    m_vbo = std::make_unique<Buffer<Vertex>>(vertices.data(), vertices.size(), GL_STATIC_DRAW);
    m_vbo->bind();
    // Pozice
    m_ebo = std::make_unique<Buffer<GLuint>>(indices.data(), indices.size(), GL_STATIC_DRAW, GL_ELEMENT_ARRAY_BUFFER);
    m_ebo->bind();
    { HANDLE_GL_ERRORS() }
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
    { HANDLE_GL_ERRORS() }
    glBindVertexArray(0);
}

void Mesh::draw(const glm::mat4 &transform, GLuint shader) {
    glBindVertexArray(m_vao);
    glUniformMatrix4fv(glGetUniformLocation(shader, "transform"), 1, GL_FALSE, &transform[0][0]);
    { HANDLE_GL_ERRORS() }
    for(auto& texture: m_textures) {
        texture.bind(shader);
    }
    { HANDLE_GL_ERRORS() }
    m_ebo->bind();
    glDrawElements(GL_TRIANGLES, m_ebo->count(), GL_UNSIGNED_INT, 0);
    { HANDLE_GL_ERRORS() }
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(0);
}
