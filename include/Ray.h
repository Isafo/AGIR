#pragma once

#include "glm/glm.hpp"

struct Ray
{
	glm::vec3 m_pos;
	glm::vec3 m_dir;
};

struct RayIntersectionData
{
	//const Material m_material;
	glm::vec3 m_intersectionPoint;
	glm::vec3 m_normal;
	float m_time;
};