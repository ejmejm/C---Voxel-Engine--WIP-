#include "batch3Drenderer.h"

namespace edan{
	namespace graphics{

		Batch3DRenderer::Batch3DRenderer()
		{
			init();
		}

		Batch3DRenderer::~Batch3DRenderer()
		{
			delete m_IBO;
			glDeleteBuffers(1, &m_VBO);
		}

		void Batch3DRenderer::init()
		{
			glGenVertexArrays(1, &m_VAO);
			glGenBuffers(1, &m_VBO);

			glBindVertexArray(m_VAO);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
			glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
			glEnableVertexAttribArray(SHADER_COLOR_INDEX);
			glEnableVertexAttribArray(SHADER_NORMAL_INDEX);
			glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
			glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData3D, VertexData3D::color)));
			glVertexAttribPointer(SHADER_NORMAL_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData3D, VertexData3D::normal)));
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			GLushort indices[RENDERER_INDICES_SIZE];

			int offset = 0;
			for (int i = 0; i < RENDERER_INDICES_SIZE; i += 36)
			{
				indices[i +  0] = 0 + offset;
				indices[i +  1] = 1 + offset;
				indices[i +  2] = 2 + offset;
				indices[i +  3] = 2 + offset;
				indices[i +  4] = 3 + offset;
				indices[i +  5] = 0 + offset;

				indices[i +  6] = 3 + offset;
				indices[i +  7] = 2 + offset;
				indices[i +  8] = 6 + offset;
				indices[i +  9] = 6 + offset;
				indices[i + 10] = 7 + offset;
				indices[i + 11] = 3 + offset;

				indices[i + 12] = 7 + offset;
				indices[i + 13] = 6 + offset;
				indices[i + 14] = 5 + offset;
				indices[i + 15] = 5 + offset;
				indices[i + 16] = 4 + offset;
				indices[i + 17] = 7 + offset;

				indices[i + 18] = 4 + offset;
				indices[i + 19] = 0 + offset;
				indices[i + 20] = 3 + offset;
				indices[i + 21] = 3 + offset;
				indices[i + 22] = 7 + offset;
				indices[i + 23] = 4 + offset;

				indices[i + 24] = 0 + offset;
				indices[i + 25] = 1 + offset;
				indices[i + 26] = 5 + offset;
				indices[i + 27] = 5 + offset;
				indices[i + 28] = 4 + offset;
				indices[i + 29] = 0 + offset;

				indices[i + 30] = 1 + offset;
				indices[i + 31] = 5 + offset;
				indices[i + 32] = 6 + offset;
				indices[i + 33] = 6 + offset;
				indices[i + 34] = 2 + offset;
				indices[i + 35] = 1 + offset;

				offset += 8;
			}

			m_IBO = new IndexBuffer(indices, RENDERER_INDICES_SIZE);

			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);

			glBindVertexArray(0);
		}

		void Batch3DRenderer::begin()
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			m_Buffer = (VertexData3D*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		}

		void Batch3DRenderer::submit(const Renderable3D *renderable)
		{
			const math::vec3 &position = renderable->getPosition();
			const float &size = renderable->getSize();
			const math::vec4 &color = renderable->getColor();

			int r = color.x * 255.0f;
			int g = color.y * 255.0f;
			int b = color.z * 255.0f;
			int a = color.w * 255.0f;

			unsigned int c = a << 24 | b << 16 | g << 8 | r;

			m_Buffer->vertex = math::vec3(position.x, position.y, position.z + size);
			m_Buffer->color = c;
			m_Buffer->normal = math::vec3(-1.0f, -1.0f, 1.0f);
			m_Buffer++;

			m_Buffer->vertex = math::vec3(position.x + size, position.y, position.z + size);
			m_Buffer->color = c;
			m_Buffer->normal = math::vec3(1.0f, -1.0f, 1.0f);
			m_Buffer++;

			m_Buffer->vertex = math::vec3(position.x + size, position.y + size, position.z + size);
			m_Buffer->color = c;
			m_Buffer->normal = math::vec3(1.0f, 1.0f, 1.0f);
			m_Buffer++;

			m_Buffer->vertex = math::vec3(position.x, position.y + size, position.z + size);
			m_Buffer->color = c;
			m_Buffer->normal = math::vec3(-1.0f, 1.0f, 1.0f);
			m_Buffer++;

			m_Buffer->vertex = math::vec3(position.x, position.y, position.z);
			m_Buffer->color = c;
			m_Buffer->normal = math::vec3(-1.0f, -1.0f, -1.0f);
			m_Buffer++;

			m_Buffer->vertex = math::vec3(position.x + size, position.y, position.z);
			m_Buffer->color = c;
			m_Buffer->normal = math::vec3(1.0f, -1.0f, -1.0f);
			m_Buffer++;

			m_Buffer->vertex = math::vec3(position.x + size, position.y + size, position.z);
			m_Buffer->color = c;
			m_Buffer->normal = math::vec3(1.0f, 1.0f, -1.0f);
			m_Buffer++;

			m_Buffer->vertex = math::vec3(position.x, position.y + size, position.z);
			m_Buffer->color = c;
			m_Buffer->normal = math::vec3(-1.0f, 1.0f, -1.0f);
			m_Buffer++;

			if (m_IndexCount >= RENDERER_INDICES_SIZE)
			{
				end();
				flush();
				begin();
			}

			m_IndexCount += 36;
		}

		void Batch3DRenderer::end()
		{
			glUnmapBuffer(GL_ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void Batch3DRenderer::flush()
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