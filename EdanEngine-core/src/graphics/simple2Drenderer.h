#pragma once

#include <deque>
#include "renderer2D.h"
#include "staticsprite.h"

namespace edan{
	namespace graphics{

		class Simple2DRenderer : public Renderer2D
		{
		private:
			std::deque<const StaticSprite*> m_RenderQueue;
		public:
			void submit(const Renderable2D *renderable);
			void flush();
		};

	}
}