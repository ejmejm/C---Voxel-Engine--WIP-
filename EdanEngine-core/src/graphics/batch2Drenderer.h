#pragma once

#include <cstddef>
#include "renderer2D.h"
#include "buffers/indexbuffer.h"

namespace edan{
	namespace graphics{

#define RENDERER_MAX_SPRITES	60000
#define RENDERER_VERTEX_SIZE	sizeof(VertexData)
#define RENDERER_SPRITE_SIZE	RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE	RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE	RENDERER_MAX_SPRITES * 6

#define SHADER_VERTEX_INDEX 0
#define SHADER_COLOR_INDEX 1

		class Batch2DRenderer : public Renderer2D
		{
		private:
			GLuint m_VBO, m_VAO;
			VertexData *m_Buffer;
			IndexBuffer *m_IBO;
			GLsizei m_IndexCount;
		public:
			Batch2DRenderer();
			~Batch2DRenderer();
			void begin();
			void submit(const Renderable2D *renderable) override;
			void end();
			void flush() override;
		private:
			void init();
		};

	}
}