//
// Created by martin on 29.11.17.
//

#include "Camera.h"
#include <glm/gtx/transform.hpp>

void CameraComponent::setPosition(const glm::vec3 &m_position) {
    CameraComponent::m_position = m_position;
    updateMatrix();
}

void CameraComponent::setDirection(const glm::vec3 &m_direction) {
    CameraComponent::m_direction = m_direction;
    updateMatrix();
}

void CameraComponent::setUp(const glm::vec3 &m_up) {
    CameraComponent::m_up = m_up;
    updateMatrix();
}

void CameraComponent::setFOV(float m_fov) {
    CameraComponent::m_fov = m_fov;
    updateProjectionMatrix();
}

void CameraComponent::updateMatrix() {
    updateViewMatrix();
    updateProjectionMatrix();
}

void CameraComponent::updateViewMatrix() {
    m_view = glm::lookAt(m_position,
                         m_position + m_direction,
                         m_up);
}

void CameraComponent::updateProjectionMatrix() {
    m_projection = glm::perspective(
            glm::radians(m_fov),
            m_aspectRatio,
            m_nearPlane,
            m_farPlane
    );
}

void CameraComponent::setAspectRatio(float m_aspectRatio) {
    CameraComponent::m_aspectRatio = m_aspectRatio;
    updateProjectionMatrix();
}

float CameraComponent::getNearPlane() const {
    return m_nearPlane;
}

void CameraComponent::setNearPlane(float m_nearPlane) {
    CameraComponent::m_nearPlane = m_nearPlane;
    updateProjectionMatrix();
}

float CameraComponent::getFarPlane() const {
    return m_farPlane;
}

void CameraComponent::setFarPlane(float m_farPlane) {
    CameraComponent::m_farPlane = m_farPlane;
    updateProjectionMatrix();
}

CameraComponent::CameraComponent(const glm::vec3 &m_position, const glm::vec3 &m_direction, const glm::vec3 &m_up,
                                 float m_fov, float m_aspectRatio, float m_nearPlane, float m_farPlane) : m_position(m_position),
        m_direction(m_direction),
        m_up(m_up),
        m_fov(m_fov),
        m_aspectRatio(m_aspectRatio),
        m_nearPlane(m_nearPlane),
        m_farPlane(m_farPlane)
{
    updateMatrix();
}

const glm::vec3 &CameraComponent::getPosition() const {
    return m_position;
}

void CameraComponent::setM_position(const glm::vec3 &m_position) {
    CameraComponent::m_position = m_position;
}
