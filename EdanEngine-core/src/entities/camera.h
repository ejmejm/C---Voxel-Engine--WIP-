#pragma once

#include "../math/math.h"
#include "../graphics/shader.h"

namespace edan
{

	class Camera
	{
	public:
		math::vec3 position;
		float pitch, yaw, roll;

		graphics::Shader m_Shader;

	public:
		Camera(math::vec3 _position, float _pitch, float _yaw, float _roll, graphics::Shader shader);

		void updateView();
	};

}