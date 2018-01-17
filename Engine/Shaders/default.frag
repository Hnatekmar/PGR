#version 330 core

uniform sampler2D diffuse;
uniform sampler2D specular;
uniform vec3 lights[8];
uniform int numberOfLights;
uniform vec3 viewPos;
uniform bool shouldShade;
in vec2 texturePosition;
in vec3 vertexNormal;
in vec3 vertexPosition;
out vec4 fragColor;

void main() {
    if(texture(diffuse, texturePosition).a != 1.0) discard;
    if(shouldShade) {
        vec3 color = vec3(0.0);
        vec3 norm = normalize(vertexNormal);
        vec3 lightColor = vec3(1.0);
        float constant = 1.0;
        float linear = 0.22;
        float quadratic = 0.20;
        for(int i = 0; i < numberOfLights; i++) {
            vec3 lightDir = normalize(lights[i] - vertexPosition);
            float distance = length(lights[i] - vertexPosition);
            float attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance));
            float diff = max(dot(norm, lightDir), 0.0);
            vec3 specular = texture(specular, texturePosition).xyz;
            vec3 viewDir = normalize(viewPos - vertexPosition);
            vec3 reflectDir = reflect(-lightDir, norm);
            float spec = pow(max(dot(viewDir, reflectDir), 0.0), 16);
            color += attenuation * (0.5 * lightColor + diff * lightColor + specular * spec * lightColor) * texture(diffuse, texturePosition).rgb;
        }
        fragColor = vec4(color, 1.0);
    } else {
        fragColor = texture(diffuse, texturePosition);
    }
}