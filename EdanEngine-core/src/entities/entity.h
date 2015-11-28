#pragma once

#include "../math/math.h"

namespace edan
{

	class Entity
	{
	public:
		math::vec3 position;
	public:
		Entity(math::vec3 _position);
	};

}