#pragma once

#include "renderable3D.h"

namespace edan{
	namespace graphics{

		class StaticCube : public Renderable3D
		{
		private:
			VertexArray *m_VertexArray;
			IndexBuffer *m_IndexBuffer;
			Shader &m_Shader;
		public:
			StaticCube(float x, float y, float z, float sideLength, const math::vec4 &color, Shader &shader);
			~StaticCube();
			inline const VertexArray *getVAO() const { return m_VertexArray; }
			inline const IndexBuffer *getIBO() const { return m_IndexBuffer; }
			inline Shader &getShader() const { return m_Shader; }
		};

	}
}