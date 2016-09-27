#pragma once
#include <memory>

#include "glm/glm.hpp"

#include "Triangle.h"

class Hexagon
{
public:
	Hexagon();
	Hexagon(bool);
	~Hexagon() = default;

private:
	std::unique_ptr<Triangle> m_t1, m_t2, m_t3, m_t4, m_t5, m_t6;
};