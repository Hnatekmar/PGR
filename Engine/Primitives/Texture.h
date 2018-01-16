//
// Created by martin on 18.11.17.
//

#ifndef PROJECT_TEXTURE_H
#define PROJECT_TEXTURE_H

#include <string>
#include <GL/glew.h>

enum class TextureType {
    diffuse,
    specular,
    normal
};

class Texture {
    GLuint m_textureID;
    TextureType m_type;
public:
    Texture(TextureType textureType, std::string path);
    void bind(GLuint programID);
};

#endif //PROJECT_TEXTURE_H
