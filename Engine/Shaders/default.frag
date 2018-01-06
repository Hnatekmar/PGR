#version 330 core

uniform sampler2D diffuse;
in vec2 texturePosition;
in vec3 vertexNormal;
out vec4 fragColor;

void main() {
    if(texture(diffuse, texturePosition).a < 0.01) discard;
    fragColor = texture(diffuse, texturePosition);
}