#include "Texture.h"
#include <stdexcept>
#include <il.h>
#include "../Exceptions/EngineException.h"

Texture::Texture(TextureType textureType, std::string path): m_type(textureType) {
    glGenTextures(1, &m_textureID);
    glBindTexture(GL_TEXTURE_2D, m_textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    ILuint ImgId = 0;
    ilGenImages(1, &ImgId);
    ilBindImage(ImgId);
    if(ilLoadImage(path.c_str()) != IL_TRUE) {
        throw std::runtime_error("Couldn't load image " + path);
    }
    if(ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE) != IL_TRUE) {
        throw std::runtime_error("Image conversion failed " + path);
    }
    auto width = ilGetInteger(IL_IMAGE_WIDTH);
    auto height = ilGetInteger(IL_IMAGE_HEIGHT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*) ilGetData());
    glGenerateMipmap(GL_TEXTURE_2D);
    HANDLE_GL_ERRORS()
    ilBindImage(0);
    ilDeleteImage(ImgId);
}

void Texture::bind(GLuint programID) {
    if(m_type == TextureType::diffuse) {
        glActiveTexture(GL_TEXTURE0);
    }
    if(m_type == TextureType::specular) {
        glActiveTexture(GL_TEXTURE1);
    }
    { HANDLE_GL_ERRORS() }
    glBindTexture(GL_TEXTURE_2D, m_textureID);
    { HANDLE_GL_ERRORS() }
    if(m_type == TextureType::diffuse) {
        auto diffuse = glGetUniformLocation(programID, "diffuse");
        glUniform1i(diffuse, 0);
        { HANDLE_GL_ERRORS() }
    }
    if(m_type == TextureType::specular) {
        auto specular = glGetUniformLocation(programID, "specular");
        glUniform1i(specular, 0);
        { HANDLE_GL_ERRORS() }
    }
}
