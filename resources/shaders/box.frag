#version 460 core
out vec4 FragColor;

in vec3 ambient;
in vec3 diffuse; 
in vec3 specular;

uniform vec3 objectColor;

void main()
{
    vec3 lighting = ambient + diffuse + specular;
    FragColor = vec4(lighting * objectColor, 1.0);
}