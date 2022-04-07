#version 460 core

in vec3 TextureCoords;

out vec4 FragColor;

uniform samplerCube skybox;

void main()
{
    FragColor = texture(skybox, TextureCoords);
}