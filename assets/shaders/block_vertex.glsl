#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 aTextureCoords;

out vec2 textureCoords;
out float visibility;

uniform mat4 projection;
uniform mat4 view;

const float denisity = 0.007;
const float gradient = 1.5;

void main()
{
    textureCoords = aTextureCoords;
	vec4 positionRelativeToCamera = view * vec4(position, 1.0);
    gl_Position = projection * view * vec4(position, 1.0f);
	
	float distance = length(positionRelativeToCamera.xyz);
	visibility = exp(-pow((distance * denisity), gradient));
	visibility = clamp(visibility, 0.0, 1.0);
}