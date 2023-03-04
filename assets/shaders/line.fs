#version 430 core
layout (location = 0) out vec4 FragColor;

in vec4 fColor;
in vec2 fDistanceToCenter;

void main()
{
	FragColor = vec4(fColor.rgb, fColor.a - fColor.a * length(fDistanceToCenter));
}