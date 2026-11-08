#version 460 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float shininess;
};

struct DirectionLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float cutOff;
    float outerCutOff;
};

uniform Material material;
uniform DirectionLight dirLight;
uniform PointLight pointLights[4];
uniform SpotLight light3;
uniform vec3 viewPos;
uniform float time;

float attenu(vec3 lightPos, float constant, float linear, float quadra) {
    float dist = distance(lightPos, FragPos);
    return 1.0 / (constant + linear * dist + quadra * pow(dist, 2));
}
vec3 directionalShading(DirectionLight light) {
    vec3 ambient = vec3(0);
    vec3 diffuse = vec3(0);
    vec3 specular = vec3(0);
    ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(-light.direction);
    // vec3 diffuse = max(0.0, dot(normal, lightDir)) * material.diffuse * light.diffuse;
    diffuse = light.diffuse * max(0.0, dot(normal, lightDir)) * vec3(texture(material.diffuse, TexCoords));
    
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    specular = vec3(texture(material.specular, TexCoords)) * spec * light.specular;

    return ambient + diffuse + specular;
}
vec3 pointShading(PointLight light) {
    vec3 ambient = vec3(0);
    vec3 diffuse = vec3(0);
    vec3 specular = vec3(0);

    ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    // vec3 diffuse = max(0.0, dot(normal, lightDir)) * material.diffuse * light.diffuse;
    diffuse = light.diffuse * max(0.0, dot(normal, lightDir)) * vec3(texture(material.diffuse, TexCoords));
    
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    specular = vec3(texture(material.specular, TexCoords)) * spec * light.specular;

    float attenuation = attenu(light.position, 1.0, 0.09, 0.032);
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return ambient + diffuse + specular;
}
vec3 spotShading(SpotLight light) {
    vec3 ambient = vec3(0);
    vec3 diffuse = vec3(0);
    vec3 specular = vec3(0);

    ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    // vec3 diffuse = max(0.0, dot(normal, lightDir)) * material.diffuse * light.diffuse;
    diffuse = light.diffuse * max(0.0, dot(normal, lightDir)) * vec3(texture(material.diffuse, TexCoords));
    
    vec3 viewDir = normalize(viewPos - FragPos); // already works as spotlight direction
    vec3 reflectDir = reflect(-lightDir, normal);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    specular = vec3(texture(material.specular, TexCoords)) * spec * light.specular;
    
    

    float theta = dot(normalize(-light.direction), lightDir);
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = (theta - light.outerCutOff) / epsilon;
    diffuse *= intensity;
    specular *= intensity;
    float attenuation = attenu(light.position, 1.0, 0.09, 0.032);
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    vec3 lighting = ambient + diffuse + specular;
    
    return lighting;
}
void main()
{
    vec3 lighting = vec3(0);
    lighting += directionalShading(dirLight);
    
    for (int i = 0; i < 4; i++) {
        lighting += pointShading(pointLights[i]);
    }

    lighting += spotShading(light3);
    vec3 emission = vec3(0);
    if (vec3(texture(material.specular, TexCoords)) == vec3(0)) {
        emission = vec3(texture(material.emission, vec2(TexCoords.x, TexCoords.y + time))) * 2.0;
    }
    FragColor = vec4(lighting, 1.0);
}