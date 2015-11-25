#pragma once

#include <cstddef>
#include "renderer3D.h"
#include "buffers/indexbuffer.h"

namespace edan{
	namespace graphics{

#define RENDERER_MAX_CUBES		10000
#define RENDERER_VERTEX_SIZE	sizeof(VertexData3D)
#define RENDERER_CUBES_SIZE		RENDERER_VERTEX_SIZE * 8
#define RENDERER_BUFFER_SIZE	RENDERER_CUBES_SIZE * RENDERER_MAX_CUBES
#define RENDERER_INDICES_SIZE	RENDERER_MAX_CUBES * 36

#define SHADER_VERTEX_INDEX 0
#define SHADER_COLOR_INDEX 1

		class Batch3DRenderer : public Renderer3D
		{
		private:
			GLuint m_VBO, m_VAO;
			VertexData3D *m_Buffer;
			IndexBuffer *m_IBO;
			GLsizei m_IndexCount;
		public:
			Batch3DRenderer();
			~Batch3DRenderer();
			void begin();
			void submit(const Renderable3D *renderable) override;
			void end();
			void flush() override;
		private:
			void init();
		};

	}
}