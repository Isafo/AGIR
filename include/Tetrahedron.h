#pragma once
#include <memory>

#include "glm/glm.hpp"

#include "Triangle.h"

class Tetrahedron
{
public:
	Tetrahedron(const glm::vec3 p, float dX, float dY, float dZ );
	~Tetrahedron() = default;

private:
	std::unique_ptr<Triangle> m_t1, m_t2, m_t3, m_t4;
};