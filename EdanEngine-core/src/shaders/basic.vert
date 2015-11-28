#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec3 normal;

uniform mat4 pr_matrix = mat4(1.0);
uniform mat4 vw_matrix = mat4(1.0);
uniform mat4 ml_matrix = mat4(1.0);

uniform vec3 light_pos;

out DATA
{
	vec4 color;
	vec3 normal;
	vec3 toLight;
} vs_out;

void main(){
	vec4 worldPosition = ml_matrix * position;
	gl_Position = pr_matrix * vw_matrix * worldPosition;
	vs_out.color = color;
	vs_out.normal = (ml_matrix * vec4(normal, 0.0f)).xyz;
	vs_out.toLight = light_pos - (worldPosition.xyz);
}