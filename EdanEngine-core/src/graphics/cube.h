#pragma once

#include "renderable3D.h"

namespace edan{
	namespace graphics{

		class Cube : public Renderable3D
		{
		private:
		public:
			Cube(float x, float y, float z, float sideLength, const math::vec4 &color);
		};

	}
}