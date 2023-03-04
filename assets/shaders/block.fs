#version 460 core

in vec2 textureCoords;
in float visibility;

out vec4 outColor;

uniform sampler2D textureSampler;

void main()
{
	vec3 skyColour = vec3(0.5, 0.5, 0.5);
    outColor = texture(textureSampler, textureCoords);
	outColor = mix(vec4(skyColour, 1.0), outColor, visibility);
}