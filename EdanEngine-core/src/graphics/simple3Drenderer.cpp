#include "simple3Drenderer.h"

namespace edan{
	namespace graphics{

		void Simple3DRenderer::submit(const Renderable3D *renderable)
		{
			m_RenderQueue.push_back((StaticCube*)renderable);
		}

		void Simple3DRenderer::flush()
		{
			while (!m_RenderQueue.empty())
			{
				const StaticCube *sprite = m_RenderQueue.front();
				sprite->getVAO()->bind();
				sprite->getIBO()->bind();

				sprite->getShader().setUniformMat4("ml_matrix", math::mat4::translation(sprite->getPosition()));
				glDrawElements(GL_TRIANGLES, sprite->getIBO()->getCount(), GL_UNSIGNED_SHORT, nullptr);

				sprite->getIBO()->unbind();
				sprite->getVAO()->unbind();

				m_RenderQueue.pop_front();
			}
		}

	}
}