#version 460 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

void main()
{
    float ambientStrength = 0.2;
    vec3 ambient = lightColor * ambientStrength;
 
    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 diffuse = max(0.0, dot(normal, lightDir)) * lightColor;
    
    vec3 lighting = ambient + diffuse;
    
    FragColor = vec4(lighting * objectColor, 1.0);
}