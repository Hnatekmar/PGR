#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv;
uniform mat4 transform;
out vec2 texturePosition;
out vec3 vertexNormal;

void main() {
    gl_Position = transform * vec4(position, 1.0f);
    texturePosition = uv;
    vertexNormal = normal;
}