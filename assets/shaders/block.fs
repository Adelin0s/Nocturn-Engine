#version 460 core

out vec4 OutColor;

in vec3 FragPos;  
in vec2 textureCoords;
in float fLightLevel;
in float fSkyLightLevel;
in float visibility;

uniform sampler2D textureSampler;
uniform vec3 uLightPos;
uniform vec3 uViewPos;
uniform vec3 uObjectColor;

void main()
{
    vec3 Normal = vec3(1.0f, 1.0f, 1.0f);

    // ambient 
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * vec3(1.0f);
  	
    // diffuse 
    vec3 norm = normalize(Normal); 
    vec3 lightDir = normalize(uLightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * vec3(1.0f);
    
    float sunlightIntensity = lightDir.y * 0.96f;
    float skyLevel = max(float(fSkyLightLevel) * sunlightIntensity, 7.0f);
	float combinedLightLevel = max(skyLevel, float(fLightLevel));
    
    float baseLightColor = .04;
	float lightIntensity = pow(clamp(combinedLightLevel / 31.0, 0.006, 1.0f), 1.4) + baseLightColor;
	vec4 lightColor = vec4(vec3(lightIntensity), 1.0) * vec4(uObjectColor, 1.0);

    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(uViewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * vec3(1.0f);  
        
    vec3 result = (ambient + diffuse + specular) * uObjectColor;
    vec4 LightColorResult = vec4(result, 1.0);

    vec3 skyColour = vec3(0.5, 0.5, 0.5);
    OutColor = texture(textureSampler, textureCoords);
	OutColor = mix(vec4(skyColour, 1.0), OutColor, visibility) * LightColorResult;
} 