#pragma once

#include "../math/math.h"
#include "../graphics/shader.h"
#include "entity.h"

namespace edan
{

	class Camera : public Entity
	{

	private:
		graphics::Shader m_Shader;
	public:
		float pitch, yaw, roll;
	public:
		Camera(math::vec3 _position, float _pitch, float _yaw, float _roll, graphics::Shader shader);

		void updateView();
	};

}