#version 330 core

uniform sampler2D diffuse;
in vec2 texturePosition;
in vec3 vertexNormal;
out vec4 fragColor;

void main() {
    fragColor = texture(diffuse, texturePosition);
}