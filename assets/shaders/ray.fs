#version 460 core

in vec2 textureCoords;

out vec4 outColor;

uniform sampler2D textureSampler;

void main()
{
	outColor = vec4(0.5f, 0.2f, 0.6f, 1.0f);
}