//
// Created by martin on 4.11.17.
//

#ifndef PROJECT_MESH_H
#define PROJECT_MESH_H

#include "../IDrawable.h"
#include "../Buffer.h"
#include "Vertex.h"
#include "Texture.h"
#include <memory>
#include <vector>
/**
 * @brief Třída, která obaluje a vykresluje data z 3D modelu
 */
class Mesh: public IDrawable {
    std::unique_ptr<Buffer<Vertex>> m_vbo;
    std::unique_ptr<Buffer<GLuint>> m_ebo;
    GLuint m_vao;
    std::vector<Texture> m_textures;
public:
    Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures);
    void draw(const glm::mat4 &transform, GLuint shader) override;
};


#endif //PROJECT_MESH_H
