#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;

uniform mat4 u_Transform;

void main()
{
	gl_Position = u_Transform * position;
}

#shader fragment
#version 330 core

out vec4 fragColor;

uniform vec4 u_Color;
uniform vec3 lightColor;
uniform float ambientStrength;

void main()
{
	vec3 ambient = ambientStrength * lightColor;
	vec4 res = vec4(ambient * vec3(u_Color.x, u_Color.y, u_Color.z), u_Color.w);
	
	fragColor = u_Color * res;
};