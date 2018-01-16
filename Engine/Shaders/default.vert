#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv;
uniform mat4 transform;
uniform mat4 model;
out vec2 texturePosition;
out vec3 vertexNormal;
out vec3 vertexPosition;

void main() {
    gl_Position = transform * vec4(position, 1.0f);
    texturePosition = uv;
    vertexNormal = normal;
    vertexPosition = vec3(model * vec4(position, 1.0));
}