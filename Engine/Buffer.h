//
// Created by martin on 27.10.17.
//

#ifndef PROJECT_VBO_H
#define PROJECT_VBO_H

#include <GL/glew.h>
#include <list>
#include "Exceptions/EngineException.h"

/**
 * @brief Obal nad vbo. Jeho hlavní výhoda je, že se díky RAII postará o uvolnění bufferu
 */
template<typename T>
class Buffer {
    GLuint m_buffer;
    GLsizeiptr m_size;
    GLenum m_type;
public:
    Buffer(const T* data, GLsizeiptr count, GLenum usagePattern, const GLenum type = GL_ARRAY_BUFFER): m_buffer(0), m_size(count * sizeof(T)), m_type(type) {
        glGenBuffers(1, &m_buffer);
        glBindBuffer(type, m_buffer);
        glBufferData(type, count * sizeof(T), data, usagePattern);
        HANDLE_GL_ERRORS()
    }

    /**
     * Vrací počet prvků uložených v bufferu
     * @return počet prvků
     */
    GLsizei count() const {
        return m_size / sizeof(T);
    }

    /**
     * @brief Nabinduje buffer
     */
    void bind() {
        glBindBuffer(m_type, m_buffer);
    }

    /**
     * @brief Unbinduje buffer
     */
    void unbind() {
        glBindBuffer(m_type, 0);
    }

    ~Buffer() {
        glDeleteBuffers(1, &m_buffer);
    }
};


#endif //PROJECT_VBO_H
