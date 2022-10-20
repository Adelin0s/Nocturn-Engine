#version 460 core

layout (location = 0) in vec3 position;

out vec3 TextureCoords;
out float visibility;

uniform mat4 projection;
uniform mat4 view;

const float denisity = 0.27;
const float gradient = 1.5;

void main()
{
    TextureCoords = position;
	vec4 positionRelativeToCamera = view * vec4(position, 1.0);
    vec4 pos = projection * view * vec4(position, 1.0f);
    gl_Position = vec4(pos.x, pos.y, pos.w, pos.w);
	
	float distance = length(positionRelativeToCamera.xyz);
	visibility = exp(-pow((distance * denisity), gradient));
	visibility = clamp(visibility, 0.0, 1.0);
}