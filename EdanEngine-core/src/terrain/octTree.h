/*

*Currently working on an array based system
*instead of an octtree system.
*I might come back to test an octtree system,
*but I think arrays will be more efficient

#pragma once

#include "../math/math.h"
#include "../graphics/renderable3D.h"
#include <vector>

namespace edan
{

	class OctTree
	{
	private:
		const int m_MinSize = 1;
		OctTree *m_childNodes[8];
		OctTree *m_Parent;
		math::vec3 m_CenterPoint;
		float m_SideLength;
		std::vector<graphics::Renderable3D*> m_Objects;
	public:
		OctTree(std::vector<graphics::Renderable3D*> objects, math::vec3 centerPoint, float sideLength);
		OctTree(std::vector<graphics::Renderable3D*> objects);
		OctTree(math::vec3 centerPoint, float sideLength);
		OctTree();
		~OctTree() { }
	};

}
*/