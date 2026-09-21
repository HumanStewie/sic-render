#version 460 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec3 LightPos;
in vec2 TexCoords;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform Light light1;
uniform Light light2;
uniform vec3 viewPos;
uniform float time;

vec3 phongShading(Light light, float radius) {
    float dist = distance(FragPos, light.position);

    vec3 ambient = vec3(0);
    vec3 diffuse = vec3(0);
    vec3 specular = vec3(0);
    if (dist < radius) {
        ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

        vec3 normal = normalize(Normal);
        vec3 lightDir = normalize(light.position - FragPos);
        // vec3 diffuse = max(0.0, dot(normal, lightDir)) * material.diffuse * light.diffuse;
        diffuse = light.diffuse * max(0.0, dot(normal, lightDir)) * vec3(texture(material.diffuse, TexCoords));
        
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, normal);  
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        specular = vec3(texture(material.specular, TexCoords)) * spec * light.specular;
    }

    return ambient + diffuse + specular;
}
void main()
{
    vec3 phong1 = phongShading(light1, 5.0);
    vec3 phong2 = phongShading(light2, 5.0);
    vec3 emission = vec3(0);
    if (vec3(texture(material.specular, TexCoords)) == vec3(0)) {
        emission = vec3(texture(material.emission, vec2(TexCoords.x, TexCoords.y + time))) * 2.0;
    }
    vec3 lighting = phong1 + phong2 + emission;
    FragColor = vec4(lighting, 1.0);
}