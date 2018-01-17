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
#include <map>
#include "Engine/AnimatedTexture.h"

class Billboard: public IDrawable {
    GLuint m_vao;
    std::map<std::string, AnimatedTexture> m_billboardAnimations;
    std::unique_ptr<Buffer<Vertex>> m_vbo;
    std::string m_currentAnimation;
public:
    const std::string &getCurrentAnimation() const;

public:
    explicit Billboard(std::map<std::string, std::vector<std::string>> imagePath, float width, float height);
    void draw(const glm::mat4 &transform, GLuint shader) override;
    void play(const std::string current) {
        m_currentAnimation = current;
        m_billboardAnimations.at(m_currentAnimation).start();
    }
};


#endif //PROJECT_BILLBOARD_H
