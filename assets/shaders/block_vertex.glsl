#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTextureCoords;

out vec2 textureCoords;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    textureCoords = aTextureCoords;
    gl_Position = projection * view * vec4(aPos, 1.0f);
}