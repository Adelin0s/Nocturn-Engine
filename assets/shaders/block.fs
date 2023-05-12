#version 460 core

out vec4 OutColor;

in vec3 FragPos;  
in vec2 textureCoords;
in float visibility;

uniform sampler2D textureSampler;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 objectColor;

void main()
{
    vec3 Normal = vec3(0.0f, 1.0f, 0.0f);

    // ambient 
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;  
        
    vec3 result = (ambient + diffuse + specular) * objectColor;
    vec4 LightColorResult = vec4(result, 1.0);

    vec3 skyColour = vec3(0.5, 0.5, 0.5);
    OutColor = texture(textureSampler, textureCoords);
	OutColor = mix(vec4(skyColour, 1.0), OutColor, visibility) * LightColorResult;
} 