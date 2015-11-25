#include "cube.h"

namespace edan{
	namespace graphics{

		Cube::Cube(float x, float y, float z, float sideLength, const math::vec4 &color)
			: Renderable3D(math::vec3(x, y, z), sideLength, color)
		{ }

	}
}