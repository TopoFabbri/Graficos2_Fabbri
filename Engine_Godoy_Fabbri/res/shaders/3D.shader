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
vec3 position;
vec3 ambient;
vec3 diffuse;
vec3 specular;

vec3 attenuation;
};

in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

uniform Material material;
uniform Light light;
uniform vec3 viewPos;

void main()
{
vec3 ambient = light.ambient * material.ambient;

vec3 norm = normalize(Normal);
vec3 lightDir = normalize(light.position - FragPos);
// vec3 lightDir = normalize(-light.direction);
float diff = max(dot(norm, lightDir), 0.0);
vec3 diffuse = light.diffuse * (diff * material.diffuse);

vec3 viewDir = normalize(viewPos - FragPos);
vec3 reflectDir = reflect(-lightDir, norm);
float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
vec3 specular = light.specular * (spec * material.specular);

float constant = light.attenuation.x;
float linear = light.attenuation.y;
float quadratic = light.attenuation.z;

float distance = length(light.position - FragPos);
float attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance));   

ambient  *= attenuation; 
diffuse  *= attenuation;
specular *= attenuation; 

vec3 result = ambient + diffuse + specular;

FragColor = vec4(result, 1.0);
};