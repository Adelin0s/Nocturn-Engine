#version 460 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aTextureCoords;
layout (location = 2) in vec2 aData;

out vec2 textureCoords;
out float fLightLevel;
out float fSkyLightLevel;
out float visibility;
out vec3 FragPos;

uniform mat4 uProjection;
uniform mat4 uView;

const float denisity = 0.007;
const float gradient = 1.5;

void main()
{
    textureCoords = aTextureCoords;
	fLightLevel = aData.x;
	fSkyLightLevel = aData.y;
	vec4 positionRelativeToCamera = uView * vec4(aPosition, 1.0);
    FragPos = aPosition;
    gl_Position = uProjection * uView * vec4(aPosition, 1.0f);
	
	float distance = length(positionRelativeToCamera.xyz);
	visibility = exp(-pow((distance * denisity), gradient));
	visibility = clamp(visibility, 0.0, 1.0);
}