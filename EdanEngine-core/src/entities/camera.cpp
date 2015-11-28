#include "camera.h"

namespace edan
{

	Camera::Camera(math::vec3 _position, float _pitch, float _yaw, float _roll, graphics::Shader shader)
		: Entity(_position),pitch(_pitch), yaw(_yaw), roll(_roll), m_Shader(shader) { }

	void Camera::updateView()
	{
		m_Shader.setUniformMat4("vw_matrix", math::mat4::view(position, yaw, pitch, roll));
	}
}