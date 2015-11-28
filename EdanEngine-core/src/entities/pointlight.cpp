#include "pointlight.h"

namespace edan
{

	PointLight::PointLight(math::vec3 position, math::vec4 color, graphics::Shader shader)
		: Entity(position), m_Color(color), m_Shader(shader) { }

	void PointLight::render()
	{
		m_Shader.setUniform3f("light_pos", position);
		m_Shader.setUniform4f("light_color", m_Color);
	}

}