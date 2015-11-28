#pragma once

#include "../math/math.h"
#include "../blocks/block.h"

namespace edan
{

	class Chunk
	{
	private:
		math::vec3 m_Position; //Chunk coordinates are mapped the same as cube coordinates
		float m_Width, m_Length, m_Height; //Bounding region, m_Width = x, m_Length = z, m_Height = y
		std::vector<Block> m_Blocks;
	private:
		void insertBlock(const Block &block);											// Insering should really only 
		void insertBlock(const int &x, const int &y, const int &z, const Block &block); // be done through the World because 
		void insertBlocks(const std::vector<Block> &blocks);							//	of the fragility of this system
	public:
		Chunk(std::vector<Block> blocks, math::vec3 centerPoint, float width, float height, float length); //Could lead to being out of bounds if blocks is bigger than the defined width * length * height
		Chunk(math::vec3 centerPoint, float width, float height, float length); //Default chunk size is 16 * 64 * 16
		Chunk(math::vec3 centerPoint); //Default chunk size is 16 * 64 * 16
	};

}