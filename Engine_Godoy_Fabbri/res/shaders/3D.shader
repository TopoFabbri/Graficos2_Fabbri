#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

out vec3 FragPos;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f);
    FragPos = vec3(model * vec4(position, 1.0f));
    Normal = mat3(transpose(inverse(model))) * normal;
}

#shader fragment
#version 330 core

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light
{
    int type;
    vec3 position;
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    vec3 attenuation;
    float cutoff;
    float outerCutoff;
};

vec3 calculateDirLight(Light pointLight);
vec3 calculatePointLight(Light pointLight);
vec3 calculateSpotLight(Light spotLight);

in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

uniform Material material;
uniform Light light;
uniform vec3 viewPos;

void main()
{
    vec3 calculatedLight;

    if (light.type == 0)
    {
        calculatedLight = calculateDirLight(light);
    }
    else if (light.type == 1)
    {
        calculatedLight = calculatePointLight(light);
    }
    else
    {
        calculatedLight = calculateSpotLight(light);
    }
    
    FragColor = vec4(calculatedLight, 1.0);
}

vec3 calculateDirLight(Light dirLight)
{
    vec3 ambient = dirLight.ambient * material.ambient;
    
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(dirLight.direction);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = dirLight.diffuse * (diff * material.diffuse);
    
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = dirLight.specular * (spec * material.specular);
    
    return ambient + diffuse + specular;
}

vec3 calculatePointLight(Light pointLight)
{
    vec3 ambient = pointLight.ambient * material.ambient;
    
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(pointLight.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = pointLight.diffuse * (diff * material.diffuse);
    
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = pointLight.specular * (spec * material.specular);
    
    float distance = length(pointLight.position - FragPos);
    float attenuation = 1.0 / (pointLight.attenuation.x + pointLight.attenuation.y * distance + pointLight.attenuation.z * distance * distance);
    
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    
    return ambient + diffuse + specular;
}

vec3 calculateSpotLight(Light spotLight)
{
    vec3 ambient = spotLight.ambient * material.ambient;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(spotLight.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = spotLight.diffuse * (diff * material.diffuse);

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = spotLight.specular * (spec * material.specular);
    
    float theta = dot(lightDir, normalize(-spotLight.direction));
    float epsilon = (spotLight.cutoff - spotLight.outerCutoff);
    float intensity = clamp((theta - spotLight.outerCutoff) / epsilon, 0.0, 1.0);
    
    diffuse  *= intensity;
    specular *= intensity;
    
    float distance = length(spotLight.position - FragPos);
    float attenuation = 1.0 / (spotLight.attenuation.x + spotLight.attenuation.y * distance + spotLight.attenuation.z * distance * distance);

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    
    return ambient + diffuse + specular;
}