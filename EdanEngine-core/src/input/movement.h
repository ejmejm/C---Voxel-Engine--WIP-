#pragma once

#include "../graphics/window.h"
#include "../entities/camera.h"

namespace edan
{
	class Movement
	{
	public:
		static void movementUpdate(const graphics::Window &window, Camera &camera, const float &speed, const double &delta, const double &deltaX, const double &deltaY)
		{
			math::vec3 direction = math::vec3(-cos(math::toRadians((camera.pitch + 90))), 0, -cos(math::toRadians(camera.pitch))).norm();
			math::vec3 directionlr = math::vec3(-cos(math::toRadians((camera.pitch + 90 + 90))), 0, -cos(math::toRadians(camera.pitch + 90))).norm();

			double ds = speed * delta;

			if (window.isKeyPressed(GLFW_KEY_W))
			{
				camera.position += math::vec3(ds * direction.x, ds * direction.y, ds * direction.z);
			}
			if (window.isKeyPressed(GLFW_KEY_S))
			{
				camera.position -= math::vec3(ds * direction.x, ds * direction.y, ds * direction.z);
			}
			if (window.isKeyPressed(GLFW_KEY_A))
			{
				camera.position -= math::vec3(ds * directionlr.x, ds * directionlr.y, ds * directionlr.z);
			}
			if (window.isKeyPressed(GLFW_KEY_D))
			{
				camera.position += math::vec3(ds * directionlr.x, ds * directionlr.y, ds * directionlr.z);
			}
			if (window.isKeyPressed(GLFW_KEY_SPACE))
			{
				camera.position.y += speed * delta;
			}
			if (window.isKeyPressed(GLFW_KEY_LEFT_SHIFT) || window.isKeyPressed(GLFW_KEY_RIGHT_SHIFT))
			{
				camera.position.y -= speed * delta;
			}

			camera.yaw += speed * delta * deltaY * 80;
			camera.pitch += speed * delta * deltaX * 80;

			if (window.isKeyPressed(GLFW_KEY_ESCAPE))
			{
				window.close();
			}
		}
	};

}