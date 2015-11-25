#pragma once

#include <deque>
#include "renderer3D.h"
#include "staticcube.h"

namespace edan{
	namespace graphics{

		class Simple3DRenderer : public Renderer3D
		{
		private:
			std::deque<const StaticCube*> m_RenderQueue;
		public:
			void submit(const Renderable3D *renderable);
			void flush();
		};

	}
}