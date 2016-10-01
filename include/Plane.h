#pragma once
#include "Triangle.h"

#include <memory>

// d -- c
// |    |
// a -- b
struct Plane
{
	Plane(const glm::vec3 a, const glm::vec3 b, const glm::vec3 c, const glm::vec3 d, 
		float dR, float dG, float dB, float eR, float eG, float eB)
	{
		m_triangles[0] = std::make_unique<Triangle>
		(
			a,
			b,
			c,
			dR,
			dG,
			dB,
			eR,
			eG,
			eB
		);

		m_triangles[1] = std::make_unique<Triangle>
		(
			a,
			c,
			d,
			dR,
			dG,
			dB,
			eR,
			eG,
			eB
		);
	}
	std::unique_ptr<Triangle> m_triangles[2];
};