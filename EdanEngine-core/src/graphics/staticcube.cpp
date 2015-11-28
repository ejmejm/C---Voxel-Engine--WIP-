#include "staticcube.h"

namespace edan {
	namespace graphics{

		StaticCube::StaticCube(float x, float y, float z, float sideLength, const math::vec4 &color, Shader &shader)
			: Renderable3D(math::vec3(x, y, 0), sideLength, color), m_Shader(shader)
		{
			m_VertexArray = new VertexArray();

			GLfloat vertices[] =
			{
				0, 0, sideLength,
				sideLength, 0, sideLength,
				sideLength, sideLength, sideLength,
				0, sideLength, sideLength,
				0, 0, 0,
				sideLength, 0, 0,
				sideLength, sideLength, 0,
				0, sideLength, 0
			};

			GLfloat normals[] =
			{
				-1.0f, -1.0f, 1.0f,
				1.0f, -1.0f, 1.0f,
				1.0f, 1.0f, 1.0f,
				-1.0f, 1.0f, 1.0f,
				-1.0f, -1.0f, -1.0f,
				1.0f, -1.0f, -1.0f,
				1.0f, 1.0f, -1.0f,
				-1.0f, 1.0f, -1.0f
			};

			GLfloat colors[] =
			{
				color.x, color.y, color.z, color.w,
				color.x, color.y, color.z, color.w,
				color.x, color.y, color.z, color.w,
				color.x, color.y, color.z, color.w,
				color.x, color.y, color.z, color.w,
				color.x, color.y, color.z, color.w,
				color.x, color.y, color.z, color.w,
				color.x, color.y, color.z, color.w
			};

			m_VertexArray->addBuffer(new Buffer(vertices, 8 * 3, 3), 0);
			m_VertexArray->addBuffer(new Buffer(colors, 8 * 4, 4), 1);
			m_VertexArray->addBuffer(new Buffer(normals, 8 * 3, 3), 2);

			GLushort indices[] = { 
				0, 1, 2, 2, 3, 0,
				3, 2, 6, 6, 7, 3,
				7, 6, 5, 5, 4, 7,
				4, 0, 3, 3, 7, 4,
				0, 1, 5, 5, 4, 0,
				1, 5, 6, 6, 2, 1 
			};

			m_IndexBuffer = new IndexBuffer(indices, 36);
		}

		StaticCube::~StaticCube()
		{
			delete m_VertexArray;
			delete m_IndexBuffer;
		}

	}
}