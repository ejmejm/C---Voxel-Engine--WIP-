#pragma once

#include "renderable2D.h"

namespace edan{
	namespace graphics{

		class Sprite : public Renderable2D
		{
		private:
		public:
			Sprite(float x, float y, float width, float height, const math::vec4 &color);
		};

	}
}