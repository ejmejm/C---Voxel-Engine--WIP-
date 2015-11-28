#version 330 core

layout (location = 0) out vec4 color;

uniform vec4 light_color;

in DATA
{
	vec4 color;
	vec3 normal;
	vec3 toLight;
} fs_in;

void main(){
	vec3 unitToLight = normalize(fs_in.toLight);
	vec3 unitNormal = normalize(fs_in.normal);

	float nDotL = dot(unitToLight, unitNormal);
	float intensity = max(nDotL, 0.2f);
	vec4 diffuse = intensity * light_color;

	color = fs_in.color * diffuse;
}