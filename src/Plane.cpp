#include "Plane.h"
#include "glm/glm.hpp"

// d -- c
// |    |
// a -- b
Plane::Plane(const glm::vec3 a, const glm::vec3 b, const glm::vec3 c, const glm::vec3 d)
{
	m_t1 = std::make_unique<Triangle>
		(
			a,
			b,
			c
		);

	m_t1 = std::make_unique<Triangle>
		(
			a,
			c,
			d
		);
}