#include "chunk.h"

namespace edan
{

	// -- Reference a value from a matrix as: [(x * m_Height + y) * m_Width + z] -- \\

	Chunk::Chunk(std::vector<Block> blocks, math::vec3 centerPoint, float width, float height, float length)
		: m_Position(centerPoint), m_Width(width), m_Height(height), m_Length(length)
	{
		m_Blocks.resize(width * height * length);

		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < width; j++)
			{
				for (int k = 0; k < width; k++)
				{
					m_Blocks[(i * height + j) * width + k] = blocks[(i * height + j) * width + k];
				}
			}
		}
	}

	Chunk::Chunk(math::vec3 centerPoint, float width, float height, float length)
		: m_Position(centerPoint), m_Width(width), m_Height(height), m_Length(length)
	{
		m_Blocks.resize(width * height * length);
	}

	Chunk::Chunk(math::vec3 centerPoint)
		: m_Position(centerPoint)
	{
		m_Blocks.resize(16 * 64 * 16);
	}

	void Chunk::insertBlock(const Block &block)
	{
		math::vec3 relativePos = block.getPosition() - m_Position; // Realtive position of block to the chunk
		m_Blocks[(relativePos.x * m_Height + relativePos.y) * m_Width + relativePos.z] = block;
	}

	void Chunk::insertBlock(const int &x, const int &y, const int &z, const Block &block)
	{
		m_Blocks[(x * m_Height + y) * m_Width + z] = block;	// If you are inserting manually with this be VERY CAREFULL.
	}														//If the position is not right for the chunk you will get an error... I think

	void Chunk::insertBlocks(const std::vector<Block> &blocks)
	{
		for (int i = 0; i < blocks.size(); i++)
		{
			math::vec3 relativePos = blocks[i].getPosition() - m_Position; // Realtive position of block to the chunk
			m_Blocks[(relativePos.x * m_Height + relativePos.y) * m_Width + relativePos.z] = blocks[i];
		}
	}

}