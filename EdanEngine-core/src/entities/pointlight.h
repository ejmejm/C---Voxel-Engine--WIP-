#pragma once

#include "entity.h"
#include "../math/math.h"
#include "../graphics/shader.h"

namespace edan
{

	class PointLight : public Entity
	{
	private:
		math::vec4 m_Color;
		graphics::Shader m_Shader;
	public:
		PointLight(math::vec3 position, math::vec4 color, graphics::Shader shader);
		void render();
	};

}