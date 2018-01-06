//
// Created by martin on 6.1.18.
//

#ifndef PROJECT_BILLBOARD_H
#define PROJECT_BILLBOARD_H


#include "Engine/IDrawable.h"
#include "Engine/Primitives/Texture.h"
#include "Engine/Buffer.h"
#include "Engine/Primitives/Vertex.h"
#include <string>
#include <memory>

class Billboard: public IDrawable {
    GLuint m_vao;
    Texture m_bilboardTexture;
    std::unique_ptr<Buffer<Vertex>> m_vbo;
public:
    explicit Billboard(std::string imagePath, float width, float height);
    void draw(const glm::mat4 &transform, GLuint shader) override;
};


#endif //PROJECT_BILLBOARD_H
