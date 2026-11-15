#version 460 core

struct StandardMaterial {
    sampler2D albedoMap;
    sampler2D normalMap;
    sampler2D specularMap;
    sampler2D roughnessMap;
};

struct Light {
    vec3 position;
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float cutOff;
    float outerCutOff;

    uint type;
};

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform StandardMaterial material;
uniform Light dirLight;
uniform vec3 viewPos;
uniform float time;

const uint DirLight = 0u;
const uint PointLight = 1u;
const uint SpotLight = 2u;

vec3 normal;

float attenu(vec3 lightPos, float constant, float linear, float quadra) {
    float dist = distance(lightPos, FragPos);
    return 1.0 / (constant + linear * dist + quadra * pow(dist, 2));
}
vec3 calculatePhong(Light light) {
    vec3 ambient = vec3(0);
    vec3 diffuse = vec3(0);
    vec3 specular = vec3(0);
    ambient = light.ambient * vec3(texture(material.albedoMap, TexCoords));

    vec3 lightDir = light.type == DirLight ? normalize(-light.direction) : normalize(light.position - FragPos);
    // vec3 diffuse = max(0.0, dot(normal, lightDir)) * material.albedoMap * light.diffuse;
    diffuse = light.diffuse * max(0.0, dot(normal, lightDir)) * vec3(texture(material.albedoMap, TexCoords));

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    specular = vec3(texture(material.specularMap, TexCoords)) * spec * light.specular;

    if (light.type == SpotLight) {
        float theta = dot(normalize(-light.direction), lightDir);
        float epsilon = light.cutOff - light.outerCutOff;
        float intensity = smoothstep(0.0, 1.0, (theta - light.outerCutOff) / epsilon);
        diffuse *= intensity;
        specular *= intensity;
    }
    if (light.type != DirLight) {
        float attenuation = attenu(light.position, 1.0, 0.09, 0.032);
        ambient *= attenuation;
        diffuse *= attenuation;
        specular *= attenuation;
    }

    return ambient + diffuse + specular;
}

void main() {
    normal = normalize(Normal);
    if (dot(viewPos - FragPos, normal) < 0) discard;
    
    vec3 lighting = vec3(0);

    lighting += calculatePhong(dirLight);

    FragColor = vec4(lighting, 1);
    // FragColor = vec4(1, 0, 1, 1); 
}
