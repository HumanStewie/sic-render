#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 ambient;
out vec3 diffuse; 
out vec3 specular;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightPos;
uniform vec3 lightColor;

void main()
{
	vec3 Normal = mat3(transpose(inverse(view))) * aNormal;
	vec3 FragPos = vec3(view * vec4(aPos, 1.0)); 
	vec3 LightPos = vec3(view * vec4(lightPos, 1.0));

    float ambientStrength = 0.2;
    ambient = lightColor * ambientStrength;

    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(LightPos - FragPos);
    diffuse = max(0.0, dot(normal, lightDir)) * lightColor;
    
    float specularStrength = 0.9;
    vec3 viewDir = normalize(-FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 128);
    specular = specularStrength * spec * lightColor;

	gl_Position = projection * view * model * vec4(aPos, 1.0);
}