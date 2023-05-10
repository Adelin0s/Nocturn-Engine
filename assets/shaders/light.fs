#version 330 core

in vec3 FragPos;
in vec3 Normal;

uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform float lightIntensity;

uniform vec3 viewPos;
uniform vec3 objectColor;

out vec4 FragColor;

void main() 
{
    // Ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPosition - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    // Attenuation
    float distance = length(lightPosition - FragPos);
    float attenuation = 1.0 / (1.0 + 0.09 * distance + 0.032 * (distance * distance));
    vec3 result = (ambient + lightIntensity * (diffuse + specular)) * objectColor;
    result *= attenuation;

    FragColor = vec4(result, 1.0);
}