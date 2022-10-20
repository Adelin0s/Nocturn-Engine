#version 460 core

in vec3 TextureCoords;
in float visibility;

out vec4 outColor;

uniform samplerCube skybox;

void main()
{
	vec3 skyColour = vec3(0.5, 0.5, 0.5);
    outColor = texture(skybox, TextureCoords);
	outColor = mix(vec4(skyColour, 1.0), outColor, visibility);
}