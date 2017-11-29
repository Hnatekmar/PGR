//
// Created by martin on 29.11.17.
//

#ifndef PROJECT_CAMERA_H
#define PROJECT_CAMERA_H

#include <glm/detail/type_mat.hpp>
#include <glm/detail/type_mat4x4.hpp>
/**
 * Komponenta, která uchovává informace o kameře. Zároveň abstrahuje výpočet
 */
class CameraComponent {
    glm::mat4 m_projection;
    glm::mat4 m_view;
    glm::vec3 m_position;
public:
    const glm::vec3 &getPosition() const;

    void setM_position(const glm::vec3 &m_position);

private:
    glm::vec3 m_direction;
    glm::vec3 m_up;
    float m_fov;
    float m_aspectRatio;
    float m_nearPlane;
    float m_farPlane;

    /**
     * Nastaví transformační matice dle parametrů kamery
     */
    void updateMatrix();

    /**
     * Nastaví pohledovou matici
     */
    void updateViewMatrix();

    /**
     * Nastaví projekční matici
     */
    void updateProjectionMatrix();
public:
    void setPosition(const glm::vec3 &m_position);

    CameraComponent(const glm::vec3 &m_position, const glm::vec3 &m_direction, const glm::vec3 &m_up, float m_fov,
                    float m_aspectRatio, float m_nearPlane, float m_farPlane);

    void setDirection(const glm::vec3 &m_direction);

    void setUp(const glm::vec3 &m_up);

    void setFOV(float m_fov);

    float getNearPlane() const;

    void setNearPlane(float m_nearPlane);

    float getFarPlane() const;

    void setFarPlane(float m_farPlane);

    void setAspectRatio(float m_aspectRatio);

    glm::mat4 getPVMatrix() {
        return m_projection * m_view;
    }
};


#endif //PROJECT_CAMERA_H
