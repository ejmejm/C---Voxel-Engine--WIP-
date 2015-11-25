#include "batch2Drenderer.h"

namespace edan{
	namespace graphics{

		Batch2DRenderer::Batch2DRenderer()
		{
			init();
		}

		Batch2DRenderer::~Batch2DRenderer()
		{
			delete m_IBO;
			glDeleteBuffers(1, &m_VBO);
		}

		void Batch2DRenderer::init()
		{
			glGenVertexArrays(1, &m_VAO);
			glGenBuffers(1, &m_VBO);

			glBindVertexArray(m_VAO);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
			glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
			glEnableVertexAttribArray(SHADER_COLOR_INDEX);
			glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*) 0);
			glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::color)));
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			GLushort indices[RENDERER_INDICES_SIZE];
			
			int offset = 0;
			for (int i = 0; i < RENDERER_INDICES_SIZE; i += 6)
			{
				indices[  i  ] = 0 + offset;
				indices[i + 1] = 1 + offset;
				indices[i + 2] = 2 + offset;

				indices[i + 3] = 2 + offset;
				indices[i + 4] = 3 + offset;
				indices[i + 5] = 0 + offset;

				offset += 4;
			}

			m_IBO = new IndexBuffer(indices, RENDERER_INDICES_SIZE);

			glBindVertexArray(0);
		}

		void Batch2DRenderer::begin()
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			m_Buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		}

		void Batch2DRenderer::submit(const Renderable2D *renderable)
		{
			const math::vec3 &position = renderable->getPosition();
			const math::vec2 &size = renderable->getSize();
			const math::vec4 &color = renderable->getColor();

			int r = color.x * 255.0f;
			int g = color.y * 255.0f;
			int b = color.z * 255.0f;
			int a = color.w * 255.0f;

			unsigned int c = a << 24 | b << 16 | g << 8 | r;

			m_Buffer->vertex = position;
			m_Buffer->color = c;
			m_Buffer++;

			m_Buffer->vertex = math::vec3(position.x, position.y + size.y, position.z);
			m_Buffer->color = c;
			m_Buffer++;

			m_Buffer->vertex = math::vec3(position.x + size.x, position.y + size.y, position.z);
			m_Buffer->color = c;
			m_Buffer++;

			m_Buffer->vertex = math::vec3(position.x + size.x, position.y, position.z);
			m_Buffer->color = c;
			m_Buffer++;

			m_IndexCount += 6;
		}

		void Batch2DRenderer::end()
		{
			glUnmapBuffer(GL_ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void Batch2DRenderer::flush()
		{
			glBindVertexArray(m_VAO);
			m_IBO->bind();

			glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_SHORT, NULL);

			m_IBO->unbind();
			glBindVertexArray(0);

			m_IndexCount = 0;
		}
	}
}