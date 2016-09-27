#pragma once
#include "Triangle.h"

#include <memory>

class Plane
{
public:
	Plane(const glm::vec3 a, const glm::vec3 b, const glm::vec3 c, const glm::vec3 d);
	~Plane() = default;

private:
	std::unique_ptr<Triangle> m_t1;
	std::unique_ptr<Triangle> m_t2;
};