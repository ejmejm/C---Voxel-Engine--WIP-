#pragma once

#include "renderable3D.h"

namespace edan{
	namespace graphics{

		class Renderer3D
		{
		protected:
			virtual void submit(const Renderable3D *renderable) = 0;
			virtual void flush() = 0;
		};

	}
}