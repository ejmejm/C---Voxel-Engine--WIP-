/*

*Currently working on an array based system
*instead of an octtree system.
*I might come back to test an octtree system,
*but I think arrays will be more efficient

#include "octTree.h"

namespace edan
{

	OctTree::OctTree(std::vector<graphics::Renderable3D*> objects, math::vec3 centerPoint, float sideLength)
		: m_Objects(objects), m_CenterPoint(centerPoint), m_SideLength(sideLength)
	{ }

	OctTree::OctTree(std::vector<graphics::Renderable3D*> objects)
		: m_Objects(objects)
	{ }

	OctTree::OctTree(math::vec3 centerPoint, float sideLength)
		: m_CenterPoint(centerPoint), m_SideLength(sideLength)
	{ }

}
*/