#include "block.h"

namespace edan
{

	Block::Block(float x, float y, float z, const math::vec4 &color)
		: Cube(x, y, z, 1.0f, color), lightValue(0.0f)
	{ }

	Block::Block()
		: Cube(NULL, NULL, NULL, NULL, math::vec4(NULL, NULL, NULL, NULL)), lightValue(NULL)
	{ }
}