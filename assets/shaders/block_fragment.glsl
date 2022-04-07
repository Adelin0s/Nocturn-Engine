#version 460 core

in vec2 textureCoords;

out vec4 outColor;

uniform sampler2D textureSampler;

void main()
{
    outColor = texture(textureSampler, textureCoords);
}