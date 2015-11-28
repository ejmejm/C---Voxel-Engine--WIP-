#pragma once

#include "buffers/buffer.h"
#include "buffers/indexbuffer.h"
#include "buffers/vertexarray.h"
#include "shader.h"
#include "../math/math.h"


namespace edan{
	namespace graphics{
		
		struct VertexData3D
		{
			math::vec3 vertex;
			unsigned int color;
			math::vec3 normal;
		};

		class Renderable3D
		{
		protected:
			math::vec3 m_Position;
			float m_Size;
			math::vec4 m_Color;
		public:
			Renderable3D(math::vec3 position, float size, math::vec4 color)
				: m_Position(position), m_Size(size), m_Color(color) { }

			~Renderable3D() { }

			inline const math::vec3 &getPosition() const { return m_Position; }
			inline const float &getSize() const { return m_Size; }
			inline const math::vec4 &getColor() const { return m_Color; }

			inline void setPosition(math::vec3 position) { m_Position = position; }
			inline void setSize(float size) { m_Size = size; }
			inline void setColor(math::vec4 color) { m_Color = color; }
		};


	}
}