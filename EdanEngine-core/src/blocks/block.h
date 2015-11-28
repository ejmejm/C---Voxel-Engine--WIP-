#pragma once

#include "../graphics/cube.h"

namespace edan
{

	class Block : public graphics::Cube
	{
	private:
		float lightValue;
	public:
		Block(float x, float y, float z, const math::vec4 &color);
		Block();
		~Block() { }
		inline const float &const getLightValue() const { return lightValue; }
	};

}